#include "student.h"

Student::Student(string name, unsigned int age)
{
      this->age = age;
      this->name = name;
}

Student::~Student()
{
    cout << "Student left school building.";
}
