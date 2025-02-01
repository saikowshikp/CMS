#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Admin; // Forward declaration

class College {
private:
    vector<class Student> students;
    vector<class Course> courses;
    Admin *admin;
    string adminPassword = "password";
    int studentID = 0, courseID = 0;

    void addStudent(const string &name) {
        students.push_back(Student(++studentID, name));
    }

    void addCourse(const string &name, const string &instructor) {
        courses.push_back(Course(++courseID, name, instructor));
    }

public:
    College() { admin = new Admin(); }
    ~College() { delete admin; }

    Admin *getAdmin(const string &pwd);

    friend class Admin;
};

class Student {
private:
    int id;
    string name;
    vector<pair<int, int>> enrolledCourses; //(courseId, grade)

public:
    Student(int id, const string &name) : id(id), name(name) {}
    friend class Admin;
};

class Course {
private:
    int id;
    string name;
    string instructor;

public:
    Course(int id, const string &name, const string &instructor)
        : id(id), name(name), instructor(instructor) {}
    friend class Admin;
};

class Admin {
public:
    void addStudent(College &college, const string &name) {
        college.addStudent(name);
    }

    void addCourse(College &college, const string &name, const string &instructor) {
        college.addCourse(name, instructor);
    }
};

Admin *College::getAdmin(const string &pwd) {
    if (pwd == adminPassword)
        return admin;
    return nullptr;
}

int main() {
    College iith;

    Admin *admin = iith.getAdmin("password");
    if (admin) {
        admin->addStudent(iith, "Sai Kowshik");
        admin->addStudent(iith, "Pravarsh");
        admin->addCourse(iith, "Introduction to Programming", "Kotaro");
        cout << "Students and courses added successfully." << endl;
    } else {
        cout << "Access denied: Incorrect password!" << endl;
    }
    return 0;
}
