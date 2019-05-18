const path = require("path");
const webpack = require("webpack");

const createConfig = ({
  name,
  entry,
  outputLibraryTarget,
  target = "web"
}) => ({
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
  node: {
    Buffer: false
  }
  // plugins: [
  //   new webpack.IgnorePlugin({
  //     resourceRegExp: /\/(double-struck|fraktur(-bold)?|monospace|sans-serif(-bold)?(-italic)?|script(-bold)?|tex-caligraphic(-bold)?|tex-oldstyle(-bold)?|tex-variant).js/
  //   })
  // ]
});

module.exports = [
  createConfig({
    name: "client",
    entry: "./src/client.bs.js",
    outputLibraryTarget: "commonjs2"
  }),
  createConfig({
    name: "worker",
    entry: "./src/worker.bs.js",
    outputLibraryTarget: "var"
  }),
  createConfig({
    name: "math-typeset",
    entry: "./src/math-typeset.js",
    outputLibraryTarget: "commonjs2",
    target: "node"
  })
];
