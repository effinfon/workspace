#ifndef ASSETS_HPP_INCLUDED
#define ASSETS_HPP_INCLUDED

#include <GL/glew.h>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

#include "CollectionTypes.hpp"
#include "NumberTheory.hpp"
#include <vector>

struct PixelRGB {
    uint8_t red {};
    uint8_t green {};
    uint8_t blue {};

    PixelRGB() : red(0.0), green(0.0), blue(0.0) {}
    PixelRGB(uint8_t red, uint8_t green, uint8_t blue) :
        red(red), green(green), blue(blue) {}
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

            // seg-faults
/*
    std::streamsize available(std::ifstream& is ) {
        std::streampos pos = is.tellg();
        is.seekg( 0, std::ios::end );
        std::streamsize len = is.tellg() - pos;
        is.seekg( pos );
        return len;
    }
*/

    void LoadImageBitmap(std::string filepathname) {
        DynamicArray<PixelRGB> result {};
        std::vector<PixelRGB> result_vec {};

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

            // this seems to be the file header, but I am still uncertain up to what
                // point does the header extend, so I'd like to turn the whole binary
                // into an image and see what "renders correctly / expectedly"
//4d42 bef2 0015 0000 0000 008a 0000 007c
//0000 02ee 0000 01db 0000 0001 0020 0003
//0000 be68 0015 0000 0000 0000 0000 0000
//0000 0000 0000 0000 00ff ff00 0000 00ff
//0000 0000 ff00 4742 7352 c280 28f5 b860
//151e 8520 01eb 3340 1333 6680 2666 6640
//0666 99a0 0999 0a3c 03d7 5c24 328f
            //std::streamsize avail = available(istream);
            //std::cout << "Available bytes: " << avail;

            while (istream) {
                std::ios::pos_type before = istream.tellg();
                uint8_t r, g, b;
                istream >> r; if(istream) istream >> g; else std::cout << "Green byte missing.\n";
                if(istream) istream >> b; else std::cout << "Blue byte missing.\n";
                // result += PixelRGB(r, g, b); // (!!?) because this doesn't produce hard-copies, I think it seg-faults
                result_vec.push_back(PixelRGB(r, g, b));    // does it hard-copy by default or why does it not seg-fault ?
                        // aahh, I guess that DynamicArray<typename> tried to reallocate memory and had to copy things, so
                        // when it tried to access the temporary variable's pointer / reference it went out of memory access;
                        // so, does vector hard-copy or just doesn't get to have to reallocate ?
                // let's force it to access
                PixelRGB temp_access = result_vec[result_vec.size() - 1];   // works fine, oh well
                std::ios::pos_type after = istream.tellg();
                //std::cout << static_cast<int>(r) << ' ';  // for "debugging purposes"
            }

            istream.close();
            }

        Uint32_t2 num = DecomposeIntoWidthAndHeight_v1(result_vec.size());
        std::cout << "decompose " << result_vec.size() << " into " << num.x << " and " << num.y << " such that x * y = " << num.x * num.y << "\n";
        width = num.x;
        height = num.y;
        bitmap = new PixelRGB[width * height];

        for(uint16_t idx {0}; idx < width * height; idx++) {
            bitmap[idx] = result_vec[idx];
        }
    } else {std::cerr << "File not found or cannot be opened.\n";} }

    void Draw() {

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


#endif // ASSETS_HPP_INCLUDED
