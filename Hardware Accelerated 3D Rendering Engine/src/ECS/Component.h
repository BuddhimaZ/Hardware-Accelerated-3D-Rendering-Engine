#ifndef COMPONENT_H
#define COMPONENT_H

//Local Includes

//Standard Includes
#include <string>

//Forward declare the entity class and it's functions
class Entity;


class Component {
public:
	Component(Entity* pEntity, const std::string& name);
	
	virtual void OnStart() = 0;
	virtual void OnUpdate(const float& dt) = 0;

	constexpr const std::string& GetName() const {
		return m_sName;
	}

protected:
	Entity* GetParent() const;


private:
	Entity* m_pParent = nullptr;
	std::string m_sName = "Component";
};

#endif // !COMPONENT_H
