#include "CrappyComponent.h"

CrappyComponent::CrappyComponent(
	const CrappyEntity* pOwner
) :
	m_pOwner(pOwner)
{
}

const CrappyEntity* CrappyComponent::GetOwner() const
{
	return m_pOwner;
}
