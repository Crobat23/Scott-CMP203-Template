// includes all the basic structures and most standard library containers used throughout Skateboard
#include "sktbdpch.h"

#include "TutorialScene.h"

#include "Skateboard/Application.h"
#include "Skateboard/Platform.h"
#include "Skateboard/Assets/AssetManager.h"

TutorialScene::TutorialScene(const std::string& name): 
	Scene(name)
{
	Renderer.Init();
	// Disable lighting, until we have a light in the scene
	Renderer.UnsetPipelineFlags(CMP203::LIT);
}

void TutorialScene::OnHandleInput(Skateboard::TimeManager* time)
{
	Scene::OnHandleInput(time);
}

void TutorialScene::OnUpdate(Skateboard::TimeManager* time)
{
	Scene::OnUpdate(time);
}

void TutorialScene::OnRender()
{
	Renderer.Begin();

	drawTriangle(float2(3.0f, 9.0f), float3(1.0f, 1.0f, 0.0f));
	drawFan(8, 1.0f, float2(1.0f, 0.0f), float3(0.0f, 1.0f, 1.0f));
	drawFan(5, 1.0f, float2(-3.0f, -5.0), float3(1.0f, 1.0f, 1.0f));
	drawSquare(float2(5.0f, 6.0f), float3(1.0f, 0.0f, 0.0f));
	drawSquareWithStrip(float2(-8.0f, 4.0f), float3(0.0f, 1.0f, 0.0f));
	drawHexagonFan(float2(5.0f, -4.0f), float3(0.0f, 0.0f, 1.0f));

	Renderer.End();
}

