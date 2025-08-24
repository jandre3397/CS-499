
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Struct to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Global hash table to store courses
unordered_map<string, Course> courseTable;

// Function to display the main menu
void displayMenu() {
    cout << "\n====== ABCU Course Advising System ======" << endl;
    cout << "1. Load Data File" << endl;
    cout << "2. Print Course List (Alphanumeric Order)" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

// Function to load course data into the hash table
void loadCourses() {
    courseTable.clear(); // Clear any existing data

    // Manually inserting courses into the hash table
    courseTable["CSCI100"] = {"CSCI100", "Introduction to Computer Science", {}};
    courseTable["CSCI101"] = {"CSCI101", "Introduction to Programming in C++", {"CSCI100"}};
    courseTable["CSCI200"] = {"CSCI200", "Data Structures", {"CSCI101"}};
    courseTable["MATH201"] = {"MATH201", "Discrete Mathematics", {}};
    courseTable["CSCI300"] = {"CSCI300", "Introduction to Algorithms", {"CSCI200", "MATH201"}};
    courseTable["CSCI301"] = {"CSCI301", "Advanced Programming in C++", {"CSCI101"}};
    courseTable["CSCI350"] = {"CSCI350", "Operating Systems", {"CSCI300"}};
    courseTable["CSCI400"] = {"CSCI400", "Large Software Development", {"CSCI301", "CSCI350"}};

    cout << "Courses successfully loaded into the system." << endl;
}

// Function to print courses in alphanumeric order
void printCourseList() {
    if (courseTable.empty()) {
        cout << "No courses loaded. Please load the data first." << endl;
        return;
    }

    vector<string> courseNumbers;

    // Extract course numbers from the hash table
    for (const auto& pair : courseTable) {
        courseNumbers.push_back(pair.first);
    }

    // Sort course numbers alphabetically
    sort(courseNumbers.begin(), courseNumbers.end());

    // Display sorted courses
    cout << "\n====== Course List ======" << endl;
    for (const string& courseNumber : courseNumbers) {
        cout << courseNumber << ": " << courseTable[courseNumber].courseTitle << endl;
    }
}

// Function to display course information and prerequisites
void displayCourseInfo() {
    if (courseTable.empty()) {
        cout << "No courses loaded. Please load the data first." << endl;
        return;
    }

    string courseNumber;
    cout << "Enter the course number: ";
    cin >> courseNumber;

    if (courseTable.find(courseNumber) != courseTable.end()) {
        Course course = courseTable[courseNumber];
        cout << "\n====== Course Information ======" << endl;
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Title: " << course.courseTitle << endl;

        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites: ";
            for (const string& prereq : course.prerequisites) {
                if (courseTable.find(prereq) != courseTable.end()) {
                    cout << prereq << " (" << courseTable[prereq].courseTitle << ") ";
                } else {
                    cout << prereq << " (Course not found) ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "Course not found. Please check the course number and try again." << endl;
    }
}

// Main function to run the program
int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                loadCourses();
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                displayCourseInfo();
                break;
            case 9:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}
