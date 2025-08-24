const mongoose = require("mongoose");

const AnimalSchema = new mongoose.Schema({
  name: { type: String, required: true },
  species: { type: String, required: true },
  age: { type: Number, required: true },
  adopted: { type: Boolean, default: false }
}, { timestamps: true });

module.exports = mongoose.model("Animal", AnimalSchema);
