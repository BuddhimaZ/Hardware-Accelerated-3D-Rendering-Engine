#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

//Local Includes
#include "CrappyComponent.h"
#include "TransformComponent.h"

//DirectX Includes
#include <DirectXMath.h>

//Standard Includes
#include <unordered_map>
#include <string>

class ShittyCameraComponent : public CrappyComponent {
public:
	//Any component of the scene can access all the camera components in the scene
	//They can enumerate the camera component by the name of the Camera entity ( Entity that holds the camera component )
	static std::unordered_map<std::string, ShittyCameraComponent*> SceneCameras;
public:

	ShittyCameraComponent(
		const CrappyEntity* pOwner,
		const DirectX::XMMATRIX& ProjectionMatrix
	);

	// TODO : Remove this shitty code once you implement a proper way of doing this shit
	ShittyCameraComponent(
		const CrappyEntity* pOwner,
		const DirectX::XMMATRIX& ProjectionMatrix,
		Viewports* pViewports,
		RenderTargets* pRenderTargets
	);


	void OnStart() override;

	const DirectX::XMMATRIX GetXMCameraMatrix() const;

private:
	const DirectX::XMMATRIX m_xmmatProjectionMatrix;
	const TransformComponent& m_transform;


	//To be removed.
	//This is not a clean way of doing this but for the time being we are going to do it this way
	// TODO : Remove this shitty code once you implement a proper way of doing this shit
	Viewports* m_pViewports = nullptr;
	RenderTargets* m_pRenderTargets = nullptr;
};

#endif // !CAMERACOMPONENT_H