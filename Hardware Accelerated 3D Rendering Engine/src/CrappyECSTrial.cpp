#include "CrappyECSTrial.h"

bool CrappyECSTrial::OnStart()
{
    using namespace DirectX;
    
    pScene = new CrappyScene(GetRenderer());

    CrappyScene& Scene = *pScene;

    //Construct the scene

    //Add a camera to the scene
    Scene["MainCamera"].operator()<ShittyCameraComponent>(XMMatrixPerspectiveLH(1.0f, (float)GetHeight() / (float)GetWidth(), 0.5f, 100.0f), new Viewports(GetRenderer(), { {0.0f, 0.0f, (FLOAT)GetWidth(), (FLOAT)GetHeight(), 0.0f, 1.0f} }), new RenderTargets(GetRenderer(), { GetRenderer()->GetBackbufferTargetView() }, GetRenderer()->GetDepthStencilView()));
    
    //Attach Camera controller script to Camera
    Scene["MainCamera"].operator() < CameraController > ();

    //Add a Cube model to the scene
    Scene.operator()("Cube", XMFLOAT3(5.0f, 0.0f, 4.0f), XMFLOAT3(0.0f, -XM_PIDIV2, XM_PI)).operator() < ShittyMeshComponent > ("Models/Cube.obj", std::wstring(L"Models/Cube.png"));

    //Add a skull model to the scene
    Scene.operator()("Skull", XMFLOAT3(0.0f, -10.0f, 50.0f), XMFLOAT3(0.0f, 0.0f, 0.0f)).operator()<ShittyMeshComponent>("Models/12140_Skull_v3_L2.obj", std::wstring(L"Models/Skull.jpg"));
    
    Scene.OnSceneStart();

    return true;
}

bool CrappyECSTrial::OnUpdate(float dt)
{
    pScene->OnSceneUpdate(dt);
    return true;
}

bool CrappyECSTrial::OnDestroy()
{
    delete pScene;
    return true;
}
