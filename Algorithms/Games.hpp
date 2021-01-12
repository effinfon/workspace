#ifndef GAMES_HPP_INCLUDED
#define GAMES_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include <thread>
#include <chrono>
#include <mutex>
#include <random>

/// TODO
    // these are to be used for developing (A)AI players, defining "concepts" and "abstractions" needed for (A)AI architecture
/*
    Chess
    Go
    Pacman
    Tetris
    Life Cellular Automata -> this one is very important; it starts by fixing which cellular automaton is being used, and yet it's still "Turing complete";
        next, the state-space is potentially infinite / "arbitrarily large" [there would be an interesting case, a space that grows dynamically, probably
        much like our universe; things could "spread out into space", maybe at some point meet and annihilate reducing the need to compute that space anymore (!?),
        but I do not see how anything could catch up to a pixel that has started moving earlier than the one trying to catch -> similar to how light works; except,
        what about the "space itself", how could it "warp / deform" (?!) while considering that it is a discrete space (*?)]
    custom TB-RPG ~ final fantasy's "select your action" / Pokemon games for Nintendo or that "infinite tower climber (`ranker`)"
    Minesweeper
    Tic-Tac-Toe
    Snake
    "Ray reflector in a box" (with "self-continuing state-space")

*/
/*  SETTINGS (MENU)

    keyboard mapping:
        // character set,...
        // mapping a particular Keyboard.code to a particular action (or said inversely, assigning Keyboard.code's to actions <e.g.> Crouch: C / RSHIFT, etc.)
*/

// (*?) need a mechanism for specifying different "variants" for an abstraction / "thing" / "concept" / "function" / "struct" / "implementation", etc (!?)
// <e.g.> for now, ConwayLife will be using a static (discrete) state-space / "map", but eventually it will be able to adapt dynamically (and maybe use a non
    // 2Dim array state-space as well (*!?) [maybe graph-based, or sparse-matrix ?]

// (*?) need an abstraction for "border constraint (checker)", for when iterating over spaces that are bounded, such as a chess table, ConwayLife state-space,
    // a matrix, a bitmap, ect.; the general problem is that of "adjacency"; but do also think about "borders of self-continuing (discrete) state-spaces", such
    // as some variants of $Snake

namespace Games {

struct ConwayLife {
    // let's start with a 64 by 64 state-space, such as to have a square space but also utilize the register memory well
    // this will involve bit operations
    uint64_t initial_state_space[64] {};   // used for resets, if they will be needed at all actually

/*
    uint64_t current_state_space[64];   // instead of copying into one another, these should be used as double buffers
    uint64_t next_state_space[64];
*/
    uint64_t state_space[2][64] {};
    uint8_t work_buffer {1};

    ConwayLife() {}
    ConwayLife(uint64_t initial_state_space[64]) /* state_space(initial_state) */ /* doesn't work */ { // (*?) if only C++ has array-op syntax to hard- / soft- copy this in a single sub-expression... or does it already, since they're references ?
        for(uint8_t idx {0}; idx < 64; idx++) { // 8 bit index -> very good loop unwrapping; but, the act ion inside the loop, how parallelizable is that ? it's a 64 bit memory move... so
                        // unless specialized hardware can buffer the instruction or prefetch it (as it is quite "static"), maybe
            this->state_space[0][idx] = initial_state_space[idx];
            this->initial_state_space[idx] = initial_state_space[idx];
        }
    }

    void Reset() {
        work_buffer = 1;
        for(uint8_t idx {0}; idx < 64; idx++) {
            state_space[0][idx] = initial_state_space[idx];
            state_space[1][idx] = 0;
        }
    }
    // (*?) this doesn't forcefully Reset() though, it only sets the initial_state_space for when a reset
        // will be manually called, if it will be called
    void SetInitialSpace(uint64_t initial_state_space[64]) {
        for(uint8_t idx {0}; idx < 64; idx++) {
            this->initial_state_space[idx] = initial_state_space[idx];
        }
    }

