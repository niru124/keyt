//menu
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

#include "ftxui/component/event.hpp"          // for Event
#include "ftxui/component/mouse.hpp" // for Mouse, Mouse::Left, Mouse::Middle, Mouse::None, Mouse::Pressed, Mouse::Released, Mouse::Right, Mouse::WheelDown, Mouse::WheelUp

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;
using namespace ftxui;

static vector<int>change(256,-1);  
const char *device = "/dev/input/event16"; // Adjusted accordingly to script
vector<int> keyState(256, 0);
ScreenInteractive screen = ScreenInteractive::Fullscreen();


Element make_box(int dimx, int dimy, string inside, int keycode) {
    int state = keyState[keycode];

    auto box = border(text(" " + inside + " ") | hcenter) |
               size(WIDTH, EQUAL, dimx) |
               size(HEIGHT, EQUAL, dimy);

    if (state == 2) {
        box |= color(Color::RGB(255,255,255)); // Pressed
        change[keycode]=1;
    } else if (state == 1) {
        box |= color(Color::Green);  // Released recently
        change[keycode]=1;
    } else {
        box |= color(Color::Red);    // Idle
    }

    return box;
}

void readKeyboardInput() {
    int fd = open(device, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        cerr << "Failed to open device: " << device << endl;
        return;
    }

    struct input_event ev;
    while (true) {
        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
        if (bytesRead > 0 && ev.type == EV_KEY) {
            if (ev.value == 1) { 
                keyState[ev.code] = 2; 
                screen.PostEvent(Event::Custom);
            } else if (ev.value == 0) { 
                keyState[ev.code] = 1; 
                screen.PostEvent(Event::Custom);
            }
        }
        usleep(5000);
    }
}


