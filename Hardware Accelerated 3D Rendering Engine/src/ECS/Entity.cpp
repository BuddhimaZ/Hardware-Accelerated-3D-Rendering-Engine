#include "Entity.h"
#include "TransformComponent.h"

Entity::Entity(Entity* pParent, const std::string& name) : m_pParent(pParent), m_sName (name)
{
	//Create a transform component
	auto transform = std::make_unique<TransformComponent>(this);
	m_components.insert({
		transform->GetName(), std::move(transform)
		});
}

Component* Entity::GetComponentByName(const std::string& name)
{
	return m_components[name].get();
}

Entity* Entity::GetChildByName(const std::string& name)
{
	return m_childern[name].get();
}

Entity* Entity::GetSiblingByName(const std::string& name)
{
	return m_pParent->m_childern[name].get();
}

Entity* Entity::GetParent() const
{
	return m_pParent;
}

const void Entity::AddChild(std::unique_ptr<Entity> child)
{
	m_childern.insert({
		child->m_sName, std::move(child)
		});
}

const void Entity::AddComponent(std::unique_ptr<Component> component)
{
	m_components.insert({
			component->GetName(), std::move(component)
		});
}
