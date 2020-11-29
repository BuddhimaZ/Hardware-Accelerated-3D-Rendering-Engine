#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

//Local Includes
#include "CrappyComponent.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes


class TransformComponent : public CrappyComponent {
public:
	TransformComponent(
		const CrappyEntity* pOwner, 
		const DirectX::XMFLOAT3& pos, 
		const DirectX::XMFLOAT3& rot,
		const DirectX::XMFLOAT3& scale
		);

	TransformComponent(
		const CrappyEntity* pOwner
	);


public:
	const DirectX::XMFLOAT3& GetPosition() const;
	const DirectX::XMFLOAT3& GetRotation() const;
	const DirectX::XMFLOAT3& GetScale() const;

	const DirectX::XMFLOAT3& GetRealPosition() const;
	const DirectX::XMFLOAT3& GetRealRotation() const;
	const DirectX::XMFLOAT3& GetRealScale() const;

	const void SetPosition(const DirectX::XMFLOAT3& pos);
	const void SetRotation(const DirectX::XMFLOAT3& rot);
	const void SetScale(const DirectX::XMFLOAT3& scale);

	const DirectX::XMMATRIX GetXMTransformMatrix() const;

private:

	void OnStart() override;
	void OnUpdate(const float& dt) override;

private:
	const TransformComponent* m_pParentTransform = nullptr;

	DirectX::XMFLOAT3 m_xmf3Position	=	DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_xmf3Rotation	=	DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_xmf3Scale		=	DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	DirectX::XMFLOAT3 m_xmf3RealPosition	=	DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_xmf3RealRotation	=	DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_xmf3RealScale		=	DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
};


#endif // !TRANSFORMCOMPONENT_H
