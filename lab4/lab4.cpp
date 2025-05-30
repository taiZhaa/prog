#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Student {
public:
    string name;
    int age;
    string major;

    // Конструктор по умолчанию
    Student() : name(""), age(0), major("") {}

    // Метод для преобразования объекта в строку
    string toString() const {
        return name + " " + to_string(age) + " " + major;
    }

    // Метод для создания объекта из строки
    void fromString(const string& str) {
        istringstream iss(str);
        iss >> name >> age >> major;
    }
};

class Database {
private:
    vector<Student> students;
    string filename;

public:
    Database(const string& fname) : filename(fname) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto& student : students) {
            file << student.toString() << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        string line;
        students.clear();
        while (getline(file, line)) {
            Student student;
            student.fromString(line);
            students.push_back(student);
        }
        file.close();
    }

    void updateStudent(int index, const Student& student) {
        if (index >= 0 && index < students.size()) {
            students[index] = student;
        }
    }

    void deleteStudent(int index) {
        if (index >= 0 && index < students.size()) {
            students.erase(students.begin() + index);
        }
    }

    void displayStudents() const {
        for (const auto& student : students) {
            cout << student.toString() << endl;
        }
    }
};

int main() {
    Database db("students.txt");

    // Пример добавления студентов
    Student student1;
    student1.name = "Alice";
    student1.age = 20;
    student1.major = "ComputerScience";
    db.addStudent(student1);

    Student student2;
    student2.name = "Bob";
    student2.age = 22;
    student2.major = "Mathematics";
    db.addStudent(student2);

    // Сохранение студентов в файл
    db.saveToFile();

    // Загрузка студентов из файла
    db.loadFromFile();

    // Отображение студентов
    cout << "Список студентов:" << endl;
    db.displayStudents();

    // Обновление студента
    Student updatedStudent;
    updatedStudent.name = "Alice";
    updatedStudent.age = 21;
    updatedStudent.major = "DataScience";
    db.updateStudent(0, updatedStudent);

    // Удаление студента
    db.deleteStudent(1);

    // Сохранение изменений в файл
    db.saveToFile();

    return 0;
}
