#pragma once
#include "ShapeObject.h"

class Cube : public ShapeObject
{
public:
	Cube();
	~Cube();

	void setUV(float2 uvValues);
	void setUV(std::vector<float2> uvValues);
	void setColours(std::vector<float3> colours);
};

