const fs = require("fs");
const path = require("path");
const {
  boldItalic,
} = require("mathjax-full/js/output/svg/fonts/tex/bold-italic");
const { bold } = require("mathjax-full/js/output/svg/fonts/tex/bold");
const { italic } = require("mathjax-full/js/output/svg/fonts/tex/italic");
const { largeop } = require("mathjax-full/js/output/svg/fonts/tex/largeop");
const { normal } = require("mathjax-full/js/output/svg/fonts/tex/normal");
const { smallop } = require("mathjax-full/js/output/svg/fonts/tex/smallop");
const { texSize3 } = require("mathjax-full/js/output/svg/fonts/tex/tex-size3");
const { texSize4 } = require("mathjax-full/js/output/svg/fonts/tex/tex-size4");

const skewX = (char, deg) => {
  const c = Math.atan((deg * 2 * Math.PI) / 360);
  const data = char.slice();
  const p = data
    .pop()
    .p.replace(
      /(-?\d+)\s+(-?\d+)/g,
      (_, x, y) => `${(+x + +y * c).toFixed(0)} ${y}`
    );
  data.push({ p });
  return data;
};

for (let i = 0x3b1; i <= 0x3c9; i += 1) {
  normal[i] = skewX(italic[i], -15);
  bold[i] = skewX(boldItalic[i], -15);
}

const fontsPath = path.resolve(__dirname, "./fonts-prebuilt");
try {
  fs.mkdirSync(fontsPath);
} catch (e) {}

fs.writeFileSync(
  path.join(fontsPath, "bold-italic.json"),
  JSON.stringify(boldItalic)
);
fs.writeFileSync(path.join(fontsPath, "bold.json"), JSON.stringify(bold));
fs.writeFileSync(path.join(fontsPath, "italic.json"), JSON.stringify(italic));
fs.writeFileSync(path.join(fontsPath, "largeop.json"), JSON.stringify(largeop));
fs.writeFileSync(path.join(fontsPath, "normal.json"), JSON.stringify(normal));
fs.writeFileSync(path.join(fontsPath, "smallop.json"), JSON.stringify(smallop));
fs.writeFileSync(
  path.join(fontsPath, "tex-size3.json"),
  JSON.stringify(texSize3)
);
fs.writeFileSync(
  path.join(fontsPath, "tex-size4.json"),
  JSON.stringify(texSize4)
);
