#pragma once
#include "Skateboard/Scene/Scene.h"
#include "Skateboard/ComponentSystems/Systems/BaseSystem.h"

#include "CMP203/Renderer203.h"

class TutorialScene : public Skateboard::Scene {
public:
	explicit TutorialScene(const std::string& name);

	TutorialScene() = delete;

	virtual void OnHandleInput(Skateboard::TimeManager* time) override;
	virtual void OnUpdate(Skateboard::TimeManager* time) override;
	virtual void OnRender() override;
	virtual void OnEvent(Event& e) override;
	virtual void OnImGuiRender() override;

	void drawTriangle(float3 colour, float scale, float3 translation, float rotationAngle);
	CMP203::InstanceData drawSquare(float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle);
	CMP203::InstanceData drawSquare(float3 colour, float3 scaleVal, float3 translationVal, float rotationAngle, CMP203::InstanceData parentData);
	void drawSquareWithStrip(float2 offset, float3 colour);
	void drawHexagonFan(float2 offset, float3 colour);

private:
	bool bWireframe = false;
	CMP203::Renderer203 Renderer;

	float triangleScale= 1.f;
	float triangleRotate = 0.f;
	float triangleTransform[3] = { 0.f, 0.f, 0.f };

	float upperArmRotate = 0.f;
	float lowerArmRotate = 0.f;
	float handRotate = 0.f;
	float armTransform[3] = { 0.f,0.f,0.f };
};
