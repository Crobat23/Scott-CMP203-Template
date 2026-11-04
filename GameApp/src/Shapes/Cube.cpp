#include "Cube.h"

Cube::Cube()
{
	CMP203::Vertex v0, v1, v2, v3, v4, v5, v6, v7;

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

	setTopology(Skateboard::SKTBD_PRIMITIVE_TOPOLOGY::SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Cube::~Cube()
{

}

void Cube::setUV(float2 uvValues)
{
	for (int i = 0; i < 6; i++) {
		getVertex(i * 4).UV = { uvValues.x,uvValues.y };
		getVertex(i * 4 + 1).UV = { 0,uvValues.y };
		getVertex(i * 4 + 2).UV = { 0,0 };
		getVertex(i * 4 + 3).UV = { uvValues.x,0 };
	}
}

void Cube::setUV(std::vector<float2> uvValues)
{
	if (uvValues.size() < 6) return;

	for (int i = 0; i < 6; i++) {
		getVertex(i * 4).UV = { uvValues.at(i).x,uvValues.at(i).y};
		getVertex(i * 4 + 1).UV = { 0,uvValues.at(i).y };
		getVertex(i * 4 + 2).UV = { 0,0 };
		getVertex(i * 4 + 3).UV = { uvValues.at(i).x,0 };
	}
}

void Cube::setColours(std::vector<float3> colours)
{
	if (colours.size() < 6) return;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			getVertex(i * 4 + j).Colour = colours.at(i);
		}
	}
}
