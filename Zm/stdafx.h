#pragma once
#define WIN32_LEAN_AND_MEAN 
#pragma warning(disable:4996) // I'm safe
#pragma warning(disable:4244) // To stop the "conversion from 'X' to 'Y', possible loss of data" spam
#define _CRT_SECURE_NO_WARNINGS

#define offset(type, address) reinterpret_cast<type *>(address);

#include "targetver.h"
#include <windows.h>
#include <iostream>
#include <mutex>
#include <cstdio>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <chrono>
#include <string>
#pragma comment(lib, "d3d11.lib") // get the d3d11 lib cause windows is dumb
#pragma comment(lib, "d3dcompiler.lib")
#include "Detours\include\detours.h"
#pragma comment(lib, "Detours\\lib.X86\\detours.lib")
#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_dx11.h"
