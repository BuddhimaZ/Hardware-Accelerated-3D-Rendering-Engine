#ifndef CRAPPYENTITY_H
#define CRAPPYENTITY_H

//Local Includes
#include "../Renderer.h"

#include <DirectXMath.h>

//Standard Includes
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <type_traits>

//Forward declare CrappyComponent class
class CrappyComponent;

class CrappyEntity {
	friend class CrappyComponent;
public:
	CrappyEntity(
		const CrappyEntity* pParent, 
		const std::string& name, 
		const DirectX::XMFLOAT3& pos, 
		const DirectX::XMFLOAT3& rot, 
		const DirectX::XMFLOAT3& scale
	);

	CrappyEntity(
		const CrappyEntity* pParent, 
		const std::string& name
	);
	~CrappyEntity();

	//Get the name of the Entity
	const std::string& GetName() const;

	// Add a new child enity to the current entity
	// If a child exist with the given name this function
	// will return a pointer to the already existing child
	CrappyEntity* AddChild(const std::string& name);

	CrappyEntity* AddChild(
		const std::string& name,
		const DirectX::XMFLOAT3& pos,
		const DirectX::XMFLOAT3& rot,
		const DirectX::XMFLOAT3& scale
	);

	// Get the child entity of this entity by name
	// Returns a pointer to the child entity if a child
	// by the given name exists.
	// Otherwise returns nullptr
	CrappyEntity* GetChild(const std::string& name) const;

	//Get a pointer to the parent of the current Entity
	const CrappyEntity* GetParent() const;

	// Add a new Component to the current entity
	// If a Component exist with the given type this function
	// will return a pointer to the already existing component
	// And will delete the parsed component

	template<class T, class... _Types>
	T* AddComponent(_Types&&... args) {
		//Check if the T is a derrived class of the componet class
		static_assert(std::is_base_of<CrappyComponent, T>::value, "T must inherit from CrappyComponent class");

		
		//Check if there's already a child by given name
		T* pComponent = static_cast<T*>(GetComponent<T>());

		//A component exists
		if (pComponent) {
			return pComponent;
		}

		//Add the new component to the map
		pComponent = new T(this, std::forward<_Types>(args)...);
		m_pComponents.insert({ typeid(T).name(), pComponent });
		return pComponent;
	}

	template<class T>
	T* AddComponent() {
		//Check if the T is a derrived class of the componet class
		static_assert(std::is_base_of<CrappyComponent, T>::value, "T must inherit from CrappyComponent class");


		//Check if there's already a child by given name
		T* pComponent = static_cast<T*>(GetComponent<T>());

		//A component exists
		if (pComponent) {
			return pComponent;
		}

		//Add the new component to the map
		pComponent = new T(this);
		m_pComponents.insert({ typeid(T).name(), pComponent });
		return pComponent;
	}

	// Get the Component entity of this entity by name
	// Returns a pointer to the Component entity if a child
	// by the given name exists.
	// Otherwise returns nullptr
	//CrappyComponent* GetComponent(const std::string& type) const;

	template<class T>
	T* GetComponent() const 
	{
		//Check if the T is a derrived class of the componet class
		static_assert(std::is_base_of<CrappyComponent, T>::value, "T must inherit from CrappyComponent class");

		auto it = m_pComponents.find(typeid(T).name());

		if (it == m_pComponents.end()) {
			//There's no component by the given name
			return nullptr;
		}

		//Otherwise return the pointer to the component
		return static_cast<T*>(it->second);
	}

	CrappyEntity& operator[] (const std::string& name);

	CrappyEntity& operator() (
		const std::string& name, 
		const DirectX::XMFLOAT3& pos,
		const DirectX::XMFLOAT3& rot, 
		const DirectX::XMFLOAT3& scale
		);

	template<class T, class... _Types>
	T& operator() (_Types&&... args) {
		return *(AddComponent<T>(args...));
	}

	template<class T>
	T& operator() () {
		return *(AddComponent<T>());
	}

public:

	//Call this function to initialize all the components in this entity and children
	const void OnStart() const;

	//Call this function to update all the components in this entity and children
	const void OnUpdate(const float& dt) const;

protected:
	std::unordered_map<std::string, CrappyEntity*> m_pChildren = {};
	const Renderer* m_pRenderer = nullptr;
private:
	const std::string m_sName;
	const CrappyEntity* m_pParent = nullptr;
	std::unordered_map<std::string, CrappyComponent*> m_pComponents = {};
	
};

#endif // !CRAPPYENTITY_H
