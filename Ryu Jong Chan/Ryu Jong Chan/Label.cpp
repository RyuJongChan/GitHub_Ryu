#include "Label.h"
#include "graphic.h"

//lib ���� �߰�
#pragma comment(lib, "font/freetype.lib")

Label::Label(const char * txt, const char * ttf, int fontSize, unsigned int fontColor, float px, float py, int tag)
	:GameObject("label", tag, px, py)
{	
	if (FT_Init_FreeType(&library) != 0)
	{
		printf("FreeType Fontlib init failed\n");
	}
	
	if (FT_New_Face(library, ttf, 0, &face) != 0)
	{
		printf("ttf file load failed\n");
	}
	
	FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	this->fontSize  = fontSize;
	this->fontColor = fontColor;
	
	//�ѱ� �ڵ� ��ȯ (�����ڵ�� ��ȯ�ϱ�)
	int len = MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), NULL, 0);  //��ȯ�� �����ڵ带 ������ ���� ���
	this->wtxt = new WCHAR[len + 1];

	MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), this->wtxt, len);  //��ȯ ����
	wtxtLen = len;  //��ȯ�� ���ڿ� ���� ����
}

Label::~Label()
{
	delete[] wtxt;

	FT_Done_Face(face);
	FT_Done_FreeType(library);	
}

void Label::setFontColor(unsigned int fontColor)
{
	this->fontColor = fontColor;
}

void Label::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
	FT_Set_Pixel_Sizes(face, fontSize, fontSize);
}

void Label::setText(const char * txt)
{
	//������ wtxt�� �����Ҵ� ���� �޸� ����
	delete[] this->wtxt;

	//�ѱ� �ڵ� ��ȯ (�����ڵ�� ��ȯ�ϱ�)
	int len = MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), NULL, 0);  //��ȯ�� �����ڵ带 ������ ���� ���
	this->wtxt = new WCHAR[len + 1];

	MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), this->wtxt, len);  //��ȯ ����
	wtxtLen = len;  //��ȯ�� ���ڿ� ���� ����
}

void Label::draw()
{
	float fontx = px;
	float fonty = py;

	for (int i = 0; i < wtxtLen; i++)
	{
		int idx = FT_Get_Char_Index(face, wtxt[i]);
		FT_Load_Glyph(face, idx, FT_LOAD_DEFAULT);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		int width = face->glyph->bitmap.width;   //�о�� ��Ʈ�� �̹����� ���� ũ��
		int row = face->glyph->bitmap.rows;      //�о�� ��Ʈ�� �̹����� ���� ũ��
		unsigned char *data = face->glyph->bitmap.buffer; //��Ʈ �̹����� a(����)��

		for (int y = 0; y < row; y++)
		{
			for (int x = 0; x < width; x++)
			{
				float         a = data[y*width + x] / (float)255.0;

				//��Ʈ ����
				unsigned char r = (fontColor >> 16)  & 0xff;
				unsigned char g = (fontColor >> 8)   & 0xff;
				unsigned char b = (fontColor >> 0)   & 0xff;

				//����� RGB ������
				unsigned int Bpixel = getPixel((int)fontx + x, (int)fonty + y);

				unsigned char Br = (Bpixel >> 16)  & 0xff;
				unsigned char Bg = (Bpixel >> 8)   & 0xff;
				unsigned char Bb = (Bpixel >> 0)   & 0xff;

				r = r * a + Br * (1 - a);
				g = g * a + Bg * (1 - a);
				b = b * a + Bb * (1 - a);
				
				setPixel((int)fontx+x, (int)fonty+y, r, g, b);				
			}			
		}

		fontx=fontx+face->glyph->advance.x / 64;
		fonty=fonty+face->glyph->advance.y / 64;
	}
}