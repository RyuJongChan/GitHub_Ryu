#pragma once

#include <vector>
#include "GameObject.h"

class Animation : public GameObject
{
private:
	//DDS 이미지 stl Vector
	std::vector<DDS_IMAGE> aniSprite;

	//애니메이션 구동 변수
	float aniRate;   
	float aniTimer;  
	int   aniIndex;   	
	int   blendMode;  //0 - 알파블렌딩
	                  //1 - 가산블렌딩

public:
	Animation(float px, float py);
	Animation(float px, float py, const char * name, int tag);
	virtual ~Animation();

	void addAniSprite(DDS_IMAGE image);

	//애니메이션 속도 변경함수
	void setAniRate(float aniRate);

	//애니메이션 블렌딩 모드 변경함수
	void setBlendMode(int mode);
	
	virtual void init();
	virtual void update();
	virtual void draw();
};
