#pragma once
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

class Tui {
	//DOXYGEN

	ScreenInteractive screen = ScreenInteractive::Fullscreen();
	std::vector<std::string> menuEntries = {
		"Show hello world",
		"Show input",
		"Show scrollable",
		"Show all students",
		"Exit"
	};

	enum ActiveScreen {
		MenuScreen = -1,
		HelloWordldScreen = 0,
		ShowInput,
		ShowScrollable,
		PrintStudents,
		Exit
	};

	ActiveScreen activeScreen = MenuScreen;

	void showMenu();
	void showHelloWorldScreen();
	void showAllStudents();
	void showInputScreen();
	Color inputBgColor(bool isValid);
	void showScrollableScreen();

public:
	void run();
};