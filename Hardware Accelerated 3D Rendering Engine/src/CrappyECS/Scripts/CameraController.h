#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "../Components/Components.h"

#include <DirectXMath.h>

class CameraController : public CrappyComponent {
public:
	using CrappyComponent::CrappyComponent;

private:
	void OnStart() override;
	void OnUpdate(const float& dt) override;

private:
	const void TranslateRelCamera(DirectX::XMFLOAT3 translation, const float& dt);

	const void RotateCamera(DirectX::XMFLOAT3 dRotation, const float& dt);

private:
	TransformComponent* pTransform = nullptr;
	const float fCameraMovingSpeed = 20.0f;
	const float fCameraRotatingSpeed = 2.0f;
};

#endif // !CAMERACONTROLLER_H
