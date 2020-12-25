#ifndef OPENGL_V2_H_INCLUDED
#define OPENGL_V2_H_INCLUDED

#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

    // (!?) variables / data allocated like this, as "global variables", can it still be deallocated / memory freed ? or is this why they should be "packed into an object" which is ~ "modularly managed from a memory POV" (?!)

namespace v2 {

// "helper" functions / utilitaries (?!)
    // (!!) this is closest to working properly and being general enough; further work is to be done on this code
std::string LoadFile(std::string file_pathname) {
        std::string current_path = std::filesystem::current_path();
        std::string total_path {};

        if(file_pathname[0] == '/') {
            total_path = current_path + file_pathname;
        } else if (file_pathname[0] == '.' && file_pathname[1] == '/') {
            total_path = current_path;
            for(uint32_t idx{1}; idx < file_pathname.size(); idx++) {
                total_path += file_pathname[idx];
            }
        } else {
            total_path = current_path + '/' + file_pathname;
        }
//        std::cout << "total path: " << total_path << "\n";

        if(fs::exists(total_path)) {
            std::ifstream file = std::ifstream(total_path, std::ios_base::binary);

            file.seekg(0, std::ios_base::end);
            size_t file_size = file.tellg();
            file.seekg(0, std::ios_base::beg);

            char buffer[file_size + 1] {};
            file.read(buffer, file_size);
            file.close();

//            std::string content {buffer};   // (*?) the whole question is whether this will create a copy or not
                    // answer: it does not copy anything

/*
            std::string content{};
            for(size_t idx {0}; idx < file_size; idx++) {
                    content += buffer[idx];
            }
*/
            std::string content {buffer};   // so back to this "move constructor" then, and no delete[] after it (!)

            //delete[] buffer;  // interesting: after changing the constructor for the std::string, it became apparent that I was doing a double free here
                    // which means this: std::string {char*}; is a "move constructor", because the std::string gains ownership of the char*

            return content;
        } else {
            fprintf(stderr, "File not found.\n");
            return std::string {};
        }
    }


// attribute structs
struct IndicesTriangle {};  // (td;)

struct Position3f {
        union { // ~ "type's inside structure aliasing" (*?)
            struct {    // "annonymous structs" (!?)
            GLfloat x {0.0};
            GLfloat y {0.0};
            GLfloat z {0.0};
            };
            GLfloat value[3];
        };

        Position3f() { }
        Position3f(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) { }

        operator GLfloat* () {
            return &value[0];
        }
    };

struct Color3f {
    union {
        struct {
            GLfloat red {1.0f};
            GLfloat green {1.0f};
            GLfloat blue {1.0f};
        };
        GLfloat value[3];
    };

    operator GLfloat* () {
        return &value[0];
    }
};

struct RandomAttribute10f {
    GLfloat value[10] {};

    operator GLfloat* () {
        return &value[0];
    }
};

struct MultiAttributeVertex {
    Position3f position;
    Color3f color;
    Position3f normal;
    RandomAttribute10f random;
};



// (constants / default / test / playground) global data
Position3f cubeVertices[] {
        Position3f(-0.5f, -0.5f, 0.5f),
        Position3f(0.5f, -0.5f, 0.5f),
        Position3f(-0.5f, -0.5f, -0.5f),
        Position3f(0.5f, -0.5f, -0.5f),
        Position3f(-0.5f, 0.5f, 0.5f),
        Position3f(0.5f, 0.5f, 0.5f),
        Position3f(-0.5f, 0.5f, -0.5f),
        Position3f(0.5f, 0.5f, -0.5f), // the 8 vertices of a cube, normalized
    };

Position3f rectangleVertices[] {
    Position3f(-.5f, -.5f, .0f),
    Position3f(-.5f, .5f, .0f),
    Position3f(.5f, .5f, .0f),
    Position3f(.5f, -.5f, .0f),
};

GLuint indicesSquare[] {
    1, 2, 3,
    0, 1, 3,
};

MultiAttributeVertex multiAttributeVertices [] {
//    MultiAttributeVertex(Position3f(), Color3f(), Position3f(), RandomAttribute10f),
//    MultiAttributeVertex(Position3f(), Color3f(), Position3f(), RandomAttribute10f),
//    MultiAttributeVertex(Position3f(), Color3f(), Position3f(), RandomAttribute10f),
    }; // try loading these and randomly initializing them; then define the glAttribPointers for the buffer

float positions_thecherno[] = {
    -0.5f, -0.5f, .0f,
    0.0f, 0.5f, .0f,
    0.5f, -0.5f, .0f,
};

// shader management (file reading, memory loading, compiling, etc.; and deleting source code; maybe not the "object code")
    // and program management (attach, link, validate, delete, etc.)
    // they both need some collection types / manager types to also handle communication between shaders and progams
std::vector<GLuint> vertexShaders;
std::vector<GLuint> fragmentShaders;
std::vector<GLuint> programs;
GLuint currentProgram;

