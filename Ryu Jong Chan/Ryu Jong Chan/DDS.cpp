#include <stdio.h>
#include "DDS.h"
#include "graphic.h"

bool readDDS(const char * filename, DDS_IMAGE *pimage)
{
	//(1)DDS �������� ����ü
	DDS_FILE dds;

	//(2)DDS ���� �б�
	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS ���� ���� ���� :%d\n", err);
		return false;  //DDS ���� �б⸦ ��������
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	pimage->width  = dds.header.dwWidth;
	pimage->height = dds.header.dwHeight;

	//DDS ������ �ȼ�����Ÿ �о� ����
	pimage->argb = new unsigned int[pimage->width * pimage->height];

	fread(pimage->argb, sizeof(unsigned int), pimage->width*pimage->height, fp); //RGB ���� �о��

	fclose(fp);  //���� �ݱ�

	return true;  //DDS ���� �бⰡ ��������
}

bool readDDSRect(const char *filename, int x, int y, int width, int height, DDS_IMAGE *pimage)
{
	//(1)DDS �������� ����ü
	DDS_FILE dds;

	//(2)DDS ���� �б�
	FILE * fp;
	errno_t err;

	err = fopen_s(&fp, filename, "rb");

	if (err != 0)
	{
		printf("DDS ���� ���� ���� :%d\n", err);
		return false;  //DDS ���� �б⸦ ��������
	}

	fread(&dds, sizeof(DDS_FILE), 1, fp);

	////////����ü�� �����ϴ� �̹��� ���̿� ����///////////
	pimage->width  = width;    //������ �о�� �̹��� ���� ũ��
	pimage->height = height;   //������ �о�� �̹��� ���� ũ��
	pimage->argb   = new unsigned int[width * height];

	////////������ ����Ÿ�� ���� ��ġ�� �̵�-fseek�� �̿�/////
	int start = y * dds.header.dwWidth * 4 + x * 4;   //�׸��� ��ġ�� �ȼ�������..���ȼ��� 4����Ʈ

	fseek(fp, start, SEEK_CUR);  //������ġ����..������ �Ÿ���ŭ...���� �б� ��ġ�� �̵����Ѷ�!!

	for (int i = 0; i < height; i++)
	{
		//���Ͽ��� i ��° ���о� ����
		fread(&pimage->argb[i*width], width * 4, 1, fp);

		//�ʿ���� �κ� �ǳ� �ٱ�
		int skip = dds.header.dwWidth * 4 - width * 4;
		fseek(fp, skip, SEEK_CUR);
	}

	fclose(fp);

	return true;
}

///////////////���� �������� DDS �̹����� ����ϴ� �Լ�//////////////////////
void drawDDS(int px, int py, DDS_IMAGE *pimage)
{
	//////////////////////RGB ����ϱ�////////////////////////////
	for (int y = 0; y < pimage->height; y++)  //���� ��ȣ 
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x]; //32��Ʈ rgb��

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

			//x, y ��ǥ�� �׸����� �о�� RGB�� �����
			setPixel(px + x, py + y, (int)r, (int)g, (int)b);
		}
	}
	//////////////////////////////////////////////////////////////
}

////////////////////����������� DDS �̹��� ����Լ�///////////////
void drawDDSAdditiveBlending(int px, int py, DDS_IMAGE *pimage)
{
	//////////////////////RGB ����ϱ�////////////////////////////
	for (int y = 0; y < pimage->height; y++)  //���� ��ȣ 
	{
		for (int x = 0; x < pimage->width; x++)
		{
			unsigned int pixel = pimage->argb[y*pimage->width + x]; //32��Ʈ rgb��

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

			//x, y ��ǥ�� �׸����� �о�� RGB�� �����
			setPixel(px + x, py + y, r, g, b);
		}
	}
	//////////////////////////////////////////////////////////////
}
