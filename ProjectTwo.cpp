
//----------------------------------------------------------------------------
// Name        : ProjectTwo.cpp
// Author      : Timothy Ness
// Version     : 1.0
// Description : ABCU Advising Assistance Program
// Loads course data from CSV, stores in BST (map).
// Menu options: 1) Load file, 2) Print course list (alphanumeric order). 3) Print course detail, 9) Exit.
// Prints sorted course list, prints course details.
//----------------------------------------------------------------------------

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------
// Data Model
//----------------------------------------------------------------------------

/**
 * Course object: holds single course's number, title, and prereqs.
 * - courseNumber: ex "CSCI200"
 * - title: ex "Data Structures"
 * - prereqs: list of prereqs course numbers ex ["CSCI101", "MATH201"]
 */
struct Course {
    string courseNumber;
    string title;
    vector<string> prereqs;
};

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

/**
 * Trim whitespace from both ends of string.
 */
static inline string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
        start++;
    }

    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
        end--;
    }

    return s.substr(start, end - start);
}

/**
 * Convert to uppercase to avoid case sensitivity issues.
 */
static inline string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return s;
}

/**
 * Split a line by comma into tokens; tokens kept empty if present.
 */
static vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    string token;

    // Basic CSV splitting; no quoted commas expected.
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

/**
 * Print single course in required format:
 * - Shows course number, title.
 * - Shows prereqs as numbers and titles if known.
 */
static void printCourseDetails(const Course& c, const map<string, Course>& bst) {
    cout << '\n';
    cout << "Course Information:" << endl;
    cout << "-------------------" << endl;
    cout << '\n';
    cout << c.courseNumber << ", " << c.title << endl;

    if (c.prereqs.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";
    for (size_t i = 0; i < c.prereqs.size(); i++) {
        const string& pre = c.prereqs[i];
        cout << pre;

        // If prereq exists in the BST/map, print title.
        auto it = bst.find(pre);
        if (it != bst.end()) {
            cout << " (" << it->second.title << ")";
        }

        if (i + 1 < c.prereqs.size()) {
            cout << ", ";
        }
    }
    cout << endl;
}

//----------------------------------------------------------------------------
// Core Program Logic (BST-based using std::map)
//----------------------------------------------------------------------------

/**
 * Load courses from CSV file into BST-like structure (std::map).
 *
 * Validation rules required:
 * 1) Each line must have at least two parameters: courseNumber and title.
 * 2) Any prerequisite listed must exist as a course in the file.
 *
 * Additional validations to aligg with 'industry best practices':
 * 1) Duplicate course numbers are rejected.
 * 2) Empty tokens are ignored for prereqs.
 */
static bool loadCoursesFromFile(const string& fileName, map<string, Course>& bst) {
    bst.clear();

    ifstream fin(fileName);
    if (!fin.is_open()) {
        cout << '\n';
        cout << "Error: could not open file '" << fileName << "'." << endl;
        cout << "Tip: Place the CSV in the program's working directory, or enter a full file path.\n";
        return false;
    }

    // Track course numbers during reading for prereq existence validation.
    set<string> courseNumbers;

    // Temporarily store prereqs to validate after reading entire file.
    // key = courseNumber, value = prereq list
    map<string, vector<string>> pendingPrereqs;

    string line;
    int lineNumber = 0;

    while (getline(fin, line)) {
        lineNumber++;

        // Skip truly blank lines.
        if (trim(line).empty()) {
            continue;
        }

        vector<string> tokens = splitCSVLine(line);

        // Validation #1: Must have at least courseNumber and title.
        if (tokens.size() < 2) {
            cout << "File format error on line " << lineNumber
                << ": missing course number and/or title." << endl;
            fin.close();
            bst.clear();
            return false;
        }

        string courseNum = toUpper(tokens[0]);
        string title = tokens[1];

        if (courseNum.empty() || title.empty()) {
            cout << "File format error on line " << lineNumber
                << ": course number or title is blank." << endl;
            fin.close();
            bst.clear();
            return false;
        }

        // Check duplicates.
        if (courseNumbers.find(courseNum) != courseNumbers.end()) {
            cout << "File format error on line " << lineNumber
                << ": duplicate course number '" << courseNum << "'." << endl;
            fin.close();
            bst.clear();
            return false;
        }

        Course c;
        c.courseNumber = courseNum;
        c.title = title;

        // Read prereqs from tokens[2..].
        for (size_t i = 2; i < tokens.size(); i++) {
            string prereq = toUpper(tokens[i]);
            if (!prereq.empty()) {
                c.prereqs.push_back(prereq);
            }
        }

        // Insert into BST/map.
        bst[c.courseNumber] = c;
        courseNumbers.insert(c.courseNumber);
        pendingPrereqs[c.courseNumber] = c.prereqs;
    }

    fin.close();

    // Validation #2: every prereq must exist as course in file.
    for (const auto& pair : pendingPrereqs) {
        const string& courseNum = pair.first;
        const vector<string>& prereqs = pair.second;

        for (const string& prereq : prereqs) {
            if (courseNumbers.find(prereq) == courseNumbers.end()) {
                cout << "File format error: prerequisite '" << prereq
                    << "' for course '" << courseNum
                    << "' does not exist in the file." << endl;
                bst.clear();
                return false;
            }
        }
    }

    return true;
}

/**
 * Print alphanumeric list of all courses.
 * Using std::map means keys are always in sorted order.
 */
static void printCourseList(const map<string, Course>& bst) {
    if (bst.empty()) {
        cout << "No course data loaded. Please load a file first (Option 1)." << endl;
        return;
    }
    cout << '\n';
    cout << "Course List:" << endl;
    cout << "------------" << endl;
    cout << '\n';
    for (const auto& pair : bst) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl;
    }
}

