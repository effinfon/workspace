#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <thread>
#include <filesystem>
namespace fs = std::filesystem;

#include "SFML_Utilitary.hpp"

/// TD
/* GENERAL OBJECTIVES

    dynamically render text (per frame, on modification, on resize, etc.)
        // saving the render state is also possible (since there is little if anything changing), and simply
            re-display the same buffer
        // keep a double buffer for when a change does occur, to have smooth transitions;
        // implement a framerate limiter (?)
        // ...
    have a user input thread and a rendering thread
        // the user input thread sends messages to the rendering thread
        // adjustable sleep cycles, but what about adaptive (*?)
        // the threads can terminate each other by sending signals [the other thread would then "listen" to the signal "when it can" (*?)]
        // (*!?) preferably, the call to start the editor is not blocking, so the program can actually go on as the editor runs in parallel;
            // this involves the management of the threads to be "object scoped" (if they are to be "function scoped", then it will block, or be terminated
                right after having been forked)
            // ...
        // ...
    ...
*/
/*  MANEUVERABILITY OF RENDERING

    before rendering, decide the arrangement of the textbox on [lines  (no, these are not lines)/] rows [rather, they are rows, indeed] (*?),
        do the necessary splits;
    textboxes need to be adjustable (movable, resizable -> font could automatically size down to fit, etc.)
        // eventually, another canvas will be integrated with the text / font rendering (*?)[slight differences: handwritting, glyphs, chinese kanji,
            special symbols and mathematical notations; these would also be used, and they are not exactly "text" (*?)] -> "text around box", "adjust left / right", etc.
        // ...
    ...
*/
/*  CHARACTERS SETS, ENCODINGS, FONTS

    multiple character sets (ANSI, UTF, Unicode, etc.) and encodings (Huffmann, etc.) supported (even simultaneously, but preferably defined
        "per collection type" <e.g.> std::vector<std::string<utf8>> or std::vector<std::string<ansi>>, etc.)
    multiple fonts (even simultaneously) [maybe multiple windows, each with its font ? or maybe comments use a specific font, then source code
        in for()/while() loops another font, global code another font, etc. (*?)]
    ...
*/
/*  LINE MANAGEMENT

    at the moment, each line gets a row; if the cursor ever reaches a "row margin", then an offest will be applied (when possible, <e.g.> it cannot be
        applied when at the beginning of the line or the end of the line)
    design possibilities:
        // (i) do not store a per-line offset, but instead offset the whole rendering
        // (ii) the offset of a line does not affect the other lines (thus need to store a per-line offset)
        // (iii)
    ...
*/
/*  LOGGING AND ERROR REPORTING-DIAGNOSTIC-HANDLING

    dts introspection
    (*?) thread logging:
        // chrono -> creating time, termination time, sleep time and awake time, etc.
        // allocated resourecs (*?)[memory used, CPU time per schedule, etc.]
    ...
*/
/*  CANVAS: MIXING TEXT-IMAGES-VIDEOS-EVERYTHING

    an image display canvas mixed in with the text
        // simple design: ~ Wolfram's / Mathematica's notebooks, such an image or video receives a row of its own
        // further: support for "overlays" (and layers of overlays) <e.g.> drawing with a pencil / stensil / brush, adding an audio recording,
            support for "hover over sub-space of image" or clicks or etc. -> event (which could be a text overlay, an audio player trigger, some script, etc.),
    (*!?) in-source code explanations: they might require video explanations, or scripted (interactive) diagrams of the assistant mechanisms, etc.
    (*!?) at other times, I wish I'd have control structures automatically re-written based on something that needs changing
        // (*) I need some examples for this
    ...
*/
/*  WRITTING - PATTERNS, "EDITOR ASSIST", ETC.

    tab:
        // a sort of "column alignment"
        // aligning all rows included in the selection to (??) -> syntax styling, "first previous occurence's expected alignment", the previous (Shift+Tab)
            or the next (Tab) "alignment column", (??) etc.
        // ...
    selection:
        // everything from the cursor to the left [ending at the beginning of the row / line (*?)] or to the right (ending at the end of the row / line)
        // the next or the previous "word" (*?)[there is a problem with "what a word should be" or "what a word would be efficient to be" -> (?) customizable
            (?"word / atom / word-block / ??"?)]
        // ...
    redo - undo:
        // ...
    scope alignment:
        // (*?) for starters, something like Python's syntax style
    (*?) sometimes I wish I could just box the text and move it around; at other times I wish I could just "take-out" source code and "put it besides", "making it inactive"
        as I go about writting something else or remaking the design; having "inactive code for reference is great; having multiple references is even better
    (*?) being able to copy reference code from the internet, to copy-paste into the active code or to jsut have it as a ~ "side-overlay" or something, etc.
    ...
*/
/*  EVENTS

    (*!?) the sleep - awake mechanism is not efficient if it's based on a fixed sleeping interval; it needs to do all the tasks that it can and then
        to go to sleep on its own; when it receives any tasks, it is also woken (in essence, a better use of interrupt mechanisms that the hardware provides)
    keyboard events:
        // multi-key support <e.g.> Shift+A or A+Shift (*?), Shift+Ctrl+Alt, Alt+Control+Delete
            // so, commutativity and associativity over the ordering are relevant
        // state bool for special characters (*?) <e.g> Ctrl+X Ctrl+V (*?)[do it by holding the Ctrl pressed, pressing X, releasing X, pressing Y, releasing Y, releasing Ctrl]
        // ...
    ...
*/
/*  CURSOR

    cursor's column attribute (or, seen as corresponding the index in the row's string)
        // the cursor places itself (/ draws itself) to the left of the index position in the row's string
        // by default, deleting is to the left of the cursor and writting is to the right
            // (*?) but, writting should be doable right to left as well (thus delete would be to the right)
            ...
        // ...
    ability to select text (*?)[in essence this means 2 points in 2Dim: the row and column of the beginning of the selection and the row and column of the end of the selection]
    ...
*/
/*  (SCROLLING WINDOW /) TEXT DISPLAY -> VIRTUAL WINDOW, design decisions


*/
/*  "KINDS OF FUNCTIONS" and CODE STRUCTURING, CODE ARRANGEMENT, "CODE GRAPH (STRUCTURE)"

    (*?) inline functions which are modularized for convenience of code reusability and arrangement
        <e.g.> when writting the event handling loop inside a function, I wanted to move it out of there and replace it with a call,
            but in essence I could also have just "collapsed all the text in an aesthetic way" as well (for example, it could instead get
            replaced by a "(fake) function call-like statement" (*?)
        <e.g.> ...
        // (*?) there is also the discussion about the mechanisms / possibility of maximizing code reuse, of utilizing "indirections" wherever change
            is expected (and thus ~ "centralizing the change to one single place and then `spreading` it to wherever needed"), minimizing "reformating /
            refactorization effort" (*?) [reformatting could be those cases where code / whole blocks of code get to be moved from one place to another,
            but checks about correctness are needed and it's hard to actually do it correctly in the first try, so it would help if there were mechanisms
            ...
        // ...
    ...
*/
struct Editor {
    sf::RenderWindow window {}; // callback functions interface (*?)

