#include "newCamera.h"

newCamera::newCamera()
{
	updateUnitVectors(0.f, 0.f, 0.f);
}

newCamera::~newCamera()
{

}

float3 newCamera::getPos()
{
	return position;
}

float3 newCamera::getUpVector()
{
	return camUp;
}

float3 newCamera::getForwardVector()
{
	return camForward;
}

void newCamera::updatePosition(char direction, Skateboard::TimeManager* time)
{
	switch (direction)
	{
	case ('W'):
		position += camForward * moveSpeed * time->DeltaTime();
		break;
	case ('S'):
		position -= camForward * moveSpeed * time->DeltaTime();
		break;
	case ('A'):
		position -= camRight * moveSpeed * time->DeltaTime();
		break;
	case ('D'):
		position += camRight * moveSpeed * time->DeltaTime();
		break;
	}
}

void newCamera::setAngle(int2 mouseDeltas, Skateboard::TimeManager* time)
{
	angle[1] += mouseDeltas.x * time->DeltaTime() * rotateSpeed;
	angle[0] -= mouseDeltas.y * time->DeltaTime() * rotateSpeed;
	updateUnitVectors(angle[0], angle[1], angle[2]);
}

void newCamera::updateUnitVectors(float pitchAngle, float yawAngle, float rollAngle)
{
	float cosP = glm::cos(glm::radians(pitchAngle));
	float sinP = glm::sin(glm::radians(pitchAngle));
	float cosY = glm::cos(glm::radians(yawAngle));
	float sinY = glm::sin(glm::radians(yawAngle));
	float cosR = glm::cos(glm::radians(rollAngle));
	float sinR = glm::sin(glm::radians(rollAngle));

	camForward.x = sinY * cosP;
	camForward.y = sinP;
	camForward.z = cosP * cosY;
	camForward = glm::normalize(camForward);

	camUp.x = -cosY * sinR - sinY * sinP * cosR;
	camUp.y = cosP * cosR;
	camUp.z = sinY * sinR - sinP * cosR * cosY;
	camUp = glm::normalize(camUp);

	camRight = glm::cross(camUp, camForward);
}