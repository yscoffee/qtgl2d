#include "textures.h"
#include <cassert>
#include <QtOpenGL>
#include <QGLWidget>
#include <iostream>
#include "./bmp/bitmap.h"
#include "soil/SOIL.h"
Textures::Textures():texture_ID(0){

}

void Textures::initial(const char* path){
    memset(&bmpinfo,0,sizeof(bmpinfo));
    loadImage(path);
    //setupTexBuffer();
}
void Textures::loadImage(const char* path){

    /* load an image file directly as a new OpenGL texture */
    texture_ID = SOIL_load_OGL_texture
            (
                path,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_TEXTURE_REPEATS  | SOIL_FLAG_INVERT_Y |
                SOIL_FLAG_POWER_OF_TWO |SOIL_FLAG_COMPRESS_TO_DXT
                );

    /* check for an error during the load process */
    if( 0 == texture_ID )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}
void Textures::loadBMP(const char * path){

   /* image = loadBitmapFile(path, &bmpinfo);
    //image = LoadPixelBitmapFile(imgFile, &bmpinfo);
    width = bmpinfo.bmiHeader.biWidth;
    height = bmpinfo.bmiHeader.biHeight;
    assert(image);
    */
    /* load an image file directly as a new OpenGL texture */
    texture_ID = SOIL_load_OGL_texture
            (
                path,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                );

    /* check for an error during the load process */
    if( 0 == texture_ID )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}

GLubyte * Textures::loadBitmapFile(const char *fileName, BITMAPINFO *bitmapInfo)
{
    FILE            *fp;
    BITMAPFILEHEADER bitmapFileHeader;   // Bitmap file header
    GLubyte         *bitmapImage;      // Bitmap image data
    unsigned int     lInfoSize;         // Size of information
    unsigned int     lBitSize;         // Size of bitmap

    int pixel;
    int p=0;

    fp = fopen(fileName, "rb");
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);         //讀取 bitmap header

    lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);   //Info的size
    fread(bitmapInfo, lInfoSize, 1, fp);


    lBitSize = bitmapInfo->bmiHeader.biSizeImage;                  //配置記憶體
    bitmapImage = new GLubyte[lBitSize];
    fread(bitmapImage, 1, lBitSize, fp);                        //讀取影像檔

    fclose(fp);

    pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

    unsigned char change;
    for( int i=0 ; i<pixel ; i++, p+=3 )
    {
        //交換bitmapImage[p]和bitmapImage[p+2]的值
        change = bitmapImage[p];
        bitmapImage[p] = bitmapImage[p+2];
        bitmapImage[p+2]  = change;
    }
    std::cout<<bitmapImage<<std::endl;


    return (bitmapImage);

}

void Textures::bindTexture()
{
    glEnable(GL_TEXTURE_2D);
    glColor3ub(255,255,255);
    //switch to current Texture
    glBindTexture(GL_TEXTURE_2D,texture_ID);
}

Textures::~Textures()
{
    delete [] image;
}

void Textures::printInnter()
{
    int pixel = (bmpinfo.bmiHeader.biWidth)*(bmpinfo.bmiHeader.biHeight);

    int p=0;
    for( int i=0 ; i<pixel ; i++, p+=3 )
    {
        std::cout<<image[p]+'0';
    }
    std::cout<<endl;
}

void Textures::setupTexBuffer()
{
    //get a unused ID.
    glGenTextures(1,&texture_ID);
    //use it
    glBindTexture(GL_TEXTURE_2D,texture_ID);
    //attributes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    std::cerr<<"Texture settings:"<<gluErrorString(glGetError())<<endl;
    //allocate
    //glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    int res=gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGB,GL_UNSIGNED_BYTE,image);
    if(res!=0){
        std::cerr<<"Texture build failed\n"
                <<gluErrorString(res)<<endl;
        //exit(1);
    }



}
