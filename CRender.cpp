#include "CRender.h"

CRender::CRender()
{
	bIsCreated = FALSE;

	Colors[BLACK] = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f);
	Colors[WHITE] = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);
	Colors[RED] = D3DCOLOR_COLORVALUE(1.0f, 0.0f, 0.0f, 1.0f);
	Colors[GREEN] = D3DCOLOR_COLORVALUE(0.0f, 1.0f, 0.0f, 1.0f);
	Colors[DARKBLUE] = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 1.0f, 1.0f);
	Colors[YELLOW] = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 0.0f, 1.0f);
	Colors[SKYBLUE] = D3DCOLOR_COLORVALUE(0.0f, 0.6f, 1.0f, 1.0f);
	Colors[PINK] = D3DCOLOR_COLORVALUE(1.0f, 0.0f, 0.7f, 1.0f);
	Colors[BROWN] = D3DCOLOR_COLORVALUE(0.3f, 0.1f, 0.0f, 1.0f);
	Colors[ORANGE] = D3DCOLOR_COLORVALUE(1.0f, 0.6f, 0.0f, 1.0f);
	Colors[GRAY] = D3DCOLOR_COLORVALUE(0.3f, 0.3f, 0.3f, 1.0f);
	Colors[MENUTOPBORDERSTART] = D3DCOLOR_COLORVALUE(0.5f, 0.0f, 0.0f, 1.0f);
	Colors[MENUTOPBORDEREND] = D3DCOLOR_COLORVALUE(0.3f, 0.0f, 0.0f, 1.0f);
	Colors[MENUBUTTONSTART] = D3DCOLOR_COLORVALUE(0.5f, 0.0f, 0.0f, 1.0f);
	Colors[MENUBUTTONEND] = D3DCOLOR_COLORVALUE(0.3f, 0.0f, 0.0f, 1.0f);
	Colors[MENUBORDER] = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f);
	Colors[MENUDEFAULT] = D3DCOLOR_COLORVALUE(0.15f, 0.15f, 0.15f, 1.0f);
	Colors[MENUBACKGROUND] = D3DCOLOR_RGBA(20, 20, 20, 255);
	Colors[MENUTEXT] = D3DCOLOR_RGBA(217, 235, 255, 255);
	Colors[MENUSLIDER] = D3DCOLOR_RGBA(54, 66, 88, 255);
	Colors[MENUCOMBOBOXNOTSELECTED] = D3DCOLOR_RGBA(56, 72, 91, 255);
	Colors[MENUCOMBOBOXSELECTED] = D3DCOLOR_RGBA(203, 210, 226, 255);
	Colors[MENUBLOP] = D3DCOLOR_RGBA(96, 96, 96, 255);
	Colors[GOLDENROD] = D3DCOLOR_RGBA(218, 165, 32, 255);
	Colors[MENUBLOPSELECTED] = D3DCOLOR_RGBA(144, 155, 173, 255);
	Colors[MENUTITLEBG] = D3DCOLOR_RGBA(71, 83, 102, 255);
	Colors[BRIGHTGREEN] = D3DCOLOR_RGBA(16, 183, 18, 255);
	Colors[DARKGOLDENROD] = D3DCOLOR_RGBA(184, 134, 11, 255);
	Colors[GOLD] = D3DCOLOR_RGBA(255, 215, 0, 255);
	Colors[AZURE] = D3DCOLOR_RGBA(240, 255, 255, 255);
	Colors[TRANSPARENT_BLACK] = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 0.3f);
	Colors[TRANSPARENT_GRAY] = D3DCOLOR_COLORVALUE(0.3f, 0.3f, 0.3f, 0.3f);
	Colors[LAVENDER] = D3DCOLOR_RGBA(230, 230, 250, 255);
	Colors[TEAL] = 0xFF696969;
	Colors[ScoreBoardHeader] = D3DCOLOR_RGBA(119, 136, 153, 255);
	Colors[ScoreBoardRowEven] = D3DCOLOR_RGBA(32, 178, 170, 255);
	Colors[ScoreBoardRowOdd] = D3DCOLOR_RGBA(173, 216, 230, 255);
	Colors[LightGreen] = D3DCOLOR_RGBA(25, 194, 165, 255);
	Colors[LightBlue] = D3DCOLOR_RGBA(64, 159, 223, 255);
	Colors[Turkis] = D3DCOLOR_RGBA(70, 91, 112, 255);
	Colors[LightRed] = D3DCOLOR_RGBA(233, 93, 104, 255);
	Colors[DarkBrown] = D3DCOLOR_RGBA(71, 62, 63, 255);
}

