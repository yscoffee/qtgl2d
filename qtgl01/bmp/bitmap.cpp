/* 
 *	BITMAP.CPP
 *	讀取 BMP 圖檔至記憶體
 *
 */

#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include "bitmap.h"

GLubyte *LoadBitmapFile(const char *fileName, BITMAPINFO *bitmapInfo)
{

	FILE				*fp;
	BITMAPFILEHEADER	bitmapFileHeader;	// Bitmap file header
	GLubyte				*bitmapImage;		// Bitmap image data
	unsigned int		lInfoSize;			// Size of information
	unsigned int		lBitSize;			// Size of bitmap

	fp = fopen(fileName, "rb");

	if (fp == NULL)
		return NULL;

	// 讀取 bitmap header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1 , fp);

	 

	// Check for BM
	if (bitmapFileHeader.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}
	
	// 讀取 bitmap information header
	lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);		// Info size
	if(fread(bitmapInfo, 1, lInfoSize, fp) < lInfoSize)
	{
		fclose(fp);
		return NULL;
	}

	// 配置記憶體
	lBitSize = bitmapInfo->bmiHeader.biSizeImage;
	bitmapImage = new BYTE[lBitSize];
	// Verify memory allocation
	if (!bitmapImage)
	{
		fclose(fp);
		return NULL;
	}

	// 讀取影像檔
	if(fread(bitmapImage, 1, lBitSize, fp) < lBitSize)
	{
		delete [] bitmapImage;
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bitmapImage;
}

GLubyte *LoadPixelBitmapFile(const char *fileName, BITMAPINFO *bitmapInfo)
{

	FILE				*fp;
	BITMAPFILEHEADER	bitmapFileHeader;	// Bitmap file header
	GLubyte				*bitmapImage;		// Bitmap image data
	unsigned int		lInfoSize;			// Size of information
	unsigned int		lBitSize;			// Size of bitmap

	fp = fopen(fileName, "rb");

	if (fp == NULL)
		return NULL;

	// 讀取 bitmap header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1 , fp);

	 

	// Check for BM
	if (bitmapFileHeader.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}
	
	// 讀取 bitmap information header
	lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);		// Info size
	if(fread(bitmapInfo, 1, lInfoSize, fp) < lInfoSize)
	{
		fclose(fp);
		return NULL;
	}

	// 配置記憶體
	lBitSize = bitmapInfo->bmiHeader.biSizeImage;
	bitmapImage = new BYTE[lBitSize];
	// Verify memory allocation
	if (!bitmapImage)
	{
		fclose(fp);
		return NULL;
	}

	// 讀取影像檔
	if(fread(bitmapImage, 1, lBitSize, fp) < lBitSize)
	{
		delete [] bitmapImage;
		fclose(fp);
		return NULL;
	}
   
	fclose(fp);
	// swap the red and blue components 
	unsigned char temp; 
    for (int k=0; k<lBitSize; k+=3)
       { temp = bitmapImage[k];
         bitmapImage[k] = bitmapImage[k+2];
         bitmapImage[k+2] = temp; 
       } 
	
	return bitmapImage;
}