void TutorialScene::drawTriangle(float2 offset, float3 colour)
{

	CMP203::Vertex v0, v1, v2;

	v0.Position = float3(0.0f + offset.x , 0.0f + offset.y, 0.0f);
	v1.Position = float3(0.0f + offset.x, -1.0f + offset.y, 0.0f);
	v2.Position = float3(1.0f + offset.x, -1.0f + offset.y, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2 };
	std::vector<uint32_t> indices = { 0, 1, 2 };

	Renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void TutorialScene::drawSquare(float2 offset, float3 colour)
{
	CMP203::Vertex v0, v1, v2, v3;

	v0.Position = float3(0.0f + offset.x, 0.0f + offset.y, 0.0f);
	v1.Position = float3(0.0f + offset.x, -1.0f + offset.y, 0.0f);
	v2.Position = float3(1.0f + offset.x, -1.0f + offset.y, 0.0f);
	v3.Position = float3(1.0f + offset.x, 0.0f + offset.y, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = v3.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3 };
	std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

	Renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void TutorialScene::drawSquareWithStrip(float2 offset, float3 colour)
{
	CMP203::Vertex v0, v1, v2, v3;

	v0.Position = float3(0.0f + offset.x, 0.0f + offset.y, 0.0f);
	v1.Position = float3(0.0f + offset.x, -1.0f + offset.y, 0.0f);
	v2.Position = float3(1.0f + offset.x, -1.0f + offset.y, 0.0f);
	v3.Position = float3(1.0f + offset.x, 0.0f + offset.y, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = v3.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3 };
	std::vector<uint32_t> indices = {1, 2, 0, 3};

	Renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void TutorialScene::drawHexagonFan(float2 offset, float3 colour)
{
	CMP203::Vertex v0, v1, v2, v3, v4, v5, v6, v7;

	v0.Position = float3(0.0f + offset.x, 0.0f + offset.y, 0.0f);
	v1.Position = float3(-0.5f + offset.x, -0.87f + offset.y, 0.0f);
	v2.Position = float3(0.5f + offset.x, -0.87f + offset.y, 0.0f);
	v3.Position = float3(1.0f + offset.x, 0.0f + offset.y, 0.0f);
	v4.Position = float3(0.5f + offset.x, 0.87f + offset.y, 0.0f);
	v5.Position = float3(-0.5f + offset.x, 0.87 + offset.y, 0.0f);
	v6.Position = float3(-1.0f + offset.x, 0.0f + offset.y, 0.0f);
	v0.Colour = v1.Colour = v2.Colour = v3.Colour = v4.Colour = v5.Colour = v6.Colour = colour;

	std::vector<CMP203::Vertex> vertices = { v0, v1, v2, v3, v4, v5, v6 };
	std::vector<uint32_t> indices = {0,1,2,2,3,3,4,4,5,5,6,6,1};

	Renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void TutorialScene::drawFan(int sides, float size, float2 offset, float3 colour)
{
	if (sides <= 2)
		return;

	float centreAngle = 360 / sides;
	float edgeAngles = (180 - centreAngle) / 2;
	float distanceFromCentre = size;
	float edgeDistance = sqrt(2 * (distanceFromCentre * distanceFromCentre) - 2 * distanceFromCentre * distanceFromCentre * cos(centreAngle));

	float x_edgeDistance = abs(edgeDistance * cos(edgeAngles));
	float y_edgeDistance = abs(edgeDistance * sin(edgeAngles));
	
	bool yIncreasing = true;
	bool xIncreasing = false;
	
	float2 prevPoint = float2(size, size);
	float2 newPoint = prevPoint;

	CMP203::Vertex v0, v1;
	v0.Position = float3(0.0f + offset.x, 0.0f + offset.y, 0.0f);
	v1.Position = float3(0 + offset.x, size + offset.y, 0.0f);
	v0.Colour = v1.Colour = colour;
	std::vector<CMP203::Vertex> vertices = {v0, v1};
	std::vector<uint32_t> indices = { 0,1 };

	for (int i = 2; i <= sides; i++)
	{
		if (xIncreasing) {
			if ((newPoint.x + x_edgeDistance) > size)
			{
				xIncreasing = false;
				newPoint.x = newPoint.x - x_edgeDistance;
			}
			else newPoint.x = newPoint.x + x_edgeDistance;
		}
		else {
			if ((newPoint.x - x_edgeDistance) < -size)
			{
				xIncreasing = true;
				newPoint.x = newPoint.x + x_edgeDistance;
			}
			else newPoint.x = newPoint.x - x_edgeDistance;
		}

		if (yIncreasing) {
			if ((newPoint.y + y_edgeDistance) > size)
			{
				yIncreasing = false;
				newPoint.y = newPoint.y - y_edgeDistance;
			}
			else newPoint.y = newPoint.y + y_edgeDistance;
		}
		else {
			if ((newPoint.y - y_edgeDistance) < -size)
			{
				yIncreasing = true;
				newPoint.y = newPoint.y + y_edgeDistance;
			}
			else newPoint.y = newPoint.y - y_edgeDistance;
		}

		prevPoint = newPoint;

		CMP203::Vertex newVertex;
		newVertex.Position = float3(newPoint.x + offset.x, newPoint.y + offset.y, 0.0f);
		newVertex.Colour = colour;

		vertices.push_back(newVertex);
		indices.push_back(i);
		indices.push_back(i);
	}
	indices.push_back(1);

	Renderer.SetTopology(SKTBD_PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
	Renderer.DrawVertices(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void TutorialScene::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) -> bool {
		Renderer.OnResize(e.GetWidth(), e.GetHeight()); return false; });
}

void TutorialScene::OnImGuiRender()
{
	ImGui::Begin("ImGui");// Creates new ImGui window

	ImGui::Text("Hello CMP203!");
	ImGui::Text("FPS: %f", Skateboard::Platform::GetTimeManager()->FPS());
	ImGui::Text("Mouse position X: %d, Y: %d", Input::GetMousePos().x, Input::GetMousePos().y);
	// If the checkbox is clicked, toggle the wireframe mode
	if (ImGui::Checkbox("wireframe", &bWireframe))
	{
		if (bWireframe)
			Renderer.SetPipelineFlags(CMP203::PipelineFlags::WIREFRAME);
		else
			Renderer.UnsetPipelineFlags(CMP203::PipelineFlags::WIREFRAME);

	}
	ImGui::End();
}