VOID CRender::Create(LPDIRECT3DDEVICE9 pGameDevice)
{
	this->pDevice = pGameDevice;


	D3DXCreateSprite(pDevice, &pSprite);
	D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial", &pFont);
	D3DXCreateLine(pDevice, &line);

	bIsCreated = TRUE;
}

VOID CRender::Begin()
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pDevice->GetFVF(&dwOldFVF);
	pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
}

VOID CRender::End()
{
	pDevice->SetFVF(dwOldFVF);
	pSprite->End();
}

VOID CRender::OnLostDevice()
{
	if (pSprite != NULL)
		pSprite->OnLostDevice();

	if (pFont != NULL)
		pFont->OnLostDevice();

	if (line != NULL)
		line->OnLostDevice();
}

VOID CRender::OnResetDevice()
{
	if (pSprite != NULL)
		pSprite->OnResetDevice();

	if (pFont != NULL)
		pFont->OnResetDevice();

	if (line != NULL)
		line->OnResetDevice();
}

VOID CRender::DrawCursor(FLOAT X, FLOAT Y)
{
	DrawRect(X, Y, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 1, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 2, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 3, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 4, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 5, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 6, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 7, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 8, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 9, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 10, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 11, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 12, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 13, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X, Y + 14, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 1, Y, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 1, Y + 1, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 2, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 3, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 4, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 5, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 9, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 10, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 11, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 12, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 1, Y + 13, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 2, Y + 1, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 2, Y + 2, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 3, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 4, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 5, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 9, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 10, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 2, Y + 11, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 3, Y + 2, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 3, Y + 3, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 4, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 5, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 9, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 3, Y + 10, 1, 1, GetColor(Colors::WHITE));

	DrawRect(X + 4, Y + 3, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 4, Y + 4, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 5, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 9, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 10, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 4, Y + 11, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 4, Y + 12, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 5, Y + 4, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 5, Y + 5, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 9, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 10, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 11, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 12, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 5, Y + 13, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 5, Y + 14, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 6, Y + 5, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 6, Y + 6, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 9, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 6, Y + 10, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 6, Y + 11, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 12, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 13, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 14, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 6, Y + 15, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 6, Y + 16, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 7, Y + 6, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 7, Y + 7, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 9, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 7, Y + 11, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 7, Y + 12, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 7, Y + 13, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 14, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 15, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 16, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 7, Y + 17, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 8, Y + 7, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 8, Y + 8, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 8, Y + 9, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 8, Y + 13, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 8, Y + 14, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 8, Y + 15, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 8, Y + 16, 1, 1, GetColor(Colors::WHITE));
	DrawRect(X + 8, Y + 17, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 9, Y + 8, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 9, Y + 9, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 9, Y + 15, 1, 1, GetColor(Colors::BLACK));
	DrawRect(X + 9, Y + 16, 1, 1, GetColor(Colors::BLACK));

	DrawRect(X + 10, Y + 9, 1, 1, GetColor(Colors::BLACK));
}

