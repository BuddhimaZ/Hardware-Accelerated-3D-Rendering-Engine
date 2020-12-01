#include "CameraController.h"

void CameraController::OnStart()
{
	//Get the transform component of the camera
	pTransform = GetOwner()->GetComponent<TransformComponent>();
}

void CameraController::OnUpdate(const float& dt)
{
	using namespace DirectX;
	if (Input.GetKey(KB_KEY::W).bHeld) { TranslateRelCamera(XMFLOAT3( 0.0f,  0.0f,  1.0f), dt); }
	if (Input.GetKey(KB_KEY::S).bHeld) { TranslateRelCamera(XMFLOAT3( 0.0f,  0.0f, -1.0f), dt); }
	if (Input.GetKey(KB_KEY::A).bHeld) { TranslateRelCamera(XMFLOAT3(-1.0f,  0.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::D).bHeld) { TranslateRelCamera(XMFLOAT3( 1.0f,  0.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::Q).bHeld) { TranslateRelCamera(XMFLOAT3( 0.0f,  1.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::E).bHeld) { TranslateRelCamera(XMFLOAT3( 0.0f, -1.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::I).bHeld) { RotateCamera(XMFLOAT3(-1.0f,  0.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::K).bHeld) { RotateCamera(XMFLOAT3( 1.0f,  0.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::J).bHeld) { RotateCamera(XMFLOAT3( 0.0f, -1.0f,  0.0f), dt); }
	if (Input.GetKey(KB_KEY::L).bHeld) { RotateCamera(XMFLOAT3( 0.0f,  1.0f,  0.0f), dt); }
}

const void CameraController::TranslateRelCamera(DirectX::XMFLOAT3 translation, const float& dt) {
	using namespace DirectX;
	float fScaler = fCameraMovingSpeed * dt;
	const auto& pos = pTransform->GetPosition();
	const auto& rot = pTransform->GetRotation();
	XMStoreFloat3( &translation, XMVector3Transform( XMLoadFloat3(&translation), XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rot)) * XMMatrixScaling(fScaler, fScaler, fScaler) ));
	pTransform->SetPosition( { pos.x + translation.x, pos.y + translation.y, pos.z + translation.z });
}

const void CameraController::RotateCamera(DirectX::XMFLOAT3 dRotation, const float& dt) {
	const auto& rot = pTransform->GetRotation();
	float fScaler = fCameraRotatingSpeed * dt;

	dRotation = { rot.x + dRotation.x * fScaler, rot.y + dRotation.y * fScaler, rot.z + dRotation.z * fScaler };

	if (dRotation.x > DirectX::XM_PIDIV2) dRotation.x = DirectX::XM_PIDIV2;
	else if (dRotation.x < -DirectX::XM_PIDIV2) dRotation.x = -DirectX::XM_PIDIV2;

	if (dRotation.y < 0.0f) dRotation.y += DirectX::XM_2PI;
	else if (dRotation.y >= DirectX::XM_2PI) dRotation.y -= DirectX::XM_2PI;

	pTransform->SetRotation(dRotation);
}
