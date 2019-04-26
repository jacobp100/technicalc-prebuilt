type node = ScilineCalculator.ASTTypes.t;

type t = [
  | `Calculate(
      node,
      option(Belt.Map.String.t(ScilineCalculator.Encoding.encoding)),
    )
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