/**
 * Find and print course title, prerequisites, for single course number.
 */
static void printSingleCourse(const map<string, Course>& bst, const string& courseNumInput) {
    if (bst.empty()) {
        cout << "No course data loaded. Please load a file first (Option 1)." << endl;
        return;
    }

    string key = toUpper(trim(courseNumInput));
    auto it = bst.find(key);

    if (it == bst.end()) {
        cout << '\n';
        cout << "Course '" << key << "' not found." << endl;
        return;
    }

    printCourseDetails(it->second, bst);
}

//----------------------------------------------------------------------------
// Menu / UI
//----------------------------------------------------------------------------

static void printMenu() {
    cout << endl << endl; // Menu spacing for readability.
    cout << "Menu:" << endl;
    cout << "-----" << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course" << endl;
    cout << "  9. Exit" << endl;
    cout << '\n';
    cout << "Enter choice: ";
    cout << '\n';
}

int main() {
    // Welcome message to user.
    cout << "Welcome to the ABCU Course Planner." << endl;
    map<string, Course> bst;   // Chosen BST-style structure, sorted by courseNumber.
    bool dataLoaded = false;

    int choice = 0;
    while (choice != 9) {
        printMenu();
        cin >> choice;

        // Basic input validation for non-integer menu entries.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << '\n';
            cout << "Invalid input. Please enter a menu number (1, 2, 3, or 9)." << endl;
            continue;
        }

        if (choice == 1) {
            cout << '\n';
            cout << "Enter the file name: ";
            string fileName;
            cin >> fileName;

            dataLoaded = loadCoursesFromFile(fileName, bst);

            if (dataLoaded) {
                cout << '\n';
                cout << "File loaded successfully. Courses loaded: " << bst.size() << endl;
            }
            else {
                cout << "File load failed." << endl;
            }
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load data first (Option 1)." << endl;
            }
            else {
                printCourseList(bst);
            }
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load data first (Option 1)." << endl;
            }
            else {
                cout << '\n';
                cout << "Enter course number: ";
                cout << '\n';
                string courseNum;
                cin >> courseNum;
                printSingleCourse(bst, courseNum);
            }
        }
        else if (choice == 9) {
            cout << '\n';
            cout << "Thank you for using the course planner. Goodbye!" << endl;
            cout << '\n';
        }
        else {
            cout << "Invalid selection. Please choose 1, 2, 3, or 9." << endl;
        }
    }

    return 0;
}