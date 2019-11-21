const path = require("path");
const webpack = require("webpack");

const createConfig = ({
  name,
  entry,
  outputLibraryTarget = "commonjs2",
  target = "web"
}) => ({
  mode: "production",
  entry,
  output: {
    filename: `${name}.js`,
    path: __dirname,
    libraryTarget: outputLibraryTarget
  },
  target,
  resolve: {
    alias: {
      "bs-platform": path.resolve(__dirname, "node_modules/bs-platform")
    }
  },
  plugins: [
    new webpack.NormalModuleReplacementPlugin(
      /svg[\\\/]fonts[\\\/]tex[\\\/].*.js$/,
      require.resolve("./mathjax-stubs/fonts")
    ),
    new webpack.NormalModuleReplacementPlugin(
      /util[\\\/]Entities.js$/,
      require.resolve("./mathjax-stubs/entities")
    )
  ]
});

module.exports = [
  createConfig({
    name: "client",
    entry: "./src/Client.bs.js"
  }),
  createConfig({
    name: "worker-web",
    entry: "./src/WorkerWeb.bs.js",
    outputLibraryTarget: "var"
  }),
  createConfig({
    name: "worker",
    entry: "./src/Worker.bs.js"
  }),
  createConfig({
    name: "math-typeset",
    entry: "./src/math-typeset.js",
    target: "node"
  })
];
