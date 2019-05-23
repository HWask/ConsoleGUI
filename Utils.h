#pragma once
#include <Windows.h>

class Utils
{
public:
	bool static DataCompare(const BYTE* Data, const BYTE* HexMask, const char* MatchMask)
	{
		for (; *MatchMask; ++MatchMask, ++Data, ++HexMask)
		{
			if (*MatchMask == 'x' && *Data != *HexMask)
			{
				return false;
			}
		}
		return (*MatchMask) == NULL;
	}

	DWORD static FindPattern(DWORD Address, DWORD Len, BYTE* HexMask, char* MatchMask)
	{
		for (DWORD i = 0; i < Len; i++)
		{
			if (DataCompare((BYTE*)(Address + i), HexMask, MatchMask))
			{
				return (DWORD)(Address + i);
			}
		}

		return NULL;
	}
};