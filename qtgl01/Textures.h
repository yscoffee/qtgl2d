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

public:

    explicit Textures(const char* path);
    ~Textures();
    GLubyte *loadBitmapFile(const char *, BITMAPINFO *);
    void printInnter();
    void bindTexture();
};




#endif // TEXTURES_H
