#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    string imie;
    string nazwisko;
    int wiek;
    int numerAlbumu;
    double ocenaKoncowa;

    Student(string imie, string nazwisko, int wiek, int numerAlbumu, double ocenaKoncowa)
        : imie(imie), nazwisko(nazwisko), wiek(wiek), numerAlbumu(numerAlbumu), ocenaKoncowa(ocenaKoncowa) {}

    Student() : imie(""), nazwisko(""), wiek(0), numerAlbumu(0), ocenaKoncowa(0.0) {}

    void wypiszInformacje() const {
        cout << "Imie: " << imie << endl;
        cout << "Nazwisko: " << nazwisko << endl;
        cout << "Wiek: " << wiek << endl;
        cout << "Numer albumu: " << numerAlbumu << endl;
        cout << "Ocena koncowa: " << ocenaKoncowa << endl;
    }

    bool operator==(const Student& other) const {
        return imie == other.imie && nazwisko == other.nazwisko && wiek == other.wiek && numerAlbumu == other.numerAlbumu && ocenaKoncowa == other.ocenaKoncowa;
    }
};