#pragma once
#include "ShapeObject.h"
#include "Disc.h"

class Cone : public ShapeObject
{
public:
	Cone();
	~Cone();

	void setColour(float3 colour);

	void setTransformAll(float3 translate, float3 rotation, float3 scale);

	void setConeHeight(float newHeight) { coneHeight = newHeight; }

	void setDiscSides(int newSides);

	void renderAll(CMP203::Renderer203& Renderer);
private:
	Disc base;

	float coneHeight = 2.f;
};

