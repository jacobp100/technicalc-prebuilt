const path = require("path");
const webpack = require("webpack");

const createConfig = ({
  name,
  entry,
  outputDirectory,
  outputLibraryTarget = "commonjs2",
  target = "web",
}) => ({
  mode: "production",
  entry,
  output: {
    filename: `${name}.js`,
    path: path.resolve(__dirname, outputDirectory),
    libraryTarget: outputLibraryTarget,
    publicPath: "/assets/",
  },
  target,
  externals: ["react", /^react-native-svg/],
  resolve: {
    alias: {
      "bs-platform": path.resolve(__dirname, "node_modules/bs-platform"),
    },
  },
  plugins: [
    new webpack.NormalModuleReplacementPlugin(
      /svg[\\\/]fonts[\\\/]tex[\\\/].*.js$/,
      require.resolve("./mathjax-stubs/fonts")
    ),
    new webpack.NormalModuleReplacementPlugin(
      /util[\\\/]Entities.js$/,
      require.resolve("./mathjax-stubs/entities")
    ),
  ],
});

module.exports = [
  createConfig({
    name: "client",
    outputDirectory: "dist",
    entry: "./src/Client.bs.js",
  }),
  createConfig({
    name: "worker",
    outputDirectory: "dist",
    entry: "./src/Worker.bs.js",
  }),
  createConfig({
    name: "typeset",
    outputDirectory: "dist",
    entry: "./src/typeset/index.js",
    target: "node",
  }),
  createConfig({
    name: "technicalc",
    outputDirectory: "web",
    entry: "./src/WebClient/index.js",
    outputLibraryTarget: "var",
  }),
  createConfig({
    name: "technicalc-worker",
    outputDirectory: "web",
    entry: "./src/WorkerWeb.bs.js",
    outputLibraryTarget: "var",
  }),
];
