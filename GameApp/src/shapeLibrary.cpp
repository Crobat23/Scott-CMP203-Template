#include "shapeLibrary.h"

shapeLibrary::shapeLibrary()
{

}

shapeLibrary::~shapeLibrary()
{

}

void shapeLibrary::drawTriangle(CMP203::Renderer203 &renderer, float3 colour, float scaleVal, float3 translationVal, float rotationAngle)
{
	CMP203::Vertex v0, v1, v2;
	CMP203::InstanceData triangleData;
	glm::mat4 transform, rotation, scale;

	scale = glm::scale(float3{ scaleVal, scaleVal, scaleVal });
	transform = glm::translate(translationVal);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle), float3(0, 0, -1));
	rotation = glm::toMat4(rotationQuat);

	triangleData.World = transform * rotation * scale;

	v0.Position = float3(0.0f, 0.0f, 0.0f);
	v1.Position = float3(0.0f, -1.0f, 0.0f);
	v2.Position = float3(1.0f, -1.0f, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2 };
	std::vector<uint32_t> indices = { 0, 1, 2 };

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &triangleData);
}

CMP203::InstanceData shapeLibrary::drawSquare(CMP203::Renderer203& renderer, float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle)
{
	CMP203::Vertex v0, v1, v2, v3;

	CMP203::InstanceData squareData;
	glm::mat4 transform, rotation, scale;

	scale = glm::scale(scaleVal);
	transform = glm::translate(translationVal);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle), float3(0, 0, -1));
	rotation = glm::toMat4(rotationQuat);

	squareData.World = transform * (glm::translate(float3(0.f, -0.5f, 0.f)) * rotation * glm::translate(float3(0.0f, 0.5f, 0.f))) * scale;

	v0.Position = float3(0.0f, 0.0f, 0.0f);
	v1.Position = float3(0.0f, -1.0f, 0.0f);
	v2.Position = float3(1.0f, -1.0f, 0.0f);
	v3.Position = float3(1.0f, 0.0f, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = v3.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3 };
	std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &squareData);

	return squareData;
}

CMP203::InstanceData shapeLibrary::drawSquare(CMP203::Renderer203& renderer, float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle, CMP203::InstanceData parentData)
{
	CMP203::Vertex v0, v1, v2, v3;

	CMP203::InstanceData squareData;
	glm::mat4 transform, rotation, scale;

	scale = glm::scale(scaleVal);
	transform = glm::translate(translationVal);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle), float3(0, 0, -1));
	rotation = glm::toMat4(rotationQuat);

	squareData.World = parentData.World * (transform * (glm::translate(float3(0.0f, -0.5f, 0.f)) * rotation * glm::translate(float3(0.0f, 0.5f, 0.f))) * scale);

	v0.Position = float3(0.0f, 0.0f, 0.0f);
	v1.Position = float3(0.0f, -1.0f, 0.0f);
	v2.Position = float3(1.0f, -1.0f, 0.0f);
	v3.Position = float3(1.0f, 0.0f, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = v3.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3 };
	std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &squareData);

	return squareData;
}
