#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Student {
public:
    string name;
    string lastName;
    int age;
    int indexNumber;
    double finalGrade;

    Student(string imie, string nazwisko, int wiek, int numerAlbumu, double ocenaKoncowa)
        : name(imie), lastName(nazwisko), age(wiek), indexNumber(numerAlbumu), finalGrade(ocenaKoncowa) {}

    Student() : name(""), lastName(""), age(0), indexNumber(0), finalGrade(0.0) {}

    std::string printStudent() const {
        return "\nName: " + name + "\n" + 
            "Last Name: " + lastName + "\n" + 
            "Age: " + std::to_string(age) + "\n" +
            "Index Number: " + std::to_string(indexNumber) + "\n" + 
            "Final Grade: " + std::to_string(finalGrade) + "\n";
    }

    bool operator==(const Student& other) const {
        return name == other.name && lastName == other.lastName && age == other.age && indexNumber == other.indexNumber && finalGrade == other.finalGrade;
    }

};

inline void serialize(std::ostream& os, const Student& s) {
    size_t len_name = s.name.size();
    size_t len_last = s.lastName.size();

    os.write(reinterpret_cast<const char*>(&len_name), sizeof(len_name));
    os.write(s.name.c_str(), len_name);

    os.write(reinterpret_cast<const char*>(&len_last), sizeof(len_last));
    os.write(s.lastName.c_str(), len_last);

    os.write(reinterpret_cast<const char*>(&s.age), sizeof(s.age));
    os.write(reinterpret_cast<const char*>(&s.indexNumber), sizeof(s.indexNumber));
    os.write(reinterpret_cast<const char*>(&s.finalGrade), sizeof(s.finalGrade));
}

inline void deserialize(std::istream& is, Student& s) {
    size_t len_name, len_last;

    is.read(reinterpret_cast<char*>(&len_name), sizeof(len_name));
    s.name.resize(len_name);
    is.read(&s.name[0], len_name);

    is.read(reinterpret_cast<char*>(&len_last), sizeof(len_last));
    s.lastName.resize(len_last);
    is.read(&s.lastName[0], len_last);

    is.read(reinterpret_cast<char*>(&s.age), sizeof(s.age));
    is.read(reinterpret_cast<char*>(&s.indexNumber), sizeof(s.indexNumber));
    is.read(reinterpret_cast<char*>(&s.finalGrade), sizeof(s.finalGrade));
}