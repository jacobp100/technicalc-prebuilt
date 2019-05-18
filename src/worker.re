type results = array(ScilineCalculator.Encoding.encoding);

[@bs.deriving abstract]
type postMessageData = {
  didError: bool,
  results,
};

[@bs.val] external postMessage: postMessageData => unit = "postMessage";

[@bs.deriving abstract]
type onMessageEvent = {data: Work.t};

[@bs.deriving abstract]
type self = {mutable onmessage: option(onMessageEvent => unit)};

[@bs.val] external self: self = "self";

{
  let getResults = work =>
    ScilineCalculator.AST.(
      switch (work) {
      | `Calculate(a, context) =>
        let context =
          context->Belt.Option.map(x =>
            Belt.Map.String.map(x, ScilineCalculator.Encoding.decode)
          );
        let res = eval(~context?, a);
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
      }
    );

  let callback = e =>
    postMessage(
      try (
        postMessageData(
          ~didError=false,
          ~results=
            dataGet(e)
            ->getResults
            ->Belt.Array.map(ScilineCalculator.Encoding.encode),
        )
      ) {
      | _ => postMessageData(~didError=true, ~results=[||])
      },
    );

  onmessageSet(self, Some(callback));
};
