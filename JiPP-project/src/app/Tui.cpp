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

void Tui::showAllStudents()
{

}

void Tui::showInputScreen()
{
	Component backButton = Button("Back", screen.ExitLoopClosure());

	std::string name;
	std::string lastname;
	std::string ageStr;
	int age;
	bool ageIsCorrect;

	InputOption inputOption;
	inputOption.on_change = [&] {
		try {
			age = std::stoi(ageStr);
			ageIsCorrect = true;
		}
		catch (...) {
			ageIsCorrect = false;
		}
	};

	Component nameInput = Input(&name);
	Component lastnameInput = Input(&lastname);
	Component ageInput = Input(&ageStr, inputOption);

	ageInput |= CatchEvent([&](Event event) {
		return event.is_character() && !std::isdigit(event.character()[0]);
	});

	Component navigation = Container::Vertical({
		nameInput,
		lastnameInput,
		ageInput,
		backButton
	});

	Component renderer = Renderer(navigation, [&] {
		return vbox({
				hbox({text("Name: "), nameInput->Render()}),
				hbox({text("Last Name: "), lastnameInput->Render()}),
				hbox({text("Age: "), ageInput->Render()}) | bgcolor(inputBgColor(ageIsCorrect)),
				separator(),
				text("Name: " + name),
				text("Last Name: " + lastname),
				text("Age: " + ageStr),
				hbox({filler(), backButton->Render(), filler()})
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

void Tui::showScrollableScreen()
{
	Component backButton = Button("Back", screen.ExitLoopClosure());
	
	std::vector<std::string> name = {
		"Anna", "Jan", "Katarzyna", "Piotr", "Maria", "Tomasz",
		"Agnieszka", "Micha�", "Joanna", "Krzysztof", "Magdalena", "Pawe�",
		"Ewa", "Adam", "Aleksandra", "Mateusz", "Natalia", "Marcin",
		"Barbara", "�ukasz", "Julia", "Jakub", "Zofia", "Szymon",
		"Karolina", "Grzegorz", "Monika", "Dawid", "Weronika", "Rafa�"
	};

	std::vector<Element> listOfElements;

	for (int i = 0; i < name.size(); ++i) {
		listOfElements.push_back(hbox({ text(std::to_string(i + 1) + ". "), text(name[i]) }));
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
			showScrollableScreen();
			break;
		default:
			std::cout << "Unknown screen" << std::endl;
			activeScreen = Exit;
			break;
		}
	}
}
