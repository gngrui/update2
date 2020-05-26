#pragma once

#include "block.h"
#include <d2d1.h>

template <class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

class D2DResource
{
public:
	D2DResource() : 
		m_pD2DFactory(nullptr),
		m_pRenderTarget(nullptr),

		m_pSolidDarkBlueBrush(nullptr),
		m_pSolidIvorynBrush(nullptr),
		m_pSolidRedBrush(nullptr),
		m_pSolidYellowBrush(nullptr),
		m_pSolidGreenBrush(nullptr)
	{}
	~D2DResource() 
	{
		SafeRelease(&m_pD2DFactory);
		SafeRelease(&m_pRenderTarget);

		SafeRelease(&m_pSolidDarkBlueBrush);
		SafeRelease(&m_pSolidIvorynBrush);
		SafeRelease(&m_pSolidRedBrush);
		SafeRelease(&m_pSolidYellowBrush);
		SafeRelease(&m_pSolidGreenBrush);
		SafeRelease(&m_pSolidGrayBrush);
	}

	HRESULT Initialize(HWND& hwnd);
	ID2D1HwndRenderTarget& getRenderTarget() const;

	ID2D1SolidColorBrush& getSolidDarkBlueBrush() const;
	ID2D1SolidColorBrush& SolidIvorynBrush() const;
	ID2D1SolidColorBrush& getSolidRedBrush() const;
	ID2D1SolidColorBrush& getSolidYellowBrush() const;
	ID2D1SolidColorBrush& getSolidGreenBrush() const;
	ID2D1SolidColorBrush& getSolidGrayBrush() const;

	ID2D1SolidColorBrush* getBrushByColor(BLOCK_COLOR& color);

private:
	HRESULT CreateD2DResource(HWND& hwnd);
private:
	ID2D1Factory* m_pD2DFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1SolidColorBrush* m_pSolidDarkBlueBrush;
	ID2D1SolidColorBrush* m_pSolidIvorynBrush;
	ID2D1SolidColorBrush* m_pSolidRedBrush;
	ID2D1SolidColorBrush* m_pSolidYellowBrush;
	ID2D1SolidColorBrush* m_pSolidGreenBrush;
	ID2D1SolidColorBrush* m_pSolidGrayBrush;
};