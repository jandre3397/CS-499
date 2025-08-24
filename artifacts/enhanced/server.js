// Boot log
console.log("[BOOT] Starting server.js");

// Load environment variables
require("dotenv").config();

const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");

const MONGO_URI = process.env.MONGO_URI;
// Force port 9090 for safety if not in .env
const PORT = process.env.PORT || 9090;

if (!MONGO_URI) {
  console.error("[CONFIG] MONGO_URI missing in .env");
  process.exit(1);
}

const app = express();

// Middleware
app.use(cors());
app.use(express.json());

// Request logger
app.use((req, res, next) => {
  console.log(`[REQUEST] ${req.method} ${req.url}`);
  next();
});

// Root test route
app.get("/", (req, res) => {
  console.log("[ROOT] Hit /");
  res.send("Hello from Express root!");
});

// Health check
app.get("/health", (req, res) => {
  console.log("[HEALTH] Hit");
  res.json({ ok: true, message: "Server is running" });
});

// Animal routes
const animalRoutes = require("./routes/animals");
app.use("/api/animals", animalRoutes);

// Error handling for unknown routes
app.use((req, res) => {
  res.status(404).json({ message: "Route not found" });
});

// Handle async errors
process.on("unhandledRejection", (r) =>
  console.error("[UNHANDLED REJECTION]", r)
);
process.on("uncaughtException", (e) =>
  console.error("[UNCAUGHT EXCEPTION]", e)
);

// Start server after DB connects
(async () => {
  try {
    console.log("[DB] Connecting…");
    await mongoose.connect(MONGO_URI);
    console.log("[DB] Connected ✅");

    // Force Express to bind only to IPv4 localhost
    app.listen(PORT, "127.0.0.1", () => {
      console.log(`[SERVER] Listening on http://127.0.0.1:${PORT}`);
    });
  } catch (err) {
    console.error("[DB] Connection error:", err.message);
    process.exit(1);
  }
})();
