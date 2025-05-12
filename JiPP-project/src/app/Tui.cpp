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
    Component addButton;

    std::string name, lastname, ageStr, indexStr, gradeStr;
    int age = 0;
    int indexNumber = 0;
    double finalGrade = 0.0;

    bool ageValid = false, indexValid = false, gradeValid = false;
    bool showStudent = false;
    Student newStudent;

    // Input validation
    InputOption ageOption, indexOption, gradeOption;

    ageOption.on_change = [&] {
        try {
            age = std::stoi(ageStr);
            ageValid = true;
        }
        catch (...) {
            ageValid = false;
        }
        };

    indexOption.on_change = [&] {
        try {
            indexNumber = std::stoi(indexStr);
            indexValid = true;
        }
        catch (...) {
            indexValid = false;
        }
        };

    gradeOption.on_change = [&] {
        try {
            finalGrade = std::stod(gradeStr);
            gradeValid = true;
        }
        catch (...) {
            gradeValid = false;
        }
        };

    // Input components
    Component nameInput = Input(&name);
    Component lastnameInput = Input(&lastname);
    Component ageInput = Input(&ageStr, ageOption);
    Component indexInput = Input(&indexStr, indexOption);
    Component gradeInput = Input(&gradeStr, gradeOption);

    // Block non-digit input where needed
    ageInput |= CatchEvent([&](Event e) {
        return e.is_character() && !std::isdigit(e.character()[0]);
        });

    indexInput |= CatchEvent([&](Event e) {
        return e.is_character() && !std::isdigit(e.character()[0]);
        });

    gradeInput |= CatchEvent([&](Event e) {
        return e.is_character() && !(std::isdigit(e.character()[0]) || e.character() == ".");
        });

    // Add button
    addButton = Button("Dodaj", [&] {
        if (!name.empty() && !lastname.empty() && ageValid && indexValid && gradeValid) {
            newStudent = Student(name, lastname, age, indexNumber, finalGrade);
            smartArray.pushBack(newStudent);
            showStudent = true;

            // Reset inputs
            name.clear();
            lastname.clear();
            ageStr.clear();
            indexStr.clear();
            gradeStr.clear();
            ageValid = indexValid = gradeValid = false;
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
        std::vector<Element> elements = {
            hbox({text("Name: "), nameInput->Render()}),
            hbox({text("Last Name: "), lastnameInput->Render()}),
            hbox({text("Age: "), ageInput->Render()}) | bgcolor(inputBgColor(ageValid)),
            hbox({text("Index Number: "), indexInput->Render()}) | bgcolor(inputBgColor(indexValid)),
            hbox({text("Final Grade: "), gradeInput->Render()}) | bgcolor(inputBgColor(gradeValid)),
            separator(),
            hbox({addButton->Render()}),
        };

        if (showStudent) {
            elements.push_back(text("Dodano studenta:"));
            elements.push_back(paragraph(newStudent.printStudent()));
        }

        elements.push_back(separator());
        elements.push_back(hbox({ filler(), backButton->Render(), filler() }));

        return vbox(elements);
        });

    screen.Loop(renderer);
    activeScreen = MenuScreen;
}

