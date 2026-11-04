#pragma once
#include "Skateboard/Graphics/RHI/ResourceFactory.h"
#include "Skateboard/Application.h"

class newCamera
{
public:
	newCamera();
	~newCamera();

	float3 getPos();
	float3 getUpVector();
	float3 getForwardVector();
	void setMoveSpeed(float newSpeed) { moveSpeed = newSpeed; }
	void setRotateSpeed(float newSpeed) { rotateSpeed = newSpeed; }

	void updateUnitVectors(float yawAngle, float pitchAngle, float rollAngle);
	void setAngle(int2 mouseDeltas, Skateboard::TimeManager* time);
	void updatePosition(char direction, Skateboard::TimeManager* time);

private:
	float3 position = { 0.f,0.f,0.f };
	float3 angle = { 0.f,0.f,0.f };

	float3 camForward;
	float3 camUp;
	float3 camRight;

	float moveSpeed = 10.f;
	float rotateSpeed = 15.f;
};

