#include "gtest/gtest.h"
#include "WackUtils/process.h"
#include "../util/shared.h"

TEST(Process, findProcesses) {
	// With predicate
	ASSERT_TRUE(WackUtils::findProcesses([](PROCESSENTRY32 process) { return FILTER_STOP; }).empty());
	ASSERT_FALSE(WackUtils::findProcesses([](PROCESSENTRY32 process) { return FILTER_ACCEPT; }).empty());
	ASSERT_EQ(WackUtils::findProcesses([](PROCESSENTRY32 process) { return FILTER_ACCEPT_STOP; }).size(), 1);

	// By name
	EXPECT_FALSE(WackUtils::findProcesses("tests.exe").empty());
	EXPECT_TRUE(WackUtils::findProcesses("not_found.exe").empty());

	// Find first
	EXPECT_TRUE(WackUtils::findFirstProcess("tests.exe"));
	EXPECT_FALSE(WackUtils::findFirstProcess("not_found.exe"));
}

TEST(Process, getProcesses) {
	EXPECT_FALSE(WackUtils::getProcesses().empty());
}

TEST(Process, getProcessName) {
	EXPECT_STREQ(WackUtils::getProcessName(GetCurrentProcess()).c_str(), "tests.exe");
}

TEST(Process, getProcessID) {
	EXPECT_EQ(WackUtils::getProcessID(GetCurrentProcess()), GetCurrentProcessId());
	EXPECT_EQ(WackUtils::getProcessID("not_found.exe"), 0);
}

TEST(Process, isProcessRunning) {
	EXPECT_TRUE(WackUtils::isProcessRunning("tests.exe"));
	EXPECT_FALSE(WackUtils::isProcessRunning("not_found.exe"));
	EXPECT_TRUE(WackUtils::isProcessRunning(GetCurrentProcess()));
}

TEST(Process, startProcess) {
	auto dummy = WackUtils::startProcess("target.exe");
	EXPECT_TRUE(dummy.success);
	TerminateProcess(dummy.handle, 0);

	dummy = WackUtils::startProcess("target.exe", "");
	EXPECT_TRUE(dummy.success);
	TerminateProcess(dummy.handle, 0);

	EXPECT_FALSE(WackUtils::startProcess("not_found.exe").success);
	EXPECT_FALSE(WackUtils::startProcess("not_found.exe", "args").success);
}

TEST(Process, killProcess) {
	auto dummy = testingShared::createDummy();
	EXPECT_TRUE(WackUtils::killProcess("target.exe"));
	EXPECT_FALSE(WackUtils::isProcessRunning(dummy.process));
	testingShared::destroyDummy(dummy);

	dummy = testingShared::createDummy();
	EXPECT_TRUE(WackUtils::killProcess(dummy.process));
	EXPECT_FALSE(WackUtils::isProcessRunning(dummy.process));
	testingShared::destroyDummy(dummy);

	dummy = testingShared::createDummy();
	EXPECT_TRUE(WackUtils::killProcess(dummy.pi.dwProcessId));
	EXPECT_FALSE(WackUtils::isProcessRunning(dummy.pi.dwProcessId));
	testingShared::destroyDummy(dummy);

	EXPECT_FALSE(WackUtils::killProcess("not_found.exe"));
}

TEST(Process, killProcesses) {
	std::vector<dummy> processes;
	for (int i = 0; i < 10; i++) {
		processes.push_back(testingShared::createDummy());
	}

	std::vector<HANDLE> handles;

	for (auto& dummy : processes) {
		handles.push_back(dummy.process);
	}

	EXPECT_TRUE(WackUtils::killProcesses(handles));
	for (auto process : processes) {
		EXPECT_FALSE(WackUtils::isProcessRunning(process.process));
	}

	for (auto& dummy : processes) {
		testingShared::destroyDummy(dummy);
	}
}