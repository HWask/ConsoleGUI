#include "Menu.h"
#include "Console.h"
#include "Utils.h"
#include "detours.h"
#include "Test.h"

#pragma comment(lib, "detours")

typedef HRESULT(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9 pDevice);
EndScene_t oEndScene;
HRESULT __stdcall hk_EndScene(LPDIRECT3DDEVICE9 pDevice);

CRender* g_pRender;
Menu* g_pMenu = 0;
void InitMenu();

Test* g_pTest = new Test();

void Thread()
{
	DWORD D3d9Base = (DWORD)GetModuleHandle("d3d9.dll");
	while (!D3d9Base)
		D3d9Base = (DWORD)GetModuleHandle("d9d9.dll");

	DWORD TempAdd = Utils::FindPattern(D3d9Base, 0x128000, (BYTE*)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");

	DWORD oldProtect = 0;
	DWORD* D3d9VTable = (DWORD*)*(DWORD*)(TempAdd + 2);

	oEndScene = (EndScene_t)DetourFunction((PBYTE)D3d9VTable[42], (PBYTE)hk_EndScene);

	g_pRender = new CRender();
}

bool __stdcall DllMain(HINSTANCE hinst, DWORD dwreason, LPVOID lpreserved)
{
	if (dwreason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
	else if (dwreason == DLL_PROCESS_DETACH)
	{
		DetourRemove((PBYTE)oEndScene, (PBYTE)hk_EndScene);
		g_pRender->Release();
	}

	return true;
}

HRESULT __stdcall hk_EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!g_pRender->IsCreated())
		g_pRender->Create(pDevice);

	if (!g_pMenu)
	{
		g_pMenu = new Menu(g_pRender);
		InitMenu();
	}

	g_pRender->Begin();

	g_pMenu->Render();

	g_pRender->End();

	return oEndScene(pDevice);
}

void InitMenu()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	Console* con = new Console(100, 50, 900, 400, g_pRender);
	g_pMenu->AddTab(con);

	con->RegisterInt("weapon.ak47.rcs", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 1", 0, 50, g_pTest, 0);
	con->RegisterFloat("aimbot.fov", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 2", 0, 360, g_pTest, 2);
	con->RegisterBool("manegro", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 3", g_pTest, 1);
	con->RegisterArray("trigger.hitboxes", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 4", std::vector<int>{1, 2, 3, 4, 5}, g_pTest, 3);

	con->RegisterInt("weapon.asdfsdk47.rcs", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 1", 0, 50, g_pTest, 0);
	con->RegisterFloat("aimbot.fov", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 2", 0, 360, g_pTest, 2);
	con->RegisterBool("manegro", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 3", g_pTest, 1);

	con->RegisterInt("weaponsdf.ak47.rcs", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 1", 0, 50, g_pTest, 0);
	con->RegisterFloat("aimbsdfot.fov", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 2", 0, 360, g_pTest, 2);
	con->RegisterBool("manesdfgro", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 3", g_pTest, 1);

	con->RegisterInt("weapofghfghn.ak47.rcs", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 1", 0, 50, g_pTest, 0);
	con->RegisterFloat("aisdfghfmbot.fov", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 2", 0, 360, g_pTest, 2);
	con->RegisterBool("maneghgro", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 3", g_pTest, 1);

	con->RegisterInt("weapfghjnon.ak47.rcs", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 1", 0, 50, g_pTest, 0);
	con->RegisterFloat("aimvbnmmbot.fov", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 2", 0, 360, g_pTest, 2);
	con->RegisterBool("manevbngro", "TooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltipTooltip 3", g_pTest, 1);
}