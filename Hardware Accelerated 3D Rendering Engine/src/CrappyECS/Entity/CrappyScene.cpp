#include "CrappyScene.h"

CrappyScene::CrappyScene(const Renderer* pRenderer) : CrappyEntity(nullptr, "Scene")
{
	m_pRenderer = pRenderer;
}

CrappyScene::CrappyScene() : CrappyScene(nullptr)
{
}

const void CrappyScene::SetRenderer(const Renderer* pRenderer) {
	m_pRenderer = pRenderer;
}

void CrappyScene::OnSceneStart() const
{
	for (auto& pEntity : m_pChildren) {
		pEntity.second->OnStart();
	}
}

void CrappyScene::OnSceneUpdate(const float& dt) const
{
	for (auto& pEntity : m_pChildren) {
		pEntity.second->OnUpdate(dt);
	}
}
