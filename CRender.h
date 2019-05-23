#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <cstdio>
#include <cstdarg>
#include <vector>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define CColor DWORD
#define PI 3.14159265358f

enum Colors
{
	BLACK,
	WHITE,
	RED,
	GREEN,
	DARKBLUE,
	YELLOW,
	SKYBLUE,
	PINK,
	BROWN,
	ORANGE,
	GRAY,
	MENUTOPBORDERSTART,
	MENUTOPBORDEREND,
	MENUBUTTONSTART,
	MENUBUTTONEND,
	MENUBORDER,
	MENUDEFAULT,
	MENUBACKGROUND,
	MENUTEXT,
	MENUSLIDER,
	MENUCOMBOBOXSELECTED,
	MENUCOMBOBOXNOTSELECTED,
	MENUBLOP,
	MENUBLOPSELECTED,
	MENUTITLEBG,
	BRIGHTGREEN,
	TRANSPARENT_BLACK,
	TRANSPARENT_GRAY,
	AZURE,
	GOLDENROD,
	DARKGOLDENROD,
	GOLD,
	LAVENDER,
	TEAL,
	ScoreBoardHeader,
	ScoreBoardRowEven,
	ScoreBoardRowOdd,
	LightGreen,
	LightBlue,
	Turkis,
	LightRed,
	DarkBrown,
	COLOR_MAX,
};

class CVertexList
{
public:
	FLOAT X, Y, Z;
	DWORD dColor;
};

class CRender
{
public:
	CRender();
	VOID Create(LPDIRECT3DDEVICE9 pGameDevice);
	BOOL IsCreated()        { return bIsCreated; }
	VOID Release();
	VOID OnLostDevice();
	VOID OnResetDevice();

	CColor GetColor(INT iColorNumber)        { return Colors[iColorNumber]; }

	VOID Begin();
	VOID End();

	INT DrawFontText(INT X, INT Y, CColor dColor, PCHAR szString, ...);
	VOID DrawOutlinedFontText(INT X, INT Y, CColor dColor, PCHAR szString, ...);

	INT DrawFontTextW(INT X, INT Y, CColor dColor, PWCHAR szString, ...);
	VOID DrawOutlinedFontTextW(INT X, INT Y, CColor dColor, PWCHAR szString, ...);

	VOID DrawFilledCircle(FLOAT x, FLOAT y, FLOAT r, FLOAT smoothness, CColor dColor);
	VOID DrawCircle(FLOAT x, FLOAT y, FLOAT r, FLOAT smoothness, CColor dColor);

	VOID GetStringSize(INT& Width, INT& Height, PCHAR szString, ...);

	VOID DrawRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor);
	VOID DrawOutlinedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor);
	VOID DrawGradientRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor1, CColor dColor2);

	VOID DrawBox(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fSize, CColor dColor);
	VOID DrawDot(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor);
	VOID DrawCross(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor);

	VOID DrawCrosshairRedWhite(FLOAT X, FLOAT Y);
	VOID DrawCrosshairCSGO(FLOAT X, FLOAT Y);
	VOID DrawCrosshairOlofMeister(FLOAT X, FLOAT Y);

	VOID DrawBar(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2, CColor dColor3);
	VOID DrawBase(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2);
	VOID DrawTab(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2);
	VOID DrawTabOpen(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2);
	VOID DrawButton(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2, CColor dColor3);

	VOID DrawUpperLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawUpperRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawLowerLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawLowerRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);

	VOID DrawFilledUpperLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawFilledUpperRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawFilledLowerLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);
	VOID DrawFilledLowerRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor);

	VOID DrawFilledRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor);
	VOID DrawRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor);
	VOID DrawHalfRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor);

	VOID DrawFilledHalfRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor);
	VOID DrawFilledHalfRoundedRectWithOutline(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor FillColor,
		CColor OutlineColor);
	VOID DrawFilledRoundedRectWithOutline(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor FillColor,
		CColor OutlineColor);

	VOID DrawLine(FLOAT startx, FLOAT starty, FLOAT endx, FLOAT endy, FLOAT width, CColor dCcolor);
	VOID DrawHealthBar(INT x, INT y, INT w, INT h, INT Health);

	VOID DrawCursor(FLOAT X, FLOAT Y);

	LPDIRECT3DDEVICE9 GetDevice();
private:
	BOOL bIsCreated, bNeedsFlush;

	DWORD dwOldFVF;

	LPDIRECT3DDEVICE9 pDevice;
	LPD3DXSPRITE pSprite;
	LPD3DXSPRITE pCursor;
	LPD3DXFONT pFont;
	LPD3DXLINE line;

	CColor Colors[COLOR_MAX];
};