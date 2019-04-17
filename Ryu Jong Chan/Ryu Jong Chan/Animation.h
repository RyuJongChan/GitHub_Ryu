#pragma once

#include <vector>
#include "GameObject.h"

class Animation : public GameObject
{
private:
	//DDS �̹��� stl Vector
	std::vector<DDS_IMAGE> aniSprite;

	//�ִϸ��̼� ���� ����
	float aniRate;   
	float aniTimer;  
	int   aniIndex;   	
	int   blendMode;  //0 - ���ĺ���
	                  //1 - �������

public:
	Animation(float px, float py);
	Animation(float px, float py, const char * name, int tag);
	virtual ~Animation();

	void addAniSprite(DDS_IMAGE image);

	//�ִϸ��̼� �ӵ� �����Լ�
	void setAniRate(float aniRate);

	//�ִϸ��̼� ���� ��� �����Լ�
	void setBlendMode(int mode);
	
	virtual void init();
	virtual void update();
	virtual void draw();
};
