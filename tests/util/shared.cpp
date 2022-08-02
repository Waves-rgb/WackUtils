#include "shared.h"
#include "gtest/gtest.h"


dummy testingShared::createDummy() {
	dummy d{};

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA((std::filesystem::current_path() / "target.exe").string().c_str(), nullptr, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
		return {};

	d.pi = pi;
	d.process = &pi.hProcess;
	while (d.process && !d.window)
		d.window = FindWindowA("WackUtilsTestingTarget", "WackUtils Testing Target");
	return d;
}

void testingShared::destroyDummy(dummy &d) {
	TerminateProcess(d.process, 0);

	CloseHandle(d.process);
	CloseHandle(d.pi.hThread);
	CloseHandle(d.pi.hProcess);
}

TEST(TestRequirements, dummies) {
	auto d = testingShared::createDummy();
	ASSERT_TRUE(d.window);
	ASSERT_TRUE(d.process);
	ASSERT_TRUE(d.pi.hProcess);
	ASSERT_TRUE(d.pi.hThread);
	testingShared::destroyDummy(d);
}
