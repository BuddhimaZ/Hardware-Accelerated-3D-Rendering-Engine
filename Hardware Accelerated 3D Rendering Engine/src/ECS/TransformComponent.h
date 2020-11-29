#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

//Loacal Includes
#include "Component.h"

//DirectX Includes
#include <DirectXMath.h>

class TransformComponent : public Component {
public:
	TransformComponent(
		Entity* pParent, 
		const DirectX::XMFLOAT3& relPosition, 
		const DirectX::XMFLOAT3& relRotation, 
		const DirectX::XMFLOAT3& relScale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
	);
	
	TransformComponent(Entity* pParent);

	constexpr const DirectX::XMFLOAT3& GetPosition()		const { return m_f3RelPosition	;	}
	constexpr const DirectX::XMFLOAT3& GetRotation()		const { return m_f3RelRotation	;	}
	constexpr const DirectX::XMFLOAT3& GetScale()			const { return m_f3RelScale		;	}
	constexpr const DirectX::XMFLOAT3& GetRealPosition()	const { return m_f3RealPosition	;	}
	constexpr const DirectX::XMFLOAT3& GetRealRotation()	const { return m_f3RealRotation	;	}
	constexpr const DirectX::XMFLOAT3& GetRealScale()		const { return m_f3RealScale	;	}

	const void SetPosition(const DirectX::XMFLOAT3& pos);
	const void SetRotation(const DirectX::XMFLOAT3& rot);
	const void SetScale(const DirectX::XMFLOAT3& scale);

	const DirectX::XMMATRIX GetXMTransformMatrix() const;

	void OnStart() override;
	void OnUpdate(const float& dt) override;

private:
	const TransformComponent* m_pParentTransform = nullptr;

	DirectX::XMFLOAT3 m_f3RealPosition = {};
	DirectX::XMFLOAT3 m_f3RealRotation = {};
	DirectX::XMFLOAT3 m_f3RealScale = {};

	DirectX::XMFLOAT3 m_f3RelPosition = {};
	DirectX::XMFLOAT3 m_f3RelRotation = {};
	DirectX::XMFLOAT3 m_f3RelScale = {};

};

#endif // !TRANSFORMCOMPONENT_H
