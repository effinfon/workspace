#ifndef ASSETS_HPP_INCLUDED
#define ASSETS_HPP_INCLUDED

#include <GL/glew.h>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

struct PixelRGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Texture {
    uint16_t width;
    uint16_t height;
    PixelRGB * bitmap;

    // loading a bitmap image into memory (of this object)
    // define the RGB attribute here, for OpenGL, and the drawing procedure, etc.
    // scaling and morphing onto a "geometry"

//    PixelRGB operator [][](int x, int y) {}  // will not work on C++, this needs two arguments like C# (?!)
            // as it has a much simpler syntax
    void LoadImageBitmap(std::string filepathname) {
        std::string full_path = fs::current_path();
        if(filepathname[0] != '/') {
            full_path += "/" + filepathname;
        } else {
            full_path += filepathname;
        }

        bool fileExists {std::filesystem::exists(full_path)};
        std::cout << "File " << full_path; printf(" exists: %d.\n", fileExists);

        if(fileExists) {
            std::ifstream istream {full_path, std::ios_base::binary};
            if(istream.is_open()) {
/*
4d42 bef2 0015 0000 0000 008a 0000 007c
0000 02ee 0000 01db 0000 0001 0020 0003
0000 be68 0015 0000 0000 0000 0000 0000
0000 0000 0000 0000 00ff ff00 0000 00ff
0000 0000 ff00 4742 7352 c280 28f5 b860
151e 8520 01eb 3340 1333 6680 2666 6640
0666 99a0 0999 0a3c 03d7 5c24 328f
*/
/*
            std::noskipws();
            while (istream) {
                std::ios::pos_type before = istream.tellg();
                uint8_t x;
                istream >> x;
                std::ios::pos_type after = source.tellg();
                std::cout << before << ' ' << static_cast<int>(x) << ' '
                          << after << std::endl;
            }
*/
            istream.close();
        }
    }
};

struct Point2F {
    GLfloat x {};
    GLfloat y {};

    Point2F() : x(0.0), y(0.0) {}
    explicit Point2F(GLfloat x, GLfloat y) : x(x), y(y) {}
};
struct Triangle {
    Point2F vertices[3] {};
};

struct Quadrilateral {
    Point2F vertices[4] {}; // [1] and [2] need to be "diagonal vertices" (relative property)

    explicit Quadrilateral(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4) {
        vertices[0].x = x1;
        vertices[1].x = x2;
        vertices[2].x = x3;
        vertices[3].x = x4;

        vertices[0].y = y1;
        vertices[1].y = y2;
        vertices[2].y = y3;
        vertices[3].y = y4;
    }

    void Draw(GLint attribute_coord2d) {
        // program booting
//        glUseProgram(program);  // select the program
//        glEnableVertexAttribArray(attribute_coord2d);   // then manually select those
        // variables that it needs... seriously ?

        // load / set data
        glVertexAttribPointer(
        attribute_coord2d, // attribute GLint
        2,  // how many elements per vertex; here it's x and y positions
        GL_FLOAT,   // the type of each element; all elements of same type
        GL_FALSE,   // "take values as-is" (?)
        0,  // no stride / data inbetween each position (or element ?)
        &vertices[0]    // pointer to data in C array
        );

        // "push each element in buffer_vertices to the vertex shader" (!?)
        glDrawArrays(GL_TRIANGLES, 0, 3);   // type, first, count

        glVertexAttribPointer(
        attribute_coord2d, // attribute GLint
        2,  // how many elements per vertex; here it's x and y positions
        GL_FLOAT,   // the type of each element; all elements of same type
        GL_FALSE,   // "take values as-is" (?)
        0,  // no stride / data inbetween each position (or element ?)
        &vertices[1]    // pointer to data in C array
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(attribute_coord2d);  // host switches off attribute,
    }
    void Translate(GLfloat x, GLfloat y) {
        for(uint8_t idx {0}; idx < 4; idx++) {
            vertices[idx].x += x;
            vertices[idx].y += y;
        }
    }
    void Rotate(GLfloat radians) {

    }
    void Scale(GLfloat ratio) {
        for(uint8_t idx {0}; idx < 4; idx++) {
            vertices[idx].x *= ratio;
            vertices[idx].y *= ratio;
        }
    }

    Point2F Centroid() {
        Point2F centroid {0.0, 0.0};

        for(uint8_t idx {0}; idx < 4; idx++) {
            centroid.x += vertices[idx].x / 4.0;
            centroid.y += vertices[idx].y / 4.0;
        }

        return centroid;
    }

    void DrawStairs(GLint attribute_coord2d) {
        static GLfloat ratio {1.0};
        Scale(ratio);
        Draw(attribute_coord2d);
        ratio -= 0.1;
        if(ratio <= 0.0) ratio = 1.0;
    }
};

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
#endif // ASSETS_HPP_INCLUDED
