#include "Cylinder.h"

Cylinder::Cylinder()
{

	bottom.buildDisc(0.f, discSides);
	top.buildDisc(cylinderLength, discSides);

	top.flipWindingOrder();

	setVertices(bottom.getVertices());
	
	std::vector<CMP203::Vertex> topVertices = top.getVertices();

	for (auto& i : topVertices) //Add the vertices from the second disc to the vector for the first.
	{
		addVertex(i);
	}

	for (int i = 1; i <= discSides; i++)
	{
		int bottomLeft = i;
		int bottomRight = i - 1;

		if (bottomRight == 0) bottomRight = discSides;

		int topLeft = bottomLeft + discSides + 2;
		int topRight = bottomRight + discSides + 2;

		addIndice(bottomRight);
		addIndice(topRight);
		addIndice(bottomLeft);
		addIndice(bottomLeft);
		addIndice(topRight);
		addIndice(topLeft);
	}

	setTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Cylinder::~Cylinder()
{

}


void Cylinder::setColour(float3 colour)
{
	for (int i = 0; i < getVertices().size(); i++)
	{
		getVertex(i).Colour = colour;
	}

	bottom.setColour(colour);

	top.setColour(colour);
}

void Cylinder::setTransformAll(float3 translate, float3 rotation, float3 scale)
{
	setTransform(translate, rotation, scale);

	bottom.setTransform(getTransform());

	top.setTransform(getTransform());
}

void Cylinder::setCylinderLength(float newLength)
{
	float3 colour = getVertex(0).Colour; // Get the colour to reset the shape to after rebuild.

	cylinderLength = newLength;

	top.buildDisc(cylinderLength, discSides);

	top.flipWindingOrder();

	setVertices(bottom.getVertices());

	std::vector<CMP203::Vertex> topVertices = top.getVertices();

	for (auto& i : topVertices) //Add the vertices from the second disc to the vector for the first.
	{
		addVertex(i);
	}

	setColour(colour);
}

void Cylinder::setDiscSides(int newSides)
{
	float3 colour = getVertex(0).Colour; // Get the colour to reset the shape to after rebuild.

	discSides = newSides;

	bottom.buildDisc(0.f, discSides);
	top.buildDisc(cylinderLength, discSides);

	top.flipWindingOrder();

	setVertices(bottom.getVertices());

	std::vector<CMP203::Vertex> topVertices = top.getVertices();

	for (auto& i : topVertices) //Add the vertices from the second disc to the vector for the first.
	{
		addVertex(i);
	}

	setIndices({});

	for (int i = 1; i <= discSides; i++)
	{
		int bottomLeft = i;
		int bottomRight = i - 1;

		if (bottomRight == 0) bottomRight = discSides;

		int topLeft = bottomLeft + discSides + 2;
		int topRight = bottomRight + discSides + 2;

		addIndice(bottomRight);
		addIndice(topRight);
		addIndice(bottomLeft);
		addIndice(bottomLeft);
		addIndice(topRight);
		addIndice(topLeft);
	}

	setColour(colour);
}

void Cylinder::renderAll(CMP203::Renderer203& Renderer)
{
	Render(Renderer);
	bottom.Render(Renderer);
	top.Render(Renderer);
}