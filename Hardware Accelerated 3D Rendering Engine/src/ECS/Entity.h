#ifndef ENTITY_H
#define ENTITY_H

//Local Includes
#include "Component.h"


//Standard Includes
#include <unordered_map>
#include <memory>

class Entity {
public:
	Entity(Entity* pParent, const std::string& name);
	Component* GetComponentByName(const std::string& name);
	Entity* GetChildByName(const std::string& name);
	Entity* GetSiblingByName(const std::string& name);
	Entity* GetParent() const;

	const void AddChild(std::unique_ptr<Entity> child);
	const void AddComponent(std::unique_ptr<Component> component);

private:
	Entity* m_pParent = nullptr;
	std::string m_sName = "";
	std::unordered_map<std::string, std::unique_ptr<Component>> m_components;
	std::unordered_map<std::string, std::unique_ptr<Entity>> m_childern;
	
};

#endif // !ENTITY_H
