#pragma once
#include "Item.h"
#include "CRender.h"
#include "Textarea.h"
#include "Textbox.h"

class Tab : public Item
{
private:
	int _x;
	int _y;
	int _w;
	int _h;

	bool hasFocus = false;
	bool isActive = true;
	std::string _name;
	CRender* _pRender;

	int MouseX;
	int MouseY;
	int relMouseX;
	int relMouseY;

	int HeaderHeight = 20;

	std::vector<Item*> items;

	bool IsDragging = false;
	int DeltaX;
	int DeltaY;
public:
	Tab(int x, int y, int w, int h, std::string name, CRender* pRender) : _x(x), _y(y), _w(w), _h(h), _name(name),
		_pRender(pRender) {}

	void AddChild(Item* item)
	{
		items.push_back(item);
	}

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

	bool HasFocus() override
	{
		return hasFocus;
	}

	bool IsActive() override
	{
		return isActive;
	}

	CRender* getRender()
	{
		return _pRender;
	}

	void Draw() override
	{
		//Background
		_pRender->DrawRect(_x, _y, _w, _h, _pRender->GetColor(Colors::LAVENDER));

		//Header
		_pRender->DrawRect(_x, _y, _w, HeaderHeight, _pRender->GetColor(Colors::ScoreBoardHeader));

		int textW, textH;
		_pRender->GetStringSize(textW, textH, (char*)_name.c_str());
		_pRender->DrawFontText(_x + _w/2 - textW/2, _y + HeaderHeight / 2 - textH / 2,
			_pRender->GetColor(Colors::WHITE), (char*)_name.c_str());

		//Children
		for (auto child : items)
		{
			child->Draw();
		}
	}

	void OnKeyPressed(char c[2], int i) override
	{
		for (auto child : items)
			child->OnKeyPressed(c, i);
	}

	void OnLMouseButtonDown() override
	{
		if (relMouseX >= 0 && relMouseX <= _w && relMouseY >= 0 && relMouseY <= HeaderHeight)
		{
			IsDragging = true;
			DeltaX = MouseX - _x;
			DeltaY = MouseY - _y;
		}

		for (auto child : items)
			child->OnLMouseButtonDown();
	}

	void OnLMouseButtonUp() override
	{
		IsDragging = false;

		for (auto child : items)
			child->OnLMouseButtonUp();
	}

	void OnLMouseButtonClicked() override
	{
		for (auto child : items)
			child->OnLMouseButtonClicked();
	}

	void SetMousePos(int x, int y) override
	{
		MouseX = x;
		MouseY = y;
		relMouseX = x-_x;
		relMouseY = y-_y;

		if (IsDragging)
		{
			_x = MouseX - DeltaX;
			_y = MouseY - DeltaY;
		}

		for (auto child : items)
		{
			int __x, __y;
			child->GetPos(__x, __y);
			child->SetMousePos(relMouseX-__x, relMouseY-__y);
		}
	}

	std::string GetName() override
	{
		return _name;
	}

	void Activate() override
	{
		isActive = true;
	}

	void Deactivate() override
	{
		isActive = false;
	}
};