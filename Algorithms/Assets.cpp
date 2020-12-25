#include "Assets.hpp"

GLuint LoadBMPIntoOpenGL(Bitmap_v2 bitmap) {
    GLuint textureID;   // apparently the name of a bitmap changes into "texture"
        // when it is loaded into a 3D renderer / engine / rasterizer / whatever (?!)
    glGenTextures(1, &textureID);

    // author: "bind the newly create texture; all future functions will modify this texture"
        // ah, the "selector / selection" mechanism
    glBindTexture(GL_TEXTURE_2D, textureID);    // also, it offers "contextual information" about it, interesting (*?)

    // author: "give the image to OpenGL"
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.height, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmap.data);

        // I suppose it has something to do with adjusting the input RGB(A) [0, 255]
        // to something related to either the video card of the display device (?!)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // author: "`very important` to use `power of two` texture sizes", for whatever reason
        // -> "`bad`: 127 * 128"; well, to me "bad" means "it still works"
}
