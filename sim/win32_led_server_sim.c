#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Ws2_32.lib")

#define K15_FALSE 0
#define K15_TRUE 1

typedef unsigned char bool8;
typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

void printErrorToFile(const char* p_FileName)
{
	DWORD errorId = GetLastError();
	char* textBuffer = 0;
	DWORD writtenChars = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, errorId, 
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&textBuffer, 512, 0);

	if (writtenChars > 0)
	{
		FILE* file = fopen(p_FileName, "w");

		if (file)
		{
			fwrite(textBuffer, writtenChars, 1, file);			
			fflush(file);
			fclose(file);
		}
	}
}

void allocateDebugConsole()
{
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
}

void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height);

HDC backbufferDC = 0;
HBITMAP backbufferBitmap = 0;
uint32 screenWidth = 1024;
uint32 screenHeight = 768;
uint32 timePerFrameInMS = 16;

SOCKET socketfd;
struct sockaddr server;
int serverPort = 3500;
//int serverPort = 80;
byte serverInit = 0;
FILE* pOutFile = NULL;

void K15_WindowCreated(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_WindowClosed(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_KeyInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseButtonInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseMove(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseWheel(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_WindowResized(HWND p_HWND, UINT p_Messaeg, WPARAM p_wParam, LPARAM p_lParam)
{
	WORD newWidth = (WORD)(p_lParam);
	WORD newHeight = (WORD)(p_lParam >> 16);

	resizeBackbuffer(p_HWND, newWidth, newHeight);
}

LRESULT CALLBACK K15_WNDPROC(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	bool8 messageHandled = K15_FALSE;

	switch (p_Message)
	{
	case WM_CREATE:
		K15_WindowCreated(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_CLOSE:
		K15_WindowClosed(p_HWND, p_Message, p_wParam, p_lParam);
		PostQuitMessage(0);
		messageHandled = K15_TRUE;
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		K15_KeyInput(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_SIZE:
		K15_WindowResized(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_XBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
		K15_MouseButtonInput(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_MOUSEMOVE:
		K15_MouseMove(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_MOUSEWHEEL:
		K15_MouseWheel(p_HWND, p_Message, p_wParam, p_lParam);
		break;
	}

	if (messageHandled == K15_FALSE)
	{
		return DefWindowProc(p_HWND, p_Message, p_wParam, p_lParam);
	}

	return 0;
}

HWND setupWindow(HINSTANCE p_Instance, int p_Width, int p_Height)
{
	WNDCLASS wndClass = {0};
	wndClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	wndClass.hInstance = p_Instance;
	wndClass.lpszClassName = "K15_Win32Template";
	wndClass.lpfnWndProc = K15_WNDPROC;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wndClass);

	HWND hwnd = CreateWindowA("K15_Win32Template", "Win32 Template",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		p_Width, p_Height, 0, 0, p_Instance, 0);

	if (hwnd == INVALID_HANDLE_VALUE)
		MessageBox(0, "Error creating Window.\n", "Error!", 0);
	else
		ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}

uint32 getTimeInMilliseconds(LARGE_INTEGER p_PerformanceFrequency)
{
	LARGE_INTEGER appTime = {0};
	QueryPerformanceCounter(&appTime);

	appTime.QuadPart *= 1000; //to milliseconds

	return (uint32)(appTime.QuadPart / p_PerformanceFrequency.QuadPart);
}

void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height)
{
	DeleteObject(backbufferBitmap);

	HDC originalDC = GetDC(p_HWND);
	backbufferBitmap = CreateCompatibleBitmap(originalDC, p_Width, p_Height);
	screenWidth = p_Width;
	screenHeight = p_Height;
	
	SelectObject(backbufferDC, backbufferBitmap);
}

void setup(HWND p_HWND)
{
	allocateDebugConsole();
	
	HDC originalDC = GetDC(p_HWND);
	backbufferDC = CreateCompatibleDC(originalDC);
	resizeBackbuffer(p_HWND, screenWidth, screenHeight);

	if (fopen_s(&pOutFile, "out.txt", "w") < 0)
	{
		printf("error: could not open 'out.txt' for writing.\n");
		return;
	}

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		printf("error initializing winsock.\n");
		return;
	} 

	socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketfd == SOCKET_ERROR)
	{
		printf("error creating socket file descriptor.\n");
		return;
	}

	int mode = 1; //FK: Non blocking
	if (ioctlsocket(socketfd, FIONBIO, &mode) == SOCKET_ERROR)
	{
		printf("error marking the socket as non-blocking.\n");
		return;
	}

	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(serverPort);

	if (bind(socketfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("error creating server at port '%u'.\n", serverPort);
		return;
	}

	if (listen(socketfd, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("error putting server into listen mode.\n");
		return;
	}

	serverInit = 1;
}

void swapBuffers(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);
	
	//blit to front buffer
	BitBlt(originalDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, SRCCOPY);

	//clear backbuffer
	BitBlt(backbufferDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, BLACKNESS);
}

void drawDeltaTime(uint32 p_DeltaTimeInMS)
{
	RECT textRect;
	textRect.left = 70;
	textRect.top = 70;
	textRect.bottom = screenHeight;
	textRect.right = screenWidth;

	char messageBuffer[64];
	SetTextColor(backbufferDC, RGB(255, 255, 255));
	SetBkColor(backbufferDC, RGB(0, 0, 0));

	sprintf_s(messageBuffer, 64, "MS: %d", p_DeltaTimeInMS);
	DrawTextA(backbufferDC, messageBuffer, -1, &textRect, DT_LEFT | DT_TOP);
}

void doFrame(uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	drawDeltaTime(p_DeltaTimeInMS);

	if (serverInit)
	{
		SOCKET client = accept(socketfd, 0, 0);
		if (client != EWOULDBLOCK && client != -1)
		{
			if (client == ENOTSOCK)
			{
				printf("error during accept() - ENOTSOCK\n");
			}
			else if (client == EOPNOTSUPP)
			{
				printf("error during accept() - EOPNOTSUPP\n");
			}

			char buffer[512];
			int bytesRead = 0u;
			
			do 
			{
				bytesRead = recv(client, buffer, sizeof(buffer)-1, 0u);

				if (bytesRead == -1)
				{
					break;
				}

				buffer[bytesRead] = 0;
				fwrite(buffer, 1u, bytesRead, pOutFile);
				fflush(pOutFile);
			} while(1);

			char text[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n";
			send(client, text, sizeof(text), 0u);
		}

		closesocket(client);
	}	
	
	swapBuffers(p_HWND);
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);

	HWND hwnd = setupWindow(hInstance, screenWidth, screenHeight);

	if (hwnd == INVALID_HANDLE_VALUE)
		return -1;

	setup(hwnd);

	uint32 timeFrameStarted = 0;
	uint32 timeFrameEnded = 0;
	uint32 deltaMs = 0;

	bool8 loopRunning = K15_TRUE;
	MSG msg = {0};

	while (loopRunning)
	{
		timeFrameStarted = getTimeInMilliseconds(performanceFrequency);

		while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				loopRunning = K15_FALSE;
		}

		doFrame(deltaMs, hwnd);

		timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
		deltaMs = timeFrameEnded - timeFrameStarted;

		if (deltaMs < timePerFrameInMS)
			Sleep(timePerFrameInMS - deltaMs);
	}

	return 0;
}