#pragma once

#include <Windows.h>
#include <filesystem>

struct dummy {
	HANDLE process;
	HWND window;
	PROCESS_INFORMATION pi;
};
namespace testingShared {
	dummy createDummy();
	void destroyDummy(dummy& dummy);
}
