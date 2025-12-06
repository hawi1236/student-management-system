#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Student class definition
class Student {
private:
    int id;
    string name;
    int age;
    string department;
    float gpa;
    int attendance;

public:
    // Constructor
    Student(int id = 0, string name = "", int age = 0,
            string department = "", float gpa = 0.0, int attendance = 0) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->department = department;
        this->gpa = gpa;
        this->attendance = attendance;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getDepartment() const { return department; }
    float getGPA() const { return gpa; }
    int getAttendance() const { return attendance; }

    // Setters
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setDepartment(string department) { this->department = department; }
    void setGPA(float gpa) { this->gpa = gpa; }
    void setAttendance(int attendance) { this->attendance = attendance; }

    // Display student information
    void display() const {
        cout << "\n┌─────────────────────────────────────────────────────┐" << endl;
        cout << "│                 STUDENT INFORMATION                 │" << endl;
        cout << "├─────────────────────────────────────────────────────┤" << endl;
        cout << "│ ID:           " << setw(38) << left << id << "│" << endl;
        cout << "│ Name:         " << setw(38) << left << name << "│" << endl;
        cout << "│ Age:          " << setw(38) << left << age << "│" << endl;
        cout << "│ Department:   " << setw(38) << left << department << "│" << endl;
        cout << "│ GPA:          " << setw(38) << left << fixed << setprecision(2) << gpa << "│" << endl;
        cout << "│ Attendance:   " << setw(38) << left << attendance << "% │" << endl;
        cout << "└─────────────────────────────────────────────────────┘" << endl;
    }

    // Convert to string for file storage
    string toString() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," +
               department + "," + to_string(gpa) + "," + to_string(attendance);
    }

    // Load from string
    static Student fromString(const string& str) {
        vector<string> tokens;
        string token;
        stringstream ss(str);

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6) {
            int id = stoi(tokens[0]);
            int age = stoi(tokens[2]);
            float gpa = stof(tokens[4]);
            int attendance = stoi(tokens[5]);

            return Student(id, tokens[1], age, tokens[3], gpa, attendance);
        }

        return Student();
    }
};

// Student Management System Class
class StudentManagementSystem {
private:
    vector<Student> students;
    string filename;

    // Helper function to validate GPA
    bool isValidGPA(float gpa) {
        return gpa >= 0.0 && gpa <= 4.0;
    }

    // Helper function to validate attendance
    bool isValidAttendance(int attendance) {
        return attendance >= 0 && attendance <= 100;
    }

