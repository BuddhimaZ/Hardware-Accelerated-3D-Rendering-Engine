#ifndef VIEWPORTS_H
#define VIEWPORTS_H

//Local Includes
#include "Bindable.h"

//Standard Includes
#include <vector>

class Viewports : public Bindable {
public:
	Viewports(
		const Renderer* pRenderer, 
		const std::vector<D3D11_VIEWPORT>& viewPorts
	);

	Viewports(
		const Renderer* pRenderer,
		D3D11_VIEWPORT& viewPorts
	);

	virtual void Bind() const override;

private:
	std::vector<D3D11_VIEWPORT> m_vecViewports = {};
};

#endif // !VIEWPORTS_H
