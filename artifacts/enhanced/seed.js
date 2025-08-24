const mongoose = require("mongoose");
require("dotenv").config();
const Animal = require("./models/Animal");
const data = require("./animals.json");

(async () => {
  try {
    await mongoose.connect(process.env.MONGO_URI);
    console.log("[DB] Connected");

    await Animal.deleteMany({});
    await Animal.insertMany(data);

    console.log("[SEED] Inserted", data.length, "records");
    process.exit(0);
  } catch (e) {
    console.error("[SEED ERROR]", e.message);
    process.exit(1);
  }
})();