    inline static char const * title = "Editor";
    uint16_t width {640};
    uint16_t height {480};

    sf::Font font;
    sf::Text text;
    std::vector<std::string> rows {};
    std::string current_row {};
    std::vector<uint16_t> line_offset;

    struct Cursor {
        uint16_t row {};    // selects the row string
        uint16_t column {}; // or the index into the row's string
    } cursor;

    bool ShiftIsPressed {false};
    bool AltIsPressed {false};
    bool ControlIsPressed {false};

    Editor() {
        Init();
        MainLoop();
    }

    void Init() {
        window.create(sf::VideoMode(width, height), title);

        std::string path = fs::current_path();
        std::string font_file = "font/arial.ttf";
        printf("%s/%s\n", path.c_str(), font_file.c_str());

        if(!font.loadFromFile(font_file.c_str())) { printf("Error loading font\n"); }

        text.setFont(font);
        text.setCharacterSize(24);  // (*?) I need to know what does this size mean
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold|sf::Text::Underlined);
    }

    std::vector<std::string> StringToLines(std::string& string) {

    }
    std::vector<std::string> LinesToRows(std::vector<std::string>& lines) {
    }
    std::vector<std::string> StringToRows(std::string& string) {
        // now, there are two considered scenarios: (i) either a whole string is received as a function argument, case in which it has to be
            // analyzed and broken into lines first, then into rows, or (ii) the input is received through the event system, case in which
            // each character is received one at a time, so the separation into lines is done there
    }

    void RenderRow(uint16_t row, uint16_t offset_height_rows) { // the offset is measured in ["row heights"]
        text.setPosition(0, offset_height_rows * window.getSize().y * (1.0f));
    }

    void MainLoop() {
        std::string push_line {};

        while(window.isOpen()) {
            window.clear();

            for(auto row : rows) {
                text.setString(row);
                window.draw(text);
            }
            text.setString(current_row);
            window.draw(text);

            window.display();

            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type  == sf::Event::KeyPressed) {
                    // cursor none
                    if(SFML_Utilitary::toString(event.key.code) == "LShift" ||
                       SFML_Utilitary::toString(event.key.code) == "RShift") {
                            ShiftIsPressed = true;
                    } else if (SFML_Utilitary::toString(event.key.code) == "LAlt" ||
                                SFML_Utilitary::toString(event.key.code) == "RAlt") { // still have other characters to handle separately; then there are the multi-key characters such as Shift+A ('A') or Shift+, ('<'), etc.
                            AltIsPressed = true;
                    } else if (SFML_Utilitary::toString(event.key.code) == "LControl" ||
                                SFML_Utilitary::toString(event.key.code) == "RControl") { // still have other characters to handle separately; then there are the multi-key characters such as Shift+A ('A') or Shift+, ('<'), etc.
                            ControlIsPressed = true;
                    }
                    // cursor write
                    else if(SFML_Utilitary::toString(event.key.code) == "Return") {
                        current_row += "\n";

                        push_line = std::string(current_row);
                        rows.push_back(push_line);

//                        printf("current content of lines:\n");
//                        for(auto row : rows) { printf("%s\n", row.c_str()); }

                        current_row = std::string {};
                    } else if (SFML_Utilitary::toString(event.key.code) == "Space") {
                        current_row += " ";
                    } else if (SFML_Utilitary::toString(event.key.code) == "Tab") {
                        current_row += "\t";
                    } else if (SFML_Utilitary::toString(event.key.code) == "BackSpace") {
                        // (*?) how to turn this into an arithmetic expression
//                            current_row.resize(current_row.size() - 1 + ((current_row.size() == 0) ? 1 : 0));
                        if(current_row.size() == 0) {
                            // switch to the previous row
                            if(rows.size() > 0) {   // (*?) I am afraid of this causing ~ "mis-logic", since size() is unsigned anyway; this effectively
                                                    // only needs to be "size() != 0"
                                current_row = rows[rows.size() - 1];    // (*?) does this copy ?
                                rows.pop_back();  // initially it just moves back a line, the next backspace will
                                                                // actually consume a character
                            }
                        } else {    // delete content from the currrent row -> need to integrate with a cursor
                            current_row.resize(current_row.size() - 1);
                        }
                    } else if (SFML_Utilitary::toString(event.key.code) == "...") { // still have other characters to handle separately; then there are the multi-key characters such as Shift+A ('A') or Shift+, ('<'), etc.
                    } else if (SFML_Utilitary::toString(event.key.code) == "...") {
                    } else if (SFML_Utilitary::toString(event.key.code) == "...") {
                    } else if (SFML_Utilitary::toString(event.key.code) == "Escape") {
                        window.close();
                    } else {
                        if(ShiftIsPressed) {
                            current_row += SFML_Utilitary::toString(event.key.code);
                        } else {
                            std::string temp = SFML_Utilitary::toString(event.key.code);    // I simply hate not being able to work directly with a char... what's with all this overhead (?!)
                            temp[0] = tolower(temp[0]); // I don't know how portable this is, but it better work
                            current_row += temp;
                        }
//                    printf("%s\n", current_row.c_str());
                    }
                } else if(event.type == sf::Event::KeyReleased) {
                    if(SFML_Utilitary::toString(event.key.code) == "LShift" ||
                       SFML_Utilitary::toString(event.key.code) == "RShift") {
                        ShiftIsPressed = false;
                       }
                }

                // cursor delete
                if(true) {}
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(7));
        }
    }
};

