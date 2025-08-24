import tkinter as tk
from tkinter import filedialog, messagebox
import csv

# Dictionary to hold course data
course_data = {}

# Load courses from a CSV file
def load_courses_from_csv(filepath):
    global course_data
    course_data.clear()

    try:
        with open(filepath, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                course_number = row['courseNumber'].strip()
                course_title = row['courseTitle'].strip()
                prereq_string = row['prerequisites'].strip()
                prerequisites = prereq_string.split('|') if prereq_string else []

                course_data[course_number] = {
                    'title': course_title,
                    'prerequisites': prerequisites
                }

        print("Loaded courses:")
        for key, val in course_data.items():
            print(f"{key}: {val['title']} (Prereqs: {val['prerequisites']})")

        messagebox.showinfo("Success", "Courses loaded successfully!")
        update_dropdown_menu()

    except Exception as e:
        messagebox.showerror("Error", f"Failed to load courses: {e}")

# Populate dropdown menu with courses
def update_dropdown_menu():
    menu = course_dropdown['menu']
    menu.delete(0, 'end')

    for course_number in sorted(course_data.keys()):
        menu.add_command(label=course_number, command=tk._setit(course_var, course_number))

    course_var.set("Select a course")
    print("Dropdown menu updated.")

# Display selected course information
def show_course_info():
    selected_course = course_var.get()
    print(f"Selected course: {selected_course}")
    print(f"All available courses: {list(course_data.keys())}")

    if selected_course not in course_data:
        messagebox.showwarning("No Selection", "Please select a valid course.")
        return

    course_info = course_data[selected_course]
    title = course_info['title']
    prerequisites = course_info['prerequisites']

    # Enable box to edit
    display_box.config(state=tk.NORMAL)
    display_box.delete('1.0', tk.END)

    display_box.insert(tk.END, f"Course Number: {selected_course}\n")
    display_box.insert(tk.END, f"Title: {title}\n")

    if not prerequisites:
        display_box.insert(tk.END, "Prerequisites: None\n")
    else:
        display_box.insert(tk.END, "Prerequisites:\n")
        for prereq in prerequisites:
            prereq_title = course_data.get(prereq, {}).get('title', "(Not Found)")
            display_box.insert(tk.END, f"  {prereq} - {prereq_title}\n")

    # Lock text box again
    display_box.config(state=tk.DISABLED)

# GUI Setup
root = tk.Tk()
root.title("ABCU Course Advising System")
root.geometry("600x500")

# Load CSV
load_button = tk.Button(root, text="Load CSV File", command=lambda: load_courses_from_csv(filedialog.askopenfilename()))
load_button.pack(pady=10)

# Course selector
course_var = tk.StringVar(root)
course_var.set("Select a course")
course_dropdown = tk.OptionMenu(root, course_var, "Select a course")
course_dropdown.pack(pady=5)

# Show info button
show_button = tk.Button(root, text="Show Course Info", command=show_course_info)
show_button.pack(pady=5)

# Frame for text display
frame = tk.LabelFrame(root, text="Course Information", padx=10, pady=10)
frame.pack(pady=15)

# Text box for output
display_box = tk.Text(frame, height=12, width=70, wrap=tk.WORD, bg="#f5f5f5", borderwidth=2, relief="sunken")
display_box.pack()
display_box.config(state=tk.DISABLED)

# Exit button
exit_button = tk.Button(root, text="Exit", command=root.quit)
exit_button.pack(pady=10)

# Debug mode 
load_courses_from_csv("courses.csv")
course_var.set("CSCI300")
show_course_info()

root.mainloop()




