const Module = require("../build/lib");

async function main() {
  const instance = await Module();
  const app = new instance.Application();

  console.log(app.clipboard().get("entry")._size);
}

main();
