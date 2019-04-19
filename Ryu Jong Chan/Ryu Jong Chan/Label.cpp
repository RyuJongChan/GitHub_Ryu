#include "Label.h"
#include "graphic.h"

//lib 파일 추가
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
	
	//한글 코드 변환 (유니코드로 변환하기)
	int len = MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), NULL, 0);  //변환된 유니코드를 저장할 공간 계산
	this->wtxt = new WCHAR[len + 1];

	MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), this->wtxt, len);  //변환 실행
	wtxtLen = len;  //변환된 문자열 길이 저장
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
	//이전에 wtxt의 동적할당 받은 메모리 제거
	delete[] this->wtxt;

	//한글 코드 변환 (유니코드로 변환하기)
	int len = MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), NULL, 0);  //변환된 유니코드를 저장할 공간 계산
	this->wtxt = new WCHAR[len + 1];

	MultiByteToWideChar(CP_ACP, 0, txt, strlen(txt), this->wtxt, len);  //변환 실행
	wtxtLen = len;  //변환된 문자열 길이 저장
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

		int width = face->glyph->bitmap.width;   //읽어온 폰트의 이미지의 가로 크기
		int row = face->glyph->bitmap.rows;      //읽어온 폰트의 이미지의 세로 크기
		unsigned char *data = face->glyph->bitmap.buffer; //폰트 이미지의 a(알파)값

		for (int y = 0; y < row; y++)
		{
			for (int x = 0; x < width; x++)
			{
				float         a = data[y*width + x] / (float)255.0;

				//폰트 색상
				unsigned char r = (fontColor >> 16)  & 0xff;
				unsigned char g = (fontColor >> 8)   & 0xff;
				unsigned char b = (fontColor >> 0)   & 0xff;

				//배경의 RGB 가져옴
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