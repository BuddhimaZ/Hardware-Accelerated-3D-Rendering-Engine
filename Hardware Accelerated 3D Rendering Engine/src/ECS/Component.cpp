#include "Component.h"
#include "Entity.h"

Component::Component(Entity* pEntity, const std::string& name) : m_pParent(pEntity), m_sName(name)
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}
