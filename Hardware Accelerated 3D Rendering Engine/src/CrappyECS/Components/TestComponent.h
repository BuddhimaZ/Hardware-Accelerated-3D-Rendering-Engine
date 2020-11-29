#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "CrappyComponent.h"

class TestComponent : public CrappyComponent {
public:
	TestComponent(const CrappyEntity* pOwner);

private:
	void OnStart() override;

	void OnUpdate(const float& dt) override;

};

#endif // !TESTCOMPONENT_H