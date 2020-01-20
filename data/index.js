// Android font: GFS Didot
const { TeX } = require("mathjax3/mathjax3/input/tex.js");
const { SVG } = require("mathjax3/mathjax3/output/svg.js");
const {
  HTMLDocument
} = require("mathjax3/mathjax3/handlers/html/HTMLDocument.js");
const { liteAdaptor } = require("mathjax3/mathjax3/adaptors/liteAdaptor.js");

const { AllPackages } = require("mathjax3/mathjax3/input/tex/AllPackages.js");

const MmlVisitor = require("mathjax3/mathjax3/core/MmlTree/SerializedMmlVisitor.js")
  .SerializedMmlVisitor;

const { valueOfString, valueToString } = require("../dist/client");
const { default: mathTypeset } = require("../dist/math-typeset");
const titles = require("./titles");

const Typeset = (string, display) => {
  const tex = new TeX({ packages: AllPackages.sort() });
  const svg = new SVG();

  const html = new HTMLDocument("", liteAdaptor(), {
    InputJax: tex,
    OutputJax: svg
  });

  const visitor = new MmlVisitor();
  const toMathML = node => visitor.visitTree(node, html);

  const math = new html.options.MathItem(string, tex, display);
  math.setMetrics(16, 16, 80, 100000, 1);
  math.compile(html);
  math.typeset(html);

  const out = toMathML(math.root)
    .replace(/>[\s\n]*</gm, "><")
    .replace(/\s?class="[^"]*"/g, "");
  return out;
};

const unnestDocument = d => d.replace(/<\/?math[^>]*>/g, "");

const superscriptReplacements = {
  "-": "⁻",
  0: "⁰",
  1: "¹",
  2: "²",
  3: "³",
  4: "⁴",
  5: "⁵",
  6: "⁶",
  7: "⁷",
  8: "⁸",
  9: "⁹"
};

const subscriptReplacements = {
  0: "₀",
  1: "₁",
  2: "₂",
  3: "₃",
  4: "₄",
  5: "₅",
  6: "₆",
  7: "₇",
  8: "₈",
  9: "₉",
  h: "h"
};

const data = require("./data");
const nist = require("fs")
  .readFileSync(__dirname + "/data.csv", "utf8")
  .split("\n")
  .filter(l => l)
  .map(l =>
    l
      .match(/^("[^"]+"|[^,]+),([^,]+)\s*,([^,]+)$/)
      .slice(1)
      .map(p =>
        p
          .replace(/^"/, "")
          .replace(/"$/, "")
          .trim()
      )
  )
  .map(([title, value, units]) => {
    if (value == null) throw new Error("Oh");

    value = value.replace(/\s/g, "").replace("...", "");
    let valueMml = valueToString(valueOfString(value), {
      mode: "mathml-inline",
      style: "decimal"
    });
    if (units) {
      const unitsMml = units
        .split(" ")
        .map(str => {
          const [unitBase, power] = str.split("^");
          const [unit, base] = unitBase.split("_");
          const unitWithHtml = unit.replace("ohm", "&#x2126;");
          const miUnit = `<mi mathvariant="normal">${unitWithHtml}</mi>`;
          const miBase =
            base == null
              ? ""
              : isNaN(base)
              ? `<mi>${base}</mi>`
              : `<mn>${base}</mn>`;
          const unitMml = miBase ? `<msub>${miUnit}${miBase}</msub>` : miUnit;
          return power ? `<msup>${unitMml}<mn>${power}</mn></msup>` : unitMml;
        })
        .join("<mo>&#183;</mo>");
      valueMml = valueMml.replace(
        "</math>",
        `<mspace width="8px">${unitsMml}</math>`
      );
    }

    if (valueMml.includes("NaN")) {
      throw new Error(`Invalid MML for ${title}`);
    }

    let valueUtf = valueToString(valueOfString(value), {
      mode: "string",
      style: "decimal"
    }).replace(/e(.+)/, "×10^$1");

    if (units) {
      valueUtf += ` ${units.replace("ohm", "Ω")}`;
    }

    valueUtf = valueUtf.replace(
      /([_^])([-\w]+)/g,
      (_, subSuper, subSuperArg) => {
        const map =
          subSuper === "^" ? superscriptReplacements : subscriptReplacements;
        return Array.from(subSuperArg, x => {
          const val = map[x];
          if (val == null) throw new Error(`No mapping for ${x} (${valueUtf})`);
          return val;
        }).join("");
      }
    );

    if (valueUtf.includes("^") || valueUtf.includes("_")) {
      throw new Error(`Invalud valueUtf (${valueUtf})`);
    }

    return { title, value, valueMml, valueUtf };
  });

const formats = [
  ["\\AA", "\\unicode{x212B}"],
  ["\\hbar", "\\unicode{x127}"],
  ["\\lbar", "\\unicode{x19b}"],
  ["\\lambdabar", "\\unicode{x19b}"],
  ["\\unicode{x212B}", "A"],
  ["\\unicode{x19b}", "\\lambda"]
];

let out = data.map(({ title, name: n, tex }, i) => {
  let formattedTex = tex;
  formattedTex = formattedTex.replace(
    /(?:\$([^$]*)\$|([^$,]+))/g,
    (full, tex, raw) => {
      if (tex) return tex;
      if (raw) return `{\\rm ${raw}}`;
      throw new Error("Oh");
    }
  );
  // Take first if comma group (like c, c_0) UNLESS the comma is in a _{} or ^ group
  formattedTex = formattedTex
    .match(/^((?:[^{,_^]|[_^][^\{]|[_^]?\{(?:[^}]|\{[^}]*\})*\})*).*$/)[1]
    .trim();
  formattedTex = formats.reduce(
    (out, [a, b]) => out.replace(a, b),
    formattedTex
  );

  const normalizeTitle = a =>
    a
      .replace(/\s/g, "")
      .toLowerCase()
      .replace("moment", "mom.")
      .replace("magnetic", "mag.")
      .trim();

  const { value, valueUtf } = nist.find(
    nist => normalizeTitle(title) === normalizeTitle(nist.title)
  );
  let symbolMml;
  let symbolMath;

  try {
    symbolMml = unnestDocument(Typeset(formattedTex, true));

    if (symbolMml.includes("merror")) {
      throw new Error(`Invalid tex ${tex}`);
    }

    symbolMath = {
      ...mathTypeset(`<math display="inline">${symbolMml}</math>`),
      positionMap: null
    };
  } catch (e) {
    console.log("FAILED");
    console.log(e);
    console.log(title);
    console.log(n);
    console.log(formattedTex);
    throw e;
  }

  title = title[0].toUpperCase() + title.slice(1);

  return { title, value, symbolMml, symbolMath, valueUtf };
});

out = out
  .filter(t => !/in [KMG]?eV/.test(t.title))
  .filter(t => {
    const filter = titles.get(t.title);
    if (filter == null) {
      throw new Error(`Missing filter for ${t.title}`);
    }
    return filter;
  });

const test = new Map();
out.forEach(({ title, symbolMml }) => {
  const existing = test.get(symbolMml) || [];
  existing.push(title);
  test.set(symbolMml, existing);
});

const conflicts = Array.from(test.values()).filter(values => values.length > 0);

require("fs").writeFileSync(
  require("path").resolve(__dirname, "../dist/constants.json"),
  JSON.stringify(out)
);

export {};
