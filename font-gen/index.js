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
const { skewX } = require("./font-util");
const buildFont = require("./build-font");

for (let i = 0x3b1; i <= 0x3c9; i += 1) {
  normal[i] = skewX(italic[i], -15);
  bold[i] = skewX(boldItalic[i], -15);
}

const fontsJsonPath = path.resolve(__dirname, "../fonts-json");
try {
  fs.mkdirSync(fontsJsonPath);
} catch (e) {}

const fontsAssetsPath = path.resolve(__dirname, "../fonts-assets");
try {
  fs.mkdirSync(fontsAssetsPath);
} catch (e) {}

const jsonFont = (font, { preserveSvgChars }) => {
  // for (key in font) {
  //   const keepChar = Array.isArray(preserveSvgChars)
  //     ? preserveSvgChars.includes(+key)
  //     : preserveSvgChars != null
  //     ? preserveSvgChars
  //     : false;

  //   const data = font[key][3];
  //   if (!keepChar && data != null) {
  //     delete data.p;
  //     delete data.sk;
  //   }
  // }

  return JSON.stringify(font);
};

const writeFont = (font, name, options = {}) => {
  if (options.preserveSvgChars !== true) {
    fs.writeFileSync(
      path.join(fontsAssetsPath, `mathjax-${name}.otf`),
      buildFont({ familyName: `mathjax-${name}`, styleName: "Regular" }, font)
    );
  }

  fs.writeFileSync(
    path.join(fontsJsonPath, `${name}.json`),
    jsonFont(font, options)
  );
};

writeFont(boldItalic, "bold-italic", { preserveSvgChars: true });
writeFont(bold, "bold", { preserveSvgChars: true });
writeFont(italic, "italic", { preserveSvgChars: true });
writeFont(normal, "normal", { preserveSvgChars: true /*[0x25a1]*/ });

writeFont(largeop, "largeop", { preserveSvgChars: true });
writeFont(smallop, "smallop", { preserveSvgChars: true });
writeFont(texSize3, "size3", { preserveSvgChars: true });
writeFont(texSize4, "size4", { preserveSvgChars: true });
