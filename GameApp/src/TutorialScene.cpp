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

	if (renderTriangle)
	{
		shapeLibrary.drawTriangle(Renderer, float3(1.0f, 1.0f, 0.0f), triangleScale, float3(triangleTransform[0], triangleTransform[1], triangleTransform[2]), triangleRotate);
	}
	
	if (renderArm)
	{
		CMP203::InstanceData upperArm = shapeLibrary.drawSquare(Renderer, float3(0.0f, 0.0f, 1.0f), float3(1.0f, 1.0f, 1.0f), float3(armTransform[0], armTransform[1], armTransform[2]), upperArmRotate);
		CMP203::InstanceData lowerArm = shapeLibrary.drawSquare(Renderer, float3(0.0f, 0.0f, 1.0f), float3(1.f, 1.f, 1.f), float3(1.0f, 0.0f, 0.f), lowerArmRotate, upperArm);
		CMP203::InstanceData hand = shapeLibrary.drawSquare(Renderer, float3(0.0f, 0.0f, 1.0f), float3(1.0f, 1.0f, 1.f), float3(1.0f, 0.f, 0.f), handRotate, lowerArm);
	}

	if (renderCube)
	{
		std::vector<float3> cubeColours = { float3(0.f,0.f,1.f), float3(0.f,1.f,0.f), float3(1.f,0.f,0.f), float3(1.f,0.f,1.f), float3(0.f,1.f,1.f), float3(1.f,1.f,0.f) };
		shapeLibrary.drawCube(Renderer, cubeColours, cubeScale, float3(cubeTransform[0], cubeTransform[1], cubeTransform[2]), float3(cubeRotate[0], cubeRotate[1], cubeRotate[2]));
	}

	if (renderCone) 
	{
		shapeLibrary.drawCone(Renderer, coneDiscSides, float3(0.6f, 0.6f, 0.2f), coneScale, float3(coneTransform[0], coneTransform[1], coneTransform[2]), float3(coneRotate[0], coneRotate[1], coneRotate[2]));
	}

	if (renderCylinder)
	{
		shapeLibrary.drawCylinder(Renderer, cylinderDiscSides, float3(0.2f, 0.2f, 0.8f), cylinderLength, cylinderScale, float3(cylinderTransform[0], cylinderTransform[1], cylinderTransform[2]), float3(cylinderRotate[0], cylinderRotate[1], cylinderRotate[2]));
	}

	Renderer.End();
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

	ImGui::Checkbox("Render Triangle", &renderTriangle);
	if (renderTriangle) {
		ImGui::SliderFloat("Triangle scale:", &triangleScale, 0.1f, 10.0f);
		ImGui::SliderFloat("Triangle rotation:", &triangleRotate, 0.0f, 360.0f);
		ImGui::SliderFloat3("Triangle position:", triangleTransform, -15.0f, 15.0f);
	}

	ImGui::Checkbox("Render Arm", &renderArm);
	if (renderArm) {
		ImGui::SliderFloat("Upper arm rotation:", &upperArmRotate, 0.0f, 360.f);
		ImGui::SliderFloat("Lower arm rotation:", &lowerArmRotate, 0.0f, 360.f);
		ImGui::SliderFloat("Hand rotation:", &handRotate, 0.0f, 360.f);
		ImGui::SliderFloat3("Arm position:", armTransform, -15.0f, 15.0f);
	}

	ImGui::Checkbox("Render Cube", &renderCube);
	if (renderCube) {
		ImGui::SliderFloat("Cube scale:", &cubeScale, 0.1f, 10.0f);
		ImGui::SliderFloat3("Cube rotation:", cubeRotate, 0.0f, 360.0f);
		ImGui::SliderFloat3("Cube position:", cubeTransform, -15.0f, 15.0f);
	}

	ImGui::Checkbox("Render Cone", &renderCone);
	if (renderCone) {
		ImGui::SliderInt("Cone disc sides:", &coneDiscSides, 4, 30);
		ImGui::SliderFloat("Cone scale:", &coneScale, 0.1f, 10.0f);
		ImGui::SliderFloat3("Cone rotation:", coneRotate, 0.0f, 360.0f);
		ImGui::SliderFloat3("Cone position:", coneTransform, -15.0f, 15.0f);
	}

	ImGui::Checkbox("Render Cylinder", &renderCylinder);
	if (renderCylinder) {
		ImGui::SliderInt("Cylinder disc sides:", &cylinderDiscSides, 4, 30);
		ImGui::SliderFloat("Cylinder Length:", &cylinderLength, 1.f, 100.f);
		ImGui::SliderFloat("Cylinder scale:", &cylinderScale, 0.1f, 10.0f);
		ImGui::SliderFloat3("Cylinder rotation:", cylinderRotate, 0.0f, 360.0f);
		ImGui::SliderFloat3("Cylinder position:", cylinderTransform, -15.0f, 15.0f);
	}

	ImGui::End();
}
