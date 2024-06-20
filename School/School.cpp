
#include <iostream>
#include <vector>
#include <string>

// Базовый класс для людей в школе
class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& name, int age) : name(name), age(age) {}
    virtual ~Person() {}

    std::string getName() const { return name; }
    int getAge() const { return age; }
    virtual void printInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

// Класс учеников
class Student : public Person {
private:
    std::string studentID;

public:
    Student(const std::string& name, int age, const std::string& studentID)
        : Person(name, age), studentID(studentID) {}

    std::string getStudentID() const { return studentID; }
    void printInfo() const override {
        Person::printInfo();
        std::cout << "Student ID: " << studentID << std::endl;
    }
};

// Класс учителей
class Teacher : public Person {
private:
    std::string subject;

public:
    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {}

    std::string getSubject() const { return subject; }
    void printInfo() const override {
        Person::printInfo();
        std::cout << "Subject: " << subject << std::endl;
    }
};

// Класс предметов
class Subject {
private:
    std::string name;
    Teacher* teacher;

public:
    Subject(const std::string& name, Teacher* teacher) : name(name), teacher(teacher) {}

    std::string getName() const { return name; }
    Teacher* getTeacher() const { return teacher; }
};

// Класс классов (групп учеников)
class Classroom {
private:
    std::string name;
    Teacher* teacher;
    std::vector<Student*> students;

public:
    Classroom(const std::string& name, Teacher* teacher) : name(name), teacher(teacher) {}

    void addStudent(Student* student) {
        students.push_back(student);
    }

    void printInfo() const {
        std::cout << "Classroom: " << name << std::endl;
        teacher->printInfo();
        std::cout << "Students:" << std::endl;
        for (const auto& student : students) {
            student->printInfo();
        }
    }
};

// Класс школы
class School {
private:
    std::string name;
    std::vector<Classroom*> classrooms;
    std::vector<Subject*> subjects;

public:
    School(const std::string& name) : name(name) {}

    void addClassroom(Classroom* classroom) {
        classrooms.push_back(classroom);
    }

    void addSubject(Subject* subject) {
        subjects.push_back(subject);
    }

    void printInfo() const {
        std::cout << "School: " << name << std::endl;
        std::cout << "Classrooms:" << std::endl;
        for (const auto& classroom : classrooms) {
            classroom->printInfo();
        }
        std::cout << "Subjects:" << std::endl;
        for (const auto& subject : subjects) {
            std::cout << "Subject: " << subject->getName() << std::endl;
            subject->getTeacher()->printInfo();
        }
    }
};

int main() {
    // Создаем учителей
    Teacher* teacher1 = new Teacher("Alice Johnson", 35, "Mathematics");
    Teacher* teacher2 = new Teacher("Bob Smith", 40, "Physics");

    // Создаем предметы
    Subject* math = new Subject("Mathematics", teacher1);
    Subject* physics = new Subject("Physics", teacher2);

    // Создаем учеников
    Student* student1 = new Student("John Doe", 16, "S12345");
    Student* student2 = new Student("Jane Doe", 15, "S12346");

    // Создаем классы
    Classroom* classroom1 = new Classroom("Class A", teacher1);
    classroom1->addStudent(student1);
    classroom1->addStudent(student2);

    // Создаем школу
    School school("Greenwood High School");
    school.addClassroom(classroom1);
    school.addSubject(math);
    school.addSubject(physics);

    // Вывод информации о школе
    school.printInfo();

    // Освобождаем память
    delete teacher1;
    delete teacher2;
    delete math;
    delete physics;
    delete student1;
    delete student2;
    delete classroom1;

    return 0;
}