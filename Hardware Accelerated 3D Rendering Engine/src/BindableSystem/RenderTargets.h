#ifndef RENDERTARGETS_H
#define RENDERTARGETS_H

//Local Includes
#include "Bindable.h"

//Standard Includes
#include <vector>

class RenderTargets : public Bindable {
public:
	RenderTargets(
		const Renderer* pRenderer, 
		const std::vector<ID3D11RenderTargetView*>& renderTargetViews,
		ID3D11DepthStencilView* pDepthStencilView
	);

	RenderTargets(
		const Renderer* pRenderer,
		ID3D11RenderTargetView* renderTargetViews,
		ID3D11DepthStencilView* pDepthStencilView = nullptr
	);

	virtual void Bind() const override;

private:
	std::vector<ID3D11RenderTargetView*> m_vecRenderTargets = {};
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
};

#endif // !RENDERTARGETS_H
