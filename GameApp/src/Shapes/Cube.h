#pragma once
#include "ShapeObject.h"

class Cube : public ShapeObject
{
public:
	Cube();
	~Cube();

	void setColours(std::vector<float3> colours);
};

