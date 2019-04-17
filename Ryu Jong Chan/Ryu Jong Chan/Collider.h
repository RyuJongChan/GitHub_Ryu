#pragma once

#define CTCircle 0
#define CTAABB   1

class Collider
{
protected:
	char name[32];   
	int  tag;
	bool state;     

	float px, py;   
	
	//CTCircle, CTAABB
	int  colType;   

public:
	Collider(const char *name, int tag, float px, float py);
	virtual ~Collider();
	
	virtual void draw();

	void setOwnerPosition(float ownerpx, float ownerpy);
	
	void translate(float dx, float dy);
	
	int getColType();
	
	char * getName();
	int    getTag();  
};