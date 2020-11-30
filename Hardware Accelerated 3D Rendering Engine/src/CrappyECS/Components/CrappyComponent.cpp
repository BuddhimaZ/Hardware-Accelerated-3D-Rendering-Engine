#include "CrappyComponent.h"

CrappyComponent::CrappyComponent(
	const CrappyEntity* pOwner
) :
	m_pOwner(pOwner)
{
}

CrappyComponent::~CrappyComponent()
{
	for (auto& pBindable : m_vecBindables) {
		if (pBindable) delete pBindable;
	}
}

void CrappyComponent::OnStart() {}

void CrappyComponent::OnUpdate(const float& dt) {}

const CrappyEntity* CrappyComponent::GetOwner() const
{
	return m_pOwner;
}

const void CrappyComponent::AddBindable(Bindable* pBindable)
{
	m_vecBindables.push_back(pBindable);
}

const void CrappyComponent::Bind() const
{
	for (const auto& pBindable : m_vecBindables) {
		pBindable->Bind();
	}
}

const Renderer* CrappyComponent::GetRenderer() const
{
	return m_pOwner->m_pRenderer;
}
