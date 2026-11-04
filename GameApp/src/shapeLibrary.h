#pragma once
#include "CMP203/Renderer203.h"
class shapeLibrary
{
public:
	shapeLibrary();
	~shapeLibrary();

	void drawTriangle(CMP203::Renderer203 &renderer, float3 colour, float scale, float3 translation, float rotationAngle);
	CMP203::InstanceData drawSquare(CMP203::Renderer203& renderer, float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle);
	CMP203::InstanceData drawSquare(CMP203::Renderer203& renderer, float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle, CMP203::InstanceData parentData);
};

