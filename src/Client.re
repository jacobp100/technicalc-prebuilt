[@bs.deriving abstract]
type format = {
  [@bs.optional]
  mode: string,
  [@bs.optional]
  style: string,
  [@bs.optional]
  base: int,
  [@bs.optional]
  precision: int,
  [@bs.optional]
  digitGrouping: bool,
  [@bs.optional]
  decimalMinMagnitude: int,
  [@bs.optional]
  decimalMaxMagnitude: int,
};

module Editor = {
  let insertIndex = (ast, key, index) =>
    switch (key) {
    | Keys.One(element) =>
      TechniCalcEditor.AST_Insert.insertIndex(ast, element, index)
    | Many(elements) =>
      TechniCalcEditor.AST_Insert.insertArrayIndex(ast, elements, index)
    };
  let deleteIndex = TechniCalcEditor.AST_Delete.deleteIndex;

  let toMml = (x, maybeFormat, maybeInline) => {
    let digitGrouping =
      Belt.Option.flatMap(maybeFormat, digitGroupingGet)
      ->Belt.Option.getWithDefault(true);
    let inline = Belt.Option.getWithDefault(maybeInline, false);
    TechniCalcEditor.Mml.create(~digitGrouping, ~inline, x);
  };

  let parse = elements =>
    switch (TechniCalcEditor.Value.parse(elements)) {
    | `Ok(node) => (None, Some(node))
    | `Error(i) => (Some(i), None)
    };
};

module Keys = {
  let keys = Keys.keys;

  let customAtom = (~value, ~mml) =>
    `CustomAtomS({
      TechniCalcEditor.AST_Types.value: TechniCalcCalculator.Encoding.encode(value),
      mml,
    })
    ->Keys.One;
};

module Value = {
  let encode = TechniCalcCalculator.Encoding.encode;
  let decode = TechniCalcCalculator.Encoding.decode;

  let isNaN = x => x == `NaN;

  let ofString = TechniCalcCalculator.Types.ofString;

  let toMml = (x, maybeFormat, maybeInline) => {
    open TechniCalcCalculator.Formatting;

    let f = maybeFormat->Belt.Option.getWithDefault(format());

    let inline = Belt.Option.getWithDefault(maybeInline, false);
    let format = {
      mode:
        switch (modeGet(f)) {
        | Some("string") => String /* Only used in data valueUtf */
        | _ => MathML
        },
      style:
        switch (styleGet(f)) {
        | Some("decimal") => Decimal
        | Some("scientific") => Scientific
        | _ => Natural
        },
      base: baseGet(f)->Belt.Option.getWithDefault(default.base),
      precision:
        precisionGet(f)->Belt.Option.getWithDefault(default.precision),
      digitGrouping:
        digitGroupingGet(f)
        ->Belt.Option.getWithDefault(default.digitGrouping),
      decimalMinMagnitude:
        decimalMinMagnitudeGet(f)
        ->Belt.Option.getWithDefault(default.decimalMinMagnitude),
      decimalMaxMagnitude:
        decimalMaxMagnitudeGet(f)
        ->Belt.Option.getWithDefault(default.decimalMaxMagnitude),
    };

    TechniCalcCalculator.Formatting.toString(~format, ~inline, x);
  };
};

module Work = {
  let calculate = (body, context): Work.t => {
    let context =
      Js.Nullable.bind(context, (. context) =>
        Js.Dict.map(
          (. value) => TechniCalcCalculator.Encoding.encode(value),
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
};

module Units = {
  let unitsCompatible = TechniCalcCalculator.Unit_Dimensions.unitsCompatible;

  let unitToMml = TechniCalcEditor.Mml_Units.unitToMml;
  let unitPowerToMml = TechniCalcEditor.Mml_Units.unitPowerToMml;
  let unitPowersToMml = TechniCalcEditor.Mml_Units.unitPowersToMml;

  let units = Units.units;
};