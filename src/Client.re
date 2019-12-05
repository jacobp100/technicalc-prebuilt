let encodeValue = ScilineCalculator.Encoding.encode;
let decodeValue = ScilineCalculator.Encoding.decode;

let calculate = (body, context): Work.t => {
  let context =
    Js.Nullable.bind(context, (. context) =>
      Js.Dict.map(
        (. value) => ScilineCalculator.Encoding.encode(value),
        context,
      )
    );
  `Calculate((body, context));
};
let convertUnits = (body, fromUnits, toUnits): Work.t =>
  `ConvertUnits((body, fromUnits, toUnits));
let solveRoot = (body, initial): Work.t => `SolveRoot((body, initial));
let quadratic = (a, b, c): Work.t => `Quadratic((a, b, c));
let cubic = (a, b, c, d): Work.t => `Cubic((a, b, c, d));
let var2 = (x0, y0, c0, x1, y1, c1): Work.t =>
  `Var2((x0, y0, c0, x1, y1, c1));
let var3 = (x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2): Work.t =>
  `Var3((x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2));

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
  decimalMinMagnitude: int,
  [@bs.optional]
  decimalMaxMagnitude: int,
};

let valueOfString = ScilineCalculator.Types.ofString;

let valueToString = (x, maybeFormat) => {
  open ScilineCalculator.Formatting;
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

  ScilineCalculator.Formatting.toString(~format, ~inline, x);
};

let insertIndex = (ast, key, index) =>
  switch (key) {
  | Keys.One(element) =>
    ScilineEditor.AST_Insert.insertIndex(ast, element, index)
  | Many(elements) =>
    ScilineEditor.AST_Insert.insertArrayIndex(ast, elements, index)
  };
let deleteIndex = ScilineEditor.AST_Delete.deleteIndex;
let toMml = ScilineEditor.Mml.create;
let parse = elements =>
  switch (ScilineEditor.Value.parse(elements)) {
  | `Ok(node) => (None, Some(node))
  | `Error(i) => (Some(i), None)
  };

let keys = Keys.keys;

let customAtom = (~value, ~mml) =>
  `CustomAtomS({ScilineEditor.AST_Types.value: encodeValue(value), mml})
  ->Keys.One;

let unitMml = ScilineEditor.MML_Units.unitMml;
let unitPowerMml = ScilineEditor.MML_Units.unitPowerMml;
let unitsMml = ScilineEditor.MML_Units.unitsMml;

let units = Units.units;

let unitsCompatible = ScilineCalculator.Unit_Dimensions.unitsCompatible;