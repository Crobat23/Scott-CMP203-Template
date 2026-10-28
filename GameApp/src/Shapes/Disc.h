#pragma once
#include "ShapeObject.h"

class Disc : public ShapeObject
{
public:
	Disc();
	~Disc();

	void buildDisc(float offset);
	void setColour(float3 colour);

	int getSides();
	void setSides(int newSides);
private:
	int sides = 10;
};

