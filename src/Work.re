type node = TechniCalcCalculator.AST_Types.t;

type t =
  | Calculate(
      node,
      Js.nullable(Js.Dict.t(TechniCalcCalculator.Value_Encoding.encoding)),
    )
  | ConvertUnits(
      node,
      array(TechniCalcCalculator.Unit_Types.unitPower),
      array(TechniCalcCalculator.Unit_Types.unitPower),
    )
  | SolveRoot(node, node)
  | Quadratic(node, node, node)
  | Cubic(node, node, node, node)
  | Var2(node, node, node, node, node, node)
  | Var3(
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
    );
