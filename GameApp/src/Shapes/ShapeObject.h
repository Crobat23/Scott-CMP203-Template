#pragma once
#include "CMP203/Renderer203.h"

class ShapeObject
{
public:
	ShapeObject();
	~ShapeObject();

	void setVertices(std::vector<CMP203::Vertex> newVertices);
	void addVertex(CMP203::Vertex newVertex);
	CMP203::Vertex& getVertex(int index);
	std::vector<CMP203::Vertex> getVertices();

	void setIndices(std::vector<uint32_t> newIndices);
	void addIndice(uint32_t newIndice);

	void setTransform(float3 translate, float3 rotation, float3 scale);
	void setTransform(float3 translate, float3 rotation, float3 scale, CMP203::InstanceData parentData);
	void setTransform(CMP203::InstanceData parentData);
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