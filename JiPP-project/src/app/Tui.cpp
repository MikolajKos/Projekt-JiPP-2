#pragma once
#include "Tui.h"
#include <ftxui/component/component.hpp>
#include <iostream>

void Tui::showMenu()
{
	int selectedOption = 0;

	MenuOption menuOption;
	menuOption.on_enter = screen.ExitLoopClosure();

	Component menu = Menu(&menuEntries, &selectedOption, menuOption);
	screen.Loop(menu);
	std::cout << "Selected option: " << selectedOption << " " << menuEntries[selectedOption] << std::endl;
	activeScreen = static_cast<ActiveScreen>(selectedOption);
}

void Tui::showHelloWorldScreen()
{
	Component backButton = Button("Back", screen.ExitLoopClosure());
	Component renderer = Renderer(backButton, [&] {
		return vbox({
			text("Hello World") | color(Color::Blue) | bgcolor(Color::Green),
			hbox({filler(), backButton->Render(), filler()}) | bgcolor(Color::Green)
		});
	});

	screen.Loop(renderer);
	activeScreen = MenuScreen;
}

void Tui::showInputScreen()
{
	Component backButton = Button("Back", screen.ExitLoopClosure());

	std::string name;
	std::string lastname;
	std::string ageStr;
	std::string indexStr;
	std::string gradeStr;

	bool inputsValid = false;
	std::string confirmationText = "";

	InputOption validateInputs;
	validateInputs.on_change = [&] {
		try {
			std::stoi(ageStr);
			std::stoi(indexStr);
			std::stod(gradeStr);
			inputsValid = true;
		}
		catch (...) {
			inputsValid = false;
		}
		};

	Component nameInput = Input(&name, "Name");
	Component lastnameInput = Input(&lastname, "Last Name");
	Component ageInput = Input(&ageStr, "Age", validateInputs);
	Component indexInput = Input(&indexStr, "Index Number", validateInputs);
	Component gradeInput = Input(&gradeStr, "Final Grade", validateInputs);

	ageInput |= CatchEvent([&](Event e) {
		return e.is_character() && !std::isdigit(e.character()[0]);
		});
	indexInput |= CatchEvent([&](Event e) {
		return e.is_character() && !std::isdigit(e.character()[0]);
		});
	gradeInput |= CatchEvent([&](Event e) {
		return false; // Allow decimal point
		});

	Component addButton = Button("Add", [&] {
		if (inputsValid) {
			Student newStudent(
				name,
				lastname,
				std::stoi(ageStr),
				std::stoi(indexStr),
				std::stod(gradeStr)
			);

			smartArray.pushBack(newStudent);
			confirmationText = "Student added:\n" + newStudent.printStudent();

			// Clear input fields
			name.clear();
			lastname.clear();
			ageStr.clear();
			indexStr.clear();
			gradeStr.clear();
		}
		else {
			confirmationText = "Invalid input. Please correct all fields.";
		}
		});

	Component navigation = Container::Vertical({
		nameInput,
		lastnameInput,
		ageInput,
		indexInput,
		gradeInput,
		addButton,
		backButton
		});

	Component renderer = Renderer(navigation, [&] {
		return vbox({
			hbox({ text("Name: "), nameInput->Render() }),
			hbox({ text("Last Name: "), lastnameInput->Render() }),
			hbox({ text("Age: "), ageInput->Render() }),
			hbox({ text("Index Number: "), indexInput->Render() }),
			hbox({ text("Final Grade: "), gradeInput->Render() }),
			separator(),
			text(confirmationText) | color(inputsValid ? Color::Green : Color::Red),
			separator(),
			hbox({ filler(), addButton->Render(), filler() }),
			hbox({ filler(), backButton->Render(), filler() })
			});
		});

	screen.Loop(renderer);
	activeScreen = MenuScreen;
}

Color Tui::inputBgColor(bool isValid)
{
	if (isValid)
		return Color::Black;
	return Color::Red;
}

void Tui::showAllStudentsScreen()
{
	Component backButton = Button("Back", screen.ExitLoopClosure());

	std::vector<Element> listOfElements;

	for (int i = 0; i < smartArray.size(); ++i) {
		listOfElements.push_back(hbox({ text(std::to_string(i + 1) + ". "), 
			paragraph(smartArray[i].printStudent())}));
	}

	float scrollY = 0.1;
	
	Component renderer = Renderer(backButton, [&] {
		return vbox({
			hbox({text("Names")}),
			hbox({vbox(listOfElements) | focusPositionRelative(0 , scrollY) | frame | flex,
				gaugeDown(scrollY) | flex
			}) | flex,
			hbox({filler(), backButton->Render(), filler()}) | size(HEIGHT, EQUAL, 3)
		});
	});

	renderer |= CatchEvent([&](Event event) {
		if (event == Event::PageUp) {
			scrollY = std::max(0.2, scrollY - 0.1);
			return true;
		}
		else if (event == Event::PageDown) {
			scrollY = std::min(0.8, scrollY + 0.1);
			return true;
		}
		return false;
		});


	screen.Loop(renderer);
	activeScreen = MenuScreen;
}

void Tui::run()
{
	while (activeScreen != Exit) {
		switch (activeScreen)
		{
		case Tui::MenuScreen:
			showMenu();
			break;
		case Tui::HelloWordldScreen:
			showHelloWorldScreen();
			break;
		case Tui::ShowInput:
			showInputScreen();
			break;
		case Tui::ShowScrollable:
			showAllStudentsScreen();
			break;
		default:
			std::cout << "Unknown screen" << std::endl;
			activeScreen = Exit;
			break;
		}
	}
}
