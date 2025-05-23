#pragma once
#include <iostream>
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include <Student.h>
#include <SmartArray.h>
#include <ftxui\component\screen_interactive.hpp>
#include <ftxui\component\component.hpp>
#include "Tui.h"

using namespace ftxui;

int main() {
    // Default Students
    Student student1("Jan", "Kowalski", 20, 12345, 4.5);
    Student student2("Anna", "Nowak", 22, 67890, 4.8);
    Student student3("Mikolaj", "Kosiorek", 21, 155281, 5.0);

    SmartArray<Student> smartArray;
    smartArray.pushBack(student1);
    smartArray.pushBack(student2);
    smartArray.pushBack(student3);

    Tui tui(smartArray);
    tui.run();

    return 0;
}