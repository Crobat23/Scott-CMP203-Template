#include "Cone.h"

Cone::Cone()
{
	CMP203::Vertex v0;

	base.buildDisc(0.f, discSides);
	setVertices(base.getVertices());

	v0.Position = getVertex(0).Position;
	v0.Position += float3(0.f, 0.f, coneHeight);

	addVertex(v0);
	unsigned int topPoint = (getVertices().size() - 1);
	setIndices({ topPoint });

	for (int i = topPoint - 1; i >= 1; i--)
	{
		addIndice(i);
	}

	setTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}

Cone::~Cone()
{

}

void Cone::setTransformAll(float3 translate, float3 rotation, float3 scale)
{
	setTransform(translate, rotation, scale);
	
	base.setTransform(getTransform());
}

void Cone::setColour(float3 colour)
{
	for (int i = 0; i < getVertices().size(); i++)
	{
		getVertex(i).Colour = colour;
	}
	base.setColour(colour);
}

void Cone::setConeHeight(float newHeight)
{
	coneHeight = newHeight;
	int topPoint = getVertices().size() - 1;
	
	getVertex(topPoint).Position = getVertex(0).Position;
	getVertex(topPoint).Position += float3(0.f, 0.f, coneHeight);
}

void Cone::setDiscSides(int newSides)
{
	float3 colour = getVertex(0).Colour; //Store the current colour of the cone in order to restore it after vertices change.

	discSides = newSides;
	base.buildDisc(0.f, newSides);

	setVertices(base.getVertices());

	CMP203::Vertex v0;

	v0.Position = getVertex(0).Position;
	v0.Position += float3(0.f, 0.f, coneHeight);

	addVertex(v0);
	unsigned int topPoint = (getVertices().size() - 1);
	setIndices({ topPoint });

	for (int i = topPoint - 1; i >= 1; i--)
	{
		addIndice(i);
	}

	setColour(colour);
}

void Cone::renderAll(CMP203::Renderer203& Renderer)
{
	Render(Renderer);
	base.Render(Renderer);
}