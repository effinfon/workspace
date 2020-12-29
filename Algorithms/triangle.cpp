#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "triangle.hpp"
#include "Assets.hpp"
#include <chrono>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using SDL2 for the base window and OpenGL context init */
#include <SDL2/SDL.h>
/* ADD GLOBAL VARIABLES HERE LATER */

GLuint program;
GLint attribute_coord2d;

GLfloat triangle_vertices_global[] = {
    0.0,    0.8,
    -0.8,   -0.8,
    0.8,    -0.8
};

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

    // once OpenGL has the 3 screen points, it will fill the space
        // between them to make a triangle, by calling the fragment shader
        // for each pixel in the triangle

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    /*
    const char * fs_source =
        "#version 120\n"
        "void main(void) {\n"
        "gl_FragColor[0] = 0.0;\n"
        "gl_FragColor[1] = 0.0;\n"
        "gl_FragColor[2] = 1.0;\n"
        "}\n";
    */
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);  // select the program
    glEnableVertexAttribArray(attribute_coord2d);   // then manually select those
            // variables that it needs... seriously ?
    GLfloat triangle_vertices_local[] {
        0.0,    0.8,
        -0.8,   -0.8,
        0.8,    -0.8,
        1.0,    1.0,
        0.5,    -0.5,
        -0.5,   0.5
    };

//    glVertexAttribPointer(
//        attribute_coord2d, // attribute GLint
//        2,  // how many elements per vertex; here it's x and y positions
//        GL_FLOAT,   // the type of each element; all elements of same type
//        GL_FALSE,   // "take values as-is" (?)
//        0,  // no stride / data inbetween each position (or element ?)
//        &triangle_vertices_local[0]    // pointer to data in C array
//    );
//
//    // "push each element in buffer_vertices to the vertex shader" (!?)
//    glDrawArrays(GL_TRIANGLES, 0, 3);   // type, first, count
//
//    glVertexAttribPointer(
//        attribute_coord2d, // attribute GLint
//        2,  // how many elements per vertex; here it's x and y positions
//        GL_FLOAT,   // the type of each element; all elements of same type
//        GL_FALSE,   // "take values as-is" (?)
//        0,  // no stride / data inbetween each position (or element ?)
//        &triangle_vertices_local[3]    // pointer to data in C array
//    );
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    Assets::Quadrilateral quad {-1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
    quad.DrawStairs(attribute_coord2d);

    glDisableVertexAttribArray(attribute_coord2d);  // host switches off attribute,
            // but leaves program on (?)

    SDL_GL_SwapWindow(window);  // aha
}

void free_resources() {
  glDeleteProgram(program);
  fprintf(stdout, "Freed resourecs.\n");
}

void mainLoop(SDL_Window* window) {
    static uint64_t frame_number {0};

	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				return;
		}
		fprintf(stdout, "Rendering frame[%lu]: ", frame_number++);
        std::chrono::duration<uint32_t, std::micro> elapsed;
		render(window);
		uint32_t usec = elapsed.count();
		fprintf(stdout, "%u usec\n", usec); // wow, apparently this fprintf call takes a lot of time (!?)
	}
}

int Start_Triangle_v1(int argc, char* argv[]) {
	/* SDL-related initialising functions */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("My First Triangle",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 960,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
		return EXIT_FAILURE;
	}

	/* When all init functions run without errors,
	   the program can initialise the resources */
	if (!init_resources())
		return EXIT_FAILURE;

	/* We can display something if everything goes OK */
	mainLoop(window);

	/* If the program exits in the usual way,
	   free resources and exit with a success */
	free_resources();
	return EXIT_SUCCESS;
}