    // (*?) I think there supposedly was a way to make the compiler think that these two values need to be kept in the registers
    // in actuality, when this function is called, it should keep therow_value in the register as it will be used 64 bitmes, again and again;
    // (!?) I wonder if it would be any use to "reverse" the operation on the bitmask (but memorizing the number of steps to multiply by 2 also
        // requires memory, so it would seem that the particularities of the ~ "memory traffic complexity space" would determine how to optimize
        // this (for example, whether to store a const copy of bitmask and a varying one
    uint8_t GetCellState(uint8_t row, uint8_t col) {    // cell-state corresponds to a bit in the 64 bit register / word
        // (*?) this is just like with Vulkan vs OpenGL; I here intend to tell the compiler more about what I intend, but there is no mechanism to
            // give it such a "search-space hint" (!?); it is these things that make me think sometimes that even these general-purpose languages,
            // as Turing complete as they are, they do not "invariantly translate" / "translate `well`" all the time (*!?) [even so, turing compelte
            // they are, as they can indeed emulate each other; but the distinction is in the topology of the complexity map: "now there's a hill
            // where in the other language there wasn't" (!?)]
        /* static */ register const uint64_t original_bitmask {0b1000000000000000000000000000000000000000000000000000000000000000};
        uint64_t bitmask {original_bitmask};  // this should be a register sized bit pattern, with a 1 in the leftmost / MSb position
//        bitmask >> col;

        while(col--) bitmask /= 2;  // in my experience this works better; the bit shift... I don't know why it doesn't seem to do what I think it should; at least not with a uint_t
        /* static */ register uint64_t row_value = state_space[work_buffer ^ 1][row];   // a convention seems to be needed: the Get() will XOR the work_buffer, and the Set() will use it directly
        return (uint8_t) (bitmask & row_value);
    }
    bool IsAlive(uint8_t row, uint8_t col) {
        return (bool)GetCellState(row, col);    // (*?) it would seem that a typecast is essentially different somehow from calling a constructor (?)
                                                // <e.g.> (bool)Foo() !:= bool(Foo()) (?)
    }
    void SetCellState(uint8_t row, uint8_t col, uint8_t state) {
        if(state != 0) {
            uint64_t bitmask {0b1000000000000000000000000000000000000000000000000000000000000000};
            while(col--) bitmask /= 2;
            state_space[work_buffer][row] |= bitmask;
        } else {
            uint64_t bitmask {0b0111111111111111111111111111111111111111111111111111111111111111};
            const uint64_t add_back {0b1000000000000000000000000000000000000000000000000000000000000000};

                // (*?) effectively, I need a cyclic shift here
            while(col--) {
                bitmask /= 2;
                bitmask += add_back;
            }

            state_space[work_buffer][row] &= bitmask;
        }

    }
    void SpawnCell(uint8_t row, uint8_t col) {
        // let's have some checking too
        if(IsAlive(row, col)) {
            printf("Attempt to spawn cell [%d.%d] when it's already alive\n", row + 1, col + 1);
            return;
        } else {
            SetCellState(row, col, 1);
        }
    }
    void KillCell(uint8_t row, uint8_t col) {
        if(!IsAlive(row, col)) {
            printf("Attempt to kill cell [%d.%d] when it's already dead\n", row + 1, col + 1);
            return;
        } else {
            SetCellState(row, col, 0);
        }
    }
    void PropagateCellState(uint8_t row, uint8_t col) {
        SetCellState(row, col, GetCellState(row, col));
    }

