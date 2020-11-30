#include "TransformComponent.h"

TransformComponent::TransformComponent(
	const CrappyEntity* pOwner,
	const DirectX::XMFLOAT3& pos,
	const DirectX::XMFLOAT3& rot,
	const DirectX::XMFLOAT3& scale
) :
	CrappyComponent(pOwner),
	m_xmf3Position(pos),
	m_xmf3Rotation(rot),
	m_xmf3Scale(scale)
{

}

TransformComponent::TransformComponent(
	const CrappyEntity* pOwner
) :
	TransformComponent(
		pOwner, 
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
		)
{

}

void TransformComponent::OnStart()
{
	//Get the transform component of the parent of the owner
	//This can never be nullptr. Because every enity of CrappyECS always have a transformComponent
	m_pParentTransform = GetOwner()->GetParent()->GetComponent<TransformComponent>();

	//Update the real transform values according to the parent transform

	m_xmf3RealPosition.x = m_pParentTransform->m_xmf3RealPosition.x + m_xmf3Position.x;
	m_xmf3RealPosition.y = m_pParentTransform->m_xmf3RealPosition.y + m_xmf3Position.y;
	m_xmf3RealPosition.z = m_pParentTransform->m_xmf3RealPosition.z + m_xmf3Position.z;

	m_xmf3RealRotation.x = m_pParentTransform->m_xmf3RealRotation.x + m_xmf3Rotation.x;
	m_xmf3RealRotation.y = m_pParentTransform->m_xmf3RealRotation.y + m_xmf3Rotation.y;
	m_xmf3RealRotation.z = m_pParentTransform->m_xmf3RealRotation.z + m_xmf3Rotation.z;

	m_xmf3RealScale.x = m_pParentTransform->m_xmf3RealScale.x * m_xmf3Scale.x;
	m_xmf3RealScale.y = m_pParentTransform->m_xmf3RealScale.y * m_xmf3Scale.y;
	m_xmf3RealScale.z = m_pParentTransform->m_xmf3RealScale.z * m_xmf3Scale.z;

}

void TransformComponent::OnUpdate(const float& dt)
{
	//Update the real transform values according to the parent transform

	m_xmf3RealPosition.x = m_pParentTransform->m_xmf3RealPosition.x + m_xmf3Position.x;
	m_xmf3RealPosition.y = m_pParentTransform->m_xmf3RealPosition.y + m_xmf3Position.y;
	m_xmf3RealPosition.z = m_pParentTransform->m_xmf3RealPosition.z + m_xmf3Position.z;

	m_xmf3RealRotation.x = m_pParentTransform->m_xmf3RealRotation.x + m_xmf3Rotation.x;
	m_xmf3RealRotation.y = m_pParentTransform->m_xmf3RealRotation.y + m_xmf3Rotation.y;
	m_xmf3RealRotation.z = m_pParentTransform->m_xmf3RealRotation.z + m_xmf3Rotation.z;

	m_xmf3RealScale.x = m_pParentTransform->m_xmf3RealScale.x * m_xmf3Scale.x;
	m_xmf3RealScale.y = m_pParentTransform->m_xmf3RealScale.y * m_xmf3Scale.y;
	m_xmf3RealScale.z = m_pParentTransform->m_xmf3RealScale.z * m_xmf3Scale.z;
}

const DirectX::XMFLOAT3& TransformComponent::GetPosition() const { return m_xmf3Position; }
const DirectX::XMFLOAT3& TransformComponent::GetRotation() const { return m_xmf3Rotation; }
const DirectX::XMFLOAT3& TransformComponent::GetScale() const { return m_xmf3Scale; }

const DirectX::XMFLOAT3& TransformComponent::GetRealPosition() const {	return m_xmf3RealPosition; }
const DirectX::XMFLOAT3& TransformComponent::GetRealRotation() const {	return m_xmf3RealRotation; }
const DirectX::XMFLOAT3& TransformComponent::GetRealScale() const {		return m_xmf3RealScale; }

const void TransformComponent::SetPosition(const DirectX::XMFLOAT3& pos) { m_xmf3Position = pos; }
const void TransformComponent::SetRotation(const DirectX::XMFLOAT3& rot) { m_xmf3Rotation = rot; }
const void TransformComponent::SetScale(const DirectX::XMFLOAT3& scale) { m_xmf3Scale = scale; }

const DirectX::XMMATRIX TransformComponent::GetXMTransformMatrix() const
{
	using namespace DirectX;
	return 
		XMMatrixScalingFromVector(XMLoadFloat3(&m_xmf3RealScale)) *
		XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_xmf3RealRotation)) *
		XMMatrixTranslationFromVector(XMLoadFloat3(&m_xmf3RealPosition)) 
		;
}
