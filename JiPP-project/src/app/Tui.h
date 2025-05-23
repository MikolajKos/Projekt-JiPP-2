#pragma once
#include <ftxui/component/screen_interactive.hpp>
#include <Student.h>
#include <SmartArray.h>

using namespace ftxui;

class Tui {

	ScreenInteractive screen = ScreenInteractive::Fullscreen();
	std::vector<std::string> menuEntries = {
		"Add student",
		"Delete student",
		"Edit student",
		"Print all students",
		"Count all students",
		"Save students",
		"Load students",
		"Exit"
	};

	enum ActiveScreen {
		MenuScreen = -1,
		ShowInput,
		DeleteStudent,
		EditStudent,
		ShowScrollable,
		CountStudents,
		SaveToFile,
		LoadFromFile,
		Exit
	};

	ActiveScreen activeScreen = MenuScreen;

	void showMenu();
	void showInputScreen();
	Color inputBgColor(bool isValid);
	void showAllStudentsScreen();
	void removeStudentScreen();
	void editStudentScreen();
	void countStudentsScreen();
	void saveToFileScreen();
	void loadFromFileScreen();

public:
	Tui(SmartArray<Student>& students) : smartArray(students) {};

	void run();

private:
	SmartArray<Student>& smartArray;
};