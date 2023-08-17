#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Create course class
class Course {
public:
    // default constructor
    Course() {}

    string number;
    string name;
    vector<string> prerequisites;

    Course(string number, string name) : number(number), name(name) {}
};

unordered_map<string, Course> courseData;

void loadDataStructure(string file_name) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string course_number, course_name, prerequisite;
        vector<string> prerequisites;

        getline(iss, course_number, ',');
        getline(iss, course_name, ',');

        while (getline(iss, prerequisite, ',')) {
            prerequisites.push_back(prerequisite);
        }

        Course course(course_number, course_name);
        course.prerequisites = prerequisites;

        // add the course to the hash table
        courseData[course_number] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

void printCourseList() {
    if (courseData.empty()) {
        cout << "No course data available. Please load data first." << endl;
        return;
    }

    vector<Course> sorted_courses;
    for (const auto& entry : courseData) {
        sorted_courses.push_back(entry.second);
    }

    // sort the courses alphanumerically
    sort(sorted_courses.begin(), sorted_courses.end(), [](const Course& a, const Course& b) {
        return a.number < b.number;
        });

    cout << "Here is a sample schedule:" << endl;
    for (const Course& course : sorted_courses) {
        cout << course.number << ", " << course.name << endl;
    }
}

void printCourseInformation(string course_number) {
    auto it = courseData.find(course_number);
    if (it == courseData.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.number << ", " << course.name << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites:";
        for (const string& prereq : course.prerequisites) {
            cout << " " << prereq;
        }
        cout << endl;
    }
}


int main()
{  
    cout << "Welcome to the course planner." << endl;
    int choice = 1;

    while (choice != 4) {
        // display menu to user
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string file;
                cout << "Enter the file name: ";
                cin >> file;
                loadDataStructure(file);
                break;
            }
            case 2: {
                printCourseList();
                break;
            }
            case 3: {
                string course_number;
                cout << "What course do you want to know about? ";
                cin >> course_number;
                printCourseInformation(course_number);
                break;
            }
            case 4:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}