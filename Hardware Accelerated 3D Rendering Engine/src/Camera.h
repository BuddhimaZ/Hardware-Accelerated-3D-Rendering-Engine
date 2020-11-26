#ifndef CAMERA_H
#define CAMERA_H

//Local Includes

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes

class Camera {
public:
	Camera(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& rotation);
	Camera();
	constexpr DirectX::XMFLOAT3& GetPosition() { return m_position; }
	constexpr DirectX::XMFLOAT3& GetRotation() { return m_rotation; }
	const DirectX::XMMATRIX GetTransform() const;
	const void SetCameraMovSpeed(const float& speed);
	const void SetCameraRotSpeed(const float& speed);
	const void TranslateRelCamera(DirectX::XMFLOAT3 translation, const float& dt);
	const void RotateCamera(const DirectX::XMFLOAT3& dRotation, const float& dt);


private:
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;

	float m_fCameraMovingSpeed = 20.0f;
	float m_fCameraRotatingSpeed = 2.0f;
};

#endif //!CAMERA_H