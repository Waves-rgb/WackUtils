#pragma once

#include <Windows.h>
#include <string>
#include <filesystem>
#include <vector>
#include <functional>
#include <TlHelp32.h>
#include <WackUtils/common.h>

struct startProcessReturn_t {
	bool success = false;
	int processId = -1;
	HANDLE handle = nullptr;
};
typedef std::function<int(tagPROCESSENTRY32)> processFilter_t;

namespace WackUtils {
	/// getProcesses - Returns a list of all processes running on the system.
	/// @returns A vector of process handles.
	std::vector<HANDLE> getProcesses();

	/// findProcess - Finds a process by name.
	/// @param name The name of the process to find.
	/// @returns A vector of the found process(es) otherwise nullptr.
	std::vector<HANDLE> findProcesses(const std::string& name);

	/// getProcessName - Gets the name of a process.
	/// @param process The process handle.
	/// @returns The name of the process.
	std::string getProcessName(HANDLE handle);

	/// findFirstProcess - Finds the first process by name.
	/// @param predicate The predicate to use to find the process.
	/// @returns The found process otherwise nullptr.
	std::vector<HANDLE> findProcesses(const processFilter_t& filter);

	/// findFirstProcess - Finds the first process by name.
	/// @param name The name of the process to find.
	/// @returns The first found process otherwise nullptr.
	HANDLE findFirstProcess(const std::string& name);

	/// getProcessID - Gets the process ID of a process.
	/// @param handle The handle of the process.
	/// @returns The process ID.
	DWORD getProcessID(HANDLE handle);

	/// getProcessID - Gets the process ID of a process.
	/// @param name The name of the process.
	/// @returns The process ID.
	DWORD getProcessID(const std::string& name);

	/// isProcessRunning - Checks if a process is running.
	/// @param name The name of the process.
	/// @returns True if the process is running otherwise false.
	bool isProcessRunning(const std::string& name);

	/// isProcessRunning - Checks if a process is running.
	/// @param pid The process id of the process.
	/// @returns True if the process is running otherwise false.
	bool isProcessRunning(int pid);

	/// isProcessRunning - Checks if a process is running.
	/// @param handle The handle of the process.
	/// @returns True if the process is running otherwise false.
	bool isProcessRunning(HANDLE handle);

	/// killProcess - Kills a process.
	/// @param name The name of the process.
	/// @returns True if the process was killed otherwise false.
	bool killProcess(const std::string& name);

	/// killProcess - Kills a process.
	/// @param pid The process id of the process.
	/// @returns True if the process was killed otherwise false.
	bool killProcess(int pid);

	/// killProcess - Kills a process.
	/// @param handle The handle of the process.
	/// @returns True if the process was killed otherwise false.
	bool killProcess(HANDLE handle);

	/// killProcesses - Kills all processes.
	/// @returns True if all processes were killed otherwise false.
	/// @param handles The handles of the processes.
	bool killProcesses(const std::vector<HANDLE>& handles);

	/// startProcess - Starts a process.
	/// @param target The path to the target process.
	/// @param args The arguments to pass to the process (defaults to "").
	/// @returns A startProcessReturn_t struct containing the success status, process id, and process handle.
	startProcessReturn_t startProcess(std::filesystem::path target, const std::string &args = "", bool wait = false);
}