    GLuint CompileShader(std::string sourceCode, GLenum shaderType) {
        GLuint shaderID = glCreateShader(shaderType);

        // or use a switch
        if(shaderType == GL_VERTEX_SHADER) vertexShaders.push_back(shaderID);
        else if (shaderType == GL_FRAGMENT_SHADER) fragmentShaders.push_back(shaderID);
            // default: break;

//        std::cout << "Shader ID: " << shaderID << "\n";

        const char * source = sourceCode.c_str();
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        int result {};
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE) {
            int length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
            char* errorMessage = (char*)alloca((length + 1) * sizeof(char));
                // (!?) dynamic allocation on the stack... (*?) doesn't this circumvent the benefits of stack allocation ? supposedly it's a function from C, but I wonder if it requires run-time support ?
            glGetShaderInfoLog(shaderID, length, &length, errorMessage);
            std::cout << "Shader source code:\n" << sourceCode
                        << "\nError:\n" << errorMessage;
            //delete[] errorMessage;    // since alloca() was used, I expect this to be deallocated with the stack at the end of the function's lifetime

            glDeleteShader(shaderID);
            return 0;
        }

        return shaderID;
    }

    GLuint LinkShadersIntoProgram(std::vector<GLuint> shadersInOrder) {
        GLuint programID = glCreateProgram();
//        programs.push_back(programID);
        for(GLuint idx : shadersInOrder) {
            glAttachShader(programID, shadersInOrder[idx]);
//            std::cout << "Attached shaderID " << shadersInOrder[idx] << " to programID " << programID << ".\n";
        }

        glLinkProgram(programID);
        glValidateProgram(programID);

        int result {};
        glGetProgramiv(programID, GL_LINK_STATUS, &result);
        if(result == GL_FALSE) {
            int length;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
            char* errorMessage = (char*)alloca((length + 1) * sizeof(char));
                // (!?) dynamic allocation on the stack... (*?) doesn't this circumvent the benefits of stack allocation ? supposedly it's a function from C, but I wonder if it requires run-time support ?
            glGetProgramInfoLog(programID, length, &length, errorMessage);
            std::cout << "Program linking containing shaderIDs ";
            for(GLuint ID : shadersInOrder)
                std::cout << ID << " ";

            std::cout << "\nHas error:\n" << errorMessage;

            glDeleteProgram(programID);
            return 0;
        }

        return programID;
    }

    void initShadersPrograms() {
        std::string vertexShaderSourceCode = LoadFile("playground.v.glsl");
        std::string fragmentShaderSourceCode = LoadFile("shader3.fs");

        std::vector<GLuint> shaders {};
        GLuint vertexShaderID = CompileShader(vertexShaderSourceCode, GL_VERTEX_SHADER);
        shaders.push_back(vertexShaderID);

        GLuint fragmentShaderID = CompileShader(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);
        shaders.push_back(fragmentShaderID);

        GLuint programID = LinkShadersIntoProgram(shaders);
        programs.push_back(programID);
        glUseProgram(programID);
        currentProgram = programID;

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        // supposedly detach should delete the source code, but that is bad for debugging; then what does this do ?
            // it was mentioned at some point that it likely does something similar to deleting object code files (*?)
            // controversy: "technically, you should be calling glDetachShader() after having linked it to the program" (*?)

    }

    void PrepareProgram(GLuint programID) {
        if(programID == programs[0]) {
            float value[3] {1.0f, 0.0f, 0.0f};
            GLint dominatingColorUniformLocation = glGetUniformLocation(programID, "dominatingColor");
            glUniform3f(dominatingColorUniformLocation, value[0], value[1], value[2]);
        }
    }

