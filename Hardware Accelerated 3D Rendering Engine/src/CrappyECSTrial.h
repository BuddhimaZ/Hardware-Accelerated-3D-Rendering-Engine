#ifndef CRAPPYECSTRIAL_H
#define CRAPPYECSTRIAL_H

//Local Inlcudes
#include "EngineBase.h"
#include "CrappyECS/CrappyECS.h"

class CrappyECSTrial : public EngineBase {
public:
	using EngineBase::EngineBase;

private:
	bool OnStart() override;
	bool OnUpdate(float dt) override;

private:
	CrappyScene Scene;
};

#endif // !CRAPPYECSTRIAL_H
