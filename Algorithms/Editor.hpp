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
    (*?) I think that textboxes should be the focus of rendering text
        // thus, there can be multiple textboxes, they can be moved around, rotated, etc.
        // each textbox will keep its own history of the cursor
        // (*?) there should be only one or (possibly) multiple ("active") cursors ?
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
    lines can be horizontal, as well as vertical; text can also be mirrored, or written right to left, or ?? (*!?)
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
/*  WRITTING - PATTERNS, "EDITOR ASSIST", CURSOR MOVEMENTS, ETC.

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
    (*?) being able to copy reference code from the internet, to copy-paste into the active code or to just have it as a ~ "side-overlay" or something, etc.
    it is often the case that I have to reuse code which I copy-paste, but I'd rather that the comments not be included
        // hide (all / certain) comments, show (all / certain) comments; then idem for to-do lists, ?? etc.
    (*?) when switching up and down, to remember the last column position that the cursor had in on that row
        // (i) keep track of a fixed-length history
        // (ii) keep track of the history for all rows (this information can be saved in a file, together with the other data such as the text, or not saved)
    go up, at the beginning of the above row; go down at the beginning of the underneath row; and then vice-versa for the end of the row
        <e.g.> if you are at the end of a row, pressing Down will take you to the beginning of the next row and pressing Right will take you to the end of the next row
    (*!?) the ability to integrate bug / error reports into the project (and their solutioning); it should be able to include before->after source code - project wide diff actually !,
        the option to create / open, to close, and to re-open, ?? etc.
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
            but in essence I could also have just "collapsed all the text in an aesthetic way" as well [for example, it could instead get
            replaced by a "(fake) function call-like statement" (*?)]
        <e.g.> ...
        // (*?) there is also the discussion about the mechanisms / possibility of maximizing code reuse, of utilizing "indirections" wherever change
            is expected (and thus ~ "centralizing the change to one single place and then `spreading` it to wherever needed"), minimizing "reformating /
            refactorization effort" (*?) [reformatting could be those cases where code / whole blocks of code get to be moved from one place to another,
            but checks about correctness are needed and it's hard to actually do it correctly in the first try, so it would help if there were mechanisms
            ... ]
        // ...
    ...
*/
/*  PROGRAMMING: NEW CONTROL STRUCTURES (?)

    (*?) I need a control structure in which there are (possibly) multiple ~ "flags" / "states", (basically the same as /) similar to switches, in which if
        certain keys are pressed certain actions occur, but then that they all be followed by a particular ~ "post-effect" (*?); this post-effect only occurs
        for a particular "switch case", and each switch case can have its own post-effect; it is desired that I do not have to precede the switch cases by a
        condition, because the condition is one of the conditions inside the switch case (*?) [I think that essentially this would be the munade work I'd have to
        otherwise do; the other option is that I'd have to write in each if() statement's body the post-effect, after the corresponding "action"]
*/
/*  GEPHI

    Gephi is an open source software for graph and networkanalysis.   It  uses  a  3D  render  engine  to  display  largenetworks in real-time and to speed up the exploration.A flexible and multi-task architecture brings new pos-sibilities to work with complex data sets and producevaluable visual results. We present several key featuresof Gephi in the context of interactive exploration andinterpretation of networks.  It provides easy and broadaccess to network data and allows for spatializing, fil-tering, navigating, manipulating and clustering. Finally,by presenting dynamic features of Gephi, we highlightkey aspects of dynamic network visualization
    In  the  aim  of  understanding  networks,  the  visualizationof  large  graphs  has  been  developed  for  many  years  inmany  successful  projects  (Batagelj  1998;  Shannon  2003;Adar 2006). Visualizations are useful to leverage the percep-tual abilities of humans to find features in network structureand data.   However this process is inherently difficult andrequires exploration strategy (Perer 2006). As well as beingtechnically accurate and visually attractive, network explo-ration tools must head toward real-time visualizations andanalysis  to  improve  the  user’s  exploratory  process.   Inter-active techniques have successfully guided domain expertsthrough the complex exploration of large networks.We can identify some main requirements for a networkexploration tool:  high quality layout algorithms, data filter-ing,  clustering,  statistics and annotation.
    Developed  modules  can  import,  visualize, spatialize, filter, manipulate and export all types of net-works.  The visualization module uses a special 3D renderengine to render graphs in real-time.   This technique usesthe computer graphic card,  as video games do,  and leavesthe CPU free for other computing.   It can deal with largenetwork (i.e.  over 20,000 nodes) and, because it is built ona multi-task model, it takes advantage of multi-core proces-sors.
    Node design can be personalized, instead of a classicalshape it can be a texture, a panel or a photo.
    Highly con-figurable layout algorithms can be run in real-time on thegraph window.  For instance speed, gravity, repulsion, auto-stabilize, inertia or size-adjust are real-time settings of theForce Atlasalgorithm, a special force-directed algorithm de-veloped by our team.
    Several algorithms can be run in thesame time, in separate workspaces without blocking the userinterface
    The text module can show labels on the visualiza-tion window from any data attribute associated to nodes.  Aspecial algorithm namedLabel Adjustcan be run to avoidlabel overlapping.
    Sets of nodes or edgescan be obtained manually or by using the filter system.
        // programmability in C/C++
    Filters  can  select  nodes  or  edges  with  thresholds,  range  andother properties.  In practice filter boxes are chained, eachbox take in input the output of the upper box.   Thus,  it iseasy to divide a bi-partite network or to get the nodes thathave an in-degree superior to 5 and the property ”type” setto ”1”.
    Because the usefulness of a network analysis oftencomes from the data associated to nodes/edges, ordering andclustering can be processed according to these values
    For sets of nodes, graphical modules likeSize Gradient,ColorGradientorColor clusterscan  then  be  applied  to  changethe network design.  Graphical modules take a set of nodesin input and modify the display parameters,  like colors orsize, to corroborate understanding of the network structureor content.
    Exploring dynamicnetworks  in  an  easy  and  intuitive  way  has  been  incorpo-rated in Gephi from the beginning. The architecture supportsgraphs whose structure or content varies over time, and pro-pose a timeline component where a slice of the network canbe retrieved.  From the time range of the timeline slice, thesystem queries all nodes and edges that match and updatethe visualization module.  Hence a dynamic network can beplayed as movie sequences.
    The dynamic module can get network data from either acompatible graph file or from external data sources.  Whenrunning, a data source can send network data to the dynamiccontroller  at  any  time  and  immediately  see  the  results  onthe visualization module. For instance a web-crawler can beconnected to Gephi in order to see the network constructionover time. The architecture is interoperable and data sourcecan be created easily to communicate with existing software,third parties databases or web-services.
    Though the core of the software already exists, further workis required for the development of new features, especiallyfilters, statitics and tools
     A special focus is made on clus-tering and hierarchical networks.  Improvements will be in-tegrated to the data structure to support grouping and navi-gation within a network hierarchy.  As for spatialization al-gorithms, a framework will be able to host various classifi-cation algorithms.
     Gephihas  been  successfully  used  for  Internet  link  and  semanticnetwork  case  studies.   It  is  also  frequently  used  for  SNA.An effort has been made to speed up the analysis process,from data import to map export. Gephi is developed towardsupporting the whole process with only user interface ma-nipulation.  The developement of dynamic features are alsoone of the top priorities.

*/

