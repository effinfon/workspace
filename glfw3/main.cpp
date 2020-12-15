#include <iostream>
#include <pthread.h>

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>


//  -------------------------- --------------------------
//  GLFW Manager
//  -------------------------- --------------------------


struct GLFWManager {
        // some structs have to be defined as well
    std::vector<GLFWwindow *> windows;
    std::vector<int> resolutions;

    // DefaultInitHintProfile
    // DefaultWindowHintProfile

    // ActiveWindows
    // render loop for each window, sort of like a queue of commands
    // a division into static elements and dynamic elements; the static ones
        // shouldn't be re-rendered, but somehow compressed and uncompressed (?)

    void init(){}

    void CreateWindow() {}

    void WindowCloseCallback();

    void nextFrame() {} // calls the render on the active-selected windows

    void all_glfwInitHint() {}

    void all_glfwWindowHint() {}

    void verbose() {
        const unsigned char * result;
        result = glGetString(GL_VENDOR);
        std::cout << "Vendor: " << result << "\n";
        result = glGetString(GL_RENDERER);
        std::cout << "Renderer: " << result << "\n";
        result = glGetString(GL_VERSION);
        std::cout << "OpenGL version: " << result << "\n";
        result = glGetString(GL_SHADING_LANGUAGE_VERSION);
        std::cout << "Shader Language version: " << result << "\n";
        result = glGetString(GL_EXTENSIONS);
        std::cout << "Extensions: " << result << "\n";
    }
};


//  -------------------------- --------------------------
//  String Constants String Constants String Constants String Constants
//  -------------------------- --------------------------

constexpr char errorMessage1[] = "Error occured while initializing GLEW.\n";

//  -------------------------- --------------------------
//  Configuration Profile Configuration Profile Configuration Profile
//  -------------------------- --------------------------

const int winW = 900;
const int winH = 600;
const char * winTitle = "Title bar";
int fbW, fbH;


//  -------------------------- --------------------------
//  UI UI  UI UI  UI UI  UI UI  UI UI  UI UI  UI UI  UI UI
//  -------------------------- --------------------------

struct RGBA {
    float R, G, B, A;

    RGBA(float Rin, float Gin, float B, float A) : R(Rin), G(Gin), B(B), A(A) {}
};

struct UIElement {
    int id;
    int originX, originY;
    int apexX, apexY;

    void (*callback)(int id);

public:
    UIElement(){}
    virtual void draw();
};


struct Button : UIElement {
    int sizeDiagonal = 70;
    RGBA backgroundColor = RGBA(0.2f, 0.2f, 0.2f, 1.0f);

    // define the "draw array" here, specific to Button

    Button(){}

    void draw() {
        // OpenGL
        // glDrawArrays()
    }

    void move(int newOriginX, int newOriginY) {}

    void scale(int newSizeDiagonal) {}
};

struct UIManager {
private:
    std::vector<UIElement> buttons;

public:
    void CreateButton(void (*callback)(int id)) {
        Button * button = new Button();
        button->id = buttons.size();
        button->callback = callback;
    }
};


//  -------------------------- --------------------------
//  Command Queue Command Queue Command Queue Command Queue
//  -------------------------- --------------------------

struct CommandQueue {
    // a container for function calls with heterogeneous / various parameter lists
    // ... ?
};

//  -------------------------- --------------------------
//  Ring buffer
//  -------------------------- --------------------------

struct RingBuffer {
    int size = 100;
    int buffer[100];
    int i = 0, j = 0;   // buffer-state parameters
    bool empty = true;

    int deque()
    {
        if(empty == false) {
            int temp;
            if(empty == false) {
                temp = buffer[j++];
                j %= 100;
            }

            if(i == j && empty == false)
                empty = true;

            return temp;
        } else { return 0; }
    }

    void queue(int item)
    {
        buffer[i++] = item;
        empty = false;
        i %= 100;
    }

    void test() {
        // test 1: queue and dequeue
        std::cout << "Test1: ";
        for(int i = 0; i < 100; i++) {
            queue(i);
            std::cout << deque() << " ";
        } std::cout << "\n";

        // test 2: "go over" / "exceed" the buffer
        std::cout << "Test2: ";
        for(int i = 0; i < 200; i++) {
            queue(i);
        }
        for(int i = 0; i < 100; i++) {
            std::cout << deque() << " ";
        } std::cout << "\n";

        // test 3: a mixture of queue-deque and "exceed" the buffer
        std::cout << "Test3: ";
        for(int i = 0; i < 50; i++) {
            queue(i);
            std::cout << deque() << " ";
        }
        for(int i = 50; i < 350; i++) {
            queue(i);
        }
        for(int i = 0; i < 100; i++) {
            std::cout << deque() << " ";
        } std::cout << "\n";
    }
};


//  -------------------------- --------------------------
//  GLFW3 GLFW3 GLFW3 GLFW3 GLFW3 GLFW3 GLFW3 GLFW3 GLFW3
//  -------------------------- --------------------------
#define TEST_NO


