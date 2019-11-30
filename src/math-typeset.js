const { MathML } = require("mathjax3/mathjax3/input/mathml");
const { SVG } = require("mathjax3/mathjax3/output/svg");
const {
  HTMLDocument
} = require("mathjax3/mathjax3/handlers/html/HTMLDocument");
const { liteAdaptor } = require("mathjax3/mathjax3/adaptors/liteAdaptor");

const toNumberDefaultNaN = x => (x !== "" ? Number(x) : NaN);

const parseTransform = str => {
  const out = { sX: 1, sY: 1, tX: 0, tY: 0 };

  if (!str) return out;

  const re = /(\w+)\s*\(\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*\)/gi;
  let match;
  while ((match = re.exec(str))) {
    switch (match[1]) {
      case "translate":
        out.tX += Number(match[2]);
        out.tY += Number(match[3]);
        break;
      case "scale":
        out.sX *= Number(match[2]);
        out.sY *= Number(match[3] || match[2]);
        break;
      default:
        throw new Error(`Unknown transform ${match[1]}`);
    }
  }

  return out;
};

const normalizeCoordinate = x => Math.floor(x) / 1e3;
const pathRegexp = /([A-Z])\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*,?\s*(-?[\d.]*)\s*/gi;
const transformPathData = ({ sX, sY, tX, tY }, d) => {
  const x = n => normalizeCoordinate(+n * sX + tX);
  const y = n => normalizeCoordinate(-(+n * sY + tY));
  return d.replace(pathRegexp, (fullMatch, command, a, b, c, d, e, f) => {
    switch (command) {
      case "M":
      case "L":
      case "T":
        return `${command}${x(a)} ${y(b)}`;
      case "Q":
        return `Q${x(a)} ${y(b)} ${x(c)} ${y(d)}`;
      case "C":
        return `C${x(a)} ${y(b)} ${x(c)} ${y(d)} ${x(e)} ${y(f)}`;
      case "H":
        return `H${x(a)}`;
      case "V":
        return `V${y(a)}`;
      case "Z":
        return "Z";
      default:
        throw new Error(`Unhandled path command ${command}`);
    }
  });
};

const combineTransforms = (a, b) => ({
  sX: a.sX * b.sX,
  sY: a.sY * b.sY,
  tX: a.tX + b.tX * a.sX,
  tY: a.tY + b.tY * a.sY
});

const pathLayer = (c, transform, pathData) => ({
  [c]: transformPathData(transform, pathData)
});

const mergeLayersInto = (out, b) => {
  for (const key in b) {
    out[key] = (out[key] || "") + b[key];
  }
  return out;
};

const adjustViewBox = input => {
  let [x, y, width, height] = input.split(" ").map(Number);
  const minYScale = 1.2;
  x = x / 1e3;
  y = Math.min(y / 1e3, -0.8 * minYScale);
  width = width / 1e3;
  height = Math.max(height / 1e3, 1 * minYScale);
  const viewBox = `${x} ${y} ${width} ${height}`;
  const ascent = -y;
  return { viewBox, width, height, ascent };
};

const mml = new MathML();
const svg = new SVG();
const adaptor = liteAdaptor();
const html = new HTMLDocument("", adaptor, { InputJax: mml, OutputJax: svg });

const build = (string, display, { em = 16, ex = 8, cwidth = 80 * 16 } = {}) => {
  const math = new html.options.MathItem(string, mml, display);
  math.setMetrics(em, ex, cwidth, 100000, 1);
  math.compile(html);
  math.typeset(html);

  svg.setDocument(html);
  svg.math = math;
  svg.pxPerEm = math.metrics.ex / svg.font.params.x_height;
  math.root.setTeXclass(null);
  svg.nodeMap = new Map();
  const wrapper = svg.factory.wrap(math.root);
  const g = svg.svg("g");
  wrapper.toSVG(g);

  const positionMap = new Map();
  const widths = new Map();
  const addToNodeMap = wrappedNode => {
    if (!wrappedNode.element) return;
    const { id } = wrappedNode.element.attributes;

    const after = id != null ? toNumberDefaultNaN(id.split(":")[1]) : NaN;
    if (!Number.isNaN(after)) {
      const bbox = wrappedNode.getBBox();
      const width = bbox.w;
      widths.set(after, width);
    }

    wrappedNode.childNodes.forEach(addToNodeMap);
  };
  addToNodeMap(wrapper);

  const pathDefs = new Map();
  const addPathDef = element => {
    const { kind, attributes = {}, children } = element;
    const { id } = attributes;
    switch (kind) {
      case "path":
        pathDefs.set(`#${id}`, attributes.d);
        break;
      default:
        throw new Error(`Unknown element: ${element.kind}`);
    }
  };

  const iterateTree = (
    element,
    inputLayer = "default",
    inputTransform = { sX: 1, sY: 1, tX: 0, tY: 0 }
  ) => {
    const { kind, attributes = {}, children } = element;
    const { id, transform: cssTransform } = attributes;
    let layer = (attributes.class || inputLayer).trim();

    const nodeTransform = parseTransform(cssTransform);
    if (kind === "svg" && attributes.x != null && attributes.y != null) {
      // Really tall brackets need this stuff applied
      // The 0.707 is one scaling factor
      nodeTransform.tX = +attributes.x;
      nodeTransform.tY = +attributes.y;
      nodeTransform.sY *= 0.707;
    }

    const transform = combineTransforms(inputTransform, nodeTransform);

    if (id != null) {
      const [current, after] = id.split(":").map(toNumberDefaultNaN);
      let { tX: x, tY: y, sY: scale } = transform;
      x /= 1e3;
      y /= 1e3;

      if (!Number.isNaN(current)) {
        positionMap.set(current, { x, y, scale });
      }
      if (!Number.isNaN(after) && !positionMap.has(after)) {
        const width = widths.get(after);
        if (width == null) throw new Error(`No width for ${after}`);
        positionMap.set(after, { x: x + width * scale, y, scale });
      }
    }

    switch (kind) {
      case "defs":
        children.forEach(addPathDef);
        return "";
      case "use": {
        const d = pathDefs.get(attributes["xlink:href"]);
        return pathLayer(layer, transform, d);
      }
      case "path":
        return pathLayer(layer, transform, attributes.d);
      case "rect": {
        const x = Number(attributes.x);
        const y = Number(attributes.y);
        const width = Number(attributes.width);
        const height = Number(attributes.height);
        return pathLayer(
          layer,
          transform,
          `M${x} ${y}H${x + width}V${y + height}H${x}Z`
        );
      }
      case "svg":
      case "g":
        return children
          .map(child => iterateTree(child, layer, transform))
          .reduce(mergeLayersInto, {
            default: "",
            placeholder: "",
            invalid: ""
          });
      default:
        throw new Error(`Unknown element: ${element.kind}`);
    }
  };

  const layers = iterateTree(math.typesetRoot.children[0]);

  const { viewBox, width, height, ascent } = adjustViewBox(
    math.typesetRoot.children[0].attributes.viewBox
  );

  return { viewBox, width, height, layers, ascent, positionMap };
};

export default build;
