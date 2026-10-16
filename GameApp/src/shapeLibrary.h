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
	std::vector<CMP203::Vertex> drawDisc(CMP203::Renderer203& renderer, int sides, float3 colour, float offset, CMP203::InstanceData parentData, bool flipWindingOrder);

	void drawCube(CMP203::Renderer203& renderer, std::vector<float3> cubeColour, float scaleVal, float3 translationVal, float3 rotationAngle);
	void drawCone(CMP203::Renderer203& renderer, float discSides, float3 coneColour, float scaleVal, float3 translationVal, float3 rotationAngle);
	void drawCylinder(CMP203::Renderer203& renderer, float discSides, float3 cylinderColour, float length, float scaleVal, float3 translationVal, float3 rotationAngle);
};

