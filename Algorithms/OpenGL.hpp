#ifndef OPENGL_HPP_INCLUDED
#define OPENGL_HPP_INCLUDED

    // inverse order of inclusion
#include <GL/glew.h>
#include <GL/glut.h>    // freeglut3-dev
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glx.h> // what for ? for X.org
#include <SDL2/SDL.h>

/// TD
/*
    OOP approach: each object defines its own procedures for loading itself
        in OpenGL and rendering itself; likely unoptimal, but easy to use (*?);
        why ? because the rendering is "local", unaware of the "global complexity"
    verbose of OpenGL, ~ $:"glxinfo | grep OpenGL" (*?)
    check pre-existing glutInit() initialization, otherwise it just crashes
    shader loader and compiler; then the progarm attaches and final program linkage
*/


/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();

   glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
void StartGL_v1() { // ("SOLVED") [run-time bug, seg-faults]
    int argc = 0;   // "bug fix"
    char* argv {""};    // "bug fix"
    glutInit(&argc, &argv);  // this here simply doesn't handle receiving nulls as pointers
        // and accesses invalid memory... "unsafe"

    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the infinitely event-processing loop
}

// ------------------------
/// another variant
// ------------------------
#include <stdio.h>

void StartGL_v2() {
    int argc = 0;
    char* argv {""};

    glutInit(&argc, &argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("red 3D lighted cube");
    printf("GL_VERSION = %s\n",glGetString(GL_VERSION) );
}
void Info_v2() {
#define PROGRAM "glversion"
    int argc = 0;
    char* argv {""};

    char *version = NULL;
    char *vendor = NULL;
    char *renderer = NULL;
    char *extensions = NULL;
    GLuint idWindow = 0;
    int	glutVersion;


//    glutInit(&argc, &argv);
//    glutInitWindowSize(1,1);
//    glutInitDisplayMode(GLUT_RGBA);
    idWindow = glutCreateWindow(PROGRAM);
    glutHideWindow();

    glutVersion = glutGet(0x01FC);
    version =     (char*)glGetString(GL_VERSION);
    vendor =      (char*)glGetString(GL_VENDOR);
    renderer =    (char*)glGetString(GL_RENDERER);
    extensions =  (char*)glGetString(GL_EXTENSIONS);

    printf("GLUT=%d\nVERSION=%s\nVENDOR=%s\nRENDERER=%s\nEXTENSIONS=%s\n",
    glutVersion,version,vendor,renderer,extensions);

    glutDestroyWindow(idWindow);
#undef PROGRAM
}
// ------------------------
/// another variant
// ------------------------

// ------------------------
/// another variant
// ------------------------

#endif // OPENGL_HPP_INCLUDED