INT CRender::DrawFontText(INT X, INT Y, CColor dColor, PCHAR szString, ...)
{
	bNeedsFlush = TRUE;

	CHAR szBuffer[101] = "";

	va_list ArgumentList;
	va_start(ArgumentList, szString);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer)-strlen(szBuffer), szString, ArgumentList);
	va_end(ArgumentList);

	RECT Rect = { X, Y, X + 500, Y + 50 };

	return pFont->DrawText(pSprite, szBuffer, -1, &Rect, DT_NOCLIP, dColor);
}

INT CRender::DrawFontTextW(INT X, INT Y, CColor dColor, PWCHAR szString, ...)
{
	bNeedsFlush = TRUE;

	WCHAR szBuffer[200] = L"";

	va_list ArgumentList;
	va_start(ArgumentList, szString);
	vswprintf(szBuffer, szString, ArgumentList);
	va_end(ArgumentList);

	RECT Rect = { X, Y, X + 500, Y + 50 };

	return pFont->DrawTextW(pSprite, szBuffer, -1, &Rect, DT_NOCLIP, dColor);
}

VOID CRender::DrawOutlinedFontTextW(INT X, INT Y, CColor dColor, PWCHAR szString, ...)
{
	bNeedsFlush = TRUE;

	WCHAR szBuffer[200] = L"";

	va_list ArgumentList;
	va_start(ArgumentList, szString);
	vswprintf(szBuffer, szString, ArgumentList);
	va_end(ArgumentList);

	RECT Rect1 = { X, Y, X + 500, Y + 50 };
	RECT Rect2 = { X + 1, Y, X + 500, Y + 50 };
	RECT Rect3 = { X, Y + 1, X + 500, Y + 50 };

	pFont->DrawTextW(pSprite, szBuffer, -1, &Rect2, DT_NOCLIP, GetColor(Colors::BLACK));
	pFont->DrawTextW(pSprite, szBuffer, -1, &Rect3, DT_NOCLIP, GetColor(Colors::BLACK));
	pFont->DrawTextW(pSprite, szBuffer, -1, &Rect1, DT_NOCLIP, dColor);
}

VOID CRender::GetStringSize(INT& Width, INT& Height, PCHAR szString, ...)
{
	CHAR szBuffer[101] = "";

	va_list ArgumentList;
	va_start(ArgumentList, szString);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer)-strlen(szBuffer), szString, ArgumentList);
	va_end(ArgumentList);

	RECT oRect = { 0, 0, 500, 50 };
	pFont->DrawText(NULL, szBuffer, -1, &oRect, DT_CALCRECT, NULL);

	Height = oRect.bottom;
	Width = oRect.right;
}

VOID CRender::DrawHealthBar(INT x, INT y, INT w, INT h, INT Health)
{
	DrawRect(x + 1, y + 1, w - 1, h - 1, GetColor(Colors::BLACK)); // Background

	//Calc width of HP bar relative to HP and bar width
	if (Health > 100)
		Health = 100;

	int calc = (int)(((float)(w - 1) / 100.0f) * (float)Health);

	//Fading color
	int G = (int)((float)(255 * Health) / 100.0); //Map interval linearly from [0,100] to [0,255]
	int R = 255 - G;

	DrawRect(x + 1, y + 1, calc, h - 1, D3DCOLOR_RGBA(R, G, 0, 255)); // health bar
}

VOID CRender::DrawOutlinedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	CVertexList VertexList[5] =
	{
		{ X, Y + Height, 0.0f, dColor },
		{ X, Y, 0.0f, dColor },
		{ X + Width, Y, 0.0f, dColor },
		{ X + Width, Y + Height, 0.0f, dColor },
		{ X, Y + Height, 0.0f, dColor }
	};


	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, VertexList, sizeof(CVertexList));
}

