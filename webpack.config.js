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
  module: {
    rules: [
      {
        use: "null-loader",
        test: /\/(double-struck|fraktur(-bold)?|monospace|sans-serif(-bold)?(-italic)?|script(-bold)?|tex-caligraphic(-bold)?|tex-oldstyle(-bold)?|tex-variant).js/
      }
    ]
  },
  node: {
    Buffer: false
  }
});

module.exports = [
  createConfig({
    name: "client",
    entry: "./src/Client.bs.js",
    outputLibraryTarget: "commonjs2"
  }),
  createConfig({
    name: "worker-web",
    entry: "./src/WorkerWeb.bs.js",
    outputLibraryTarget: "var"
  }),
  createConfig({
    name: "worker",
    entry: "./src/Worker.bs.js",
    outputLibraryTarget: "commonjs2",
    target: "node"
  }),
  createConfig({
    name: "math-typeset",
    entry: "./src/math-typeset.js",
    outputLibraryTarget: "commonjs2",
    target: "node"
  })
];
