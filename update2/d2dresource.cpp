#include "d2dresource.h"

HRESULT D2DResource::Initialize(HWND& hwnd)
{
	HRESULT hr = S_OK;
	hr = CreateD2DResource(hwnd);
	return hr;
}

ID2D1HwndRenderTarget& D2DResource::getRenderTarget() const
{
	return *m_pRenderTarget;
}

ID2D1SolidColorBrush& D2DResource::getSolidDarkBlueBrush() const
{
	return *m_pSolidDarkBlueBrush;
}

ID2D1SolidColorBrush& D2DResource::SolidIvorynBrush() const
{
	return *m_pSolidIvorynBrush;
}

ID2D1SolidColorBrush& D2DResource::getSolidRedBrush() const
{
	return *m_pSolidRedBrush;
}

ID2D1SolidColorBrush& D2DResource::getSolidYellowBrush() const
{
	return *m_pSolidYellowBrush;
}

ID2D1SolidColorBrush& D2DResource::getSolidGreenBrush() const
{
	return *m_pSolidGreenBrush;
}

ID2D1SolidColorBrush& D2DResource::getSolidGrayBrush() const
{
	return *m_pSolidGrayBrush;
}

ID2D1SolidColorBrush* D2DResource::getBrushByColor(BLOCK_COLOR& color)
{
	ID2D1SolidColorBrush* brush = nullptr;
	if (color == BLOCK_COLOR::DARKBULE)
	{
		brush = m_pSolidDarkBlueBrush;
	}
	else if (color == BLOCK_COLOR::GREEN)
	{
		brush = m_pSolidGreenBrush;
	}
	else if (color == BLOCK_COLOR::IVORY)
	{
		brush = m_pSolidIvorynBrush;
	}
	else if (color == BLOCK_COLOR::RED)
	{
		brush = m_pSolidRedBrush;
	}
	else if (color == BLOCK_COLOR::YELLOW)
	{
		brush = m_pSolidYellowBrush;
	}
	else if (color == BLOCK_COLOR::GRAY)
	{
		brush = m_pSolidGrayBrush;
	}
	return brush;
}

HRESULT D2DResource::CreateD2DResource(HWND& hwnd)
{
	HRESULT hr = S_OK;

	// Factory
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	if (SUCCEEDED(hr)) // RenderTarget
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		D2D1_SIZE_U size = D2D1::SizeU(
			rect.right - rect.left,
			rect.bottom - rect.top
		);
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&m_pRenderTarget
		);
	}
	// Brushes
	if (SUCCEEDED(hr)) // 1
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::DarkBlue),
			&m_pSolidDarkBlueBrush
		);
	}
	if (SUCCEEDED(hr)) // 2
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Ivory),
			&m_pSolidIvorynBrush
		);
	}
	if (SUCCEEDED(hr)) // 3
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&m_pSolidRedBrush
		);
	}
	if (SUCCEEDED(hr)) // 4
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Yellow),
			&m_pSolidYellowBrush
		);
	}
	if (SUCCEEDED(hr)) // 5
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green),
			&m_pSolidGreenBrush
		);
	}
	if (SUCCEEDED(hr)) // 5
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green),
			&m_pSolidGrayBrush
		);
	}
	return hr;
}
