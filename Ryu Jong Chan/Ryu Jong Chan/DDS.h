#pragma once
#include <Windows.h>

//DDS파일 픽셀 정보 저장
struct DDS_PIXELFORMAT
{
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwABitMask;
};

//DDS 이미지 정보 저장
struct  DDS_HEADER
{
	DWORD           dwSize;
	DWORD           dwFlags;
	DWORD           dwHeight;       
	DWORD           dwWidth;        
	DWORD           dwPitchOrLinearSize;
	DWORD           dwDepth;
	DWORD           dwMipMapCount;
	DWORD           dwReserved1[11];
	DDS_PIXELFORMAT ddspf;
	DWORD           dwCaps;
	DWORD           dwCaps2;
	DWORD           dwCaps3;
	DWORD           dwCaps4;
	DWORD           dwReserved2;
};

struct DDS_FILE
{
	DWORD      magic;
	DDS_HEADER header;
};

struct DDS_IMAGE
{
	int width;         
	int height;         
	unsigned int *argb; 
};

bool readDDS(const char * filename, DDS_IMAGE *pimage);
bool readDDSRect(const char *filename, int x, int y, int width, int height, DDS_IMAGE *pimage);

void drawDDS(int px, int py, DDS_IMAGE *pimage);
void drawDDSAdditiveBlending(int px, int py, DDS_IMAGE *pimage);