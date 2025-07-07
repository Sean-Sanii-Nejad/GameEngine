#include <Window.h> 


Window* window = nullptr; // Global pointer to the window instance.

Window::Window() {  
	
}  

Window::~Window() {

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CREATE:
	{
		window->setHWND(hwnd); 
		window->onCreate();
	}
	break;
	case WM_DESTROY:
	{
		window->onDestroy();
		PostQuitMessage(0); // Post a quit message when the window is destroyed.
	}
	break;

	default:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam); // Default window procedure for unhandled messages.
	}
	}
	return NULL;
}

bool Window::init() {  
	HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc = {}; 
    wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
	
	if (!::RegisterClassEx(&wc)) // Registration of the window class, if it fails, return false.
		return false;

	if (!window)
		window = this;
	
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL); // Create the window with the class we just registered.

	if (!m_hwnd) // If the window creation failed, return false.
		return false;

	// Show and Update the window.
	::ShowWindow(m_hwnd, SW_SHOW); 
	::UpdateWindow(m_hwnd); 

	
    return true;  
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg); // Translate the message to handle keyboard input.
		DispatchMessage(&msg); // Dispatch the message to the window procedure.
	}

	window->onUpdate();

	Sleep(0);
	return true;
}

bool Window::release() {
	if (!::DestroyWindow(m_hwnd)) // If the window destruction fails, return false.
		return false;

	return true;
}

bool Window::isRun() {
	return m_is_run;
}

RECT Window::getClientWindowRect() {
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc); // Get the client area rectangle of the window.
	return rc;
}

void Window::setHWND(HWND hwnd) {
	this->m_hwnd = hwnd;
}

void Window::onDestroy() {
	std::cout << "Window is being destroyed." << std::endl;
	m_is_run = false;
}


void Window::onCreate() {
	std::cout << "Window has been created." << std::endl;
	m_is_run = true;
}

void Window::onUpdate() {
}



