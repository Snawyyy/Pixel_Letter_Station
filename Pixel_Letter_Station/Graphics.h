#pragma once

#include <Windows.h>

#include <d2d1.h>


class Graphics
{
private:

	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

public:

	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	void BeginDraw() { renderTarget->BeginDraw(); }

	void EndDraw() { renderTarget->EndDraw(); }

	void Clear(D2D1::ColorF color);
};