VOID CRender::DrawOutlinedFontText(INT X, INT Y, CColor dColor, PCHAR szString, ...)
{
	bNeedsFlush = TRUE;

	CHAR szBuffer[101] = "";

	va_list ArgumentList;
	va_start(ArgumentList, szString);
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer)-strlen(szBuffer), szString, ArgumentList);
	va_end(ArgumentList);

	RECT Rect1 = { X, Y, X + 500, Y + 50 };
	RECT Rect2 = { X + 1, Y, X + 500, Y + 50 };
	RECT Rect3 = { X, Y + 1, X + 500, Y + 50 };

	pFont->DrawText(pSprite, szBuffer, -1, &Rect2, DT_NOCLIP, GetColor(Colors::BLACK));
	pFont->DrawText(pSprite, szBuffer, -1, &Rect3, DT_NOCLIP, GetColor(Colors::BLACK));
	pFont->DrawText(pSprite, szBuffer, -1, &Rect1, DT_NOCLIP, dColor);
}

VOID CRender::DrawFilledCircle(FLOAT x, FLOAT y, FLOAT r, FLOAT smoothness, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	vertex.X = x;
	vertex.Y = y;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	for (float angle = 0.f; angle < 2 * PI; angle += smoothness)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(2 * PI) * r;
	vertex.Y = y + sinf(2 * PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, VertexList.size() - 2, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawFilledUpperLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	vertex.X = x;
	vertex.Y = y;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	for (float angle = PI; angle < (3 * PI) / 2.f; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf((3 * PI) / 2.f) * r;
	vertex.Y = y + sinf((3 * PI) / 2.f) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, VertexList.size() - 2, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawFilledUpperRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	vertex.X = x;
	vertex.Y = y;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	for (float angle = (3 * PI) / 2.f; angle < 2 * PI; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(2 * PI) * r;
	vertex.Y = y + sinf(2 * PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, VertexList.size() - 2, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawFilledLowerLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	vertex.X = x;
	vertex.Y = y;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	for (float angle = PI / 2.f; angle < PI; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(PI) * r;
	vertex.Y = y + sinf(PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, VertexList.size() - 2, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawFilledLowerRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	vertex.X = x;
	vertex.Y = y;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	for (float angle = 0.f; angle < PI / 2.f; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(PI / 2.f) * r;
	vertex.Y = y + sinf(PI / 2.f) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, VertexList.size() - 2, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawLowerLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	for (float angle = PI / 2.f; angle < PI; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(PI) * r;
	vertex.Y = y + sinf(PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, VertexList.size() - 1, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawLowerRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	for (float angle = 0.f; angle < PI / 2.f; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(PI / 2.f) * r;
	vertex.Y = y + sinf(PI / 2.f) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, VertexList.size() - 1, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawUpperLeftCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	for (float angle = PI; angle < (3 * PI) / 2.f; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf((3 * PI) / 2.f) * r;
	vertex.Y = y + sinf((3 * PI) / 2.f) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, VertexList.size() - 1, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawUpperRightCorner(FLOAT x, FLOAT y, FLOAT r, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	for (float angle = (3 * PI) / 2.f; angle < 2 * PI; angle += 0.4f)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(2 * PI) * r;
	vertex.Y = y + sinf(2 * PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, VertexList.size() - 1, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawCircle(FLOAT x, FLOAT y, FLOAT r, FLOAT smoothness, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	std::vector<CVertexList> VertexList;
	CVertexList vertex;

	for (float angle = 0.f; angle < 2 * PI; angle += smoothness)
	{
		vertex.X = x + cosf(angle) * r;
		vertex.Y = y + sinf(angle) * r;
		vertex.Z = 0.f;
		vertex.dColor = dColor;

		VertexList.push_back(vertex);
	}

	vertex.X = x + cosf(2 * PI) * r;
	vertex.Y = y + sinf(2 * PI) * r;
	vertex.Z = 0.f;
	vertex.dColor = dColor;

	VertexList.push_back(vertex);

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, VertexList.size() - 1, VertexList.data(), sizeof(CVertexList));
}

VOID CRender::DrawRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	CVertexList VertexList[4] =
	{
		{ X, Y + Height, 0.0f, dColor },
		{ X, Y, 0.0f, dColor },
		{ X + Width, Y + Height, 0.0f, dColor },
		{ X + Width, Y, 0.0f, dColor },
	};

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexList, sizeof(CVertexList));
}

VOID CRender::DrawFilledRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	DrawRect(X + fRound, Y + fRound, Width - fRound, Height - fRound, dColor);
	DrawRect(X + 2 * fRound, Y, Width - 3 * fRound, fRound, dColor);
	DrawRect(X, Y + 2 * fRound, fRound, Height - 3 * fRound, dColor);
	DrawRect(X + 2 * fRound, Y + Height, Width - 3 * fRound, fRound, dColor);
	DrawRect(X + Width, Y + 2 * fRound, fRound, Height - 3 * fRound, dColor);

	DrawFilledUpperLeftCorner(X + 2 * fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawFilledUpperRightCorner(X + Width - fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawFilledLowerLeftCorner(X + 2 * fRound, Y + Height - fRound, 2 * fRound, dColor);
	DrawFilledLowerRightCorner(X + Width - fRound, Y + Height - fRound, 2 * fRound, dColor);
}

VOID CRender::DrawFilledHalfRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	DrawRect(X + 2 * fRound, Y, Width - 3 * fRound, 2 * fRound, dColor);

	//Background
	DrawRect(X, Y + 2 * fRound, Width + fRound, Height - fRound, dColor);

	DrawFilledUpperLeftCorner(X + 2 * fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawFilledUpperRightCorner(X + Width - fRound, Y + 2 * fRound, 2 * fRound, dColor);
}

VOID CRender::DrawFilledHalfRoundedRectWithOutline(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor FillColor,
	CColor OutlineColor)
{
	DrawFilledHalfRoundedRect(X, Y, Width, Height, fRound, FillColor);
	DrawHalfRoundedRect(X, Y, Width, Height, fRound, OutlineColor);
}

VOID CRender::DrawHalfRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}
	//TOP
	DrawLine(X + 2 * fRound, Y, X + Width - fRound, Y, 1.0f, dColor);
	//BOTTOM
	DrawLine(X, Y + Height + fRound, X + Width + fRound, Y + Height + fRound, 1.0f, dColor);
	//LEFT
	DrawLine(X, Y + 2 * fRound, X, Y + Height + fRound, 1.0f, dColor);
	//RIGHT
	DrawLine(X + fRound + Width - 0.5, Y + 2 * fRound, X + Width + fRound - 0.5, Y + Height + fRound, 1.0f, dColor);

	DrawUpperLeftCorner(X + 2 * fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawUpperRightCorner(X + Width - fRound, Y + 2 * fRound, 2 * fRound, dColor);
}

VOID CRender::DrawFilledRoundedRectWithOutline(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor FillColor,
	CColor OutlineColor)
{
	DrawFilledRoundedRect(X, Y, Width, Height, fRound, FillColor);
	DrawRoundedRect(X, Y, Width, Height, fRound, OutlineColor);
}

VOID CRender::DrawRoundedRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fRound, CColor dColor)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}
	//TOP
	DrawLine(X + 2 * fRound, Y, X + Width - fRound, Y, 1.0f, dColor);
	//BOTTOM
	DrawLine(X + 2 * fRound, Y + Height + fRound - 0.5, X + Width - fRound, Y + Height + fRound - 0.5, 1.0f, dColor);
	//LEFT
	DrawLine(X, Y + 2 * fRound, X, Y + Height - fRound, 1.0f, dColor);
	//RIGHT
	DrawLine(X + fRound + Width - 0.5, Y + 2 * fRound, X + Width + fRound - 0.5, Y + Height - fRound, 1.0f, dColor);

	DrawUpperLeftCorner(X + 2 * fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawUpperRightCorner(X + Width - fRound, Y + 2 * fRound, 2 * fRound, dColor);
	DrawLowerLeftCorner(X + 2 * fRound, Y + Height - fRound, 2 * fRound, dColor);
	DrawLowerRightCorner(X + Width - fRound, Y + Height - fRound, 2 * fRound, dColor);
}

VOID CRender::DrawLine(FLOAT startx, FLOAT starty, FLOAT endx, FLOAT endy, FLOAT width, CColor dCcolor)
{
	bNeedsFlush = TRUE;

	D3DXVECTOR2 lines[] = { D3DXVECTOR2(startx, starty), D3DXVECTOR2(endx, endy) };

	line->SetWidth(width);
	line->Begin();
	line->Draw(lines, 2, dCcolor);
	line->End();
}

VOID CRender::DrawGradientRect(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor1, CColor dColor2)
{
	if (bNeedsFlush)
	{
		pSprite->Flush();
		bNeedsFlush = FALSE;
	}

	CVertexList VertexList[4] =
	{
		{ X, Y + Height, 0.0f, dColor2 },
		{ X, Y, 0.0f, dColor1 },
		{ X + Width, Y + Height, 0.0f, dColor2 },
		{ X + Width, Y, 0.0f, dColor1 },
	};

	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexList, sizeof(CVertexList));
}

VOID CRender::DrawBox(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT fSize, CColor dColor)
{
	DrawRect(X, Y, Width, fSize, dColor);
	DrawRect(X, Y, 1.0f, Height, dColor);
	DrawRect(X, Y + Height, Width + fSize, fSize, dColor);
	DrawRect(X + Width, Y, fSize, Height + fSize, dColor);
}

VOID CRender::DrawDot(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor)
{
	DrawRect(X - 1.0f, Y - 1.0f, Width + 2.0f, Height + 2.0f, D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f));
	DrawRect(X, Y, Width, Height, dColor);
}

VOID CRender::DrawCross(FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, CColor dColor)
{
	DrawRect(X - Width, Y - 0.5f, (Width * 2.0f), 1.0f, dColor);
	DrawRect(X - 0.5f, Y - Height, 1.0f, (Height * 2.0f), dColor);
}

VOID CRender::DrawBar(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2, CColor dColor3)
{
	DrawGradientRect(BaseX, BaseY, BaseW, BaseH, dColor2, dColor3);

	DrawRect(BaseX, BaseY, BaseW, 1.0f, dColor1);
	DrawRect(BaseX, BaseY, 1.0f, BaseH, dColor1);
	DrawRect(BaseX, BaseY + BaseH, BaseW, 1.0f, dColor1);
	DrawRect(BaseX + BaseW, BaseY, 1.0f, BaseH, dColor1);
}

VOID CRender::DrawBase(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2)
{
	DrawRect(BaseX, BaseY, BaseW, BaseH, dColor2);

	DrawRect(BaseX, BaseY, BaseW, 1.0f, dColor1);
	DrawRect(BaseX, BaseY, 1.0f, BaseH, dColor1);
	DrawRect(BaseX, BaseY + BaseH, BaseW, 1.0f, dColor1);
	DrawRect(BaseX + BaseW, BaseY, 1.0f, BaseH, dColor1);
}

VOID CRender::DrawTab(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2)
{
	DrawRect(BaseX, BaseY, BaseW, BaseH, dColor2);

	DrawRect(BaseX, BaseY, BaseW, 1.0f, dColor1);
	DrawRect(BaseX, BaseY, 1.0f, BaseH, dColor1);
	DrawRect(BaseX, BaseY + BaseH, BaseW, 1.0f, dColor1);
	DrawRect(BaseX + BaseW, BaseY, 1.0f, BaseH, dColor1);
}

VOID CRender::DrawTabOpen(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2)
{
	DrawRect(BaseX, BaseY, BaseW, BaseH, dColor2);

	DrawRect(BaseX, BaseY, BaseW, 1.0f, dColor1);
	DrawRect(BaseX, BaseY, 1.0f, BaseH, dColor1);
	DrawRect(BaseX, BaseY + BaseH, BaseW, 1.0f, dColor1);
}

VOID CRender::DrawButton(FLOAT BaseX, FLOAT BaseY, FLOAT BaseW, FLOAT BaseH, CColor dColor1, CColor dColor2, CColor dColor3)
{
	DrawGradientRect(BaseX, BaseY, BaseW, BaseH, dColor2, dColor3);

	DrawRect(BaseX, BaseY, BaseW, 1.0f, dColor1);
	DrawRect(BaseX, BaseY, 1.0f, BaseH, dColor1);
	DrawRect(BaseX, BaseY + BaseH, BaseW, 1.0f, dColor1);
	DrawRect(BaseX + BaseW, BaseY, 1.0f, BaseH, dColor1);
}

VOID CRender::DrawCrosshairRedWhite(FLOAT X, FLOAT Y)
{
	//horizontal
	DrawRect(X - 15, Y, 30, 1, GetColor(Colors::WHITE));
	DrawRect(X - 5, Y, 10, 1, GetColor(Colors::RED));

	//vertical
	DrawRect(X, Y - 15, 1, 30, GetColor(Colors::WHITE));
	DrawRect(X, Y - 5, 1, 10, GetColor(Colors::RED));
}

VOID CRender::DrawCrosshairCSGO(FLOAT X, FLOAT Y)
{
	//dot
	DrawRect(X - 1, Y - 1, 3, 3, GetColor(Colors::BLACK));
	DrawRect(X, Y, 1, 1, GetColor(Colors::GREEN));

	//left
	DrawRect(X - 15, Y - 1, 10, 3, GetColor(Colors::BLACK));
	DrawRect(X - 14, Y, 8, 1, GetColor(Colors::GREEN));

	//right
	DrawRect(X + 4, Y - 1, 10, 3, GetColor(Colors::BLACK));
	DrawRect(X + 5, Y, 8, 1, GetColor(Colors::GREEN));

	//top
	DrawRect(X - 1, Y - 14, 3, 10, GetColor(Colors::BLACK));
	DrawRect(X, Y - 13, 1, 8, GetColor(Colors::GREEN));

	//bottom
	DrawRect(X - 1, Y + 4, 3, 10, GetColor(Colors::BLACK));
	DrawRect(X, Y + 5, 1, 8, GetColor(Colors::GREEN));
}

VOID CRender::DrawCrosshairOlofMeister(FLOAT X, FLOAT Y)
{
	//dot
	DrawRect(X - 1, Y - 1, 3, 3, GetColor(Colors::BLACK));
	DrawRect(X, Y, 1, 1, GetColor(Colors::GREEN));

	//left
	DrawRect(X - 10, Y - 1, 8, 3, GetColor(Colors::BLACK));
	DrawRect(X - 9, Y, 6, 1, GetColor(Colors::GREEN));

	//right
	DrawRect(X + 3, Y - 1, 8, 3, GetColor(Colors::BLACK));
	DrawRect(X + 4, Y, 6, 1, GetColor(Colors::GREEN));

	//top
	DrawRect(X - 1, Y - 10, 3, 8, GetColor(Colors::BLACK));
	DrawRect(X, Y - 9, 1, 6, GetColor(Colors::GREEN));

	//bottom
	DrawRect(X - 1, Y + 3, 3, 8, GetColor(Colors::BLACK));
	DrawRect(X, Y + 4, 1, 6, GetColor(Colors::GREEN));
}

LPDIRECT3DDEVICE9 CRender::GetDevice()
{
	return pDevice;
}

VOID CRender::Release()
{
	if (pSprite)
		pSprite->Release();

	if (pFont)
		pFont->Release();

	if (line)
		line->Release();

	bIsCreated = FALSE;
}