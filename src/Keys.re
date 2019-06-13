open ScilineEditor.AST_Types;
open Flags;

type value =
  | One(t)
  | Many(array(t));

[@bs.deriving abstract]
type key = {
  value,
  flags: int,
};

let keys: Js.Dict.t(key) = Js.Dict.empty();

keys->Js.Dict.set("0", key(~value=One(`DigitS("0")), ~flags=none));
keys->Js.Dict.set("1", key(~value=One(`DigitS("1")), ~flags=none));
keys->Js.Dict.set("2", key(~value=One(`DigitS("2")), ~flags=none));
keys->Js.Dict.set("3", key(~value=One(`DigitS("3")), ~flags=none));
keys->Js.Dict.set("4", key(~value=One(`DigitS("4")), ~flags=none));
keys->Js.Dict.set("5", key(~value=One(`DigitS("5")), ~flags=none));
keys->Js.Dict.set("6", key(~value=One(`DigitS("6")), ~flags=none));
keys->Js.Dict.set("7", key(~value=One(`DigitS("7")), ~flags=none));
keys->Js.Dict.set("8", key(~value=One(`DigitS("8")), ~flags=none));
keys->Js.Dict.set("9", key(~value=One(`DigitS("9")), ~flags=none));
keys->Js.Dict.set("A", key(~value=One(`DigitS("A")), ~flags=premium));
keys->Js.Dict.set("B", key(~value=One(`DigitS("B")), ~flags=premium));
keys->Js.Dict.set("C", key(~value=One(`DigitS("C")), ~flags=premium));
keys->Js.Dict.set("D", key(~value=One(`DigitS("D")), ~flags=premium));
keys->Js.Dict.set("E", key(~value=One(`DigitS("E")), ~flags=premium));
keys->Js.Dict.set("F", key(~value=One(`DigitS("F")), ~flags=premium));
keys->Js.Dict.set(".", key(~value=One(`DecimalSeparator), ~flags=none));
keys->Js.Dict.set("+", key(~value=One(`Add), ~flags=none));
keys->Js.Dict.set("-", key(~value=One(`Sub), ~flags=none));
keys->Js.Dict.set("*", key(~value=One(`Mul), ~flags=none));
keys->Js.Dict.set("/", key(~value=One(`Div), ~flags=none));
keys->Js.Dict.set("%", key(~value=One(`Percent), ~flags=premium));
keys->Js.Dict.set("_", key(~value=One(`Frac2S), ~flags=none));
keys->Js.Dict.set("^", key(~value=One(`Superscript1), ~flags=none));
keys->Js.Dict.set("!", key(~value=One(`Factorial), ~flags=premium));
keys->Js.Dict.set("(", key(~value=One(`OpenBracket), ~flags=none));
keys->Js.Dict.set(")", key(~value=One(`CloseBracketS), ~flags=none));
keys->Js.Dict.set("base2", key(~value=One(`Base(Bin)), ~flags=premium));
keys->Js.Dict.set("base8", key(~value=One(`Base(Oct)), ~flags=premium));
keys->Js.Dict.set("base16", key(~value=One(`Base(Hex)), ~flags=premium));
keys->Js.Dict.set("sqrt", key(~value=One(`Sqrt1S), ~flags=none));
keys->Js.Dict.set(
  "cuberoot",
  key(~value=Many([|`NRoot2S, `DigitS("3"), `Arg, `Arg|]), ~flags=premium),
);
keys->Js.Dict.set("nroot", key(~value=One(`NRoot2S), ~flags=premium));
keys->Js.Dict.set("abs", key(~value=One(`Abs1S), ~flags=none));
keys->Js.Dict.set("floor", key(~value=One(`Floor1S), ~flags=none));
keys->Js.Dict.set("ceil", key(~value=One(`Ceil1S), ~flags=none));
keys->Js.Dict.set("round", key(~value=One(`Round1S), ~flags=none));
keys->Js.Dict.set("log", key(~value=One(`Function(Log)), ~flags=premium));
keys->Js.Dict.set(
  "log2",
  key(~value=Many([|`NLog1, `DigitS("2")|]), ~flags=premium),
);
keys->Js.Dict.set(
  "log10",
  key(~value=Many([|`NLog1, `DigitS("1"), `DigitS("0")|]), ~flags=premium),
);
keys->Js.Dict.set("logn", key(~value=One(`NLog1), ~flags=premium));
keys->Js.Dict.set("sin", key(~value=One(`Function(Sin)), ~flags=premium));
keys->Js.Dict.set(
  "asin",
  key(~value=One(`Function(Asin)), ~flags=premium),
);
keys->Js.Dict.set(
  "sinh",
  key(~value=One(`Function(Sinh)), ~flags=premium),
);
keys->Js.Dict.set(
  "asinh",
  key(~value=One(`Function(Asinh)), ~flags=premium),
);
keys->Js.Dict.set("cos", key(~value=One(`Function(Cos)), ~flags=premium));
keys->Js.Dict.set(
  "acos",
  key(~value=One(`Function(Acos)), ~flags=premium),
);
keys->Js.Dict.set(
  "cosh",
  key(~value=One(`Function(Cosh)), ~flags=premium),
);
keys->Js.Dict.set(
  "acosh",
  key(~value=One(`Function(Acosh)), ~flags=premium),
);
keys->Js.Dict.set("tan", key(~value=One(`Function(Tan)), ~flags=premium));
keys->Js.Dict.set(
  "atan",
  key(~value=One(`Function(Atan)), ~flags=premium),
);
keys->Js.Dict.set(
  "tanh",
  key(~value=One(`Function(Tanh)), ~flags=premium),
);
keys->Js.Dict.set(
  "atanh",
  key(~value=One(`Function(Atanh)), ~flags=premium),
);
keys->Js.Dict.set("i", key(~value=One(`ImaginaryUnitS), ~flags=premium));
keys->Js.Dict.set("x", key(~value=One(`VariableS("x")), ~flags=premium));
keys->Js.Dict.set("pi", key(~value=One(`ConstPiS), ~flags=none));
keys->Js.Dict.set("e", key(~value=One(`ConstES), ~flags=none));
keys->Js.Dict.set("ans", key(~value=One(`VariableS("Ans")), ~flags=none));
keys->Js.Dict.set("re", key(~value=One(`Function(Re)), ~flags=premium));
keys->Js.Dict.set("im", key(~value=One(`Function(Im)), ~flags=premium));
keys->Js.Dict.set("conj", key(~value=One(`Conj), ~flags=premium));
keys->Js.Dict.set(
  "gamma",
  key(~value=One(`Function(Gamma)), ~flags=premium),
);
keys->Js.Dict.set("rand", key(~value=One(`RandS), ~flags=premium));
keys->Js.Dict.set("randint", key(~value=One(`RandInt2S), ~flags=premium));
keys->Js.Dict.set("npr", key(~value=One(`NPR2), ~flags=premium));
keys->Js.Dict.set("ncr", key(~value=One(`NCR2), ~flags=premium));
keys->Js.Dict.set(
  "differential",
  key(~value=One(`Differential2), ~flags=premium),
);
keys->Js.Dict.set("integral", key(~value=One(`Integral3), ~flags=premium));
keys->Js.Dict.set("sum", key(~value=One(`Sum2), ~flags=premium));
keys->Js.Dict.set("product", key(~value=One(`Product2), ~flags=premium));
keys->Js.Dict.set("dot", key(~value=One(`Dot), ~flags=none));
keys->Js.Dict.set("magnitude", key(~value=One(`Magnitude1), ~flags=none));
keys->Js.Dict.set("degree", key(~value=One(`Degree), ~flags=premium));
keys->Js.Dict.set("arcminute", key(~value=One(`ArcMinute), ~flags=premium));
keys->Js.Dict.set("arcsecond", key(~value=One(`ArcSecond), ~flags=premium));
keys->Js.Dict.set(
  "vec2",
  key(~value=One(`TableNS({numRows: 2, numColumns: 1})), ~flags=premium),
);
keys->Js.Dict.set(
  "vec3",
  key(~value=One(`TableNS({numRows: 3, numColumns: 1})), ~flags=premium),
);
keys->Js.Dict.set(
  "mat2",
  key(~value=One(`TableNS({numRows: 2, numColumns: 2})), ~flags=premium),
);
keys->Js.Dict.set(
  "mat3",
  key(~value=One(`TableNS({numRows: 3, numColumns: 3})), ~flags=premium),
);
