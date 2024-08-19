
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//creating Course Structure
struct Course {
	string courseNumber;
	string name;
	string prerequisites;
};

//implementing function how Course will be displayed
void displayCourse(Course course) {
	cout << "CourseID: " << course.courseNumber << "\n"
		<< "Course Name: " << course.name << "\n"
		<< "Prerequisites: " << course.prerequisites << "\n" << endl;
}

//created separate to aid building courses
vector<string> separate(string str, char comma) {
	vector<string> substrings;
	string substring;
	stringstream ss(str);
	while (getline(ss, substring, comma)) {
		substrings.push_back(substring);
	}
	return substrings;
}

//open file and build courses
vector<Course> loadCourses(string csvPath) {
	vector<Course> courses;
	ifstream file(csvPath);
	string line;

	cout << "Loading CSV file " << csvPath << endl;

	if (!file.is_open()) {
		cerr << "File not read: " << csvPath << endl;
		return courses;
	}

	while (getline(file, line)) {
		if (line.empty()) continue;

		vector<string> fields = separate(line, ',');

		Course course;
		course.courseNumber = fields[0];
		course.name = fields[1];

		course.prerequisites.clear();
		for (size_t i = 2; i < fields.size(); ++i) {
			if (!course.prerequisites.empty()) {
				course.prerequisites += ",";
			}
			course.prerequisites += fields[i];
		}

		courses.push_back(course);
	}

	file.close();
	return courses;
}

//sort courses
void sortCourses(vector<Course> courses) {
	sort(courses.begin(), courses.end(), [](Course number1, Course number2) {
		return number1.courseNumber < number2.courseNumber;
		});
	for (auto course : courses) {
		displayCourse(course);
	}
}

//search function
void searchCourses(vector<Course> courses, string courseNumber) {
	auto current = find_if(courses.begin(), courses.end(), [&](Course course) {
		return course.courseNumber == courseNumber;
		});
	if (current != courses.end()) {
		displayCourse(*current);
	}
	else {
		cout << "not found" << endl;
	}
}

//Menu functions
int main() {
	vector<Course> courses;
	int choice = 0;
	string fileName;
	string courseNumber;

	while (choice != 9) {
		cout << "Menu:\n"
			<< "1. Load File Data\n"
			<< "2. Print Sorted Courses\n"
			<< "3. Print Course Information\n"
			<< "9. Exit\n"
			<< "Enter your Selection: ";
		cin >> choice;
		cin.ignore();
			
		switch (choice) {
			case 1:
				cout << "Enter file name: ";
				getline(cin, fileName);
				courses = loadCourses(fileName);
				break;
			case 2:
				sortCourses(courses);
				break;
			case 3:
				cout << "Enter course number: ";
				getline(cin, courseNumber);
				searchCourses(courses, courseNumber);
				break;
			case 9:
				cout << "Exiting" << endl;
				break;
			default:
				cout << "Invalid option" << endl;
				break;
		}
	}
	return 0;
}
