#ifndef CHESS_HPP_INCLUDED
#define CHESS_HPP_INCLUDED

#include <GL/glew.h>

struct ChessPiece {
    uint8_t x;
    uint8_t y;

    // movement procedure

};
struct ChessPiecePawn : ChessPiece {
    // init
    // texture
    // draw procedure
};
struct ChessPieceKing : ChessPiece {};
struct ChessPieceQueen : ChessPiece {};
struct ChessPieceBishop : ChessPiece {};
struct ChessPieceRook : ChessPiece {};
struct ChessPieceKnight : ChessPiece {};

struct ChessBoard {
    uint8_t width;
    uint8_t height;
    bool zero_zero_isBlack{true};

    void InitGL() {
        // shaders, program, assets
    }
    void Render /*vs Draw */() {    // rendering vs drawing (?!)
        // clear buffer, draw assets, ...; the buffer swap should occur externally because
            // there might still be things to draw on top, such as chess pieces
    }
};
struct Chess {
    ChessBoard board;
    ChessPiece pieces[];    // at some point, a piece of some derived class can be changed for another; the total number of pieces in a chess game is constant, but the number of pieces on the board at any point of the game can vary (?)

    // initialize board state: graphics / textures, positions of pieces,
    // bring in / take out ChessPiece procedure
};


#endif // CHESS_HPP_INCLUDED
