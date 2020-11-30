#ifndef SHITTYMESHCOMPONENT_H
#define SHITTYMESHCOMPONENT_H

//Local Includes
#include "CrappyComponent.h"
#include "TransformComponent.h"

//Standard Includes

class ShittyMeshComponent : public CrappyComponent {
private:
	struct Vertex {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
public:
	ShittyMeshComponent(
		const CrappyEntity* pOwner, 
		const std::string& objfilepath, 
		const std::wstring& texfilepath
	);

	void OnStart() override;
	void OnUpdate(const float& dt) override;

private:
	const TransformComponent& m_transform;
	IndexBuffer* m_pIndexBuffer = nullptr;
	VSConstantBuffer<DirectX::XMMATRIX>* m_pVSConstBuf = nullptr;
	const std::string m_sOBJfilepath;
	const std::wstring m_sTextureFilepath;
};

#endif // !SHITTYMESHCOMPONENT_H
