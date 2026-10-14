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

std::vector<CMP203::Vertex> shapeLibrary::drawDisc(CMP203::Renderer203& renderer, int sides, float3 colour, CMP203::InstanceData parentData)
{
	//Assumes radius of 1. Size can be changed through transforms.

	float interval = (2 * SKTBD_PI) / sides;
	float angle = 0;

	CMP203::Vertex v0, v1;
	v0.Position = float3(0.f, 0.f, 0.f);
	v1.Position = float3(cos(angle), sin(angle), 0.f);
	v0.Colour = v1.Colour = colour;


	std::vector<CMP203::Vertex> vertices = { v0 };
	std::vector<uint32_t> indices = { 0,1 };

	if (sides < 3) return vertices;

	for (int i = 0; i <= sides; i++)
	{
		angle += interval;
		if (angle > 360) angle = 360;

		CMP203::Vertex newVertex;
		newVertex.Position = float3(cos(angle), sin(angle), 0.f);
		newVertex.Colour = colour;

		vertices.push_back(newVertex);
		indices.push_back(i + 2);
		indices.push_back(i + 2);
	}
	indices.push_back(1);

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &parentData);

	return vertices;
}

void shapeLibrary::drawCube(CMP203::Renderer203& renderer, std::vector<float3> cubeColour, float scaleVal, float3 translationVal, float3 rotationAngle)
{
	CMP203::Vertex v0, v1, v2, v3, v4, v5, v6, v7;

	CMP203::InstanceData cubeData;
	glm::mat4 transform, rotationX, rotationY, rotationZ, scale;

	scale = glm::scale(float3(scaleVal, scaleVal, scaleVal));
	transform = glm::translate(translationVal);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[0]), float3(-1, 0, 0));
	rotationX = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[1]), float3(0, -1, 0));
	rotationY = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[2]), float3(0, 0, -1));
	rotationZ = glm::toMat4(rotationQuat);

	cubeData.World = transform * rotationX * rotationY * rotationZ * scale;

	v0.Position = float3(-1.f, -1.f, 1.f);
	v1.Position = float3(1.f, -1.f, 1.f);
	v2.Position = float3(1.f, 1.f, 1.f);
	v3.Position = float3(-1.f, 1.f, 1.f);
	v4.Position = float3(-1.f, -1.f, -1.f);
	v5.Position = float3(1.f, -1.f, -1.f);
	v6.Position = float3(1.f, 1.f, -1.f);
	v7.Position = float3(-1.f, 1.f, -1.f);

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3, v1, v5, v6, v2, v5, v4, v7, v6, v4, v0, v3, v7, v3, v2, v6, v7, v4, v5, v1, v0 };
	std::vector<uint32_t> indices = { 0,2,1,0,3,2, 4,6,5,4,7,6, 8,10,9,8,11,10, 12,14,13,12,15,14, 16,18,17,16,19,18, 20,22,21,20,23,22 };

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			vertices.at(i * 4 + j).Colour = cubeColour.at(i);
		}
	}

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &cubeData);
}

void shapeLibrary::drawCone(CMP203::Renderer203& renderer, float discSides, float3 coneColour, float scaleVal, float3 translationVal, float3 rotationAngle)
{
	CMP203::Vertex v0;

	CMP203::InstanceData coneData;
	glm::mat4 transform, rotationX, rotationY, rotationZ, scale;

	scale = glm::scale(float3{ scaleVal, scaleVal, scaleVal });
	transform = glm::translate(translationVal);

	glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[0]), float3(-1, 0, 0));
	rotationX = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[1]), float3(0, -1, 0));
	rotationY = glm::toMat4(rotationQuat);
	rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[2]), float3(0, 0, -1));
	rotationZ = glm::toMat4(rotationQuat);

	coneData.World = transform * rotationX * rotationY * rotationZ * scale;

	std::vector<CMP203::Vertex> vertices = drawDisc(renderer, discSides, coneColour, coneData);

	v0.Position = vertices.at(0).Position;
	v0.Position += float3(0.f, 0.f, 2.f);

	vertices.push_back(v0);
	unsigned int topPoint = (vertices.size() - 1);
	std::vector<uint32_t> indices = { topPoint };

	for (int i = 1; i < topPoint; i++)
	{
		indices.push_back(i);
		indices.push_back(i);
	}

	renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
	renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &coneData);
}