void Tui::removeStudentScreen()
{
    Component backButton = Button("Back", screen.ExitLoopClosure());
    Component removeButton;

    std::string indexStr;
    int indexNumber = 0;
    bool indexValid = false;
    bool studentRemoved = false;

    // Input validation for index
    InputOption indexOption;
    indexOption.on_change = [&] {
        try {
            indexNumber = std::stoi(indexStr);
            indexValid = true;
        }
        catch (...) {
            indexValid = false;
        }
        };

    Component indexInput = Input(&indexStr, indexOption);

    // Remove button
    removeButton = Button("Remove Student", [&] {
        if (indexValid) {
            bool found = false;
            // Iterate over smartArray to find student by indexNumber
            for (unsigned i = 0; i < smartArray.size(); ++i) {
                if (smartArray[i].indexNumber == indexNumber) {
                    smartArray.erase(i); // Remove student from SmartArray
                    studentRemoved = true;
                    found = true;
                    break;
                }
            }

            if (!found) {
                studentRemoved = false; // No student found with the given index
            }

            // Clear the input after removal attempt
            indexStr.clear();
            indexValid = false;
        }
        });

    Component navigation = Container::Vertical({
        indexInput,
        removeButton,
        backButton
        });

    Component renderer = Renderer(navigation, [&] {
        std::vector<Element> elements = {
            hbox({text("Enter Index Number to Remove: "), indexInput->Render()}),
            separator(),
            hbox({removeButton->Render()})
        };

        if (studentRemoved) {
            elements.push_back(text("Student removed successfully."));
        }
        else if (!studentRemoved && !indexStr.empty()) {
            elements.push_back(text("No student found with the given index."));
        }

        elements.push_back(separator());
        elements.push_back(hbox({ filler(), backButton->Render(), filler() }));

        return vbox(elements);
        });

    screen.Loop(renderer);
    activeScreen = MenuScreen;
}

void Tui::editStudentScreen()
{
    Component backButton = Button("Back", screen.ExitLoopClosure());
    Component editButton;

    std::string indexStr, name, lastname, ageStr, gradeStr;
    int indexNumber = 0, age = 0;
    double finalGrade = 0.0;

    bool indexValid = false, ageValid = false, gradeValid = false;
    bool studentFound = false;

    // Input validation for fields
    InputOption indexOption, ageOption, gradeOption;

    // Index input validation
    indexOption.on_change = [&] {
        try {
            indexNumber = std::stoi(indexStr);
            indexValid = true;
        }
        catch (...) {
            indexValid = false;
        }
        };

    // Age input validation
    ageOption.on_change = [&] {
        try {
            if (!ageStr.empty()) {  // Validate only if the age is provided
                age = std::stoi(ageStr);
                ageValid = true;
            }
            else {
                ageValid = true; // Empty field is valid
            }
        }
        catch (...) {
            ageValid = false;
        }
        };

    // Final grade input validation
    gradeOption.on_change = [&] {
        try {
            if (!gradeStr.empty()) { // Validate only if the grade is provided
                finalGrade = std::stod(gradeStr);
                gradeValid = true;
            }
            else {
                gradeValid = true; // Empty field is valid
            }
        }
        catch (...) {
            gradeValid = false;
        }
        };

    // Input components
    Component indexInput = Input(&indexStr, indexOption);
    Component nameInput = Input(&name);
    Component lastnameInput = Input(&lastname);
    Component ageInput = Input(&ageStr, ageOption);
    Component gradeInput = Input(&gradeStr, gradeOption);

    // Block non-digit input where needed
    ageInput |= CatchEvent([&](Event e) {
        return e.is_character() && !std::isdigit(e.character()[0]);
        });

    gradeInput |= CatchEvent([&](Event e) {
        return e.is_character() && !(std::isdigit(e.character()[0]) || e.character() == ".");
        });

    // Edit button
    editButton = Button("Edit Student", [&] {
        if (indexValid) {
            // Search for the student
            for (unsigned i = 0; i < smartArray.size(); ++i) {
                if (smartArray[i].indexNumber == indexNumber) {
                    // Student found, update their data
                    smartArray[i].name = name.empty() ? smartArray[i].name : name;
                    smartArray[i].lastName = lastname.empty() ? smartArray[i].lastName : lastname;
                    if (!ageStr.empty()) smartArray[i].age = age; // Only update if age is provided
                    if (!gradeStr.empty()) smartArray[i].finalGrade = finalGrade; // Only update if grade is provided

                    studentFound = true;
                    break;
                }
            }
        }
        });

    Component navigation = Container::Vertical({
        indexInput,
        nameInput,
        lastnameInput,
        ageInput,
        gradeInput,
        editButton,
        backButton
        });

    Component renderer = Renderer(navigation, [&] {
        std::vector<Element> elements = {
            hbox({text("Enter Index Number to Edit: "), indexInput->Render()}),
            hbox({text("Name: "), nameInput->Render()}),
            hbox({text("Last Name: "), lastnameInput->Render()}),
            hbox({text("Age: "), ageInput->Render()}) | bgcolor(inputBgColor(ageValid)),
            hbox({text("Final Grade: "), gradeInput->Render()}) | bgcolor(inputBgColor(gradeValid)),
            separator(),
            hbox({editButton->Render()})
        };

        if (studentFound) {
            elements.push_back(text("Student successfully updated."));
        }
        else if (indexValid && !studentFound) {
            elements.push_back(text("No student found with the given index."));
        }

        elements.push_back(separator());
        elements.push_back(hbox({ filler(), backButton->Render(), filler() }));

        return vbox(elements);
        });

    screen.Loop(renderer);
    activeScreen = MenuScreen;
}

