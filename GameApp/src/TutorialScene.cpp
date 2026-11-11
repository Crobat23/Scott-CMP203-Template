// includes all the basic structures and most standard library containers used throughout Skateboard
#include "sktbdpch.h"

#include "TutorialScene.h"

#include <iostream>

#include "Skateboard/Application.h"
#include "Skateboard/Platform.h"
#include "Skateboard/Assets/AssetManager.h"

TutorialScene::TutorialScene(const std::string& name): 
	Scene(name)
{
	size_t TriangleBuffersizeOverride = 1024 * 1024;
	size_t InstanceBufferSizeOverride = 1024 * 1024;
	Renderer.Init(TriangleBuffersizeOverride, InstanceBufferSizeOverride);

	// Oh yeah, light time
	Renderer.SetPipelineFlags(CMP203::LIT);
	Renderer.SetAmbientLight(float3(0.2f, 0.2f, 0.2f));

	CMP203::Light DirectionalLight(CMP203::LightType::LightDirectional);
	DirectionalLight.Type = CMP203::LightType::LightDirectional;
	DirectionalLight.DiffuseColour = float4(0.6f, 0.6f, 0.2f, 1.f);
	DirectionalLight.LightDirection = float3(-0.5f, -0.5f, 0.f);

	CMP203::Light SpotLight(CMP203::LightType::LightSpot);
	SpotLight.Type = CMP203::LightType::LightSpot;
	SpotLight.LightPosition = float3(0, -1, 0);
	SpotLight.LightDirection = float3(0, -1, 0);
	SpotLight.ConstantAttenuation = 0.05f;
	SpotLight.LinearAttenuation = 0.01f;
	SpotLight.SquareAttenuation = 0.001f;
	SpotLight.InnerCone = glm::radians(30.f);
	SpotLight.OuterCone = glm::radians(90.f);
	SpotLight.FalloffPower = 2.f;

	CMP203::Light PointLight(CMP203::LightType::LightPoint);
	PointLight.Type = CMP203::LightType::LightPoint;
	PointLight.DiffuseColour = float4(0.8f, 0.f, 0.f, 1.f);
	PointLight.LightPosition = float3(0, -1.f, 0);
	PointLight.ConstantAttenuation = 0.05f;
	PointLight.LinearAttenuation = 0.01f;
	PointLight.SquareAttenuation = 0.001f;

	SceneLights.push_back(DirectionalLight);
	SceneLights.push_back(SpotLight);
	SceneLights.push_back(PointLight);

	Renderer.SetLights(SceneLights);

	//Setup samplers
	samplerDesc_Clamp = CMP203::LinearSampler(SamplerMode_Clamp, SamplerMode_Clamp);
	samplerDesc_Repeat = CMP203::LinearSampler(SamplerMode_Wrap, SamplerMode_Wrap);
	samplerClamp = ResourceFactory::CreateSampler(samplerDesc_Clamp, L"ClampBoth");
	samplerRepeat = ResourceFactory::CreateSampler(samplerDesc_Repeat, L"RepeatBoth");

	//Load Textures
	AssetManager::LoadTexture(L"assets/crate.dds", "Crate");
	AssetManager::LoadTexture(L"assets/stone.dds", "Stone");

	//Setup Room
	std::vector<float3> roomColours = { float3(0.f,0.f,1.f), float3(0.f,1.f,0.f), float3(1.f,0.f,0.f), float3(1.f,0.f,1.f), float3(1.f,1.f,1.f), float3(0.5f,0.5f,0.5f) };
	std::vector<float2> roomUV = { float2(10,4), float2(10,4), float2(10,4), float2(10,4), float2(10,10), float2(10,10) };
	room.setColours(roomColours);
	room.flipWindingOrder();
	room.setTransform(float3(0.f,0.f,0.f), float3(0.f,0.f,0.f), float3(10.f,4.f,10.f));
	room.setUV(roomUV);
	room.setObjectTexture("Stone", samplerRepeat);
	room.setMaterial(float4(0.2f, 0.2f, 0.8f, 0.5f), 5, 2);

	//Setup crate and other shapes
	crate.setUV(float2(1, 1));
	crate.setObjectTexture("Crate", samplerClamp);
	cone1.setColour(float3(0.6f, 0.6f, 0.2f));
	cylinder1.setColour(float3(0.2f, 0.2f, 0.8f));

}

void TutorialScene::OnHandleInput(Skateboard::TimeManager* time)
{
	Scene::OnHandleInput(time);

	if (Input::IsKeyDown(Keys::sc_w)) camera1.updatePosition('W', time);
	else if (Input::IsKeyDown(Keys::sc_s)) camera1.updatePosition('S', time);
	else if (Input::IsKeyDown(Keys::sc_a)) camera1.updatePosition('A', time);
	else if (Input::IsKeyDown(Keys::sc_d)) camera1.updatePosition('D', time);

	if (Input::IsMouseButtonDown(MouseBtn::mb_RightButton))
	{
		int2 windowCentre = Input::GetWindowSize() / 2;
		int2 mouseDeltas = Input::GetMousePos() - MousePosOld;

		camera1.setAngle(mouseDeltas, time);

		Input::SetMousePos(windowCentre.x, windowCentre.y);
	}
	MousePosOld = Input::GetMousePos();
}