// context creation (using whatever library, like SDL2; create window, set title and "engine properties", etc.)

// data management (data loading from files or generators, reserving the memory buffers, loading data into GPU memory, defining the attribute pointers,
    // creating the relevant VAO / VBO/ EBO / IBO / etc. (whatever other bullshit)

// renderSettings

// render pipeline (maybe have multiple modes possible ?)

// mainLoop

// error logs handling

// events handling and callbacks for each (~ the GUI or State machine design part)


struct Graphics {

    std::vector<SDL_Window *> Windows {};
    std::vector<GLuint> VAOs {};
    std::vector<GLuint> VBOs {};
    std::vector<GLuint> EBOs {};
    std::vector<GLuint> AttribPointers {};

    void initBuffers() {
        GLuint vao_cube;
        glGenVertexArrays(1, &vao_cube);
        VAOs.push_back(vao_cube);

        GLuint vbo_cube;
        glGenBuffers(1, &vbo_cube);
        VBOs.push_back(vbo_cube);

        GLuint ebo_cube;
        glGenBuffers(1, &ebo_cube);
        EBOs.push_back(ebo_cube);

        glBindVertexArray(vao_cube);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
        glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), &rectangleVertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquare), indicesSquare, GL_STATIC_DRAW);
//        glVertexArrayElementBuffer(vao_cube, ebo_cube);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(ebo_cube, )
    }

    void initBuffers_thecherno() {
        unsigned int vaoID;
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(buffer, sizeof(positions_thecherno), positions_thecherno, GL_STATIC_DRAW);
        //glBufferData(buffer, 6 * sizeof(float), positions_thecherno, GL_STATIC_DRAW);

        // (!?) there is also a glEnableVertexArrayAttrib(vaoID, attribID); (?!)
        glEnableVertexAttribArray(0);   // first "enable" the attribute and then define it
            // (the pointer) ? is this like saying that the VAO gets reallocated as an array
            // of some size ? and what if I enable vertexAttribArray(100) when I only have
            // 2 or 3 already defined attributes (?!); will it allocate all of those before it [3-4..99] ?
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    }

    void render(SDL_Window* window) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        glUseProgram(squareProgram);
//        glBindVertexArray(VAOs[0]);
        PrepareProgram(currentProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // crashes if no EBO is selected; but to what VBO does EBO point to if there is no bound VBO ?
            // GL_UNSIGNED_INT is the type of the indices; so yes, the domain of the indices and the type they use to reduce memory size is a done optimization

        SDL_GL_SwapWindow(window);
    }

    void render_thecherno(SDL_Window* window) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }

    void mainLoop() {
        SDL_Window * window = initContext();
        if(window != nullptr) {
            initBuffers();
//            initBuffers_thecherno();
            initShadersPrograms();

            while(true) {   // a useless comparison; this should simply turn into a goto label and that's all
                SDL_Event ev;
                while (SDL_PollEvent(&ev)) {
                    if (ev.type == SDL_QUIT)
                        return;
                    else if(ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        return;
                }
//                render(window);
                render_thecherno(window);
            }
        }
    }

    SDL_Window* initContext() {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow("render window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 960,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        SDL_GL_CreateContext(window);

        GLenum glew_status = glewInit();
        if (glew_status != GLEW_OK) {
            std::cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << std::endl;
            return nullptr;
        }

//        Windows.push_back(window);
        return window;
    }

};
}

#endif // OPENGL_V2_H_INCLUDED
