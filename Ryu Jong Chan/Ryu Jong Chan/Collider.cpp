#include "Collider.h"
#include <iostream>

Collider::Collider(const char *name, int tag, float px, float py)
{
	strcpy_s(this->name, name);
	
	this->px = px;
	this->py = py;

	this->tag   = tag;
	this->state = true;
}

Collider::~Collider()
{
}

void Collider::draw()
{
}

void Collider::setOwnerPosition(float ownerpx, float ownerpy)
{
	px = px + ownerpx;
	py = py + ownerpy;
}

void Collider::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;
}

int  Collider::getColType()
{
	return colType;
}

char * Collider::getName()
{
	return name;
}

int Collider::getTag()
{
	return tag;
}
