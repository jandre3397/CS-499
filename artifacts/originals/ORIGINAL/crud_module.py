"""
Original CRUD Module (CS-340 Simulation)

This script demonstrates the basic Create, Read, Update, and Delete (CRUD)
operations for the Animal Shelter database in MongoDB.

Note: This is a reconstructed sample to represent the type of code used in the
original CS-340 project. The actual work was performed in Jupyter Notebook.
"""

import pymongo

# Connect to MongoDB (local or Atlas). In the original project, this
# would connect to the class-provided MongoDB Atlas cluster.
client = pymongo.MongoClient("mongodb://localhost:27017/")

# Database and collection
db = client["animal_shelter"]
collection = db["animals"]

# --- CREATE ---
def add_animal(animal):
    """Insert a new animal into the collection."""
    collection.insert_one(animal)

# --- READ ---
def get_animals():
    """Retrieve all animals from the collection."""
    return list(collection.find())

# --- UPDATE ---
def update_adoption(name, adopted):
    """Update the adoption status of an animal by name."""
    collection.update_one({"name": name}, {"$set": {"adopted": adopted}})

# --- DELETE ---
def delete_animal(name):
    """Delete an animal by name."""
    collection.delete_one({"name": name})

# Example usage (commented out for reference)
if __name__ == "__main__":
    # Create a sample animal
    add_animal({"name": "Buddy", "species": "Dog", "age": 2, "adopted": False})

    # Read animals
    animals = get_animals()
    print("Animals:", animals)

    # Update adoption status
    update_adoption("Buddy", True)

    # Delete animal
    delete_animal("Buddy")

