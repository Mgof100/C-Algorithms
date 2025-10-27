#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

//Introduce Course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

bool courseCompare(const Course& a, const Course& b) { //intial sort
    return a.courseNumber < b.courseNumber;
}

void printCourseList(const vector<Course>& courses) {

    if (courses.empty()) { //if no courses
        cout << "No courses loaded" << endl;
        return;
    }

    vector<Course> sorted = courses;
    sort(sorted.begin(), sorted.end(), courseCompare); //second sort

    cout << "Here is a sample schedule:" << endl;

    for (const auto& courseData : sorted) {
        cout << courseData.courseNumber << " " << courseData.name << endl; //output
    }
}

void searchCourse(vector<Course> courses, string courseNumber) {
    int i;
    for (i = 0; i < courses.size(); i++) {
        if (courses[i].courseNumber == courseNumber) {  //base course
            cout << courses[i].courseNumber << ", " << courses[i].name << endl;
            if (!courses[i].prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (int j = 0; j < courses[i].prerequisites.size(); j++) { //if prerequisites
                    cout << courses[i].prerequisites.size() - 1 << endl;
                    if (j != courses[i].prerequisites.size() - 1) {
                        cout << ", ";
                    }

                }
                cout << endl;
            }
            else { //no prerequisites
                cout << "No prerequisites." << endl;
            }
            return;
        }
    }
    cout << "Course not found." << endl;
}

void printMenu() { //main menu
    cout << "Welcome to the course planner." << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List. " << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << "What would you like to do? ";

}


bool loadCoursesFromFile(string filename, vector<Course>& courses) {
    ifstream fin(filename);                   // Input file stream

    if (!fin.is_open()) { //open file
        cout << "Could not open file." << endl;
        return false;
    }
    string line;


    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 2)
        {
            Course course;
            course.courseNumber = tokens[0]; //first option
            course.name = tokens[1];    // second option
            for (size_t i = 2; i < tokens.size(); i++) { //all preerequisites
                course.prerequisites.push_back(tokens[i]);
            }
            courses.push_back(course);

        }
    }

    fin.close(); //close file
    return true;

}

int main() {
    vector<Course> courses;
    bool loaded = false;
    int choice = 0;

    while (true) {
        printMenu();

        // ?? Input validation: handle non-numeric input (e.g., letters like 'g')
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n\n";
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "Enter file name: ";
            string fileName;
            cin >> fileName;

            courses.clear();  // clear previous data

            if (loadCoursesFromFile(fileName, courses)) {
                loaded = true;
                cout << "Loaded " << courses.size() << " course(s).\n\n";
            }
            else {
                loaded = false;
                cout << "Load failed.\n\n";
            }

            // clear any leftover input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        case 2:
            if (!loaded) {
                cout << "Please load the data in option 1 first.\n\n"; //if no file loaded
            }
            else {
                printCourseList(courses); //if loaded
            }
            break;

        case 3:
            if (!loaded) {
                cout << "Please load the data in option 1 first.\n\n"; //if no file loaded
            }
            else {
                cout << "What course do you want to know about?"; //select course
                string courseNumber;
                cin >> courseNumber;
                searchCourse(courses, courseNumber);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl; //exit
            return 0;

        default:
            cout << "Invalid option. Try again.\n\n"; //default
            break;
        }
    }
}