    /// TD
    // this is where it's most likely to have gone wrong
    uint8_t CountAdjacency(uint8_t row, uint8_t col) {
        uint8_t result {0};

        if(row != 0) { result += GetCellState(row - 1, col); }
        if(row != 63) { result += GetCellState(row + 1, col); }
        if(col != 0) { result += GetCellState(row, col - 1); }
        if(col != 63) { result += GetCellState(row, col + 1); }
        if(row != 0 && col != 0) { result += GetCellState(row - 1, col - 1); }
        if(row != 0 && col != 63) { result += GetCellState(row - 1, col + 1); }
        if(row != 63 && col != 0) { result += GetCellState(row + 1, col - 1); }
        if(row != 63 && col != 63) { result += GetCellState(row + 1, col + 1); }

        return result;
    }

        // (*?) a better utilization of cell-state knowledge, minimizing "querry redundancy" -> this could result in certain "efficiency trajectories" through state-space (?)
            // it could be "necessary" (or on the contrary, "possible") to use multiple such trajectories, in parallel
        // (*?) to integrate the cell-state querry, the adjacency counter, the next cell-state compute / decision making and the state-space iterator
    void NextStateSpace() { // also, the Next() function has to also XOR= 1 the work_buffer
        for(uint8_t row_idx {0}; row_idx < 64; row_idx++) {
            for(uint8_t col_idx {0}; col_idx < 64; col_idx++) {
                if(IsAlive(row_idx, col_idx) && CountAdjacency(row_idx, col_idx) < 2) {
                    KillCell(row_idx, col_idx);
                } else if (IsAlive(row_idx, col_idx) && (CountAdjacency(row_idx, col_idx) == 2 || CountAdjacency(row_idx, col_idx) == 3)) {
                    PropagateCellState(row_idx, col_idx);
                } else if (IsAlive(row_idx, col_idx) && CountAdjacency(row_idx, col_idx) > 3) {
                    KillCell(row_idx, col_idx);
                } else if (!IsAlive(row_idx, col_idx) && CountAdjacency(row_idx, col_idx) == 3) {
                    SpawnCell(row_idx, col_idx);
                } else { ; }    // (*?) so this is the "space of static" / "static space"; it is in this space that "persistence" occurs; but, there
                                // is another kind of persistence, namely the "quasi-persistence", which occurs in the "dynamic space", with "periodic patterns" (!?)
            }
        }

        work_buffer ^= 1;
    }

    void TerminalPrint() {
        for(uint8_t row_idx {0}; row_idx < 64; row_idx++) {
            for(uint8_t col_idx {0}; col_idx < 64; col_idx++) {
                printf("%c ", ((IsAlive(row_idx, col_idx)) ? '1' : '0'));
            }   printf("\n");
        }
    }
    void ToBitmap() {   // this goes to OpenGL / Vulkan to be rendered

    }
};

// (*?) as it is, it can be used to load different sprites and move them around, maybe even makign circuits using some sort of collision detection
    // and functions that "merge" / "combine" colliding sprites, etc.
struct RPG {
    // (*!?) data from files should be loaded only once in memory and shared to all instances where it is used; and yet,
        // if there are "write use cases" (and not just "read use cases"

    inline static std::mutex mainWindow_access {};
    inline static bool terminate {false};   // (*?) multi-threading dynamic start / termination by using ~ signals (shared resources / shared memory / "global variables" to communicate)

    // (*?) the current design of the program has forced me to make these static, probably due
        // to the order in which things get initialized, or because there are structs whose initialization
        // makes use of variables that themselves need initialization, but actually get initializd when an
        // object gets constructed, and not when the type gets initialized; that poses a problem for the initialization
        // of the other types
    sf::RenderWindow mainWindow;
    inline static uint32_t mainWindow_width {};
    inline static uint32_t mainWindow_height {};
    inline static const char * mainWindow_title {"RPG 1a v0.1"};

    sf::Image background_img;
    sf::Texture background_tex;
    sf::Sprite background_spr;
    inline static const char * background_image_file_pathname {"img/background.jpeg"};

