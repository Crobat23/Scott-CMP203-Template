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
