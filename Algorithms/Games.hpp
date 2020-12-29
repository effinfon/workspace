#ifndef GAMES_HPP_INCLUDED
#define GAMES_HPP_INCLUDED

/// TD
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

// (*?) need a mechanism for specifying different "variants" for an abstraction / "thing" / "concept" / "function" / "struct" / "implementation", etc (!?)
// <e.g.> for now, ConwayLife will be using a static (discrete) state-space / "map", but eventually it will be able to adapt dynamically (and maybe use a non
    // 2Dim array state-space as well (*!?) [maybe graph-based, or sparse-matrix ?]

// (*?) need an abstraction for "border constraint (checker)", for when iterating over spaces that are bounded, such as a chess table, ConwayLife state-space,
    // a matrix, a bitmap, ect.; the general problem is that of "adjacency"; but do also think about "borders of self-continuing (discrete) state-spaces", such
    // as some variants of $Snake


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
#endif // GAMES_HPP_INCLUDED
