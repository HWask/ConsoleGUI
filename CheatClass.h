#pragma once
#include <vector>

class CheatClass
{
public:
	virtual int GetIValue(int index) = 0;
	virtual bool GetBoolValue(int index) = 0;
	virtual float GetFLValue(int index) = 0;
	virtual std::vector<int> GetVECValue(int index) = 0;

	virtual void SetIValue(int val, int index) = 0;
	virtual void SetBoolValue(bool val, int index) = 0;
	virtual void SetFLValue(float val, int index) = 0;
	virtual void SetVECValue(std::vector<int> val, int index) = 0;
};