#include "ShittyMeshComponent.h"

//Local Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "ShittyCameraComponent.h"

//Standard Includes
#include <cstdint>

ShittyMeshComponent::ShittyMeshComponent(
	const CrappyEntity* pOwner, 
	const std::string& objfilepath, 
	const std::wstring& texfilepath
) :
	CrappyComponent(pOwner),
	m_sOBJfilepath(objfilepath),
	m_sTextureFilepath(texfilepath),
	m_transform(*(pOwner->GetComponent<TransformComponent>()))
{
}

void ShittyMeshComponent::OnStart()
{
	//First load the mesh

	Assimp::Importer im;
	const auto pScene = im.ReadFile(m_sOBJfilepath, aiPostProcessSteps::aiProcess_Triangulate | aiPostProcessSteps::aiProcess_JoinIdenticalVertices | aiPostProcessSteps::aiProcess_FlipUVs);

	const auto pMesh = pScene->mMeshes[0];

	std::vector<Vertex> Vertices(pMesh->mNumVertices);

	for (size_t i = 0; i < pMesh->mNumVertices; i++) {
		const auto& vertex = pMesh->mVertices[i];
		const auto& normal = pMesh->mNormals[i];
		const auto& uv = pMesh->mTextureCoords[0][i];
		Vertices[i].position = DirectX::XMFLOAT3(vertex.x, vertex.y, vertex.z);
		if (pMesh->HasNormals()) Vertices[i].normal = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
		if (pMesh->HasTextureCoords(0)) Vertices[i].uv = { uv.x,  uv.y };
	}

	std::vector<uint16_t> Indices((uint64_t)(pMesh->mNumFaces) * 3);
	for (size_t i = 0; i < pMesh->mNumFaces; i++) {
		const auto& pFace = pMesh->mFaces[i];
		if (pFace.mNumIndices != 3) throw EXCEPT_GENERAL_MSG(std::string("Loading failed faces are not triangulated!\n Loading mesh : ") + m_sOBJfilepath);
		Indices[i * 3] = pFace.mIndices[0];
		Indices[i * 3 + 1] = pFace.mIndices[1];
		Indices[i * 3 + 2] = pFace.mIndices[2];
	}
	//Create a vertex buffer
	AddBindable(new VertexBuffer(GetRenderer(), (UINT)Vertices.size(), (UINT)sizeof(Vertices[0]), Vertices.data()));

	//Create a index buffer
	m_pIndexBuffer = new IndexBuffer(GetRenderer(), (UINT)Indices.size(), (UINT)sizeof(Indices[0]), DXGI_FORMAT_R16_UINT, Indices.data());
	AddBindable(m_pIndexBuffer);


	//Create a vertex shader
	VertexShader* pVertexShader = new VertexShader(GetRenderer(), std::wstring(L"Shaders/MeshVS.cso"));
	AddBindable(pVertexShader);

	//Create a pixel shader
	AddBindable(new PixelShader(GetRenderer(), std::wstring(L"Shaders/MeshPS.cso")));

	//Create an input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
		{ "POSITION", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "NORMAL", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0u, (UINT)sizeof(Vertex::position), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "TEXCOORD", 0u, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0u, (UINT)(sizeof(Vertex::position) + sizeof(Vertex::normal)), D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u },
	};

	AddBindable(new InputLayout(GetRenderer(), inputElements, *pVertexShader));

	//Create a primitive topology
	AddBindable(new PrimitiveTopology(GetRenderer(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	//Create a Vertex Shader constant buffer
	m_pVSConstBuf = new VSConstantBuffer<DirectX::XMMATRIX>(GetRenderer());
	AddBindable(m_pVSConstBuf);

	//Create a Texture and a sampler state
	AddBindable(new Texture2D(GetRenderer(), TextureImage(m_sTextureFilepath)));

	//Create a sampler
	AddBindable(new Sampler(GetRenderer()));

}

void ShittyMeshComponent::OnUpdate(const float& dt)
{
	Bind();

	for (const auto& pCameraComp : ShittyCameraComponent::SceneCameras) {
		pCameraComp.second->Bind();
		m_pVSConstBuf->GetBuffer() = m_transform.GetXMTransformMatrix() * pCameraComp.second->GetXMCameraMatrix();
		m_pVSConstBuf->Update();
		GetRenderer()->GetContext()->DrawIndexed((UINT)(m_pIndexBuffer->GetElementCount()), 0, 0);
	}
	
}