    struct RenderWindow {
//        inline static std::mutex mainWindow_access {};
//        inline static bool terminate {false};   // (*?) multi-threading dynamic start / termination by using ~ signals (shared resources / shared memory / "global variables" to communicate)

        sf::RenderWindow mainWindow;
        uint32_t width {};
        uint32_t height {};
        inline static const char * title {"RPG 1a v0.1"};

        sf::Image background_img;
        sf::Texture background_tex;
        sf::Sprite background_spr;

        inline static const char * background_image_file_pathname {"img/background.jpeg"};
    };

    struct IntroWindow {
        struct Text {
            sf::Font font;

            sf::Text game_title;
            sf::Text start_new_game;
            sf::Text options;
            sf::Text exit;
        };
        struct Animation {
            sf::Sprite sprite_box;
            sf::Texture* animations;
        };


    };

    struct Player {
        inline static const char * player_image_file_pathname {"img/player1.png"};

        inline static const uint8_t count_players {2};
        inline static const uint8_t count_positions /* directions */ = 4;   // order: left, right, up, down
        inline static const uint8_t texture_width {26}; // (*?) this data should be dynamically handled: contained by the image files, and this maybe optimized dynamically
        inline static const uint8_t texture_height[count_players] {28, 22};

        sf::Image player_img;
        sf::Texture player_tex_atlas[count_players][count_positions]; // order: left, right, up, down
        sf::Sprite player_spr[2];  // 26 x 28 or 26 x 22

        uint8_t current_player_sprite {0};

        enum SpriteDirection {
            Left = 0,
            Right,
            Up,
            Down,
        } sprite_direction { Down };

        enum SpriteAction {
            Attack = 0,
            Parry,
            Jump,
            Crouch,
        };

    public:
        Player() { Init(); }

        void Init() {
            player_img.loadFromFile(player_image_file_pathname);

            uint64_t texture_cummulated_height {0}; // (*?) to be used later

            for(uint8_t idx_player {0}; idx_player < count_players; idx_player++) {
                for(uint8_t idx_pos {0}; idx_pos < count_positions; idx_pos++) {

                    std::pair<int, int> topleft {};
                    topleft.first = 0 + idx_pos * texture_width;
                    topleft.second = 0 + idx_player * texture_height[0];    // (*?) texture_cummulated_height, which runs across $idx_player
                                                            // (*!?) this needs to be more general; all this complication is useless; images are
                                                            // themselves strings, everything is essentially 1Dim here (!), so make adjustments to the file format

                    std::pair<int, int> bottomright {};
                    bottomright.first = topleft.first + texture_width;
                    bottomright.second = topleft.second + texture_height[idx_player];   // (*?) this one will not have to do with cummulated height itself, because
                                                            // it's written in reference to a variable that already includs that

                    player_tex_atlas[idx_player][idx_pos].loadFromImage(player_img, sf::IntRect(topleft.first, topleft.second, bottomright.first, bottomright.second));
                }

                player_spr[idx_player] = sf::Sprite(player_tex_atlas[idx_player][3]);   // initialize in position looking Down
                // (*?) there is another thing to do with sprites that have different dimensions, namely to "adjust them according to the highest sprite"
                    // so that their bottom lines aligned
                // in this case, the adjustmne twill be done manually
                player_spr[1].move(0.0f, 6.0f);
            }
        }

        void TestInit(sf::RenderWindow* mainWindow, sf::Sprite* background_spr) {
            mainWindow_access.lock();
            mainWindow->clear();
            mainWindow->draw(*background_spr);
            mainWindow->draw(player_spr[0]);
            mainWindow->display();
            mainWindow_access.unlock();
            //std::this_thread::sleep_for(std::chrono::seconds(2));


            //std::this_thread::sleep_for(std::chrono::seconds(2));
            for(uint8_t idx {0}; idx < 255; idx++) {
                if(terminate) { std::terminate(); }

                player_spr[1].move(1.0f, 1.0f);
                mainWindow_access.lock();
                mainWindow->clear();
                mainWindow->draw(*background_spr);
                mainWindow->draw(player_spr[1]);
                mainWindow->display();
                mainWindow_access.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(80));
            }

        }