void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    static int lastKey;
    // as is, this supposedly won't do well for "fine text input"; basically, it doesn't seem
        // to differentiate between lowercase and uppercase letters / characters
    // also, why does it "double" character inputs ? basically it callbacks for both the
        // press and the unpress / free; and then there's that "after a few msecs it will
        // act as if it's repeatedly being pressed, with some frequency" (?!) [this would
        // be the "repeat" action
    // there is the "press action", the "free action" and the "repeat / hold action"

    std::cout << "Key pressed: " << char(key) << "\n";

    if(key == GLFW_KEY_SPACE) {}
    else if((lastKey == GLFW_KEY_LEFT_CONTROL || lastKey == GLFW_KEY_RIGHT_CONTROL) && key == GLFW_KEY_C) {
        //glfwSetWindowShouldClose(window, GL_TRUE);
        std::cout << "Should close window " << window << "\n";

        key = lastKey;  // since the current key was consumed
    }

    if(action == GLFW_PRESS) {
        std::cout << "A button has been pressed.\n";
    } else if (action == GLFW_RELEASE || action == GLFW_REPEAT) {
        std::cout << "Release or Repeat.\n";
    }

    lastKey = key;
}

void glfw()
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow * window = glfwCreateWindow(winW, winH, winTitle, NULL, NULL);

//    // setting callbacks / event handling
//    glfwSetWindowCloseCallback();
//    glfwSetCursorEnterCallback();
//    glfwSetCursorPosCallback();
//    glfwSetDropCallback();
//    glfwSetErrorCallback();
//    glfwSetFramebufferSizeCallback();
//    glfwSetMonitorCallback();
//    glfwSetMouseButtonCallback();
//    glfwSetScrollCallback();
//    glfwSetWindowContentScaleCallback();
//    glfwSetWindowCloseCallback();   // "succint" / "annonymous" function would suffice
//    glfwSetWindowFocusCallback();
//    glfwSetWindowIconifyCallback();
//    glfwSetWindowMaximizeCallback();
    glfwSetKeyCallback(window, keyCallback);
//    glfwSetWindowPosCallback();
//    glfwSetWindowRefreshCallback();
//    glfwSetWindowSizeCallback();
//
//    // clipboard ?
//    glfwSetClipboardString();

    // even without GLEW, there is some minimal functionality working here; if
        // this framebuffer is set, I can use glClear() at the very least
    glfwGetFramebufferSize(window, &fbW, &fbH);
    glViewport(0, 0, fbW, fbH);
    glfwMakeContextCurrent(window); // use this to switch graphics from buffer to buffer
    glfwSetWindowSize(window, 1000, 1000);
        // starting GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, errorMessage1);
    }

    // other mischelleneaous
    glfwSetWindowPos(window, 0, 0);
    glfwSetWindowOpacity(window, .5f);
//    glfwSetWindowMonitor();


    // set the data buffers
    GLfloat verts[] =
    {
        0.f, 0.f,
        1.0f, 1.0f,
        -1.f, 1.f,

//        0.f, 0.f,
        -1.f, -1.f,
        1.f, -1.f
    };

    GLuint myBufferID;
    glGenBuffers(1, &myBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    GLushort indices[] =
    {
        0, 1, 2,
        0, 3, 4
    };

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    double starttime = glfwGetTime();   // seconds; use fractional for less
        // event-closed loop
    while(!glfwWindowShouldClose(window)
    #ifdef TEST
    && glfwGetTime() - starttime < 5
    #endif
    ) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // draw; call all objects, tell them to "draw themselves"; or, have the code go here,
            // more "monolithic" in style

//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
GLFWwindow * activeWindow;

void windowFocusCallback(GLFWwindow * window, int iconified) {
    activeWindow = window;
}

void glfw_2()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context

    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

    GLFWwindow* window2 = glfwCreateWindow( 1024, 768, "Tutorial 02", NULL, NULL);
	if( window2 == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window2, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowFocusCallback(window2, windowFocusCallback);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	do{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear( GL_COLOR_BUFFER_BIT );

		// Draw nothing, see you in tutorial 2 !


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(activeWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(activeWindow) == 0 );    // an "active window's pointer" mechanism is needed

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}



//  -------------------------- --------------------------
//  SDL2 SDL2 SDL2 SDL2 SDL2 SDL2 SDL2 SDL2 SDL2 SDL2 SDL2
//  -------------------------- --------------------------

void sdl2()
{
    SDL_Init(SDL_INIT_EVERYTHING);
}


int main() {
    glfw_2();
}

/// STILL NEEDED:
    /// GUI for "Browse File" (involves <filesystem> and rendering the information from it => files and folders icons => a library for loading images into memory, preferably also a compressor / decompressor for images)
    /// callbacks for: Close Window, Minimize (<e.g.> Gothic 3 stops rendering at this point, and engages a very fast game progress), Maximize (resumes rendering)
    /// a Menu Bar right under the Title bar, with a few Menu Entries and Submenu Entries
    /// a mediocre About Page / (Sub)Window
    ///

/// INTERESTING:
    /// get access to a Firefox instance (if one already exists) or create a new one (if none already exists), open a new tab in it and navigate to a URL


