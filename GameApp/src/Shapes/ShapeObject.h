#pragma once
#include "CMP203/Renderer203.h"

class ShapeObject
{
public:
	ShapeObject();
	~ShapeObject();

	void setVertices(std::vector<CMP203::Vertex> newVertices);
	void addVertex(CMP203::Vertex newVertex);
	CMP203::Vertex getVertex(int index);

	void setIndices(std::vector<uint32_t> newIndices);
	void addIndice(uint32_t newIndice);

	void setTransform(CMP203::InstanceData newTransform);
	CMP203::InstanceData getTransform();

	void setDrawType(enum Skateboard::SKTBD_PRIMITIVE_TOPOLOGY newType);

	void flipWindingOrder();

	void Render(CMP203::Renderer203& Renderer);

private:
	enum Skateboard::SKTBD_PRIMITIVE_TOPOLOGY drawType;
	std::vector<CMP203::Vertex> vertices;
	std::vector<uint32_t> indices;
	CMP203::InstanceData transformData;
};