#ifndef TEXTURES_H
#define TEXTURES_H

#include <QtOpenGL>

class Textures{

private:
    int width;
    int height;
    GLubyte *image;
    BITMAPINFO bmpinfo;
    GLuint texture_ID;
    void loadBMP(const char *);
    void setupTexBuffer();
public:

    Textures();
    ~Textures();
    GLubyte *loadBitmapFile(const char *, BITMAPINFO *);
    void printInnter();
    void initial(const char* path);
    void bindTexture();
    void loadImage(const char *path);

    inline
    GLuint getTID(){return texture_ID;}
};




#endif // TEXTURES_H
