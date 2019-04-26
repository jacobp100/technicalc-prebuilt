open ScilineCalculator;

type result = array(Encoding.encoding);

[@bs.deriving abstract]
type postMessageEvent = {data: Work.t};

[@bs.deriving abstract]
type self = {mutable onmessage: option(postMessageEvent => unit)};

[@bs.val] external self: self = "self";

[@bs.val] external postMessage: result => unit = "postMessage";

{
  let callback = e => {
    let rawResults =
      switch (dataGet(e)) {
      | `Calculate(a) =>
        let res = SciLine.eval(a);
        [|res|];
      | `Quadratic(a, b, c) =>
        let (x0, x1) = SciLine.solveQuadratic(a, b, c);
        [|x0, x1|];
      | `Cubic(a, b, c, d) =>
        let (x0, x1, x2) = SciLine.solveCubic(a, b, c, d);
        [|x0, x1, x2|];
      | `Var2(x0, y0, c0, x1, y1, c1) =>
        let (x, y) = SciLine.solveVar2(x0, y0, c0, x1, y1, c1);
        [|x, y|];
      | `Var3(x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2) =>
        let (x, y, z) =
          SciLine.solveVar3(x0, y0, z0, c0, x1, y1, z1, c1, x2, y2, z2, c2);
        [|x, y, z|];
      };
    let results = rawResults->Belt.Array.map(SciLine.encode);
    postMessage(results);
  };

  onmessageSet(self, Some(callback));
};
