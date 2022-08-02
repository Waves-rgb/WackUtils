#include <WackUtils/process.h>
#include <TlHelp32.h>
#include <iostream>

std::vector<HANDLE> WackUtils::findProcesses(const processFilter_t& predicate) {
	std::vector<HANDLE> processes;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		return processes;
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(snapshot, &processEntry)) {
		CloseHandle(snapshot);
		return processes;
	}
	do {
		const auto filterReturn = predicate(processEntry);

		if (filterReturn == FILTER_ACCEPT || filterReturn == FILTER_ACCEPT_STOP)
			processes.push_back(OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID));

		if (filterReturn == FILTER_STOP || filterReturn == FILTER_ACCEPT_STOP)
			break;

	} while (Process32Next(snapshot, &processEntry));
	return processes;
}

std::vector<HANDLE> WackUtils::getProcesses() {
	return findProcesses([](tagPROCESSENTRY32 process) {return FILTER_ACCEPT;});
}

std::vector<HANDLE> WackUtils::findProcesses(const std::string &name) {
	return std::vector<HANDLE>{findProcesses([&name](tagPROCESSENTRY32 process) {
		return process.szExeFile == name ? FILTER_ACCEPT : FILTER_REJECT;
	})};
}

HANDLE WackUtils::findFirstProcess(const std::string &name) {
	const auto processes = findProcesses([&name](tagPROCESSENTRY32 process) {
		return name == process.szExeFile ? FILTER_ACCEPT_STOP : FILTER_REJECT;
	});
	return processes.empty() ? nullptr : processes[0];
}

std::string WackUtils::getProcessName(HANDLE handle) {
	std::string name;
	const auto pid = GetProcessId(handle);
	findProcesses([&pid, &name](tagPROCESSENTRY32 process) {
		if (process.th32ProcessID == pid) {
			name = process.szExeFile;
			return FILTER_STOP;
		}
		return FILTER_REJECT;
	});
	return name;
}

DWORD WackUtils::getProcessID(HANDLE handle) {
	if (handle == nullptr) return 0;
	return GetProcessId(handle);
}

DWORD WackUtils::getProcessID(const std::string& name) {
	return GetProcessId(findFirstProcess(name));
}

bool WackUtils::isProcessRunning(const std::string& name) {
	return isProcessRunning(getProcessID(name));
}

bool WackUtils::isProcessRunning(int pid) {
	if (!pid) return false;
	const auto returnValue = findProcesses([pid](tagPROCESSENTRY32 process) {
		return process.th32ProcessID == pid ? FILTER_ACCEPT : FILTER_REJECT;
	});
	return returnValue.size() > 0;
}

bool WackUtils::isProcessRunning(HANDLE handle) {
	if (!handle) return false;
	return isProcessRunning(getProcessID(handle));
}

bool WackUtils::killProcess(const std::string& name) {
	return killProcess(findFirstProcess(name));
}

bool WackUtils::killProcess(int pid) {
	if (!pid) return false;
	const auto processes = findProcesses([pid](tagPROCESSENTRY32 process) {
		return process.th32ProcessID == pid ? FILTER_ACCEPT_STOP : FILTER_REJECT;
	});
	if (processes.empty()) return false;
	return TerminateProcess(processes[0], 0);
}

bool WackUtils::killProcess(HANDLE handle) {
	if (!handle) return false;
	return TerminateProcess(handle, 0);
}

bool WackUtils::killProcesses(const std::vector<HANDLE> &handles) {
	return std::all_of(handles.begin(), handles.end(), [](HANDLE handle) {
		return killProcess(handle);
	});
}

startProcessReturn_t WackUtils::startProcess(std::filesystem::path target, const std::string& args, bool wait) {
	if (target.empty())
		return {};

	if (!target.is_absolute())
		target = std::filesystem::current_path() / target.filename();

	if (!exists(target))
		return {};

	startProcessReturn_t ret;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	ret.success = CreateProcess(target.string().c_str(), (char*)args.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);

	if (ret.success) {
		ret.handle = pi.hProcess;
		ret.processId = (int)pi.dwProcessId;
	}

	if (wait) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	return ret;
}
