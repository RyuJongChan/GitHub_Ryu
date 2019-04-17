#pragma once

#include "GameObject.h"
#include "Label.h"

//0-�븻, 1-����, 2-Ŭ�� (btnState��)
enum {BNormal=0, BPress=1, BClick=2}; 

#define CLICKDEALY 0.2

class Button : public GameObject
{
protected:
	DDS_IMAGE imageN;  
	DDS_IMAGE imageP;  
	
	int btnState; 

	//��ư �ؽ�Ʈ
	Label *label;

	float clickDelay;

public:
	Button(float px, float py);
	virtual ~Button();

	virtual void init();
	virtual void update();
	
	virtual void OnClick();
};