struct Editor {
    struct TextBox {
        struct Cursor {};
        struct Caret {};

        std::vector<std::string> content { std::string() };

    };

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
        sf::Image image;
        sf::Sprite sprite;

        Cursor() {
            // create the image for the sprite, using a "function" instead of loading it from a file (it's just a rectangle of the same color as the text...)
        }

        operator sf::Sprite& () {
            return sprite;
        }

    } cursor;

    bool ShiftIsPressed {false};
    bool AltIsPressed {false};
    bool ControlIsPressed {false};

    Editor() {
        Init();
        MainLoop();
    }

        // (*?) if the cursor is hovering, then the writting color will be the complementary of the current text color, and the cursor's
            // sprite will be a rectangle the size of the font
    bool CursorIsHoveringOver(uint16_t row, uint16_t col) {
        if(cursor.row == row && cursor.column == col)
            return true;
        else
            return false;
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
        text.setStyle(sf::Text::Regular);
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
                    // cursor no-move
                    if(SFML_Utilitary::toString(event.key.code) == "LShift" || SFML_Utilitary::toString(event.key.code) == "RShift") {
                        ShiftIsPressed = true;
                    } else if (SFML_Utilitary::toString(event.key.code) == "LAlt" ||
                               SFML_Utilitary::toString(event.key.code) == "RAlt") { // still have other characters to handle separately; then there are the multi-key characters such as Shift+A ('A') or Shift+, ('<'), etc.
                        AltIsPressed = true;
                    } else if (SFML_Utilitary::toString(event.key.code) == "LControl" ||
                               SFML_Utilitary::toString(event.key.code) == "RControl") { // still have other characters to handle separately; then there are the multi-key characters such as Shift+A ('A') or Shift+, ('<'), etc.
                        ControlIsPressed = true;
                    } else if (SFML_Utilitary::toString(event.key.code) == "Escape") {
                        window.close();
                    }
                }
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
