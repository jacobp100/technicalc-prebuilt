let encodeJsContext = jsContext =>
  Js.Dict.entries(jsContext)
  ->Belt.Array.reduce(Belt.Map.String.empty, (accum, (key, value)) =>
      Belt.Map.String.set(
        accum,
        key,
        ScilineCalculator.Encoding.encode(value),
      )
    );

/* Save importing AST for size reasons */
let ofEncoded =
    (value: ScilineCalculator.Types.value): ScilineCalculator.AST.t =>
  `OfEncoded(ScilineCalculator.Encoding.encode(value));
