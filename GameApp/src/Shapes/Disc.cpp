#include "Disc.h"

Disc::Disc()
{

}

Disc::~Disc()
{

}

void Disc::buildDisc(float offset)
{
	//Assumes radius of 1. Size can be changed through transforms.

	float interval = (2 * SKTBD_PI) / sides;
	float angle = 0;

	CMP203::Vertex v0, v1;
	v0.Position = float3(0.f, 0.f, offset);
	v1.Position = float3(cos(angle), sin(angle), offset);

	setVertices({ v0 });
	setIndices({ 0,1 });

	for (int i = 0; i <= sides; i++)
	{
		angle += interval;
		if (angle > 360) angle = 360;

		CMP203::Vertex newVertex;
		newVertex.Position = float3(cos(angle), sin(angle), offset);

		addVertex(newVertex);
		addIndice(i + 2);
		addIndice(i + 2);
	}
	addIndice(1);

	setDrawType(Skateboard::SKTBD_PRIMITIVE_TOPOLOGY::SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}

void Disc::setColour(float3 colour)
{
	for (int i = 0; i <= sides + 1; i++)
	{
		getVertex(i).Colour = colour;
	}
}

void Disc::setSides(int newSides)
{
	sides = newSides;
}

int Disc::getSides()
{
	return sides;
}