        void SwitchSprite() {
            current_player_sprite ^= 1;

        }

        void SetSpriteDirection(Player::SpriteDirection spriteDirection) {
            sprite_direction = spriteDirection;
            for(uint8_t idx_player {0}; idx_player < count_players; idx_player++) {
                player_spr[idx_player].setTexture(player_tex_atlas[idx_player][sprite_direction]);
            }
        }
        void RotateSprite(float degrees_360) {
            for(uint8_t idx_player {0}; idx_player < count_players; idx_player++) {
                player_spr[idx_player].rotate(degrees_360); // attention: clockwise rotation (!)
            }
        }

        void MoveSprite(float x, float y) {
            player_spr[current_player_sprite].move(x, y);
        }

        void AnimateAction(SpriteAction spriteAction) {
            switch(spriteAction) {
            case Attack:
                break;
            case Parry:
                break;
            case Jump:
                break;
            case Crouch:
                break;
            }
        }

        operator sf::Sprite& () {
            return player_spr[current_player_sprite];
        }
    };

    struct Obstacles {
        // (*?) this should be a lattice / discrete map, with some parametrization, which can ease, "type casting
            // abstraction" (this involves mapping from space to space, involving logic consistency and geometry and complexity and etc.),
            // the abstraction inbetween [thus a bijective transformation / bidirectional (graph) path] an array of "state numerics" (preferably bools)
            // and (an automatically generated sprite /) a sprite (which itself can be transformed back into an array of "state numberics")
        // (*!?) it now becomes apparent that a collision algorithm's problem space has some complex topologies in some cases (such as corridors; there
            // can be corridors through which the player sprite does not fit, for example)
        // for now, consider the case where the step is equal to the sprite's dimensions, the sprite is a square and the "walls" are also cells of the
            // same dimensions as the player sprite
        uint8_t* grid {nullptr};
        uint64_t count_cells {0};

        sf::Image black_rect;   // (*?) I wish I could create a 28 x 28 rect with transparency pixels and some opaque pixels in the center,
        sf::Image white_rect;   // but for now will import them from a file actually

        inline static const char * file_pathname_black {"img/wall_block_black.png"};
        inline static const char * file_pathname_white {"img/wall_block_white.png"};

        sf::Texture drawable_texture;
        sf::Sprite drawable_sprite;

        Obstacles(uint32_t width, uint32_t height, uint8_t cell_edge_length) {
            count_cells = width * height;
            grid = new uint8_t[count_cells];

                // perlin noise or something ? or a terrain-generation function
                // but for now, using a generic pseudo-random generator
                // (*?) actually, this would need to be a maze generator rather (well, it's the beginning for all sorts
                    // of "biomes", each with its parametrization of functions with certain properties (such as "traverability"
                    // or "existence of at least one path between two distinct `peripheral cells`", etc.)
            std::mt19937 random;
            for(uint64_t idx {0}; idx < count_cells; idx++) {
                grid[idx] = random() % 2;
            }

            InitSprite(width, height, cell_edge_length);
        }

        void InitSprite(uint32_t width, uint32_t height, uint8_t cell_edge_length) {
            printf("Debugging: Obstacles::InitSprite - function entry\n");

            // for now, no textures will be loaded, but instead color-filled rects will be generated
            black_rect.loadFromFile(file_pathname_black);
            white_rect.loadFromFile(file_pathname_white);
            printf("Debugging: Obstacles::InitSprite - loaded images\n");

            drawable_texture.create(width, height);
            printf("Debugging: Obstacles::InitSprite - width: %u, height: %u\n", width, height);

            uint32_t x;
            uint32_t y;

            for(uint32_t idx_row {0}; idx_row < height; idx_row++) {
                for(uint32_t idx_col {0}; idx_col < width; idx_col++) {
                    x = idx_col * cell_edge_length;
                    y = idx_row * cell_edge_length;

                    if(grid[idx_row * width + idx_col]) {   // black
                        drawable_texture.update(black_rect, x, y);
                    } else {    // white
                        drawable_texture.update(white_rect, x, y);
                    }
                }
            }

            printf("Debugging: Obstacles::InitSprite - function exit\n");
        }