void TutorialScene::OnUpdate(Skateboard::TimeManager* time)
{
	Scene::OnUpdate(time);

	CMP203::CameraData cam_data;
	float3 camera_pos = camera1.getPos();
	float3 camera_forward = camera1.getForwardVector();
	float3 camera_up = camera1.getUpVector();

	cam_data.ProjectionMatrix = glm::perspectiveLH(glm::radians(60.f),
		GraphicsContext::Context->GetClientAspectRatio(), 100.f, 0.01f);

	cam_data.ViewMatrix = glm::lookAtLH(camera_pos, camera_pos + camera_forward, camera_up);

	Renderer.SetCameraData(cam_data);
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
		crate.Render(Renderer);
	}

	if (renderCone) 
	{
		cone1.renderAll(Renderer);
	}

	if (renderCylinder)
	{
		cylinder1.renderAll(Renderer);
	}
	
	room.Render(Renderer);

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

	if (ImGui::Button("Draw normals")) Renderer.SetDrawDebugNormals(true);
	if (ImGui::Button("Don't draw normals")) Renderer.SetDrawDebugNormals(false);

	ImGui::Text("Camera Controls");
	if (ImGui::SliderFloat("Camera Speed", &cameraSpeed, 0.1f, 30.0f))
	{
		camera1.setMoveSpeed(cameraSpeed);
	}
	if (ImGui::SliderFloat("Rotation Speed", &cameraRotateSpeed, 5.f, 30.f))
	{
		camera1.setRotateSpeed(cameraRotateSpeed);
	}

	ImGui::Text("Spotlight Controls");
	if (ImGui::SliderFloat3("Spotlight Position", spotlightPos, -15.f, 15.f))
	{
		CMP203::Light& myLightRef = Renderer.GetLight(1);
		myLightRef.LightPosition = float3(spotlightPos[0], spotlightPos[1], spotlightPos[2]);
	}
	ImGui::Text("Point Light Controls");
	if (ImGui::SliderFloat3("Point Light Position", pointLightPos, -15.f, 15.f))
	{
		CMP203::Light& myLightRef = Renderer.GetLight(2);
		myLightRef.LightPosition = float3(pointLightPos[0], pointLightPos[1], pointLightPos[2]);
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
		if (ImGui::SliderFloat("Cube scale:", &cubeScale, 0.1f, 10.0f) ||
			ImGui::SliderFloat3("Cube rotation:", cubeRotate, 0.0f, 360.0f) ||
			ImGui::SliderFloat3("Cube position:", cubeTransform, -15.0f, 15.0f))
		{
			crate.setTransform(float3(cubeTransform[0], cubeTransform[1], cubeTransform[2]),
				float3(cubeRotate[0], cubeRotate[1], cubeRotate[2]),
				float3(cubeScale, cubeScale, cubeScale));
		}
	}

	ImGui::Checkbox("Render Cone", &renderCone);
	if (renderCone) {
		if (ImGui::SliderInt("Cone disc sides:", &coneDiscSides, 4, 30))
		{
			cone1.setDiscSides(coneDiscSides);
		}
		if (ImGui::SliderFloat("Cone Height", &coneHeight, 0.3f, 5.0f))
		{
			cone1.setConeHeight(coneHeight);
		}
		if	(ImGui::SliderFloat("Cone scale:", &coneScale, 0.1f, 10.0f) ||
			ImGui::SliderFloat3("Cone rotation:", coneRotate, 0.0f, 360.0f) ||
			ImGui::SliderFloat3("Cone position:", coneTransform, -15.0f, 15.0f))
		{
			cone1.setTransformAll(float3(coneTransform[0], coneTransform[1], coneTransform[2]),
				float3(coneRotate[0], coneRotate[1], coneRotate[2]),
				float3(coneScale, coneScale, coneScale));
		}
	}

	ImGui::Checkbox("Render Cylinder", &renderCylinder);
	if (renderCylinder) {
		if (ImGui::SliderInt("Cylinder disc sides:", &cylinderDiscSides, 4, 30))
		{
			cylinder1.setDiscSides(cylinderDiscSides);
		}
		if (ImGui::SliderFloat("Cylinder Length:", &cylinderLength, 1.f, 100.f))
		{
			cylinder1.setCylinderLength(cylinderLength);
		}
		if (ImGui::SliderFloat("Cylinder scale:", &cylinderScale, 0.1f, 10.0f) ||
			ImGui::SliderFloat3("Cylinder rotation:", cylinderRotate, 0.0f, 360.0f) ||
			ImGui::SliderFloat3("Cylinder position:", cylinderTransform, -15.0f, 15.0f))
		{
			cylinder1.setTransformAll(float3(cylinderTransform[0], cylinderTransform[1], cylinderTransform[2]),
				float3(cylinderRotate[0], cylinderRotate[1], cylinderRotate[2]),
				float3(cylinderScale, cylinderScale, cylinderScale));
		}
	}

	ImGui::End();
}
