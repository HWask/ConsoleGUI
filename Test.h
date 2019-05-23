#pragma once
#include <vector>
#include "CheatClass.h"

class Test : public CheatClass
{
public:
	enum
	{
		Cheat1,
		Cheat2,
		Cheat3,
		Cheat4,
		MAX
	};

	int x = 13;
	float y = 3.54;
	bool z = false;
	std::vector<int> a;

	Test() : a({ 1, 2, 3, 4, 5 }) {}

	int GetIValue(int index)
	{
		if (index == Cheat1)
			return x;
	}

	bool GetBoolValue(int index)
	{
		if (index == Cheat2)
			return z;
	}

	float GetFLValue(int index)
	{
		if (index == Cheat3)
			return y;
	}

	std::vector<int> GetVECValue(int index)
	{
		if (index == Cheat4)
			return a;
	}

	void SetIValue(int val, int index)
	{
		if (index == Cheat1)
			x = val;
	}

	void SetBoolValue(bool val, int index)
	{
		if (index == Cheat2)
			z = val;
	}

	void SetFLValue(float val, int index)
	{
		if (index == Cheat3)
			y = val;
	}

	void SetVECValue(std::vector<int> val, int index)
	{
		if (index == Cheat4)
			a = val;
	}
};