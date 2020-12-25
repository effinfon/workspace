#ifndef VAO_VBO_HPP_INCLUDED
#define VAO_VBO_HPP_INCLUDED

//#include <chrono>
#include <iostream>
#include <stdio.h>
using namespace std;
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace _v2{
void playground_VAO_VBO() {
    GLuint VAO1, VAO2 {0}, VAO3 {0};
    GLuint VBO1, VBO2, VBO3;

    /// how do glGenVertexArrays() and glGenBuffers() handle being called in a
    /// multi-threaded environemnt (!?)
    glGenVertexArrays(1, &VAO1);    // putting a value other than 1 in here seems
    glGenVertexArrays(0, &VAO2);    // to cause a "stack smash" (*?)
    glGenVertexArrays(-1, &VAO3);
    glGenVertexArrays(-10, &VAO3);
    glGenVertexArrays(-1000, &VAO3);

    glGenBuffers(1, &VBO1); // the same here; although, 0 and negative numebrs seem to work fine
    glGenBuffers(0, &VBO2); std::cout << "(given 0) VBO2: " << VBO2 << "\n";    // although 0 was
                                //inputted, it still received a GLuint, so something was likely allocated
    glGenBuffers(-1, &VBO3); std::cout << "(given -1) VBO3: " << VBO3 << "\n";
    glGenBuffers(-10, &VBO3);   // also, reallocating (or whatever this does) doesn't
    glGenBuffers(-1000, &VBO3);   // seem to cause problems

        // supposesly, if $n is negative in the function call, then GL_INVALID_VALUE is returned
    std::cout << "GL_INVALID_VALUE: " << static_cast<GLuint>(GL_INVALID_VALUE) << "\n";

    GLuint VAO4[10];
    glGenVertexArrays(10, VAO4);    // now this does work; now I know what stack smash is as well,
                            // it's when a control goes out of its own stack, and in this case it
                            // was a "bounds check" error (unsafe procedure)
    GLuint VBO4[10];
    glGenBuffers(10, VBO4);

    // interesting type, makes things safer and automates some syntax (*!?)
    std::array<GLuint, 3> VAO5;
    std::array<GLuint, 3> VBO5;
    glGenVertexArrays(VAO5.size(), &VAO5[0]);
    glGenBuffers(VBO5.size(), &VBO5[0]);

    // after allocating, it's time to free
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteVertexArrays(10, &VAO4[0]);
    glDeleteVertexArrays(3, &VAO5[0]);
    std::cout << "After deallocation:\n";
    std::cout << "VAO1: " << VAO1 << " VAO2: " << VAO2 << " (should not have been allocatedto begin with) VAO3: "
                << VAO3 << " VAO4[0]: " << VAO4[0] << " VAO5[0]: " << VAO5[0] << "\n";

    std::array<GLuint, 100> VAO6;
    std::array<GLuint, VAO6.size()> VBO6;
    glGenVertexArrays(VAO6.size(), &VAO6[0]);
    glGenBuffers(VBO6.size(), &VBO6[0]);

    // manual: "there is no guarantee that the returned integers will be contiguous; just that they will
        // not have been previously used at the moment that glGenVertexArrays() or glgenBuffers() are called"
    for(uint16_t idx{0}; idx < VAO6.size(); idx++) {
        std::cout << "VAO6[" << idx << "]: " << VAO6[idx] << " VBO6["
                    << idx << "]: " << VBO6[idx] << "\n";
    }
}

void VAO_VBO_function() {
    // there was a discussion about the right hand rule and the coordinates
        // in OpenGL; x (+) - right, y (+) - up, z (+) - behind (?!)
        // imagining the usual xyz coordinate system and rotating it a bit,
        // indeed z (+) is behind, because it's like "looking from above,
        // at a projection which rises into the camera" (?!)
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);   // vertex indices order (*?)
    glBindVertexArray(VertexArrayID);

    GLfloat** random_data = generateTriangles(10, 5);   // 10 triangles per buffer, 5 buffers
    GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    for(int idx{0}; idx < 5; idx++) {
        for(int idx_2{0}; idx_2 < 10; idx_2++) {
            printf("buffer %d, triangle %d: %f, %f, %f\n", idx + 1, idx_2 + 1, random_data[idx][idx_2 * 3 + 0], random_data[idx][idx_2 * 3 + 1], random_data[idx][idx_2 * 3 + 2]);
        }
    }



    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer); // multi-array buffers (*?)
    // the camera seems to, by default, be in the "top position", basically
        // "looking down, perpendicularly on the xy plane" (*?)
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(   GL_ARRAY_BUFFER,    // actual vertex data (*?)
                    30,
                    random_data[1],
                    GL_STATIC_DRAW);
}

