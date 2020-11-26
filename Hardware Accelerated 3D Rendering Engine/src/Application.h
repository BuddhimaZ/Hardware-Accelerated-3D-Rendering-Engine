#ifndef APPLICATION_H
#define APPLICATION_H

//Local Includes
#include "EngineBase.h"
#include "DrawableSystem/Box.h"
#include "DrawableSystem/BoxWithTexture.h"
#include "DrawableSystem/Skull.h"
#include "DrawableSystem/Mesh.h"
#include "Camera.h"

//Standard Includes
#include <vector>
#include <cstdint>
#include <unordered_map>

class Application : public EngineBase {
public:
	using EngineBase::EngineBase;
private:
	bool OnStart() override; 
	bool OnUpdate(float dt) override; 
	bool OnDestroy() override;

private:
	std::unordered_map<std::string, Drawable*> m_drawables;
	Camera* m_pCamera = nullptr;
};

#endif // !APPLICATION_H