struct Editor_MultiThreaded {
    bool RenderThreadShouldBeAlive {true};
    bool UserListenerThreadShouldBeAlive {true};
    std::thread UserListenerThread;
    std::thread RenderThread;

    sf::RenderWindow window {}; // callback functions interface (*?)

    inline static char const * title = "Editor";
    uint16_t width {640};
    uint16_t height {480};

    std::vector<std::string> text_lines {};
    std::vector<uint16_t> line_offset;

    struct Cursor {
        uint16_t pos_row {};
        uint16_t pos_col {};
    } cursor;

    Editor_MultiThreaded() {
        Init();
        Start();
    }
    ~Editor_MultiThreaded() {
        Stop();
    }

    void Init() {
    }

    void Start() {  // effectively start them up, fork the threads and set their arguments (if any) and entry points
        UserListenerThread = std::thread(UserListenerEntryPoint, this);
        RenderThread = std::thread(RenderEntryPoint, this);
        printf("Threads initialized\n");
    }

    void Stop() {   // just send some signals
        RenderThreadShouldBeAlive = false;
        UserListenerThreadShouldBeAlive = false;

        UserListenerThread.join();
        RenderThread.join();
        printf("Threads stopped\n");
    }

    static void UserListenerEntryPoint(Editor_MultiThreaded* editor_alias) {
        // declare, allocate, initialize, etc.
        Editor_MultiThreaded& editor = *editor_alias;

        // execute
        while(editor.UserListenerThreadShouldBeAlive) {

            printf("UserListener - Alive: %b\n", editor.UserListenerThreadShouldBeAlive);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        // free / clean
    }

    static void RenderEntryPoint(Editor_MultiThreaded* editor_alias) {
        // declare, allocate, initialize, etc.
        Editor_MultiThreaded& editor = *editor_alias;

        sf::RenderWindow window;
        window.create(sf::VideoMode(editor.width, editor.height), editor.title);

//        window.setActive(true);

        std::string path = fs::current_path();
        std::string font_file = "font/arial.ttf";
        printf("%s/%s\n", path.c_str(), font_file.c_str());

        sf::Font font;
        if(!font.loadFromFile(font_file.c_str())) { printf("Error loading font\n"); }

        sf::Text text;
        text.setFont(font);
        text.setString("Blabladnflvnehkbwcgkjgbqwjrgwbrqcwbhkrnwrhn\nbweucgbwuucgwbgcwjwecr\nwcwe13123");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold|sf::Text::Underlined);

        // execute
        while(editor.RenderThreadShouldBeAlive) {
            window.clear();
            window.draw(text);
            window.display();

            printf("Renderer - Alive: %b\n", editor.RenderThreadShouldBeAlive);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        // free / clean
    }
};

#endif // EDITOR_HPP_INCLUDED
