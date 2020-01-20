type postMessageData = {
  results: array(ScilineCalculator.Encoding.encoding),
  didError: bool,
};

type onMessageEvent = {data: Work.t};

type self = {
  mutable onmessage: option(onMessageEvent => unit),
  postMessage: (. postMessageData) => unit,
};

let make = self => {
  open ScilineCalculator.AST;

  let getResults = work =>
    switch (work) {
    | `Calculate(a, context) =>
      let context =
        switch (Js.Nullable.toOption(context)) {
        | Some(context) =>
          context
          ->Js.Dict.entries
          ->Belt.Array.reduce(Belt.Map.String.empty, (accum, (key, value)) =>
              Belt.Map.String.set(
                accum,
                key,
                ScilineCalculator.Encoding.decode(value),
              )
            )
        | None => Belt.Map.String.empty
        };
      let res = eval(~context, a);
      [|res|];
    | `ConvertUnits(a, fromUnits, toUnits) =>
      let res =
        eval(~context=Belt.Map.String.empty, a)
        ->ScilineCalculator.Units.convert(~fromUnits, ~toUnits);
      [|res|];
    | `SolveRoot(body, initial) =>
      let res = solveRoot(body, initial);
      [|res|];
    | `Quadratic(a, b, c) =>
      let (x0, x1) = solveQuadratic(a, b, c);
      [|x0, x1|];
    | `Cubic(a, b, c, d) =>
      let (x0, x1, x2) = solveCubic(a, b, c, d);
      [|x0, x1, x2|];
    | `Var2(x0, y0, c0, x1, y1, c1) =>
      let (x, y) = solveVar2(x0, y0, c0, x1, y1, c1);
      [|x, y|];
    | `Var3(x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2) =>
      let (x, y, z) =
        solveVar3(x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2);
      [|x, y, z|];
    };

  let callback = e => {
    let arg =
      try({
        results:
          e.data
          ->getResults
          ->Belt.Array.map(ScilineCalculator.Encoding.encode),
        didError: false,
      }) {
      | _ => {results: [||], didError: true}
      };
    self.postMessage(. arg);
  };

  self.onmessage = Some(callback);
};