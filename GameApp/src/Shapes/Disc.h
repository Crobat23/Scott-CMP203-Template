#pragma once
#include "ShapeObject.h"

class Disc : public ShapeObject
{
public:
	Disc();
	~Disc();

	void buildDisc(float offset, int sides);
	void setColour(float3 colour);
private:
};

