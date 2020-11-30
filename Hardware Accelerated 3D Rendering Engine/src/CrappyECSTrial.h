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
	bool OnDestroy() override;

private:
	CrappyScene* pScene = nullptr;

};

#endif // !CRAPPYECSTRIAL_H
