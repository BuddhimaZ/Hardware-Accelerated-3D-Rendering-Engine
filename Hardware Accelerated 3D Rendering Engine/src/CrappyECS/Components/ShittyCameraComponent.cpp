#include "ShittyCameraComponent.h"

std::unordered_map<std::string, ShittyCameraComponent*> ShittyCameraComponent::SceneCameras;

ShittyCameraComponent::ShittyCameraComponent(
	const CrappyEntity* pOwner, 
	const DirectX::XMMATRIX& ProjectionMatrix
): 
	CrappyComponent(pOwner),
	m_xmmatProjectionMatrix(ProjectionMatrix),
	m_transform(*(pOwner->GetComponent<TransformComponent>()))
{
	//Add this camera to SceneCamera map
	SceneCameras.insert({ GetOwner()->GetName(), this });
}

ShittyCameraComponent::ShittyCameraComponent(
	const CrappyEntity* pOwner,
	const DirectX::XMMATRIX& ProjectionMatrix,
	Viewports* pViewports,
	RenderTargets* pRenderTargets
) :
	CrappyComponent(pOwner),
	m_xmmatProjectionMatrix(ProjectionMatrix),
	m_transform(*(pOwner->GetComponent<TransformComponent>())),
	m_pViewports(pViewports),
	m_pRenderTargets(pRenderTargets)
{
	//Add this camera to SceneCamera map
	SceneCameras.insert({ GetOwner()->GetName(), this });
	AddBindable(m_pRenderTargets);
	AddBindable(m_pViewports);
}



void ShittyCameraComponent::OnStart()
{

}

const DirectX::XMMATRIX ShittyCameraComponent::GetXMCameraMatrix() const
{
	using namespace DirectX;
	const auto& pos = m_transform.GetRealPosition(); const auto& rot = m_transform.GetRealRotation();
	return
		XMMatrixTranslationFromVector(-XMLoadFloat3(&pos))*
		XMMatrixRotationY(-rot.y)*
		XMMatrixRotationX(-rot.x)*
		XMMatrixRotationZ(-rot.z)*
		m_xmmatProjectionMatrix
		;
}