        operator sf::Sprite& () {
            return drawable_sprite;
        }
    };

//    struct Player_v2 : public Player {  // (*?) use from the previously defined type, but overwrite some things; I wish one could also maybe remove things as well
                                        // (*!?) the interesting thing here would be to make use of the type system / proof assistant in ~ "replacing and versioning
                                        // types", such as in this case, adjusting struct Player for use with struct Wall, due to the need for square sprites; so the point
                                        // here is to have assistance from the type system in "substituting the type, with another type, and maintain correctness to
                                        // specifications" (well, "specifications" are really the "constraints" imposed by the actual usage of the type, such as it being
                                        // called in some functions, members of it being accessed, functions of it and on it being called, etc.); still, there is a discussion
                                        // to be had with all those "virtual members", which are a mechanism that is a little sort of "unrefined" and "insufficient"; the gist of
                                        // the idea is to mark those things which are not desired from the original type and those things which are desired to be changed, and
                                        // still have the type system proof assist the correctness, and report (helpful) errors for debugging and corrections of the implementation,
                                        // as per the specifications / constraints (!?)
                                        // (*?) basically, this sort of "refactoring" kind of thing seems to be a very important usage of the type system... (?) [discuss more on this]
    struct Player_v2 {
        // (*?) there will be only one sprite this time
        inline static const char * player_image_file_pathname {"img/player3.png"};
        inline static const uint8_t texture_edge_length {28};

        inline static const uint8_t count_players {2};
        inline static const uint8_t count_positions {1};

        enum SpriteDirection {
            Left = 0,
            Right,
            Up,
            Down,
        } sprite_direction { Left };

        enum SpriteAction {
            Attack = 0,
            Parry,
            Jump,
            Crouch,
        };

        sf::Texture player_tex;
        sf::Sprite player_spr;

        uint16_t position[2] {0, 0};    // (*?) this other localization / coordinate system is what will be used for collision detection, at the moment
        Obstacles* obstacles;

    public:
        // (*?) an interesting detail is that I do not have to write this; actually, I fear that writting this will result in the double execution
            // of Init(); well, actually it also seems that the inherited constructor calls the previous version of Init();, and that is a problem (!?)
            // which I think can only be solved by not inheriting... (?)

        Player_v2() {
            printf("Debuggin: Player_v2::Init() - function entry\n");

            player_tex.loadFromFile(player_image_file_pathname);
            player_spr.setTexture(player_tex);


            obstacles = new Obstacles((mainWindow_width / texture_edge_length) * texture_edge_length, (mainWindow_height / texture_edge_length) * texture_edge_length, texture_edge_length);
            printf("Debugging: Player_v2::Init() - function exit\n");
        }

//        ~Player_v2() {
//            if(obstacles != nullptr)
//                delete obstacles;
//        }

        // (*?) I was half-expecting this to be a redefinition error, but it isn't; why ? does this overwrite the previous definition in the inheritance ?
        void Init() {
        }

        void MoveSprite(float x, float y) {
            // (*?) irrespective of the input, it will only look at the signs and move "discretely",
                // without having to change anything in the event loop itself, or the functions that
                // generate the inputs, etc.
            /// TD
            /*
                "discrete (map and step) collision detection"
            */
            if(x < 0.0f) {
                player_spr.move(-texture_edge_length, 0.0f);
            }
            else if(x > 0.0f) {
                player_spr.move(+texture_edge_length, 0.0f);
            }

            if(y < 0.0f) {
                player_spr.move(0.0f, -texture_edge_length);
            }
            else if(y > 0.0f) {
                player_spr.move(0.0f, +texture_edge_length);
            }
        }

