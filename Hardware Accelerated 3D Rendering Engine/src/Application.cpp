#include "Application.h"

//DirectX Includes
#include <DirectXMath.h>

bool Application::OnStart() {
	using namespace DirectX;

	//Initialize the camera
	m_pCamera = new Camera();

	//Set the projection matrix of the renderer
	GetRenderer()->SetProjectionMatrix(XMMatrixPerspectiveLH(1.0f, (float)GetHeight() / (float)GetWidth(), 0.5f, 100.0f));

	//Create and Bind the viewports to the pipeline
	D3D11_VIEWPORT viewports[] = { {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} };
	GetRenderer()->GetContext()->RSSetViewports((UINT)(sizeof(viewports) / sizeof(viewports[0])), viewports);

	//Create and Bind the backbuffer as the render target
	ID3D11RenderTargetView* renderTargets[] = { GetRenderer()->GetBackbufferTargetView() };
	GetRenderer()->GetContext()->OMSetRenderTargets((UINT)(sizeof(renderTargets) / sizeof(renderTargets[0])), renderTargets, GetRenderer()->GetDepthStencilView());

	m_drawables.insert({ "Skull", new Mesh(
		GetRenderer(),
		std::string("Models/12140_Skull_v3_L2.obj"),
		std::wstring(L"Models/Skull.jpg"),
		m_pCamera,
		XMFLOAT3(0.0f, -10.0f, 50.0f)
	) });

	m_drawables.insert(
		{ "Cube", 
		new Mesh(
		GetRenderer(),
		std::string("Models/Cube.obj"),
		std::wstring(L"Models/Cube.png"),
		m_pCamera,
		XMFLOAT3(5.0f, 0.0f, 7.0f),
		XMFLOAT3(0.0f, -XM_PIDIV2, XM_PI)
	) });

	//m_drawables.insert(
	//	{ "Knight",
	//	new Mesh(
	//	GetRenderer(),
	//	std::string("Models/knight.obj"),
	//	std::wstring(L"Models/knight.jpg"),
	//	m_pCamera,
	//	XMFLOAT3(5.0f, 0.0f, 15.0f)
	//) });

	return true;
}

bool Application::OnUpdate(float dt) {
	using namespace DirectX;
	
	const float fRotatingSpeed = 1.0f;

	if (Input.GetKey(KB_KEY::W).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(0.0f, 0.0f, 1.0f), dt);
	}

	if (Input.GetKey(KB_KEY::S).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(0.0f, 0.0f, -1.0f), dt);
	}

	if (Input.GetKey(KB_KEY::A).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(-1.0f, 0.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::D).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(1.0f, 0.0f, 0.0f), dt);
	}
	if (Input.GetKey(KB_KEY::Q).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(0.0f, 1.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::E).bHeld) {
		m_pCamera->TranslateRelCamera(XMFLOAT3(0.0f, -1.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::I).bHeld) {
		m_pCamera->RotateCamera(XMFLOAT3(-1.0f, 0.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::K).bHeld) {
		m_pCamera->RotateCamera(XMFLOAT3(1.0f, 0.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::J).bHeld) {
		m_pCamera->RotateCamera(XMFLOAT3(0.0f, -1.0f, 0.0f), dt);
	}

	if (Input.GetKey(KB_KEY::L).bHeld) {
		m_pCamera->RotateCamera(XMFLOAT3(0.0f, 1.0f, 0.0f), dt);
	}

	Mesh* pBox = reinterpret_cast<Mesh*>(m_drawables["Cube"]);
	Mesh* pSkull = reinterpret_cast<Mesh*>(m_drawables["Skull"]);

	//pSkull->GetRotation().y += fRotatingSpeed * dt;

	//pBox->GetRotation().x += fRotatingSpeed * dt;
	//pBox->GetRotation().z += fRotatingSpeed * dt;


	for (const std::pair<std::string, Drawable*>& drawablePair : m_drawables)
		drawablePair.second->Draw();
	return true;
}

bool Application::OnDestroy()
{
	for (const std::pair<std::string, Drawable*>& drawablePair : m_drawables)
		if (drawablePair.second) delete drawablePair.second;
	return true;
}
