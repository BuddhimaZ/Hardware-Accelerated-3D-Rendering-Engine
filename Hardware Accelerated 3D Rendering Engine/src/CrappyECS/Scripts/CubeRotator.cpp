#include "CubeRotator.h"

void CubeRotator::OnStart()
{
	//Get a ptr to the transform component of the cube
	pTransform = GetOwner()->GetComponent<TransformComponent>();

	//Get the ptr to its position and rotation vectors
	pPosition = &(pTransform->GetPosition());
	pRotation = &(pTransform->GetRotation());
}

void CubeRotator::OnUpdate(const float& dt) {
	const float dR = fRotationSpeed * dt;
	DirectX::XMFLOAT3 newRot = { pRotation->x + dR, pRotation->y + dR, pRotation->z };
	pTransform->SetRotation(newRot);
}
