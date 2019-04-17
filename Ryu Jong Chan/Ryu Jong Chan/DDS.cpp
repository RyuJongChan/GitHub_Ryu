#include <stdio.h>
#include "DDS.h"
#include "graphic.h"

bool readDDS(const char * filename, DDS_IMAGE *pimage)
{
	//(1)DDS 파일정보 구조체
	DDS_FILE dds;

	//(2)DDS 파일 읽기
	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS 파일 열기 실패 :%d\n", err);
		return false;  //DDS 파일 읽기를 실패했음
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	pimage->width  = dds.header.dwWidth;
	pimage->height = dds.header.dwHeight;

	//DDS 파일의 픽셀데이타 읽어 오기
	pimage->argb = new unsigned int[pimage->width * pimage->height];

	fread(pimage->argb, sizeof(unsigned int), pimage->width*pimage->height, fp); //RGB 값을 읽어옴

	fclose(fp);  //파일 닫기

	return true;  //DDS 파일 읽기가 성공했음
}

bool readDDSRect(const char *filename, int x, int y, int width, int height, DDS_IMAGE *pimage)
{
	//(1)DDS 파일정보 구조체
	DDS_FILE dds;

	//(2)DDS 파일 읽기
	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS 파일 열기 실패 :%d\n", err);
		return false;  //DDS 파일 읽기를 실패했음
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	////////구조체에 전달하는 이미지 넓이와 높이///////////
	pimage->width  = width;    //실제로 읽어온 이미지 가로 크기
	pimage->height = height;   //실제로 읽어온 이미지 세로 크기
	pimage->argb   = new unsigned int[width * height];

	////////실제로 데이타를 읽을 위치로 이동-fseek을 이용/////
	int start = y * dds.header.dwWidth * 4 + x * 4;   //그림의 위치는 픽셀단위로..한픽셀은 4바이트

	fseek(fp, start, SEEK_CUR);  //현재위치에서..지정된 거리만큼...파일 읽기 위치를 이동시켜라!!

	for (int i = 0; i < height; i++)
	{
		//파일에서 i 번째 줄읽어 오기
		fread(&pimage->argb[i*width], width * 4, 1, fp);

		//필요없는 부분 건너 뛰기
		int skip = dds.header.dwWidth * 4 - width * 4;
		fseek(fp, skip, SEEK_CUR);
	}

	fclose(fp);

	return true;
}

///////////////알파 블렌딩으로 DDS 이미지를 출력하는 함수//////////////////////
void drawDDS(int px, int py, DDS_IMAGE *pimage)
{
	//////////////////////RGB 출력하기////////////////////////////
	for (int y = 0; y < pimage->height; y++)  //라인 번호 
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x]; //32비트 rgb임

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

			//x, y 좌표에 그림에서 읽어온 RGB를 출력함
			setPixel(px + x, py + y, (int)r, (int)g, (int)b);
		}
	}
	//////////////////////////////////////////////////////////////
}

////////////////////가산블렌딩으로 DDS 이미지 출력함수///////////////
void drawDDSAdditiveBlending(int px, int py, DDS_IMAGE *pimage)
{
	//////////////////////RGB 출력하기////////////////////////////
	for (int y = 0; y < pimage->height; y++)  //라인 번호 
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x]; //32비트 rgb임

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

			//x, y 좌표에 그림에서 읽어온 RGB를 출력함
			setPixel(px + x, py + y, r, g, b);
		}
	}
	//////////////////////////////////////////////////////////////
}
