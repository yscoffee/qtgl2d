
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "./bitmap.cpp"

#ifdef WIN32
#include <windows.h>
#include <wingdi.h>
#else	// WIN32

#ifdef __cplusplus
extern "C" {
#endif

typedef long  LONG;
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;



#pragma pack(push,2)
typedef struct                      
{
	WORD    bfType;
    DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;      
} BITMAPFILEHEADER;
#pragma pack(pop)


typedef struct  
{
	DWORD      biSize;
    LONG       biWidth;
    LONG       biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG       biXPelsPerMeter;
    LONG       biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant; 
} BITMAPINFOHEADER;

#define BI_RGB       0             
#define BI_RLE8      1           
#define BI_RLE4      2             
#define BI_BITFIELDS 3             

typedef struct                       
{
	BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;      
} RGBQUAD;

typedef struct                      
{
    BITMAPINFOHEADER bmiHeader;      
    RGBQUAD          bmiColors[256]; 
} BITMAPINFO;

#ifdef __cplusplus
}
#endif

#endif	// WIN32

#endif	// _BITMAP_H_

GLubyte *LoadBitmapFile(const char *fileName, BITMAPINFO *bitmapInfo);
// the following function added by Rich Wang on Nov. 25, 2005. 
GLubyte *LoadPixelBitmapFile(const char *fileName, BITMAPINFO *bitmapInfo);

