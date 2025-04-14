#pragma once
#include <ftxui/component/screen_interactive.hpp>
#include <Student.h>
#include <SmartArray.h>

using namespace ftxui;

class Tui {
	//DOXYGEN

	ScreenInteractive screen = ScreenInteractive::Fullscreen();
	std::vector<std::string> menuEntries = {
		"Show hello world",
		"Add student",
		"Delete student",
		"Edit student",
		"Print all students",
		"Exit"
	};

	enum ActiveScreen {
		MenuScreen = -1,
		HelloWordldScreen = 0,
		ShowInput,
		DeleteStudent,
		EditStudent,
		ShowScrollable,
		Exit
	};

	ActiveScreen activeScreen = MenuScreen;

	void showMenu();
	void showHelloWorldScreen();
	void showInputScreen();
	Color inputBgColor(bool isValid);
	void showAllStudentsScreen();
	void removeStudentScreen();
	void editStudentScreen();

public:
	Tui(SmartArray<Student>& students) : smartArray(students) {};

	void run();

private:
	SmartArray<Student>& smartArray;
};