#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "CRender.h"
#include "Tab.h"

#define GAME "Overlay"

class Tab;

class Menu
{
private:
	std::vector<Tab*> tabs;

	bool LMButtonDown;
	bool LMButtonClicked;
	bool IsActive = false;
	BYTE keyState[256];
	bool keyDown[256];
	int MouseX;
	int MouseY;

	CRender* _pRender;
private:
	void Watermark()
	{
		_pRender->DrawFontText(0, 0, _pRender->GetColor(Colors::DARKBLUE), "Alan Turing");
	}

	void DrawMouse()
	{
		_pRender->DrawCursor(MouseX, MouseY);
	}

	void Draw()
	{
		if (!IsActive)
			return;

		for (auto tab : tabs)
		{
			if (tab->IsActive())
			{
				tab->Draw();
			}
		}
	}

	void PollInput()
	{
		//Acquire Input
		if (GetAsyncKeyState(VK_INSERT) & 1)
			IsActive = !IsActive;

		if (!IsActive)
			return;

		if (GetAsyncKeyState(VK_LBUTTON) & 1)
			LMButtonClicked = true;
		else
			LMButtonClicked = false;

		if (GetKeyState(VK_LBUTTON) & 0x8000)
			LMButtonDown = true;
		else
			LMButtonDown = false;

		GetKeyboardState(keyState);

		//Acquire Mouse Position
		auto hwnd = FindWindow(0, GAME);
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point);

		MouseX = point.x;
		MouseY = point.y;

		//Propagate Input
		for (auto tab : tabs)
		{
			if (tab->IsActive())
			{
				tab->SetMousePos(MouseX, MouseY);

				if (LMButtonDown)
					tab->OnLMouseButtonDown();

				if (!LMButtonDown)
					tab->OnLMouseButtonUp();

				if (LMButtonClicked)
					tab->OnLMouseButtonClicked();

				for (int i = 0; i < 256; i++)
				{
					if (keyState[i] & 0x80 && !keyDown[i])
					{
						keyDown[i] = true;
						auto r = MapVirtualKey(i, MAPVK_VK_TO_VSC);
						char keys[2] = { 0 };
						ToAscii(i, r, keyState, (LPWORD)keys, 0);
						tab->OnKeyPressed(keys, i);
					}

					if (!(keyState[i] & 0x80) && keyDown[i])
							keyDown[i] = false;

				}
			}
		}
	}
public:
	Menu(CRender* pRender) : _pRender(pRender) 
	{
		memset(keyDown, 0, sizeof(keyDown));
	}

	void AddTab(Tab* tab)
	{
		tabs.push_back(tab);
	}

	void Render()
	{
		PollInput();
		Draw();
		Watermark();
		DrawMouse();
	}
};