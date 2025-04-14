#pragma once
#include <iostream>
#include <string>

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

        //cout << "Imie: " << imie << endl;
        //cout << "Nazwisko: " << nazwisko << endl;
        //cout << "Wiek: " << wiek << endl;
        //cout << "Numer albumu: " << numerAlbumu << endl;
        //cout << "Ocena koncowa: " << ocenaKoncowa << endl;
    }

    bool operator==(const Student& other) const {
        return name == other.name && lastName == other.lastName && age == other.age && indexNumber == other.indexNumber && finalGrade == other.finalGrade;
    }
};