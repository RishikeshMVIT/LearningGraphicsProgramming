#include "DXDebugLayer.h"

bool DXDebugLayer::Initialize()
{
	#ifdef _DEBUG
	//Initialize D3D12 Debug Layer
	if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&m_d3d12Debug))))
	{
		m_d3d12Debug->EnableDebugLayer();
	}
	#endif // _DEBUG

	return false;
}

void DXDebugLayer::Shutdown()
{
	#ifdef _DEBUG

	#endif // _DEBUG
}