        void RotateSprite(float degrees_360) {
            // (*?) functionality disabled
            ;
        }

        void SwitchSprite() {
            // disabled
            ;
        }

        void SetSpriteDirection(Games::RPG::Player::SpriteDirection spriteDirection) {
            ;
        }

        void AnimateAction(Games::RPG::Player::SpriteAction spriteAction) {
            ;
        }

        operator sf::Sprite& () {
            return player_spr;
        }
    };

//    IntroWindow introWindow;
//    Player player;
    Player_v2 player;


    // shared events ? multi-threading ?
    RPG() { Init(); }

    void Init() {
        background_img.loadFromFile(background_image_file_pathname);
        mainWindow_width = background_img.getSize().x;
        mainWindow_height = background_img.getSize().y;
        mainWindow.create(sf::VideoMode(mainWindow_width, mainWindow_height), mainWindow_title);

        background_tex.create(background_img.getSize().x, background_img.getSize().y);
        background_tex.loadFromImage(background_img);
        background_spr.setTexture(background_tex);
    }

        // (*?) the multi-threading design of a loop will, for now, be modularized to being
            // internal to the loop )that means it will not be integrated with the rest of the system
        // so for one, there won't be "heterogeneous / general-purpose threads", only "specialized threads"
    void EventLoop() {
//        while(mainWindow.isOpen()) {
            sf::Event event;
            bool poll {false};

            do {
                mainWindow_access.lock();
                poll = mainWindow.pollEvent(event);
                mainWindow_access.unlock();

                switch(event.type) {
                    case sf::Event::Closed:
                        mainWindow.close();
                        break;
                    case sf::Event::TextEntered:
                        // event.text
                        break;
                    case sf::Event::KeyPressed:
                    {   // event.key
                    /// TD
                    /*
                        movement WASD + collision detection
                        Escape - close current "menu" and go to mainWindow / current window
                        Q to quit / window.close();
                    */
                        if(event.key.code == sf::Keyboard::Escape) { mainWindow.close(); }
                        else {
                        // (*?) ~ simultaneous directions allowed; the question is how to ensure the reading
                            // of a stream of events in a time frame (?), since they seem to be read one by one
                            // and trigger this logic -> using a frame-based, shared memory of ~ flags (?)
                        // (*?) the multi-threaded evaluation of events

                        // (*?) simultaneous multiple-keys being pressed (possibly by keeping a bool of their state, setting
                        // it to true when pressed and to false when released, and the conditions for actions would be evaluated
                        // based on those flags / bools
                            // <e.g.> Shift + Direction -> run
                        // (!?) actually, frame-rate needs to be considered in the simulator (I'd think of feeding-back
                            // data from the renderer thread into the simulation threads, to adjust the functions that generate
                            // the motions and ~ "synchronize" them to the renderer, or rathre the "user's" POV / "frame of reference")
                            if(event.key.code == sf::Keyboard::A) { /* left */
                                player.SetSpriteDirection(Player::SpriteDirection::Left);    // (*?) this is an utter failure; I had to disable inheritance
                                            // due to the implicitly called constructor, and now am forced to (manually) change the code
                                player.MoveSprite(-10.0f, 0.0f);
                            }
                            if(event.key.code == sf::Keyboard::D) { /* right */
                                player.SetSpriteDirection(Player::SpriteDirection::Right);
                                player.MoveSprite(+10.0f, 0.0f);
                            }
                            if(event.key.code == sf::Keyboard::W) { /* up */
                                player.SetSpriteDirection(Player::SpriteDirection::Up);
                                player.MoveSprite(0.0f, -10.0f);
                            }
                            if(event.key.code == sf::Keyboard::S) { /* down */
                                player.SetSpriteDirection(Player::SpriteDirection::Down);
                                player.MoveSprite(0.0f, +10.0f);
                            }
                            if(event.key.code == sf::Keyboard::Q) { /* down */
                                player.RotateSprite(-15.0f);
                            }
                            if(event.key.code == sf::Keyboard::E) { /* down */
                                player.RotateSprite(15.0f);
                            }
                            if(event.key.code == sf::Keyboard::Space) {
                                player.AnimateAction(Player::SpriteAction::Jump);
                            }
                            if(event.key.code == sf::Keyboard::C) {
                                player.AnimateAction(Player::SpriteAction::Crouch);
                            }
                            if(event.key.code == sf::Mouse::Left) {
                                player.AnimateAction(Player::SpriteAction::Attack);
                            }
                            if(event.key.code == sf::Mouse::Right) {
                                player.AnimateAction(Player::SpriteAction::Parry);
                            }

                            if(event.key.code == sf::Keyboard::P) { /* change sprite */
                                player.SwitchSprite();  // (*?) notice how, for example, using struct Player_v2, this
                                                        // function will not crash, but neither will it have any relevant side-effect (!?)
                            }
                        }
                    }
                        break;
                    case sf::Event::KeyReleased:
                        // event.key
                        break;
                    case sf::Event::LostFocus:
                        // maybe stop rendering and only compute the "simulation frames"
                        break;
                    case sf::Event::GainedFocus:
                       // maybe start rendering the simulation frames
                        break;
                    case sf::Event::MouseButtonPressed:
                        // event.mouseButton
                        break;
                    case sf::Event::MouseButtonReleased:
                        // same
                        break;
                    case sf::Event::MouseEntered:
                        // ...
                        break;
                    case sf::Event::MouseLeft:
                        // ...
                        break;
                    case sf::Event::MouseWheelScrolled:
                        // event.mouseWheelScroll
                        break;
                    case sf::Event::MouseMoved:
                        // event.mouseMove
                        break;
                    case sf::Event::Resized:
                        // event.size
                        break;
                    default:
                        break;
                }
            } while(poll);
    }

