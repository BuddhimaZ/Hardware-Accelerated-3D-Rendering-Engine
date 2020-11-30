#include "RenderTargets.h"

RenderTargets::RenderTargets(
	const Renderer* pRenderer,
	const std::vector<ID3D11RenderTargetView*>& renderTargetViews,
	ID3D11DepthStencilView* pDepthStencilView
) :
	Bindable(pRenderer),
	m_vecRenderTargets(renderTargetViews),
	m_pDepthStencilView(pDepthStencilView)
{
}

RenderTargets::RenderTargets(
	const Renderer* pRenderer, 
	ID3D11RenderTargetView* renderTargetViews, 
	ID3D11DepthStencilView* pDepthStencilView
) : 
	Bindable(pRenderer),
	m_vecRenderTargets({ renderTargetViews }),
	m_pDepthStencilView( pDepthStencilView )
{
}

void RenderTargets::Bind() const
{
	GetContext()->OMSetRenderTargets((UINT)m_vecRenderTargets.size(), m_vecRenderTargets.data(), m_pDepthStencilView);
}
