open ScilineCalculator.ASTTypes;

let encodeValue = ScilineCalculator.Encoding.encode;
let decodeValue = ScilineCalculator.Encoding.decode;

let calculate = (value, jsContext): Work.t => {
  let context =
    jsContext
    ->Belt.Option.map(jsContext =>
        Js.Dict.entries(jsContext)
        ->Belt.Array.reduce(Belt.Map.String.empty, (accum, (key, value)) =>
            Belt.Map.String.set(
              accum,
              key,
              ScilineCalculator.Encoding.encode(value),
            )
          )
      );
  `Calculate((ofValue(value), context));
};
let quadratic = (a, b, c): Work.t =>
  `Quadratic((ofValue(a), ofValue(b), ofValue(c)));
let cubic = (a, b, c, d): Work.t =>
  `Cubic((ofValue(a), ofValue(b), ofValue(c), ofValue(d)));
let var2 = (x0, y0, c0, x1, y1, c1): Work.t =>
  `Var2((
    ofValue(x0),
    ofValue(y0),
    ofValue(c0),
    ofValue(x1),
    ofValue(y1),
    ofValue(c1),
  ));
let var3 = (x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2): Work.t =>
  `Var3((
    ofValue(x0),
    ofValue(y0),
    ofValue(z0),
    ofValue(c0),
    ofValue(x1),
    ofValue(y1),
    ofValue(z1),
    ofValue(c1),
    ofValue(x2),
    ofValue(y2),
    ofValue(z2),
    ofValue(c2),
  ));

[@bs.deriving abstract]
type format = {
  [@bs.optional]
  mode: string,
  [@bs.optional]
  style: string,
  [@bs.optional]
  precision: int,
  [@bs.optional]
  base: int,
  [@bs.optional]
  decimalMinMagnitude: float,
  [@bs.optional]
  decimalMaxMagnitude: float,
};

let valueOfString = ScilineCalculator.Types.ofString;

let valueToString = (x, maybeFormat) => {
  open ScilineCalculator.OutputFormat;
  let f = maybeFormat->Belt.Option.getWithDefault(format());

  let (mode, inline) =
    switch (modeGet(f)) {
    | Some("tex") => (Tex, false)
    | Some("mathml") => (MathML, false)
    | Some("mathml-inline") => (MathML, true)
    | _ => (String, false)
    };

  let format = {
    mode,
    style:
      switch (styleGet(f)) {
      | Some("decimal") => Decimal
      | Some("scientific") => Scientific
      | _ => Natural
      },
    precision:
      precisionGet(f)->Belt.Option.getWithDefault(default.precision),
    base: baseGet(f)->Belt.Option.getWithDefault(default.base),
    decimalMinMagnitude:
      decimalMinMagnitudeGet(f)
      ->Belt.Option.getWithDefault(default.decimalMinMagnitude),
    decimalMaxMagnitude:
      decimalMaxMagnitudeGet(f)
      ->Belt.Option.getWithDefault(default.decimalMaxMagnitude),
  };

  ScilineCalculator.ToString.toString(~format, ~inline, x);
};

let insertIndex = ScilineEditor.Mutation.insertIndex;
let deleteIndex = ScilineEditor.Mutation.deleteIndex;
let length = ScilineEditor.TreeUtil.length;
let toMml = ScilineEditor.Mml.create;
let parse = elements =>
  switch (ScilineEditor.AstBuilder.parse(elements)) {
  | `Ok(node) => (None, Some(node))
  | `Error(i) => (Some(i), None)
  };

let keys = Keys.keys;
let flags = Flags.flags;

let customAtom = (~value, ~mml) =>
  ScilineEditor.Types.(
    `CustomAtom({customAtomValue: encodeValue(value), mml, superscript: []})
  );
let customAtomEncoded = (~value as customAtomValue, ~mml) =>
  ScilineEditor.Types.(`CustomAtom({customAtomValue, mml, superscript: []}));