    void RenderLoop() {
//        while(mainWindow.isOpen()) {
            // re-render
            // have a list of objects to be drawn, set in some order (be warry of the order in which items are
                // put into the list
            mainWindow.clear();
            mainWindow.draw(background_spr);
            mainWindow.draw(player);
            mainWindow.display();
    }

    void Run() {
        while(mainWindow.isOpen()) {
            EventLoop();
            RenderLoop();
        }
    // (*?) the simulation thread computes the elements of for the next frame and co-operates with the events thread,
        // while the renderer thread renders the previous frame

        // for now, this won't be used as it causes an error
//        std::thread parallel_rendering (&Player::TestInit, player, &mainWindow, &background_spr);

    // (*?) the usage of a thread for listening to events and another thread to render and compute things
        // is likely one of the design choices which can generate ~ "frame-boundary effects";
    // (*?) as such, it would be instead needed to design the "multi-threaded dynamics" such that ~ "critical points"
        // be turned into "serial / single threaded dynamics"; so, identify which sub-spaces of the dynamics need single-threaded
        // abstractions and which can work robustly with multi-threaded abstractions (!?)

//        sf::Font font;
//        font.loadFromFile("font/arial.ttf");
//        sf::Text text;
//        text.setFont(font);
//        text.setString("Welcome to the main menu");
//        text.setColor(sf::Color::White);
//        text.setCharacterSize(100);
//        sf::Vector2f text_position = text.getPosition();
//        printf("text box position: x-%f y-%f\n", text_position.x, text_position.y);
//        text.setPosition(100.0f, 100.0f);
//        text.move
//        mainWindow.draw(text);
//        mainWindow.display();
    }
};

};
#endif // GAMES_HPP_INCLUDED
