type dimensionSection = {
  title: string,
  data: array(row),
}
and row = {
  title: string,
  unit: ScilineCalculator.Unit_Types.unitType,
  next: option(array(row)),
};

let units = [|
  {
    title: "Time",
    data: [|
      {
        title: "Second",
        unit: Second,
        next:
          Some([|
            {title: "Femtosecond", unit: Femtosecond, next: None},
            {title: "Picosecond", unit: Picosecond, next: None},
            {title: "Nanosecond", unit: Nanosecond, next: None},
            {title: "Microsecond", unit: Microsecond, next: None},
            {title: "Millisecond", unit: Millisecond, next: None},
          |]),
      },
      {title: "Minute", unit: Minute, next: None},
      {title: "Hour", unit: Hour, next: None},
      {title: "Day", unit: Day, next: None},
      {title: "Week", unit: Week, next: None},
      {title: "Month", unit: Month, next: None},
      {title: "Year", unit: Year, next: None},
      {title: "Decade", unit: Decade, next: None},
      {title: "Century", unit: Century, next: None},
    |],
  },
  {
    title: "Length",
    data: [|
      {
        title: "Meter",
        unit: Meter,
        next:
          Some([|
            {title: "Meter", unit: Meter, next: None},
            {title: "Femtometer", unit: Femtometer, next: None},
            {title: "Picometer", unit: Picometer, next: None},
            {title: "Nanometer", unit: Nanometer, next: None},
            {title: "Micrometer", unit: Micrometer, next: None},
            {title: "Millimeter", unit: Millimeter, next: None},
            {title: "Centimeter", unit: Centimeter, next: None},
            {title: "Kilometer", unit: Kilometer, next: None},
          |]),
      },
      {title: "Inch", unit: Inch, next: None},
      {title: "Foot", unit: Foot, next: None},
      {title: "Yard", unit: Yard, next: None},
      {title: "Mile", unit: Mile, next: None},
      {title: "Light Year", unit: LightYear, next: None},
      {title: "Parsec", unit: Parsec, next: None},
      {title: "Angstrom", unit: Angstrom, next: None},
    |],
  },
  {
    title: "Mass",
    data: [|
      {
        title: "Gram",
        unit: Gram,
        next:
          Some([|
            {title: "Femtogram", unit: Femtogram, next: None},
            {title: "Picogram", unit: Picogram, next: None},
            {title: "Nanogram", unit: Nanogram, next: None},
            {title: "Microgram", unit: Microgram, next: None},
            {title: "Milligram", unit: Milligram, next: None},
            {title: "Kilogram", unit: Kilogram, next: None},
          |]),
      },
      {title: "Tonne", unit: Tonne, next: None},
      {title: "Ounce", unit: Ounce, next: None},
      {title: "Pound", unit: Pound, next: None},
      {title: "Stone", unit: Stone, next: None},
    |],
  },
  {
    title: "Area",
    data: [|
      {title: "Acre", unit: Acre, next: None},
      {title: "Hectare", unit: Hectare, next: None},
    |],
  },
  {
    title: "Volume",
    data: [|
      {
        title: "Liter",
        unit: Liter,
        next:
          Some([|
            {title: "Milliliter", unit: Milliliter, next: None},
            {title: "Centiliter", unit: Centiliter, next: None},
          |]),
      },
      {title: "Gallon", unit: Gallon, next: None},
      {title: "US Gallon", unit: USGallon, next: None},
      {title: "Quart", unit: Quart, next: None},
      {title: "Cup", unit: Cup, next: None},
      {title: "US Cup", unit: USCup, next: None},
      {title: "Teaspoon", unit: Teaspoon, next: None},
      {title: "Tablespoon", unit: Tablespoon, next: None},
      {title: "Fluid Ounce", unit: FluidOunce, next: None},
    |],
  },
  {
    title: "Energy",
    data: [|
      {title: "Joule", unit: Joule, next: None},
      {title: "Calorie", unit: Calorie, next: None},
      {title: "Electron Volt", unit: ElectronVolt, next: None},
      {title: "BTU", unit: BTU, next: None},
      {title: "Therm", unit: Therm, next: None},
    |],
  },
  {
    title: "Power",
    data: [|
      {
        title: "Watt",
        unit: Watt,
        next:
          Some([|
            {title: "Femtojoule", unit: Femtojoule, next: None},
            {title: "Picojoule", unit: Picojoule, next: None},
            {title: "Nanojoule", unit: Nanojoule, next: None},
            {title: "Microjoule", unit: Microjoule, next: None},
            {title: "Millijoule", unit: Millijoule, next: None},
            {title: "Centijoule", unit: Centijoule, next: None},
            {title: "Kilojoule", unit: Kilojoule, next: None},
            {title: "Megajoule", unit: Megajoule, next: None},
            {title: "Gigajoule", unit: Gigajoule, next: None},
            {title: "Terajoule", unit: Terajoule, next: None},
            {title: "Petajoule", unit: Petajoule, next: None},
          |]),
      },
    |],
  },
  {
    title: "Memory",
    data: [|
      {
        title: "Byte",
        unit: Byte,
        next:
          Some([|
            {title: "Kibibyte", unit: Kibibyte, next: None},
            {title: "Mebibyte", unit: Mebibyte, next: None},
            {title: "Gibibyte", unit: Gibibyte, next: None},
            {title: "Tebibyte", unit: Tebibyte, next: None},
            {title: "Pebibyte", unit: Pebibyte, next: None},
            {title: "Kilobyte", unit: Kilobyte, next: None},
            {title: "Megabyte", unit: Megabyte, next: None},
            {title: "Gigabyte", unit: Gigabyte, next: None},
            {title: "Terabyte", unit: Terabyte, next: None},
            {title: "Petabyte", unit: Petabyte, next: None},
          |]),
      },
      {
        title: "Bit",
        unit: Bit,
        next:
          Some([|
            {title: "Kibibit", unit: Kibibit, next: None},
            {title: "Mebibit", unit: Mebibit, next: None},
            {title: "Gibibit", unit: Gibibit, next: None},
            {title: "Tebibit", unit: Tebibit, next: None},
            {title: "Pebibit", unit: Pebibit, next: None},
            {title: "Kilobit", unit: Kilobit, next: None},
            {title: "Megabit", unit: Megabit, next: None},
            {title: "Gigabit", unit: Gigabit, next: None},
            {title: "Terabit", unit: Terabit, next: None},
            {title: "Petabit", unit: Petabit, next: None},
          |]),
      },
    |],
  },
  {
    title: "Temperature",
    data: [|
      {title: "Kelvin", unit: Kelvin, next: None},
      {title: "Celsius", unit: Celsius, next: None},
      {title: "Fahrenheit", unit: Fahrenheit, next: None},
    |],
  },
|];