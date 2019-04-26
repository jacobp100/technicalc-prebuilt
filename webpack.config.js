const path = require("path");

const createConfig = ({ name, entry, outputLibraryTarget }) => ({
  entry,
  output: {
    filename: `${name}.js`,
    path: __dirname,
    libraryTarget: outputLibraryTarget
  },
  resolve: {
    alias: {
      "bs-platform": path.resolve(__dirname, "node_modules/bs-platform")
    }
  },
  node: {
    Buffer: false
  }
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
  })
];
