#pragma once
#include "Item.h"
#include "CRender.h"
#include <functional>
#include <algorithm>

class Textbox : public Item
{
private:
	int _x;
	int _y;
	int _w;
	int _h;

	int MouseX;
	int MouseY;

	CRender* _pRender;
	Item* _parent;

	bool IsFocused = false;
	std::string textBuf;
	std::function<void(std::string)> callback = nullptr;

	int LeftMargin = 10;
public:
	Textbox(int x, int y, int w, int h, CRender* pRender, Item* parent) : _x(x), _y(y), _w(w), _h(h),
		_pRender(pRender), _parent(parent) {}

	void GetSize(int& w, int& h) override
	{
		w = _w;
		h = _h;
	}

	void GetPos(int& x, int& y) override
	{
		x = _x;
		y = _y;
	}

	void SetCallBack(std::function<void(std::string)> f)
	{
		callback = f;
	}

	bool HasFocus() override
	{
		return IsFocused;
	}

	bool IsActive() override
	{
		return true;
	}

	void Draw() override
	{
		int __x, __y;
		_parent->GetPos(__x, __y);

		_pRender->DrawRect(__x + _x, __y + _y, _w, _h, _pRender->GetColor(Colors::Turkis));

		if (IsFocused)
			_pRender->DrawOutlinedRect(__x + _x, __y + _y, _w, _h, _pRender->GetColor(Colors::MENUBLOPSELECTED));

		int textW, textH;
		_pRender->GetStringSize(textW, textH, "M");
		_pRender->DrawFontText(__x + _x + LeftMargin, __y + _y + _h / 2 - textH / 2,
			_pRender->GetColor(Colors::WHITE), (char*)textBuf.c_str());
	}

	void stripInvalidChars(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), 
			[](char c) -> bool
			{
				return !(c >= 0 && c < 256);
			}),
			str.end());
	}

	void OnKeyPressed(char c[2], int i) override 
	{
		if (IsFocused)
		{
			if (i == VK_RETURN)
			{
				if (callback != nullptr)
					callback(textBuf);

				textBuf = "";
			}
			else if (i == VK_BACK)
			{
				if (textBuf.length() >= 1)
					textBuf = textBuf.substr(0, textBuf.length() - 1);
			}
			else
			{
				textBuf += c;
				int textW, textH;
				_pRender->GetStringSize(textW, textH, (char*)textBuf.c_str());
				if (textW + LeftMargin >= _w - LeftMargin)
				{
					textBuf = textBuf.substr(0, textBuf.length() - 1);
					stripInvalidChars(textBuf);
				}
			}
		}
	}

	void OnLMouseButtonDown() override
	{
	}

	void OnLMouseButtonUp() override
	{
	}

	void OnLMouseButtonClicked() override
	{
		if (MouseX >= 0 && MouseX <= _w && MouseY >= 0 && MouseY <= _h)
			IsFocused = true;
		else
			IsFocused = false;
	}

	void SetMousePos(int x, int y)
	{
		MouseX = x;
		MouseY = y;
	}

	std::string GetName() override
	{
		return "";
	}

	void Activate() override {}

	void Deactivate() override {}
};