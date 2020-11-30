#include "Viewports.h"

Viewports::Viewports(
	const Renderer* pRenderer, 
	const std::vector<D3D11_VIEWPORT>& viewPorts
) : 
	Bindable(pRenderer), 
	m_vecViewports(viewPorts)
{
}

Viewports::Viewports(
	const Renderer* pRenderer, 
	D3D11_VIEWPORT& viewPort
) :

	Bindable(pRenderer),
	m_vecViewports({ viewPort })
{
}

void Viewports::Bind() const
{
	GetContext()->RSSetViewports((UINT)m_vecViewports.size(), m_vecViewports.data());
}
