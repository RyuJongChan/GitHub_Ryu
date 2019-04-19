#include <stdio.h>
#include "DDS.h"
#include "graphic.h"

bool readDDS(const char * filename, DDS_IMAGE *pimage)
{
	DDS_FILE dds;
	
	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS Open failed :%d\n", err);
		return false;  
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	pimage->width  = dds.header.dwWidth;
	pimage->height = dds.header.dwHeight;

	//DDS 파일의 PixelData 읽어 오기
	pimage->argb = new unsigned int[pimage->width * pimage->height];

	fread(pimage->argb, sizeof(unsigned int), pimage->width*pimage->height, fp); 

	fclose(fp);  

	return true; 
}

bool readDDSRect(const char *filename, int x, int y, int width, int height, DDS_IMAGE *pimage)
{	
	DDS_FILE dds;

	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS Open failed :%d\n", err);
		return false;  
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	pimage->width  = width;   
	pimage->height = height;   
	pimage->argb   = new unsigned int[width * height];

	int start = y * dds.header.dwWidth * 4 + x * 4;  

	fseek(fp, start, SEEK_CUR);  

	for (int i = 0; i < height; i++)
	{	
		fread(&pimage->argb[i*width], width * 4, 1, fp);
		
		int skip = dds.header.dwWidth * 4 - width * 4;
		fseek(fp, skip, SEEK_CUR);
	}

	fclose(fp);

	return true;
}

//알파 블렌딩
void drawDDS(int px, int py, DDS_IMAGE *pimage)
{	
	for (int y = 0; y < pimage->height; y++) 
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x];

			float         a = (pixel >> 24) / (float)255.0;
			unsigned char r = (pixel >> 16) & 0xff;
			unsigned char g = (pixel >> 8)  & 0xff;
			unsigned char b = (pixel >> 0)  & 0xff;

			unsigned int Bpixel = getPixel(px + x, py + y);

			unsigned char Br = (Bpixel >> 16) & 0xff;
			unsigned char Bg = (Bpixel >>  8) & 0xff;
			unsigned char Bb = (Bpixel >>  0) & 0xff;

			r = r * a + Br * (1 - a);
			g = g * a + Bg * (1 - a);
			b = b * a + Bb * (1 - a);
		
			setPixel(px + x, py + y, (int)r, (int)g, (int)b);
		}
	}	
}

//가산블렌딩
void drawDDSAdditiveBlending(int px, int py, DDS_IMAGE *pimage)
{
	for (int y = 0; y < pimage->height; y++)  
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x]; 

			unsigned char r = (pixel >> 16) & 0xff;
			unsigned char g = (pixel >> 8) & 0xff;
			unsigned char b = (pixel >> 0) & 0xff;

			unsigned int Bpixel = getPixel(px + x, py + y);

			unsigned char Br = (Bpixel >> 16) & 0xff;
			unsigned char Bg = (Bpixel >> 8) & 0xff;
			unsigned char Bb = (Bpixel >> 0) & 0xff;

			r =(unsigned char) (r + Br * (255.0f - r) / 255.0f);
			g =(unsigned char) (g + Bg * (255.0f - g) / 255.0f);
			b =(unsigned char) (b + Bb * (255.0f - b) / 255.0f);
		
			setPixel(px + x, py + y, r, g, b);
		}
	}
}
