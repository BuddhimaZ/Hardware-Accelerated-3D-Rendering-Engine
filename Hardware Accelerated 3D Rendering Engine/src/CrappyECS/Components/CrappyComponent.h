#ifndef CRAPPYCOMPONENT_H
#define CRAPPYCOMPONENT_H

//Local Includes
#include "../Entity/CrappyEntity.h"
#include "../BindableSystem/BindableSystem.h"

//Standard Includes
#include <string>

class CrappyComponent {
	friend class CrappyEntity;
public:
	CrappyComponent( const CrappyEntity* pOwner );
	~CrappyComponent();

public:
	virtual void OnStart();;
	virtual void OnUpdate(const float& dt);;

	const CrappyEntity* GetOwner() const;
	const void AddBindable(Bindable* pBindable);
	const void Bind() const;
	const Renderer* GetRenderer() const;

private:
	const CrappyEntity* m_pOwner = nullptr;
	std::vector<Bindable*> m_vecBindables = {};
};

#endif // !CRAPPYCOMPONENT_H
