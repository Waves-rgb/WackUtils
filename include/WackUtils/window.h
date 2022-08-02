#pragma once

#include <Windows.h>
#include <string>
#include <WackUtils/common.h>
#include <vector>
#include <functional>

namespace WackUtils {
	struct hookWndProcReturn_t {
		bool success = false;
		WNDPROC oldWndProc = nullptr;
	};

	struct windowFrameInfo_t {
		int x = -1;
		int y = -1;
		int width = -1;
		int height = -1;
	};

	typedef std::function<void(HWND)> windowFilter_t;

	/// Hooks the window procedure of a window.
	/// @param wnd The window to hook.
	/// @param newWndProc The new WndProc function.
	/// @return Returns a struct containing the success and old WndProc function.
	hookWndProcReturn_t hookWndProc(HWND wnd, WNDPROC &newWndProc);

	/// Gets and returns a window's title.
	/// @param wnd The window to get the title of.
	/// @return The title of the window.
	std::string getWindowName(HWND wnd);

	/// Sets the window frame of a window.
	/// @param wnd The window to set the frame of.
	/// @param frame The frame to set.
	/// @returns True if the frame was set otherwise false.
	bool setWindowFrame(HWND wnd, windowFrameInfo_t pos);

	/// Gets the window frame of a window.
	/// @param wnd The window to get the frame of.
	/// @returns The window frame otherwise nullptr.
	windowFrameInfo_t getWindowFrame(HWND wnd);

	/// Sets the visibility of a window.
	/// @param wnd The window to set the visibility of.
	/// @param visible True to make the window visible otherwise false.
	void setWindowVisible(HWND wnd, bool visible);

	/// Checks if a window is visible.
	/// @param wnd The window to check.
	/// @returns True if the window is visible otherwise false.
	bool isWindowVisible(HWND wnd);

	/// Gets the class name of a window.
	/// @param wnd The window to get the class name of.
	/// @returns The class name of the window.
	std::string getWindowClass(HWND wnd);

	/// Returns a list of all windows.
	/// @returns A vector of window handles.
	std::vector<HWND> getWindows();

	/// Returns a list of all windows that match a predicate.
	/// @param predicate The predicate to match.
	/// @returns A vector of window handles.
	std::vector<HWND> findWindows(const windowFilter_t& predicate);
}