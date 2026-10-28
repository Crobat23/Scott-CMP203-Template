#include "Cone.h"

Cone::Cone()
{
	CMP203::Vertex v0;

	///*CMP203::InstanceData coneData;
	//glm::mat4 transform, rotationX, rotationY, rotationZ, scale;

	//scale = glm::scale(float3{ scaleVal, scaleVal, scaleVal });
	//transform = glm::translate(translationVal);

	//glm::quat rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[0]), float3(-1, 0, 0));
	//rotationX = glm::toMat4(rotationQuat);
	//rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[1]), float3(0, -1, 0));
	//rotationY = glm::toMat4(rotationQuat);
	//rotationQuat = glm::rotate(glm::quat(1, 0, 0, 0), glm::radians(rotationAngle[2]), float3(0, 0, -1));
	//rotationZ = glm::toMat4(rotationQuat);

	//coneData.World = transform * rotationX * rotationY * rotationZ * scale;*/

	base.buildDisc(0.f);
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

	setDrawType(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
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
	base.setColour(colour);
	getVertex(getVertices().size() - 1).Colour = colour;
}

void Cone::setDiscSides(int newSides)
{
	base.setSides(newSides);
}

void Cone::renderAll(CMP203::Renderer203& Renderer)
{
	Render(Renderer);
	base.Render(Renderer);
}