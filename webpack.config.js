const path = require("path");

module.exports = {
  entry: {
    worker: "./src/worker.bs.js",
    client: "./src/client.bs.js"
  },
  output: {
    filename: "[name].js",
    path: __dirname,
    libraryTarget: "commonjs2"
  },
  resolve: {
    alias: {
      "bs-platform": path.resolve(__dirname, "node_modules/bs-platform")
    }
  }
};
