#pragma once

#include <vector>

#include "Collider.h"
#include "DDS.h"

class GameObject
{
protected:
	//게임오브젝트 기본 속성
	char name[32];
	int  tag;
	bool state;

	//게임오브젝트의 포지션, 회전, 스케일
	float px, py;
	float angle;
	float sx, sy;		

	//DDS 이미지 저장 
	DDS_IMAGE sprite;

	//충돌체 저장용 stl vector
	std::vector<Collider *> colliders;

	//자식 게임오브젝트 저장용 stl vector
	std::vector<GameObject *> childObjs;

public:
	//점수, 생명 전역변수
	static int GameScore;
	static int Life;

	GameObject(const char * name, int tag, float px, float py);
	virtual ~GameObject();

	//충돌체 추가 함수
	void addCollider(Collider * col);

	//자식오브젝트 추가, 제거 함수
	void addChildObject(GameObject * o, int order=0);
	void delChildObject(GameObject * o);
	
	//부모 좌표 지정함수(localPosition)
	void setParentPosition(float parentx, float parenty);

	//충돌이벤트를 전달 받는 가상함수
	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);

	//자신이 특정 오브젝트에 데미지를 주는 가상함수
	virtual void DoDamage(GameObject * fromObj, float d);

	//게터
	char * getName();
	int    getTag();

	virtual void init();
	virtual void update();
	virtual void draw();

	//게임오브젝트 이동함수
	void translate(float tx, float ty);

	//충돌체 정보
	int colSize();
	Collider * colAt(int i);
};