GLuint program;
GLint attribute_coord2d;

    // more like shaders and programs; nothing is done about
    // loading assets (textures, models / meshes, etc.)
bool init_resources(void) {
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char * vs_source =
        // "#version100\n"  // OpenGL ES 2.0 - embedded systems use GLSL 1.00 ?
        "#version 120\n"    // OpenGL 2.1 uses GLSL 1.20
        "attribute vec2 coord2d;\n"
        "void main(void) {\n"
        "gl_Position = vec4(coord2d, 0.0, 1.0);\n"
        "}";    // (*?) multi-line, single string -> concatenation

    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
    if(!compile_ok) {
        fprintf(stderr, "Error in vertex shader compilation.\n");
        GLint length {};
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
        GLchar * buffer = new GLchar[length];
        glGetShaderInfoLog(vs, length, &length, buffer);
        fprintf(stderr, "error: %s\n", buffer);
        return false;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fs_source =
        "#version 120\n"
        "void main(void) {\n"
        "gl_FragColor[0] = gl_FragCoord.x/640.0;\n"
        "gl_FragColor[1] = gl_FragCoord.y/480.0;\n"
        "gl_FragColor[2] = 0.5;\n"
        "}\n";

    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
    if(!compile_ok) {
        fprintf(stderr, "Error in fragment shader compilation.\n");
        GLint length {};
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
        GLchar * buffer = new GLchar[length];
        glGetShaderInfoLog(fs, length, &length, buffer);
        fprintf(stderr, "error: %s\n", buffer);
        return false;
    }

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if(!link_ok) {
        fprintf(stderr, "Error in program linking.\n");
        GLint length {};
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar * buffer = new GLchar[length];
        glGetProgramInfoLog(program, length, &length, buffer);
        fprintf(stderr, "error: %s\n", buffer);
        return false;
    }

    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(program, attribute_name);

    if(attribute_coord2d == -1) {
        fprintf(stderr, "Could not bind attribute %s.\n", attribute_name);
        return false;
    }

    return true;
}

void render(SDL_Window* window) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glUseProgram(program);
//    glEnableVertexAttribArray(attribute_coord2d);
//    glDisableVertexAttribArray(attribute_coord2d);
    // ...

    glEnableVertexAttribArray(0);   // is constant 0 a built-in / default (*?)
                                    // is there some default shader that produces white fragments
                                    // when given a VAO and VBO (*?)
//    glBindbuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(  // finally, describing how the data is to be interpreted (*?)
        0,                  // this seems to be very local to the usage of the data for some reason,
        3,                  // meaning that it's very common for the same buffer to contain multiple
        GL_FLOAT,           // kinds of data to be used in different parts, sequentially (*?)
        GL_TRUE,
        0,
        nullptr);
//    glVertexAttribPointer(
//        0,
//        3,
//        GL_FLOAT,
//        GL_FALSE,
//        0,
//        (void*)0
//        );
    glDrawArrays(GL_TRIANGLES, 0, 3);   // draw mode (*?) -> interpolation function based on shape (*?)
//    glDisableVertexAttribArray(0);

//    glDisableVertexAttribArray(attribute_coord2d);
    SDL_GL_SwapWindow(window);
}

void free_resources() {
  glDeleteProgram(program);
  fprintf(stdout, "Freed resourecs.\n");
}

void mainLoop(SDL_Window* window) {
	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				return;
            else if(ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return;
		}

		render(window);
	}
}

int initContext(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("render window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 960,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
		return EXIT_FAILURE;
	}

	if (!init_resources())
		return EXIT_FAILURE;

    playground_VAO_VBO();
    VAO_VBO_function();

	mainLoop(window);

	free_resources();
	return EXIT_SUCCESS;
}


};
#endif // VAO_VBO_HPP_INCLUDED
