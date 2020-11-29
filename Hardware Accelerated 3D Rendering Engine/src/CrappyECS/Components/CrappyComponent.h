#ifndef CRAPPYCOMPONENT_H
#define CRAPPYCOMPONENT_H

//Local Includes
#include "../Entity/CrappyEntity.h"

//Standard Includes
#include <string>

class CrappyComponent {
	friend class CrappyEntity;
public:
	CrappyComponent(
		const CrappyEntity* pOwner
	);

protected:
	virtual void OnStart() = 0;
	virtual void OnUpdate(const float& dt) = 0;

	const CrappyEntity* GetOwner() const;

private:
	const CrappyEntity* m_pOwner = nullptr;
};

#endif // !CRAPPYCOMPONENT_H