    // Helper function to find student by ID
    int findStudentIndex(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

public:
    StudentManagementSystem(string filename = "students.txt") {
        this->filename = filename;
        loadFromFile();
    }

    // Add a new student
    void addStudent() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    ADD NEW STUDENT" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        Student student;
        int id;
        string name;
        int age;
        string department;
        float gpa;
        int attendance;

        // Get student ID
        cout << "\nEnter Student ID: ";
        while (!(cin >> id) || id <= 0) {
            cout << "Invalid ID! Please enter a positive integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Check if ID already exists
        if (findStudentIndex(id) != -1) {
            cout << "\n❌ Student with ID " << id << " already exists!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        student.setId(id);

        // Get student name
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, name);
        student.setName(name);

        // Get student age
        cout << "Enter Student Age: ";
        while (!(cin >> age) || age < 16 || age > 60) {
            cout << "Invalid age! Please enter age between 16-60: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        student.setAge(age);

        // Get department
        cout << "Enter Department: ";
        cin.ignore();
        getline(cin, department);
        student.setDepartment(department);

        // Get GPA
        cout << "Enter GPA (0.0 - 4.0): ";
        while (!(cin >> gpa) || !isValidGPA(gpa)) {
            cout << "Invalid GPA! Please enter value between 0.0 and 4.0: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        student.setGPA(gpa);

        // Get attendance
        cout << "Enter Attendance Percentage (0-100): ";
        while (!(cin >> attendance) || !isValidAttendance(attendance)) {
            cout << "Invalid attendance! Please enter value between 0-100: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        student.setAttendance(attendance);

        students.push_back(student);
        saveToFile();

        cout << "\n✅ Student added successfully!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Display all students
    void displayAllStudents() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                   ALL STUDENTS RECORDS" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (students.empty()) {
            cout << "\n📭 No student records found!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Display header
        cout << "\n┌──────┬──────────────────────┬─────┬──────────────────┬──────┬─────────────┐" << endl;
        cout << "│  ID  │        Name          │ Age │   Department    │ GPA  │ Attendance  │" << endl;
        cout << "├──────┼──────────────────────┼─────┼──────────────────┼──────┼─────────────┤" << endl;

        // Display each student
        for (const auto& student : students) {
            cout << "│ " << setw(4) << left << student.getId() << " │ "
                 << setw(20) << left << (student.getName().length() > 20 ?
                    student.getName().substr(0, 17) + "..." : student.getName()) << " │ "
                 << setw(3) << left << student.getAge() << " │ "
                 << setw(16) << left << (student.getDepartment().length() > 16 ?
                    student.getDepartment().substr(0, 13) + "..." : student.getDepartment()) << " │ "
                 << setw(4) << left << fixed << setprecision(2) << student.getGPA() << " │ "
                 << setw(11) << left << to_string(student.getAttendance()) + "%" << " │" << endl;
        }

        cout << "└──────┴──────────────────────┴─────┴──────────────────┴──────┴─────────────┘" << endl;

        // Display statistics
        cout << "\n📊 Total Students: " << students.size() << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Search for a student by ID
    void searchStudent() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    SEARCH STUDENT" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        int id;
        cout << "\nEnter Student ID to search: ";
        while (!(cin >> id) || id <= 0) {
            cout << "Invalid ID! Please enter a positive integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
        } else {
            students[index].display();
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Update student information
    void updateStudent() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    UPDATE STUDENT" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        int id;
        cout << "\nEnter Student ID to update: ";
        while (!(cin >> id) || id <= 0) {
            cout << "Invalid ID! Please enter a positive integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Display current information
        cout << "\nCurrent Information:" << endl;
        students[index].display();

        int choice;
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                 SELECT FIELD TO UPDATE" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "1. Update Name" << endl;
        cout << "2. Update Age" << endl;
        cout << "3. Update Department" << endl;
        cout << "4. Update GPA" << endl;
        cout << "5. Update Attendance" << endl;
        cout << "6. Update All Information" << endl;
        cout << "7. Cancel Update" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "Enter your choice (1-7): ";

        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid choice! Please enter 1-7: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (choice == 7) {
            cout << "\nUpdate cancelled." << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        string name;
        int age;
        string department;
        float gpa;
        int attendance;

        switch (choice) {
            case 1: // Update Name
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, name);
                students[index].setName(name);
                break;

            case 2: // Update Age
                cout << "Enter new Age: ";
                while (!(cin >> age) || age < 16 || age > 60) {
                    cout << "Invalid age! Please enter age between 16-60: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setAge(age);
                break;

            case 3: // Update Department
                cout << "Enter new Department: ";
                cin.ignore();
                getline(cin, department);
                students[index].setDepartment(department);
                break;

            case 4: // Update GPA
                cout << "Enter new GPA (0.0 - 4.0): ";
                while (!(cin >> gpa) || !isValidGPA(gpa)) {
                    cout << "Invalid GPA! Please enter value between 0.0 and 4.0: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setGPA(gpa);
                break;

            case 5: // Update Attendance
                cout << "Enter new Attendance Percentage (0-100): ";
                while (!(cin >> attendance) || !isValidAttendance(attendance)) {
                    cout << "Invalid attendance! Please enter value between 0-100: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setAttendance(attendance);
                break;

            case 6: // Update All
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, name);
                students[index].setName(name);

                cout << "Enter new Age: ";
                while (!(cin >> age) || age < 16 || age > 60) {
                    cout << "Invalid age! Please enter age between 16-60: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setAge(age);

                cout << "Enter new Department: ";
                cin.ignore();
                getline(cin, department);
                students[index].setDepartment(department);

                cout << "Enter new GPA (0.0 - 4.0): ";
                while (!(cin >> gpa) || !isValidGPA(gpa)) {
                    cout << "Invalid GPA! Please enter value between 0.0 and 4.0: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setGPA(gpa);

                cout << "Enter new Attendance Percentage (0-100): ";
                while (!(cin >> attendance) || !isValidAttendance(attendance)) {
                    cout << "Invalid attendance! Please enter value between 0-100: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                students[index].setAttendance(attendance);
                break;
        }

        saveToFile();
        cout << "\n✅ Student information updated successfully!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Delete a student
    void deleteStudent() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    DELETE STUDENT" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        int id;
        cout << "\nEnter Student ID to delete: ";
        while (!(cin >> id) || id <= 0) {
            cout << "Invalid ID! Please enter a positive integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
        } else {
            cout << "\nStudent to be deleted:" << endl;
            students[index].display();

            char confirm;
            cout << "\n⚠️  Are you sure you want to delete this student? (y/n): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                students.erase(students.begin() + index);
                saveToFile();
                cout << "\n✅ Student deleted successfully!" << endl;
            } else {
                cout << "\nDeletion cancelled." << endl;
            }
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Generate reports
    void generateReports() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    SYSTEM REPORTS" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (students.empty()) {
            cout << "\n📭 No student records found!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        int choice;
        cout << "\nSelect Report Type:" << endl;
        cout << "1. Overall Statistics" << endl;
        cout << "2. Top Performers (GPA > 3.5)" << endl;
        cout << "3. Low Attendance Students (< 75%)" << endl;
        cout << "4. Department-wise Report" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "Enter your choice (1-5): ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice! Please enter 1-5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (choice == 5) return;

        switch (choice) {
            case 1: // Overall Statistics
                {
                    float totalGPA = 0;
                    float totalAttendance = 0;
                    float maxGPA = 0;
                    float minGPA = 4.0;
                    int maxGPAStudentId = 0;
                    int minGPAStudentId = 0;
                    string maxGPAStudentName, minGPAStudentName;

                    for (const auto& student : students) {
                        float gpa = student.getGPA();
                        totalGPA += gpa;
                        totalAttendance += student.getAttendance();

                        if (gpa > maxGPA) {
                            maxGPA = gpa;
                            maxGPAStudentId = student.getId();
                            maxGPAStudentName = student.getName();
                        }

                        if (gpa < minGPA) {
                            minGPA = gpa;
                            minGPAStudentId = student.getId();
                            minGPAStudentName = student.getName();
                        }
                    }

                    cout << "\n═══════════════════════════════════════════════════════════" << endl;
                    cout << "                 OVERALL STATISTICS REPORT" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;
                    cout << "Total Students:          " << students.size() << endl;
                    cout << "Average GPA:             " << fixed << setprecision(2) << totalGPA / students.size() << endl;
                    cout << "Average Attendance:      " << fixed << setprecision(1) << totalAttendance / students.size() << "%" << endl;
                    cout << "Highest GPA:             " << maxGPA << " (ID: " << maxGPAStudentId << ", Name: " << maxGPAStudentName << ")" << endl;
                    cout << "Lowest GPA:              " << minGPA << " (ID: " << minGPAStudentId << ", Name: " << minGPAStudentName << ")" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;
                }
                break;

            case 2: // Top Performers
                {
                    cout << "\n═══════════════════════════════════════════════════════════" << endl;
                    cout << "                TOP PERFORMERS (GPA > 3.5)" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;

                    vector<Student> topPerformers;
                    for (const auto& student : students) {
                        if (student.getGPA() > 3.5) {
                            topPerformers.push_back(student);
                        }
                    }

                    if (topPerformers.empty()) {
                        cout << "No top performers found." << endl;
                    } else {
                        for (const auto& student : topPerformers) {
                            cout << "ID: " << student.getId()
                                 << ", Name: " << student.getName()
                                 << ", GPA: " << fixed << setprecision(2) << student.getGPA()
                                 << ", Department: " << student.getDepartment() << endl;
                        }
                        cout << "\nTotal Top Performers: " << topPerformers.size() << endl;
                    }
                }
                break;

            case 3: // Low Attendance
                {
                    cout << "\n═══════════════════════════════════════════════════════════" << endl;
                    cout << "          LOW ATTENDANCE STUDENTS (< 75%)" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;

                    vector<Student> lowAttendance;
                    for (const auto& student : students) {
                        if (student.getAttendance() < 75) {
                            lowAttendance.push_back(student);
                        }
                    }

                    if (lowAttendance.empty()) {
                        cout << "No students with low attendance." << endl;
                    } else {
                        for (const auto& student : lowAttendance) {
                            cout << "ID: " << student.getId()
                                 << ", Name: " << student.getName()
                                 << ", Attendance: " << student.getAttendance() << "%"
                                 << ", Department: " << student.getDepartment() << endl;
                        }
                        cout << "\nTotal Students with Low Attendance: " << lowAttendance.size() << endl;
                    }
                }
                break;

            case 4: // Department-wise Report
                {
                    cout << "\n═══════════════════════════════════════════════════════════" << endl;
                    cout << "               DEPARTMENT-WISE REPORT" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;

                    // Count students by department
                    vector<string> departments;
                    vector<int> departmentCounts;

                    for (const auto& student : students) {
                        string dept = student.getDepartment();
                        bool found = false;

                        for (int i = 0; i < departments.size(); i++) {
                            if (departments[i] == dept) {
                                departmentCounts[i]++;
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            departments.push_back(dept);
                            departmentCounts.push_back(1);
                        }
                    }

                    for (int i = 0; i < departments.size(); i++) {
                        cout << departments[i] << ": " << departmentCounts[i] << " students" << endl;
                    }
                }
                break;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Save data to file
    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.toString() << endl;
            }
            file.close();
        }
    }

    // Load data from file
    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            students.clear();

            while (getline(file, line)) {
                if (!line.empty()) {
                    Student student = Student::fromString(line);
                    students.push_back(student);
                }
            }
            file.close();
        }
    }

    // Display main menu
    void displayMenu() {
        system("cls");
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "         STUDENT MANAGEMENT SYSTEM - MAIN MENU" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student Information" << endl;
        cout << "5. Delete Student Record" << endl;
        cout << "6. Generate Reports" << endl;
        cout << "7. Exit Program" << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "Enter your choice (1-7): ";
    }

    // Main program loop
    void run() {
        int choice;

        do {
            displayMenu();

            while (!(cin >> choice) || choice < 1 || choice > 7) {
                cout << "Invalid choice! Please enter 1-7: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    displayAllStudents();
                    break;
                case 3:
                    searchStudent();
                    break;
                case 4:
                    updateStudent();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    generateReports();
                    break;
                case 7:
                    system("cls");
                    cout << "\n═══════════════════════════════════════════════════════════" << endl;
                    cout << "  Thank you for using Student Management System!" << endl;
                    cout << "                    Goodbye! 👋" << endl;
                    cout << "═══════════════════════════════════════════════════════════" << endl;
                    break;
            }
        } while (choice != 7);
    }
};

// Main function
int main() {
    // Create an instance of StudentManagementSystem
    StudentManagementSystem sms;

    // Run the system
    sms.run();

    return 0;
}
