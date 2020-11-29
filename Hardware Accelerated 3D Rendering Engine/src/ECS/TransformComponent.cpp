#include "TransformComponent.h"
#include "Entity.h"

TransformComponent::TransformComponent(
	Entity* pParent, 
	const DirectX::XMFLOAT3& relPosition, 
	const DirectX::XMFLOAT3& relRotation, 
	const DirectX::XMFLOAT3& relScale
) 
	: 
	Component(pParent, "TransformComponent"),
	m_f3RelPosition(relPosition),
	m_f3RelRotation(relRotation),
	m_f3RelScale(relScale)
{
}

TransformComponent::TransformComponent(Entity* pParent) 
	: 
	TransformComponent(
		pParent, 
		DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
	)
{
}

const void TransformComponent::SetPosition(const DirectX::XMFLOAT3& pos)
{
	m_f3RelPosition = pos;
}

const void TransformComponent::SetRotation(const DirectX::XMFLOAT3& rot)
{
	m_f3RelRotation = rot;
}

const void TransformComponent::SetScale(const DirectX::XMFLOAT3& scale)
{
	m_f3RelScale = scale;
}

const DirectX::XMMATRIX TransformComponent::GetXMTransformMatrix() const
{
	using namespace DirectX;
	return XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_f3RealRotation)) * XMMatrixTranslationFromVector(XMLoadFloat3(&m_f3RealPosition)) * XMMatrixScalingFromVector(XMLoadFloat3(&m_f3RealScale));
}

void TransformComponent::OnStart()
{
	//Get a pointer to the transform component of the parent entity 
	m_pParentTransform = static_cast<TransformComponent*>(GetParent()->GetParent()->GetComponentByName(GetName()));
	
}

void TransformComponent::OnUpdate(const float& dt)
{
	// Update position rotation and scale according to the transform of the parent entity

	m_f3RealPosition.x = m_pParentTransform->m_f3RealPosition.x + m_f3RelPosition.x;
	m_f3RealPosition.y = m_pParentTransform->m_f3RealPosition.y + m_f3RelPosition.y;
	m_f3RealPosition.z = m_pParentTransform->m_f3RealPosition.z + m_f3RelPosition.z;

	m_f3RealRotation.x = m_pParentTransform->m_f3RealRotation.x + m_f3RelRotation.x;
	m_f3RealRotation.y = m_pParentTransform->m_f3RealRotation.y + m_f3RelRotation.y;
	m_f3RealRotation.z = m_pParentTransform->m_f3RealRotation.z + m_f3RelRotation.z;

	m_f3RealScale.x = m_pParentTransform->m_f3RealScale.x + m_f3RelScale.x;
	m_f3RealScale.y = m_pParentTransform->m_f3RealScale.y + m_f3RelScale.y;
	m_f3RealScale.z = m_pParentTransform->m_f3RealScale.z + m_f3RelScale.z;
}
