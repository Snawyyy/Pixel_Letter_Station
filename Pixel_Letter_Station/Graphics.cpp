#include "Graphics.h"

Graphics::Graphics()
{
    factory = NULL;
    renderTarget = NULL;
}

Graphics::~Graphics()
{
    if (factory) factory->Release();
    if (renderTarget) renderTarget->Release();
}



bool Graphics::Init(HWND hWnd)
{
    HRESULT h = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    if (FAILED(h))
    {
        return false;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);

    int height = rect.bottom - rect.top;
    int width = rect.right - rect.left;

    h = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,  // Or D2D1_RENDER_TARGET_TYPE_HARDWARE for hardware acceleration
            D2D1::PixelFormat(
                DXGI_FORMAT_B8G8R8A8_UNORM,  
                D2D1_ALPHA_MODE_PREMULTIPLIED 
            )),
        D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(width, height)),
        &renderTarget);

    if (FAILED(h))
    {
        return false;
    }
    return true;
}

void Graphics::Clear(D2D1::ColorF color)
{
    renderTarget->Clear(&color);
}