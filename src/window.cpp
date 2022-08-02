#include <WackUtils/window.h>
#include <iostream>

WackUtils::hookWndProcReturn_t WackUtils::hookWndProc(HWND wnd, WNDPROC &newWndProc) {
	if (wnd == nullptr || newWndProc == nullptr) return {};

	const auto old = (WNDPROC)SetWindowLongPtr(wnd, GWLP_WNDPROC, (LONG_PTR)newWndProc);
	if (old == nullptr) return {};

	return {true, old};
}

std::string WackUtils::getWindowName(HWND wnd) {
	if (wnd == nullptr) return "";
	auto title = new char[1024];
	GetWindowText(wnd, title, 1024);

	return title;
}

bool WackUtils::setWindowFrame(HWND wnd, windowFrameInfo_t pos) {
	if (wnd == nullptr) return false;
	const auto frame = getWindowFrame(wnd);

	if (pos.x == -1) pos.x = frame.x;
	if (pos.y == -1) pos.y = frame.y;
	if (pos.width == -1) pos.width = frame.width;
	if (pos.height == -1) pos.height = frame.height;

	return SetWindowPos(wnd, nullptr, pos.x, pos.y, pos.width + pos.x, pos.height + pos.y, SWP_NOZORDER);
}

WackUtils::windowFrameInfo_t WackUtils::getWindowFrame(HWND wnd) {
	if (wnd == nullptr) return {};
	RECT rect;
	GetWindowRect(wnd, &rect);
	return { rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top };
}

void WackUtils::setWindowVisible(HWND wnd, const bool visible) {
	if (wnd == nullptr) return;
	ShowWindow(wnd, visible ? SW_SHOW : SW_HIDE);
}

bool WackUtils::isWindowVisible(HWND wnd) {
	if (wnd == nullptr) return false;
	return IsWindowVisible(wnd);
}

std::string WackUtils::getWindowClass(HWND wnd) {
	if (wnd == nullptr) return "";
	const auto className = new char[256];
	GetClassName(wnd, className, 256);
	return className;
}

std::vector<HWND> WackUtils::getWindows() {
	return findWindows([](HWND wnd) { return FILTER_ACCEPT; });
}

struct lParamData {
	const WackUtils::windowFilter_t& predicate;
	std::vector<HWND> matches;
};

std::vector<HWND> WackUtils::findWindows(const WackUtils::windowFilter_t &predicate) {
	std::vector<HWND> windows;
	lParamData data = { predicate, windows };

	// TODO:fix

	// get all windows
	//EnumWindows([](HWND wnd, LPARAM lParam) {
	//	auto& data = *(lParamData*)lParam;
	//	auto ret = data.predicate(wnd);
	//
	//	if (ret == FILTER_ACCEPT || ret == FILTER_ACCEPT_STOP) data.matches.push_back(wnd);
	//	return (int)!(ret == FILTER_STOP || ret == FILTER_ACCEPT_STOP);
	//}, (LPARAM)&data);

	return data.matches;
}
