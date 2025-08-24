const express = require("express");
const router = express.Router();
const Animal = require("../models/Animal");

// GET all animals
router.get("/", async (req, res) => {
  try {
    console.log("[ANIMALS] GET request received");
    const animals = await Animal.find();
    res.json(animals);
  } catch (e) {
    res.status(500).json({ message: e.message });
  }
});

// POST create animal
router.post("/", async (req, res) => {
  try {
    const created = await Animal.create(req.body);
    res.status(201).json(created);
  } catch (e) {
    res.status(400).json({ message: e.message });
  }
});

// PUT update adoption status
router.put("/:id", async (req, res) => {
  try {
    const { adopted } = req.body;
    const updated = await Animal.findByIdAndUpdate(
      req.params.id,
      { adopted },
      { new: true }
    );
    if (!updated) return res.status(404).json({ message: "Not found" });
    res.json(updated);
  } catch (e) {
    res.status(500).json({ message: e.message });
  }
});

module.exports = router;
