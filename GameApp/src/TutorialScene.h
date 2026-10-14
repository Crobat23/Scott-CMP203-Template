#pragma once
#include "Skateboard/Scene/Scene.h"
#include "Skateboard/ComponentSystems/Systems/BaseSystem.h"

#include "shapeLibrary.h"

class TutorialScene : public Skateboard::Scene {
public:
	explicit TutorialScene(const std::string& name);

	TutorialScene() = delete;

	virtual void OnHandleInput(Skateboard::TimeManager* time) override;
	virtual void OnUpdate(Skateboard::TimeManager* time) override;
	virtual void OnRender() override;
	virtual void OnEvent(Event& e) override;
	virtual void OnImGuiRender() override;
private:
	shapeLibrary shapeLibrary;

	bool bWireframe = false;
	CMP203::Renderer203 Renderer;

	bool renderTriangle = false;
	float triangleScale= 1.f;
	float triangleRotate = 0.f;
	float triangleTransform[3] = { 0.f, 0.f, 0.f };

	bool renderArm = false;
	float upperArmRotate = 0.f;
	float lowerArmRotate = 0.f;
	float handRotate = 0.f;
	float armTransform[3] = { 0.f,0.f,0.f };

	bool renderCube = false;
	float cubeScale = 1.f;
	float cubeRotate[3] = { 0.f,0.f,0.f };
	float cubeTransform[3] = { 0.f, 0.f, 0.f };

	bool renderCone = true;
	int discSides = 8;
	float coneScale = 1.f;
	float coneRotate[3] = { 0.f, 0.f, 0.f };
	float coneTransform[3] = { 0.f, 0.f, 0.f };
};
