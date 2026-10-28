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

CMP203::Vertex &ShapeObject::getVertex(int index)
{
	return vertices.at(index);
}

std::vector<CMP203::Vertex> ShapeObject::getVertices()
{
	return vertices;
}

void ShapeObject::setIndices(std::vector<uint32_t> newIndices)
{
	indices = newIndices;
}

void ShapeObject::addIndice(uint32_t newIndice)
{
	indices.push_back(newIndice);
}

void ShapeObject::setTransform(float3 translate, float3 rotation, float3 scale)
{
	glm::mat4 _transform, _rotationX, _rotationY, _rotationZ, _scale;

	_scale = glm::scale(scale);
	_transform = glm::translate(translate);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[0]), float3(-1, 0, 0));
	_rotationX = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[1]), float3(0, -1, 0));
	_rotationY = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[2]), float3(0, 0, -1));
	_rotationZ = glm::toMat4(rotationQuat);

	transformData.World = _transform * _rotationX * _rotationY * _rotationZ * _scale;
}

void ShapeObject::setTransform(float3 translate, float3 rotation, float3 scale, CMP203::InstanceData parentData)
{
	glm::mat4 _transform, _rotationX, _rotationY, _rotationZ, _scale;

	_scale = glm::scale(scale);
	_transform = glm::translate(translate);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[0]), float3(-1, 0, 0));
	_rotationX = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[1]), float3(0, -1, 0));
	_rotationY = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotation[2]), float3(0, 0, -1));
	_rotationZ = glm::toMat4(rotationQuat);

	transformData.World = parentData.World * _transform * _rotationX * _rotationY * _rotationZ * _scale;
}

void ShapeObject::setTransform(CMP203::InstanceData parentData)
{
	transformData.World = parentData.World;
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