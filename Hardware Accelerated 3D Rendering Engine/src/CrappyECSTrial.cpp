#include "CrappyECSTrial.h"

bool CrappyECSTrial::OnStart()
{
    using namespace DirectX;

    D3D11_VIEWPORT viewport = {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} ;

    Scene.SetRenderer(GetRenderer());

    //Construct the scene
    Scene["MainCamera"].operator() < ShittyCameraComponent > (
        XMMatrixPerspectiveLH(1.0f, (float)GetHeight() / (float)GetWidth(), 0.5f, 100.0f),
        new Viewports(GetRenderer(), viewport),
        new RenderTargets(GetRenderer(), GetRenderer()->GetBackbufferTargetView(), GetRenderer()->GetDepthStencilView())
        );

    Scene["Skull"].operator() < ShittyMeshComponent > (
        std::string("Models/Cube.obj"),
        std::wstring(L"Models/Cube.png")
        );

    Scene["Skull"].operator() < TransformComponent > ().SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.0f));

    Scene.OnSceneStart();

    return true;
}

bool CrappyECSTrial::OnUpdate(float dt)
{
    Scene.OnSceneUpdate(dt);
    return true;
}
