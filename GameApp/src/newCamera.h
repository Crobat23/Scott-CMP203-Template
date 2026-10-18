#pragma once
#include "Skateboard/Graphics/RHI/ResourceFactory.h"

class newCamera
{
public:
	newCamera();
	~newCamera();

	float3 getPos();
	float3 getUpVector();
	float3 getForwardVector();
	void setPos(float3 newPos);
	void setAngle(float3 newAngle);

	void updateUnitVectors(float yawAngle, float pitchAngle, float rollAngle);

private:
	float3 position = { 0.f,0.f,0.f };
	float3 angle = { 0.f,0.f,0.f };

	float3 camForward;
	float3 camUp;
	float3 camRight;


};

