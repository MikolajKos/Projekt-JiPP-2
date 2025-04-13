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
    Tui tui;
    tui.run();



    return 0;

    //auto screen = ScreenInteractive::Fullscreen();
    //Component closeButton = Button("Close", screen.ExitLoopClosure());

    //Component renderer = Renderer(closeButton, [&] {
    //    return vbox({
    //    text("Hello World!"),
    //    closeButton->Render()
    //        });
    //    });

    //screen.Loop(renderer);
    //return 0;
    
    //Student student1("Jan", "Kowalski", 20, 12345, 4.5);
    //Student student2("Anna", "Nowak", 22, 67890, 4.8);
    //SmartArray<Student> studenci;

    //studenci.pushBack(student1);
    //studenci.pushBack(student2);

    //for (unsigned i = 0; i < studenci.size(); ++i) {
    //    studenci[i].wypiszInformacje();
    //    std::cout << std::endl;
    //}

    //studenci.erase(0);

    //for (unsigned i = 0; i < studenci.size(); ++i) {
    //    studenci[i].wypiszInformacje();
    //    std::cout << std::endl;
    //}

    //return 0;
}