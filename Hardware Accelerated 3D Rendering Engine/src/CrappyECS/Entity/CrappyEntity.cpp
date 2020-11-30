#include "CrappyEntity.h"

#include "../Components/CrappyComponent.h"
#include "../Components/TransformComponent.h"

CrappyEntity::CrappyEntity(
	const CrappyEntity* pParent, 
	const std::string& name, 
	const DirectX::XMFLOAT3& pos, 
	const DirectX::XMFLOAT3& rot, 
	const DirectX::XMFLOAT3& scale
) :
	m_pParent(pParent),
	m_sName(name),
	m_pRenderer(pParent != nullptr ? pParent->m_pRenderer : nullptr)
{
	AddComponent<TransformComponent>(pos, rot, scale);
}

CrappyEntity::CrappyEntity(
	const CrappyEntity* pParent, 
	const std::string& name
) : 
	CrappyEntity(
		pParent, 
		name,
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
	)
{
}

CrappyEntity::~CrappyEntity()
{
	for (std::pair<std::string, CrappyEntity*> child : m_pChildren) {
		CrappyEntity*& pChild = child.second;
		if (pChild) delete pChild;
	}
}

const std::string& CrappyEntity::GetName() const
{
	return m_sName;
}

// Add a new child enity to the current entity
// If a child exist with the given name this function
// will return a pointer to the already existing child

CrappyEntity* CrappyEntity::AddChild(const std::string& name)
{
	//Check if there's already a child by given name
	CrappyEntity* pChild = GetChild(name);

	//A child exists
	if (pChild) return pChild;

	//Create a new child
	pChild = new CrappyEntity(this, name);
	m_pChildren.insert({ pChild->m_sName, pChild });
	return pChild;
}

CrappyEntity* CrappyEntity::AddChild(const std::string& name, const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& rot, const DirectX::XMFLOAT3& scale)
{
	//Check if there's already a child by given name
	CrappyEntity* pChild = GetChild(name);

	//A child exists
	if (pChild) return pChild;

	//Create a new child
	pChild = new CrappyEntity(this, name, pos, rot, scale);
	m_pChildren.insert({ pChild->m_sName, pChild });
	return pChild;
}


// Get the child entity of this entity by name
// Returns a pointer to the child entity if a child
// by the given name exists.
// Otherwise returns nullptr

CrappyEntity* CrappyEntity::GetChild(const std::string& name) const {
	auto it = m_pChildren.find(name);

	if (it == m_pChildren.end()) {
		//There's no child by the given name
		return nullptr;
	}

	//Otherwise return the pointer to the child
	return it->second;
}

const CrappyEntity* CrappyEntity::GetParent() const
{
	return m_pParent;
}


CrappyEntity& CrappyEntity::operator[](const std::string& name)
{
	return *(AddChild(name));
}

CrappyEntity& CrappyEntity::operator()(const std::string& name, const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& rot, const DirectX::XMFLOAT3& scale)
{
	return *(AddChild(name, pos, rot, scale));
}

const void CrappyEntity::OnStart() const
{
	//First call the OnStart() function of Our own components
	for (auto& pComp : m_pComponents) {
		pComp.second->OnStart();
	}

	//Then call the OnStart() function of children entities
	for (auto& pChild : m_pChildren) {
		pChild.second->OnStart();
	}
}

const void CrappyEntity::OnUpdate(const float& dt) const
{
	//First call the OnUpdate() function of Our own components
	for (auto& pComp : m_pComponents) {
		pComp.second->OnUpdate(dt);
	}

	//Then call the OnUpdate() function of children entities
	for (auto& pChild : m_pChildren) {
		pChild.second->OnUpdate(dt);
	}
}
