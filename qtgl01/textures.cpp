#include "textures.h"
#include <cassert>
#include <QtOpenGL>
#include <QGLWidget>
#include <iostream>
#include "./bmp/bitmap.h"

Textures::Textures(const char* path){
    memset(&bmpinfo,0,sizeof(bmpinfo));
    loadBMP(path);
}

void Textures::loadBMP(const char * path){

    image = LoadBitmapFile(path, &bmpinfo);
    //image = LoadPixelBitmapFile(imgFile, &bmpinfo);
    width = bmpinfo.bmiHeader.biWidth;
    height = bmpinfo.bmiHeader.biHeight;
    assert(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    int res=gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGB,GL_UNSIGNED_BYTE,image);

    if(res!=0){
        //std::cerr<<"Texture build failed\n"
        //        <<gluErrorString(res)<<endl;
        //exit(1);
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

   //此時傳回bitmapImage的話，顏色會是BGR順序，下面迴圈會改順序為RGB
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
