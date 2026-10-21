#include "Cube.h"

Cube::Cube()
{
	CMP203::Vertex v0, v1, v2, v3, v4, v5, v6, v7;

	//CMP203::InstanceData cubeData;
	//glm::mat4 transform, rotationX, rotationY, rotationZ, scale;

	//scale = glm::scale(float3(scaleVal, scaleVal, scaleVal));
	//transform = glm::translate(translationVal);

	//glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[0]), float3(-1, 0, 0));
	//rotationX = glm::toMat4(rotationQuat);
	//rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[1]), float3(0, -1, 0));
	//rotationY = glm::toMat4(rotationQuat);
	//rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[2]), float3(0, 0, -1));
	//rotationZ = glm::toMat4(rotationQuat);

	//cubeData.World = transform * rotationX * rotationY * rotationZ * scale;

	v0.Position = float3(-1.f, -1.f, 1.f);
	v1.Position = float3(1.f, -1.f, 1.f);
	v2.Position = float3(1.f, 1.f, 1.f);
	v3.Position = float3(-1.f, 1.f, 1.f);
	v4.Position = float3(-1.f, -1.f, -1.f);
	v5.Position = float3(1.f, -1.f, -1.f);
	v6.Position = float3(1.f, 1.f, -1.f);
	v7.Position = float3(-1.f, 1.f, -1.f);

	setVertices({ v0, v1, v2, v3, v1, v5, v6, v2, v5, v4, v7, v6, v4, v0, v3, v7, v3, v2, v6, v7, v4, v5, v1, v0 });
	setIndices({ 0,2,1,0,3,2, 4,6,5,4,7,6, 8,10,9,8,11,10, 12,14,13,12,15,14, 16,18,17,16,19,18, 20,22,21,20,23,22 });
	//std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3, v1, v5, v6, v2, v5, v4, v7, v6, v4, v0, v3, v7, v3, v2, v6, v7, v4, v5, v1, v0 };
	//std::vector<uint32_t> indices = { 0,2,1,0,3,2, 4,6,5,4,7,6, 8,10,9,8,11,10, 12,14,13,12,15,14, 16,18,17,16,19,18, 20,22,21,20,23,22 };

	//for (int i = 0; i < 6; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		getVertex(i * 4 + j).Colour = colours.at(i);
	//	}
	//}

	//if (flipWindingOrder)
	//{
	//	for (int i = 1; i < indices.size(); i += 3)
	//	{
	//		std::swap(indices.at(i), indices.at(i + 1));
	//	}
	//}

	//renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size(), &cubeData);
}

Cube::~Cube()
{

}

void Cube::setColours(std::vector<float3> colours)
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			getVertex(i * 4 + j).Colour = colours.at(i);
		}
	}
}
