#pragma once
#include "Button.h"

class ColorButton : public Button
{
public:
	LPARAM lParam;
	LPDRAWITEMSTRUCT pDIS;
	int buttonId;
	const wchar_t* text;

	ColorButton(LPARAM lp, int id, const wchar_t* te):Button(lp, id, te), lParam(lp), buttonId(id), text(te)
	{

	}
	/*void Draw() override
	{

	}*/
};