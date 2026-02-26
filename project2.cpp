#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
    Course Object
    Stores course number, title, and prerequisite list
*/
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

/* 
   Hash table storing all courses
   key = course number
   value = course object
*/
unordered_map<string, Course> courseTable;

/*
    Convert a string to uppercase (helps searching)
*/
string toUpper(string input) {
    for (char &c : input) {
        c = toupper(c);
    }
    return input;
}

/*
    Load file into the data structure
*/
void loadDataStructure(string fileName) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // split CSV
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Invalid line in file. Skipping." << endl;
            continue;
        }

        Course course;
        course.courseId = toUpper(tokens[0]);
        course.title = tokens[1];

        // Add prerequisites
        for (size_t i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(toUpper(tokens[i]));
        }

        courseTable[course.courseId] = course;
    }

    file.close();
    cout << "Data successfully loaded." << endl;
}

/*
    Print sorted course list
*/
void printCourseList() {

    if (courseTable.empty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    vector<string> courseIds;

    // collect keys
    for (auto &pair : courseTable) {
        courseIds.push_back(pair.first);
    }

    // sort alphanumerically
    sort(courseIds.begin(), courseIds.end());

    cout << endl;
    cout << "Here is a sample schedule:" << endl;

    for (string id : courseIds) {
        cout << id << ", " << courseTable[id].title << endl;
    }

    cout << endl;
}

/*
    Print information for one course
*/
void printCourseInformation() {

    if (courseTable.empty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    string courseId;
    cout << "What course do you want to know about? ";
    cin >> courseId;

    courseId = toUpper(courseId);

    if (courseTable.find(courseId) == courseTable.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course course = courseTable[courseId];

    cout << endl;
    cout << course.courseId << ", " << course.title << endl;

    cout << "Prerequisites: ";

    if (course.prerequisites.size() == 0) {
        cout << "None";
    } 
    else {
        for (size_t i = 0; i < course.prerequisites.size(); i++) {

            string prereqId = course.prerequisites[i];

            // print title if it exists
            if (courseTable.find(prereqId) != courseTable.end()) {
                cout << prereqId << " (" 
                     << courseTable[prereqId].title << ")";
            } else {
                cout << prereqId;
            }

            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl << endl;
}

/*
    Display menu
*/
void displayMenu() {

    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

/*
    Main program
*/
int main() {

    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    string fileName;

    while (choice != 9) {

        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(fileName);
            break;

        case 2:
            printCourseList();
            break;

        case 3:
            printCourseInformation();
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}