int main() {
    // thread inputThread(readKeyboardInput2);
    thread inputThread(readKeyboardInput);
    // auto screen = ScreenInteractive::TerminalOutput();
    std::vector<std::string> entries = {
     "60% keyboard",
    "75% keyboard",
    "100% keyboard",
    };
    int selected = 0;
    auto menu = Menu({
        .entries = &entries,
        .selected = &selected,
    });
    screen.Loop(menu);
    
    Component renderer;
    switch(selected){
        case 0:
            // cout<<"You Selected 60% keyboard"<<endl;

        renderer = Renderer([] {
        return hflow(vbox(
            {
             hbox({make_box(6, 3, "~",41), make_box(6, 3, "1",2), make_box(6, 3, "2",3),
                   make_box(6, 3, "3",4), make_box(6, 3, "4",5), make_box(6, 3, "5",6),
                   make_box(6, 3, "6",7), make_box(6, 3, "7",8), make_box(6, 3, "8",9),
                   make_box(6, 3, "9",10), make_box(6, 3, "0",11), make_box(6, 3, "-",12),
                   make_box(6, 3, "=",13), make_box(12, 3, "Backspace",14), text("  ")
                   }),
             hbox({make_box(9, 3, "Tab",15), make_box(6, 3, "Q",16), make_box(6, 3, "W",17),
                   make_box(6, 3, "E",18), make_box(6, 3, "R",19), make_box(6, 3, "T",20),
                   make_box(6, 3, "Y",21), make_box(6, 3, "U",22), make_box(6, 3, "I",23),
                   make_box(6, 3, "O",24), make_box(6, 3, "P",25), make_box(6, 3, "[",26),
                   make_box(6, 3, "]",27), make_box(9, 3, "\\",43), text("  "),
                   }),
             hbox({make_box(10, 3, "Caps",58), make_box(6, 3, "A",30),
                   make_box(6, 3, "S",31), make_box(6, 3, "D",32), make_box(6, 3, "F",33),
                   make_box(6, 3, "G",34), make_box(6, 3, "H",35), make_box(6, 3, "J",36),
                   make_box(6, 3, "K",37), make_box(6, 3, "L",38), make_box(6, 3, ";",39),
                   make_box(6, 3, "'",40), make_box(14, 3, "Enter",28)}),
             hbox({make_box(15, 3, "Shift",42), make_box(6, 3, "Z",44),
                   make_box(6, 3, "X",45), make_box(6, 3, "C",46), make_box(6, 3, "V",47),
                   make_box(6, 3, "B",48), make_box(6, 3, "N",49), make_box(6, 3, "M",50),
                   make_box(6, 3, ",",51), make_box(6, 3, ".",52), make_box(6, 3, "/",53),
                   make_box(15, 3, "Shift",126)
                   }),
             hbox({make_box(9, 3, "Ctrl",29), make_box(9, 3, "Win",125),
                   make_box(9, 3, "Alt",56), make_box(38, 3, "    Spacebar    ",57),
                   make_box(7, 3, "Alt",100), make_box(7, 3, "Ctrl",0)
                   })
            }));
            });
            break; 

        case 1:
            // cout<<"You Selected 75% keyboard"<<endl;

    renderer = Renderer([] {
        return hflow(vbox(
            {hbox({make_box(6, 3, "Esc",1), make_box(7, 3, "F1",59),
                   make_box(7, 3, "F2",60), make_box(7, 3, "F3",61), make_box(7, 3, "F4",62),
                   make_box(7, 3, "F5",63), make_box(7, 3, "F6",64), make_box(7, 3, "F7",65),
                   make_box(7, 3, "F8",66), make_box(7, 3, "F9",67),
                   make_box(7, 3, "F10",68), make_box(7, 3, "F11",87),
                   make_box(7, 3, "F12",88), text("  "), make_box(6, 3, "Prt",99),
                   make_box(6, 3, "Scr",0), make_box(6, 3, "Ply",0),make_box(6,3,"NL",0),make_box(6,3,"/",0),make_box(6,3,"*",0),make_box(6,3,"-",0)}),
             hbox({make_box(6, 3, "~",41), make_box(6, 3, "1",2), make_box(6, 3, "2",3),
                   make_box(6, 3, "3",4), make_box(6, 3, "4",5), make_box(6, 3, "5",6),
                   make_box(6, 3, "6",7), make_box(6, 3, "7",8), make_box(6, 3, "8",9),
                   make_box(6, 3, "9",10), make_box(6, 3, "0",11), make_box(6, 3, "-",12),
                   make_box(6, 3, "=",13), make_box(12, 3, "Backspace",14), text("  "),
                   make_box(6, 3, "Ins",0), make_box(6, 3, "Home",0),
                   make_box(6, 3, "PgUp",104)}),
             hbox({make_box(9, 3, "Tab",15), make_box(6, 3, "Q",16), make_box(6, 3, "W",17),
                   make_box(6, 3, "E",18), make_box(6, 3, "R",19), make_box(6, 3, "T",20),
                   make_box(6, 3, "Y",21), make_box(6, 3, "U",22), make_box(6, 3, "I",23),
                   make_box(6, 3, "O",24), make_box(6, 3, "P",25), make_box(6, 3, "[",26),
                   make_box(6, 3, "]",27), make_box(9, 3, "\\",43), text("  "),
                   make_box(6, 3, "Del",111), make_box(6, 3, "End",0),
                   make_box(6, 3, "PgDn",109)}),
             hbox({make_box(10, 3, "Caps",58), make_box(6, 3, "A",30),
                   make_box(6, 3, "S",31), make_box(6, 3, "D",32), make_box(6, 3, "F",33),
                   make_box(6, 3, "G",34), make_box(6, 3, "H",35), make_box(6, 3, "J",36),
                   make_box(6, 3, "K",37), make_box(6, 3, "L",38), make_box(6, 3, ";",39),
                   make_box(6, 3, "'",40), make_box(14, 3, "Enter",28)}),
             hbox({make_box(15, 3, "Shift",42), make_box(6, 3, "Z",44),
                   make_box(6, 3, "X",45), make_box(6, 3, "C",46), make_box(6, 3, "V",47),
                   make_box(6, 3, "B",48), make_box(6, 3, "N",49), make_box(6, 3, "M",50),
                   make_box(6, 3, ",",51), make_box(6, 3, ".",52), make_box(6, 3, "/",53),
                   make_box(15, 3, "Shift",126), text("        "),
                   make_box(6, 3, "↑",103)}),
             hbox({make_box(9, 3, "Ctrl",29), make_box(9, 3, "Win",125),
                   make_box(9, 3, "Alt",56), make_box(38, 3, "    Spacebar    ",57),
                   make_box(7, 3, "Alt",100), make_box(7, 3, "Ctrl",0),
                   text("             "),
                   make_box(6, 3, "←",105), make_box(6, 3, "↓",108),
                   make_box(6, 3, "→",106)})
            }));
    });
            break;

        case 2:

    renderer = Renderer([] {
        return hflow(vbox(
            {hbox({make_box(6, 3, "Esc",1), make_box(7, 3, "F1",59),
                   make_box(7, 3, "F2",60), make_box(7, 3, "F3",61), make_box(7, 3, "F4",62),
                   make_box(7, 3, "F5",63), make_box(7, 3, "F6",64), make_box(7, 3, "F7",65),
                   make_box(7, 3, "F8",66), make_box(7, 3, "F9",67),
                   make_box(7, 3, "F10",68), make_box(7, 3, "F11",87),
                   make_box(7, 3, "F12",88), text("  "), make_box(6, 3, "Prt",99),
                   make_box(6, 3, "Scr",0), make_box(6, 3, "Ply",0)}),
             hbox({make_box(6, 3, "~",41), make_box(6, 3, "1",2), make_box(6, 3, "2",3),
                   make_box(6, 3, "3",4), make_box(6, 3, "4",5), make_box(6, 3, "5",6),
                   make_box(6, 3, "6",7), make_box(6, 3, "7",8), make_box(6, 3, "8",9),
                   make_box(6, 3, "9",10), make_box(6, 3, "0",11), make_box(6, 3, "-",12),
                   make_box(6, 3, "=",13), make_box(12, 3, "Backspace",14), text("  "),
                   make_box(6, 3, "Ins",0), make_box(6, 3, "Home",0),
                   make_box(6, 3, "PgUp",104)}),
             hbox({make_box(9, 3, "Tab",15), make_box(6, 3, "Q",16), make_box(6, 3, "W",17),
                   make_box(6, 3, "E",18), make_box(6, 3, "R",19), make_box(6, 3, "T",20),
                   make_box(6, 3, "Y",21), make_box(6, 3, "U",22), make_box(6, 3, "I",23),
                   make_box(6, 3, "O",24), make_box(6, 3, "P",25), make_box(6, 3, "[",26),
                   make_box(6, 3, "]",27), make_box(9, 3, "\\",43), text("  "),
                   make_box(6, 3, "Del",111), make_box(6, 3, "End",0),
                   make_box(6, 3, "PgDn",109)}),
             hbox({make_box(10, 3, "Caps",58), make_box(6, 3, "A",30),
                   make_box(6, 3, "S",31), make_box(6, 3, "D",32), make_box(6, 3, "F",33),
                   make_box(6, 3, "G",34), make_box(6, 3, "H",35), make_box(6, 3, "J",36),
                   make_box(6, 3, "K",37), make_box(6, 3, "L",38), make_box(6, 3, ";",39),
                   make_box(6, 3, "'",40), make_box(14, 3, "Enter",28)}),
             hbox({make_box(15, 3, "Shift",42), make_box(6, 3, "Z",44),
                   make_box(6, 3, "X",45), make_box(6, 3, "C",46), make_box(6, 3, "V",47),
                   make_box(6, 3, "B",48), make_box(6, 3, "N",49), make_box(6, 3, "M",50),
                   make_box(6, 3, ",",51), make_box(6, 3, ".",52), make_box(6, 3, "/",53),
                   make_box(15, 3, "Shift",126), text("        "),
                   make_box(6, 3, "↑",103)}),
             hbox({make_box(9, 3, "Ctrl",29), make_box(9, 3, "Win",125),
                   make_box(9, 3, "Alt",56), make_box(38, 3, "    Spacebar    ",57),
                   make_box(7, 3, "Alt",100), make_box(7, 3, "Ctrl",0),
                   text("             "),
                   make_box(6, 3, "←",105), make_box(6, 3, "↓",108),
                   make_box(6, 3, "→",106)})
            }));
    });
    break;
    }

    screen.Loop(renderer);

    inputThread.join();
    return 0;
}
