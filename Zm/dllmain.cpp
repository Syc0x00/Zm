// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Zm.h"
#include "Hooks.h"
#include "Helpers.h"
#include "Math.h"
#include "Offsets.h"
#include "Game.h"
#include "Menu.h"
#include "Input.h"

// First ever cheat other than a 2D one in which I wrote some AOB scan
// and memory manipulation Functions in C# so it will have issues.
// I also stole some functions (Ex: W2S and some helpers) from fourms
// and I can't remeber where I got all of them. I'll try to credit.

HMODULE g_DLLMOD; // Global DLL module addr so we can detach anywhere

void Main() {
	Helpers::Init();

	HANDLE D3Dhandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hooks::Init, NULL, NULL, NULL);
	HANDLE TPHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Input::Thread, NULL, NULL, NULL);

	WaitForSingleObject(D3Dhandle, INFINITE); // Wait for the F10 which will undo the Hooks
	TerminateThread(TPHandle, 0); // Then kill the input thread

	CloseHandle(TPHandle); // Close the handles ...
	CloseHandle(D3Dhandle);

	Console::Log("Successful unhook and TerminateThread()");

	Helpers::Exit(0); // ... and detach
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	g_DLLMOD = hModule;
	DWORD ThreadID;

    switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Main, NULL, NULL, &ThreadID);
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
