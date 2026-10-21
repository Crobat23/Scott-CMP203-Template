#include "ShapeObject.h"

ShapeObject::ShapeObject()
{

}

ShapeObject::~ShapeObject()
{

}

void ShapeObject::setVertices(std::vector<CMP203::Vertex> newVertices)
{
	vertices = newVertices;
}


void ShapeObject::addVertex(CMP203::Vertex newVertex)
{
	vertices.push_back(newVertex);
}

CMP203::Vertex ShapeObject::getVertex(int index)
{
	return vertices.at(index);
}

void ShapeObject::setIndices(std::vector<uint32_t> newIndices)
{
	indices = newIndices;
}

void ShapeObject::addIndice(uint32_t newIndice)
{
	indices.push_back(newIndice);
}

void ShapeObject::setTransform(CMP203::InstanceData newTransform)
{
	transformData = newTransform;
}

CMP203::InstanceData ShapeObject::getTransform()
{
	return transformData;
}

void ShapeObject::setDrawType(enum Skateboard::SKTBD_PRIMITIVE_TOPOLOGY newType)
{
	drawType = newType;
}

void ShapeObject::flipWindingOrder()
{
	int stepSize;

	if (drawType == Skateboard::SKTBD_PRIMITIVE_TOPOLOGY::SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST) stepSize = 3;
	else if (drawType == Skateboard::SKTBD_PRIMITIVE_TOPOLOGY::SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN) stepSize = 2;
	else return;

	for (int i = 1; i < indices.size(); i += stepSize)
	{
		std::swap(indices.at(i), indices.at(i + 1));
	}
}

void ShapeObject::Render(CMP203::Renderer203& Renderer)
{
	Renderer.SetTopology(drawType);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &transformData);
}