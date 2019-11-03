type node = ScilineCalculator.AST_Types.t;

type t = [
  | `Calculate(
      node,
      Js.nullable(Js.Dict.t(ScilineCalculator.Encoding.encoding)),
    )
  | `ConvertUnits(
      node,
      ScilineCalculator.Unit_Types.units,
      ScilineCalculator.Unit_Types.units,
    )
  | `SolveRoot(node, node)
  | `Quadratic(node, node, node)
  | `Cubic(node, node, node, node)
  | `Var2(node, node, node, node, node, node)
  | `Var3(
      node,
      node,
      node,
      node,
      node,
      node,
      node,
      node,
      node,
      node,
      node,
      node,
    )
];