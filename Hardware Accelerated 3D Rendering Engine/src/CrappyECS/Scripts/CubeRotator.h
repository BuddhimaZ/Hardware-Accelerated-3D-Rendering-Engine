#ifndef CUBEROTATOR_H
#define CUBEROTATOR_H

#include "../Components/Components.h"

class CubeRotator : public CrappyComponent {
public:
	using CrappyComponent::CrappyComponent;

private:
	void OnStart() override;
	void OnUpdate(const float& dt) override;

private:
	TransformComponent* pTransform = nullptr;
	const DirectX::XMFLOAT3* pPosition = nullptr;
	const DirectX::XMFLOAT3* pRotation = nullptr;

	const float fRotationSpeed = 1.0f;
};

#endif // !CUBEROTATOR_H