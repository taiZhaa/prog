#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    string name;
    string age;
    string grade;
};

vector<Student> students;
const string filename = "database.txt";

void addStudent() {
    Student s;
    cout << "Name: ";
    cin >> s.name;
    cout << "Age: ";
    cin >> s.age;
    cout << "Class: ";
    cin >> s.grade;
    students.push_back(s);
}

void saveToFile() {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& s : students) {
            file << s.name << " " << s.age << " " << s.grade << "\n";
        }
        cout << "Saved.\n";
    } else {
        cout << "Error.\n";
    }
}

void loadFromFile() {
    ifstream file(filename);
    students.clear();
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(' ');
            size_t pos2 = line.find(' ', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                Student s;
                s.name = line.substr(0, pos1);
                s.age = line.substr(pos1 + 1, pos2 - pos1 - 1);
                s.grade = line.substr(pos2 + 1);
                students.push_back(s);
            }
        }
        cout << "Saved.\n";
    } else {
        cout << "File not found.\n";
    }
}

void updateStudent() {
    cout << "Number of student: ";
    size_t i;
    cin >> i;
    
    if (i < students.size()) {
        cout << "New name: ";
        getline(cin, students[i].name);
        cout << "New age: ";
        getline(cin, students[i].age);
        cout << "New class: ";
        getline(cin, students[i].grade);
        cout << "Saved.\n";
    } else {
        cout << "There is no such number.\n";
    }
}

void deleteStudent() {
    cout << "Numper of student: ";
    size_t i;
    cin >> i;
    
    if (i < students.size()) {
        students.erase(students.begin() + i);
        cout << "Deleted.\n";
    } else {
        cout << "There is no such number.\n";
    }
}

int main() {
    loadFromFile();
    
    while (true) {
        cout << "\n1. Add student\n"
             << "2. Change\n"
             << "3. Remove\n"
             << "4. Download\n"
             << "5. Save to a file\n"
             << "Choose: ";
             
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: loadFromFile(); break;
            case 5: saveToFile(); return 0;
            default: cout << "There is no such choice in the list.\n";
        }
    }
}
