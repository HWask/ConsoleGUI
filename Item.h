#pragma once
#include <string>

class Item
{
public:
	virtual void GetSize(int& w, int& h) = 0;
	virtual void GetPos(int& x, int& y) = 0;
	virtual bool HasFocus() = 0;
	virtual bool IsActive() = 0;
	virtual void Draw() = 0;
	virtual void OnKeyPressed(char c[2], int i) = 0;
	virtual void OnLMouseButtonDown() = 0;
	virtual void OnLMouseButtonUp() = 0;
	virtual void OnLMouseButtonClicked() = 0;
	virtual void SetMousePos(int x, int y) = 0;
	virtual std::string GetName() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};