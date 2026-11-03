#pragma once
#include "ShapeObject.h"
#include "Disc.h"

class Cylinder : public ShapeObject
{
public:
	Cylinder();
	~Cylinder();

	void setColour(float3 colour);

	void setTransformAll(float3 translate, float3 rotation, float3 scale);

	void setCylinderLength(float newLength);

	void setDiscSides(int newSides);

	void renderAll(CMP203::Renderer203& Renderer);

private:
	Disc bottom;
	Disc top;

	float cylinderLength = 2.f;
	int discSides = 10;
};

