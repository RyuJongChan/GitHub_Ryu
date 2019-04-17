#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H

#include "GameObject.h"

class Label : public GameObject
{
private:	
	int fontSize;	
	unsigned int fontColor;

	//출력 메시지 저장 배열(유니코드 변환)
	WCHAR *wtxt;
	int    wtxtLen;

	FT_Library  library;	
	FT_Face face;

public:
	Label(const char * txt, const char * ttf, int fontSize, unsigned int fontColor, float px, float py, int tag);
	virtual ~Label();
	
	virtual void draw();

	//폰트 속성 변경 함수
	void setFontColor(unsigned int fontColor);
	void setFontSize(int fontSize);
	void setText(const char * txt);
};