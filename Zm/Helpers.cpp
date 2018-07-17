#include "stdafx.h"
#include "Helpers.h"

std::mutex mtx;

void Console::Log(const char *str) {
	mtx.lock();
	std::cout << "[+] " << str << std::endl;
	mtx.unlock();
}

void Console::Warn(const char *str) {
	mtx.lock();
	std::cout << "[!] " << str << std::endl;
	mtx.unlock();
}

void Console::Err(const char *str) {
	std::cout << "[?] " << str << std::endl;
	Helpers::Exit(0);
}

void Console::Address(const char *name, int address) {
	mtx.lock();
	std::cout << "[+] " << name << ": 0x" << std::hex << address << std::dec << std::endl;
	mtx.unlock();
}

void Console::Bytes(const char *name, int bytes[]) {
	mtx.lock();
	std::cout << "[+] " << name << ": " << std::endl;
	// for size of bytes
	// print 2 bytes in hex or smt
	std::cout << std::endl;
	mtx.unlock();
}

// Bad code but it works
extern HMODULE g_DLLMOD;

void Helpers::Init() {
	// Console window
	AllocConsole();
	AttachConsole(GetProcessId(GetCurrentProcess()));
	freopen("CON", "w", stdout);

	SetConsoleTitleA("Zm By Syc0x00");
	Console::Log("Console initialized");
	return;
}

void Helpers::Exit(int timer) {
	Sleep(timer);
	Console::Log("Detaching...");
	FreeConsole(); // This way you can close the console without closing BO2
	FreeLibraryAndExitThread(g_DLLMOD, 0);
}

// This needs to be tested
bool Helpers::KillService(LPCWSTR serviceName) {
	SC_HANDLE service, scm;
	SERVICE_STATUS_PROCESS serviceStatus;
	DWORD what;

	scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);
	if (!scm) {
		return 0;
	}

	service = OpenService(scm, serviceName, SERVICE_QUERY_STATUS);
	if (!service) {
		Console::Warn("The service isn't even installed asshat");
		CloseServiceHandle(scm);
		return true;
	}

	bool result = QueryServiceStatusEx(service, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&serviceStatus), sizeof(SERVICE_STATUS_PROCESS), &what);

	bool ret = true;

	if (serviceStatus.dwCurrentState != SERVICE_STOPPED) {
		if (ControlService(service, SERVICE_CONTROL_STOP, NULL) == 0)
			ret = false;
	}

	CloseServiceHandle(service);
	CloseServiceHandle(scm);

	if (ret == false)
		std::cout << "Failed to kill " << serviceName << std::endl;
	else
		std::cout << "Killed " << serviceName << std::endl;

	return ret;
}

#include <Tlhelp32.h>
#include <string>

// https://stackoverflow.com/questions/7956519/how-to-kill-processes-by-name-win32-api
bool Helpers::KillProc(const wchar_t *proc) {
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);

	while (hRes) {
		if (wcscmp(pEntry.szExeFile, proc) == 0) {
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL) {
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
				CloseHandle(hSnapShot);
				std::wcout << "[+] " << "Killed " << proc << std::endl;
				return true;
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}

	CloseHandle(hSnapShot);
	return false;
}

inline int Helpers::Ptr(int address) {
	int *ptr = reinterpret_cast<int *>(address);
	return *ptr; // Return the value of the pointer
}

void Helpers::HookFunction(PVOID *oFunction, PVOID pDetour) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(oFunction, pDetour);
	DetourTransactionCommit();
}
void Helpers::UnhookFunction(PVOID *oFunction, PVOID pDetour) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(oFunction, pDetour);
	DetourTransactionCommit();
}

// Thx SMBB
const char *Helpers::VariableText(const char *format, ...) {
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr); // It should use vsnprintf but meh doesn't matter here

	va_end(argptr);

	return buffer;
}

void Helpers::KeyPress(unsigned char keyCode) {
	Console::Log("Helpers::KeyPress doesn't work yet :(");
	keybd_event(keyCode, 0, 0, 0); //Press down the Key
	keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0); //Release the Key

	return;
}

// Sets a color green->yellow->red based on the
// amount of health the entity has
ImU32 Helpers::ColorGradient(float value) {
    return ImColor(2.0f * value, 2.0f * (1 - value), 0);
}

/*// Needs testing
ImU32 Helpers::ColorGradient(int value) {
	return ImColor(2 * value, 2 * (1 - value), 0);
}*/

ImU32 Helpers::ColorGradient(int value) {
	float fValue = value / 100.f;
    return ImColor(2.0f * fValue, 2.0f * (1 - fValue), 0);
}