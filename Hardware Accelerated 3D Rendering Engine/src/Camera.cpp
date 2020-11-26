#include "Camera.h"

Camera::Camera(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& rotation) : m_position(position), m_rotation(rotation)
{
	
}

Camera::Camera() : Camera(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))
{
}

const DirectX::XMMATRIX Camera::GetTransform() const
{
	using namespace DirectX;
	return XMMatrixTranslation(-m_position.x, -m_position.y, -m_position.z) * XMMatrixRotationY(-m_rotation.y) * XMMatrixRotationX(-m_rotation.x) * XMMatrixRotationZ(-m_rotation.z);
}

const void Camera::SetCameraMovSpeed(const float& speed)
{
	m_fCameraMovingSpeed = speed;
}

const void Camera::SetCameraRotSpeed(const float& speed)
{
	m_fCameraRotatingSpeed = speed;
}

const void Camera::TranslateRelCamera(DirectX::XMFLOAT3 translation, const float& dt) {
	using namespace DirectX;
	float fScaler = m_fCameraMovingSpeed * dt;
	XMStoreFloat3(&translation, XMVector3Transform(
		XMLoadFloat3(&translation),
		XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) *
		XMMatrixScaling(fScaler, fScaler, fScaler)
	));

	m_position = {
		m_position.x + translation.x,
		m_position.y + translation.y,
		m_position.z + translation.z
	};
}

const void Camera::RotateCamera(const DirectX::XMFLOAT3& dRotation, const float& dt) {
	m_rotation.x += dRotation.x * m_fCameraRotatingSpeed * dt;
	m_rotation.y += dRotation.y * m_fCameraRotatingSpeed * dt;
	m_rotation.z += dRotation.z * m_fCameraRotatingSpeed * dt;
	
	if (m_rotation.x > DirectX::XM_PIDIV2) m_rotation.x = DirectX::XM_PIDIV2;
	else if(m_rotation.x < -DirectX::XM_PIDIV2) m_rotation.x = -DirectX::XM_PIDIV2;

	if (m_rotation.y < 0.0f) m_rotation.y += DirectX::XM_2PI;
	else if (m_rotation.y >= DirectX::XM_2PI) m_rotation.y -= DirectX::XM_2PI;
}