void Tui::countStudentsScreen()
{
    Component backButton = Button("Back", screen.ExitLoopClosure());

    Component renderer = Renderer(backButton, [&] {
        return vbox({
            text("Total number of students: " + std::to_string(smartArray.size())),
            separator(),
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

void Tui::loadFromFileScreen() {
    std::string filename;
    bool loaded = false;

    Component input = Input(&filename, "Filename (e.g., students.bin)");

    Component loadButton = Button("Load", [&] {
        try {
            smartArray.loadFromFile(smartArray, filename);
            loaded = true;
        }
        catch (const std::exception& e) {
            loaded = false;
        }
        });

    Component backButton = Button("Back", screen.ExitLoopClosure());

    Component container = Container::Vertical({
        input,
        loadButton,
        backButton
        });

    Component renderer = Renderer(container, [&] {
        std::vector<Element> elements = {
            hbox(text("Enter filename to load: "), input->Render()),
            hbox({loadButton->Render()}),
            separator()
        };

        if (loaded) {
            elements.push_back(text("✔ Successfully loaded from file."));
        }
        else if (!filename.empty()) {
            elements.push_back(text("✘ Failed to load. Check file name or contents."));
        }

        elements.push_back(hbox({ filler(), backButton->Render(), filler() }));
        return vbox(elements);
        });

    screen.Loop(renderer);
    activeScreen = MenuScreen;
}

void Tui::saveToFileScreen() {
    std::string filename;
    bool saved = false;

    Component input = Input(&filename, "Filename (e.g., students.bin)");

    Component saveButton = Button("Save", [&] {
        try {
            smartArray.saveToFile(smartArray, filename);
            saved = true;
        }
        catch (const std::exception& e) {
            saved = false;
        }
    });

    Component backButton = Button("Back", screen.ExitLoopClosure());

    Component container = Container::Vertical({
        input,
        saveButton,
        backButton
    });

    Component renderer = Renderer(container, [&] {
        std::vector<Element> elements = {
            hbox(text("Enter filename to save: "), input->Render()),
            hbox({saveButton->Render()}),
            separator()
        };

        if (saved) {
            elements.push_back(text("✔ Successfully saved to file."));
        }

        elements.push_back(hbox({ filler(), backButton->Render(), filler() }));
        return vbox(elements);
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
        case Tui::DeleteStudent:
            removeStudentScreen();
            break;
        case Tui::EditStudent:
            editStudentScreen();
            break;        
        case Tui::CountStudents:
            countStudentsScreen();
            break;
        case Tui::SaveToFile:
            saveToFileScreen();
            break;
        case Tui::LoadFromFile:
            loadFromFileScreen();
            break;
		default:
			std::cout << "Unknown screen" << std::endl;
			activeScreen = Exit;
			break;
		}
	}
}
