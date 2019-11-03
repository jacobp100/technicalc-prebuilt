[@bs.deriving abstract]
type unit = {
  value: ScilineCalculator.Unit_Types.unitType,
  name: string,
};

let time = [|
  unit(~value=Second, ~name="Second"),
  unit(~value=Minute, ~name="Minute"),
  unit(~value=Hour, ~name="Hour"),
  unit(~value=Day, ~name="Day"),
  unit(~value=Week, ~name="Week"),
  unit(~value=Month, ~name="Month"),
  unit(~value=Year, ~name="Year"),
  unit(~value=Decade, ~name="Decade"),
  unit(~value=Century, ~name="Century"),
  unit(~value=Femtosecond, ~name="Femtosecond"),
  unit(~value=Picosecond, ~name="Picosecond"),
  unit(~value=Nanosecond, ~name="Nanosecond"),
  unit(~value=Microsecond, ~name="Microsecond"),
  unit(~value=Millisecond, ~name="Millisecond"),
|];

let length = [|
  unit(~value=Meter, ~name="Meter"),
  unit(~value=Inch, ~name="Inch"),
  unit(~value=Foot, ~name="Foot"),
  unit(~value=Yard, ~name="Yard"),
  unit(~value=Mile, ~name="Mile"),
  unit(~value=LightYear, ~name="Light Year"),
  unit(~value=Parsec, ~name="Parsec"),
  unit(~value=Angstrom, ~name="Angstrom"),
  unit(~value=Femtometer, ~name="Femtometer"),
  unit(~value=Picometer, ~name="Picometer"),
  unit(~value=Nanometer, ~name="Nanometer"),
  unit(~value=Micrometer, ~name="Micrometer"),
  unit(~value=Millimeter, ~name="Millimeter"),
  unit(~value=Centimeter, ~name="Centimeter"),
  unit(~value=Kilometer, ~name="Kilometer"),
  unit(~value=Megameter, ~name="Megameter"),
  unit(~value=Gigameter, ~name="Gigameter"),
  unit(~value=Terameter, ~name="Terameter"),
  unit(~value=Petameter, ~name="Petameter"),
|];

let mass = [|
  unit(~value=Gram, ~name="Gram"),
  unit(~value=Tonne, ~name="Tonne"),
  unit(~value=Ounce, ~name="Ounce"),
  unit(~value=Pound, ~name="Pound"),
  unit(~value=Stone, ~name="Stone"),
  unit(~value=Femtogram, ~name="Femtogram"),
  unit(~value=Picogram, ~name="Picogram"),
  unit(~value=Nanogram, ~name="Nanogram"),
  unit(~value=Microgram, ~name="Microgram"),
  unit(~value=Milligram, ~name="Milligram"),
  unit(~value=Kilogram, ~name="Kilogram"),
  unit(~value=Megagram, ~name="Megagram"),
  unit(~value=Gigagram, ~name="Gigagram"),
  unit(~value=Teragram, ~name="Teragram"),
  unit(~value=Petagram, ~name="Petagram"),
|];

let area = [|
  unit(~value=Acre, ~name="Acre"),
  unit(~value=Hectare, ~name="Hectare"),
|];

let volume = [|
  unit(~value=Liter, ~name="Liter"),
  unit(~value=Gallon, ~name="Gallon"),
  unit(~value=USGallon, ~name="US Gallon"),
  unit(~value=Quart, ~name="Quart"),
  unit(~value=Cup, ~name="Cup"),
  unit(~value=USCup, ~name="US Cup"),
  unit(~value=Teaspoon, ~name="Teaspoon"),
  unit(~value=Tablespoon, ~name="Tablespoon"),
  unit(~value=FluidOunce, ~name="Fluid Ounce"),
  unit(~value=Milliliter, ~name="Milliliter"),
  unit(~value=Centiliter, ~name="Centiliter"),
|];

let energy = [|
  unit(~value=Joule, ~name="Joule"),
  unit(~value=Calorie, ~name="Calorie"),
  unit(~value=ElectronVolt, ~name="Electron Volt"),
  unit(~value=BTU, ~name="BTU"),
  unit(~value=Therm, ~name="Therm"),
  unit(~value=Femtojoule, ~name="Femtojoule"),
  unit(~value=Picojoule, ~name="Picojoule"),
  unit(~value=Nanojoule, ~name="Nanojoule"),
  unit(~value=Microjoule, ~name="Microjoule"),
  unit(~value=Millijoule, ~name="Millijoule"),
  unit(~value=Centijoule, ~name="Centijoule"),
  unit(~value=Kilojoule, ~name="Kilojoule"),
  unit(~value=Megajoule, ~name="Megajoule"),
  unit(~value=Gigajoule, ~name="Gigajoule"),
  unit(~value=Terajoule, ~name="Terajoule"),
  unit(~value=Petajoule, ~name="Petajoule"),
|];

let power = [|
  unit(~value=Watt, ~name="Watt"),
  unit(~value=Femtowatt, ~name="Femtowatt"),
  unit(~value=Picowatt, ~name="Picowatt"),
  unit(~value=Nanowatt, ~name="Nanowatt"),
  unit(~value=Microwatt, ~name="Microwatt"),
  unit(~value=Milliwatt, ~name="Milliwatt"),
  unit(~value=Kilowatt, ~name="Kilowatt"),
  unit(~value=Megawatt, ~name="Megawatt"),
  unit(~value=Gigawatt, ~name="Gigawatt"),
  unit(~value=Terawatt, ~name="Terawatt"),
  unit(~value=Petawatt, ~name="Petawatt"),
|];

let memory = [|
  unit(~value=Byte, ~name="Byte"),
  unit(~value=Kibibyte, ~name="Kibibyte"),
  unit(~value=Mebibyte, ~name="Mebibyte"),
  unit(~value=Gibibyte, ~name="Gibibyte"),
  unit(~value=Tebibyte, ~name="Tebibyte"),
  unit(~value=Pebibyte, ~name="Pebibyte"),
  unit(~value=Bit, ~name="Bit"),
  unit(~value=Kibibit, ~name="Kibibit"),
  unit(~value=Mebibit, ~name="Mebibit"),
  unit(~value=Gibibit, ~name="Gibibit"),
  unit(~value=Tebibit, ~name="Tebibit"),
  unit(~value=Pebibit, ~name="Pebibit"),
  unit(~value=Kilobyte, ~name="Kilobyte"),
  unit(~value=Megabyte, ~name="Megabyte"),
  unit(~value=Gigabyte, ~name="Gigabyte"),
  unit(~value=Terabyte, ~name="Terabyte"),
  unit(~value=Petabyte, ~name="Petabyte"),
  unit(~value=Kilobit, ~name="Kilobit"),
  unit(~value=Megabit, ~name="Megabit"),
  unit(~value=Gigabit, ~name="Gigabit"),
  unit(~value=Terabit, ~name="Terabit"),
  unit(~value=Petabit, ~name="Petabit"),
|];

let temperature = [|
  unit(~value=Kelvin, ~name="Kelvin"),
  unit(~value=Celsius, ~name="Celsius"),
  unit(~value=Fahrenheit, ~name="Fahrenheit"),
|];

let units: Js.Dict.t(array(unit)) = Js.Dict.empty();

Js.Dict.set(units, "time", time);
Js.Dict.set(units, "length", length);
Js.Dict.set(units, "mass", mass);
Js.Dict.set(units, "area", area);
Js.Dict.set(units, "volume", volume);
Js.Dict.set(units, "energy", energy);
Js.Dict.set(units, "power", power);
Js.Dict.set(units, "memory", memory);
Js.Dict.set(units, "temperature", temperature);