module SciLine = ScilineCalculator.SciLine;

type t = [
  | `Calculate(SciLine.t)
  | `Quadratic(SciLine.t, SciLine.t, SciLine.t)
  | `Cubic(SciLine.t, SciLine.t, SciLine.t, SciLine.t)
  | `Var2(SciLine.t, SciLine.t, SciLine.t, SciLine.t, SciLine.t, SciLine.t)
  | `Var3(
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
      SciLine.t,
    )
];
