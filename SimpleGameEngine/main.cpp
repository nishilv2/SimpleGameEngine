#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include<stdio.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "SimpleGame"
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

LPDIRECT3DDEVICE9 d3ddevice = NULL;
ID3DXFont* pfont = NULL;
RECT fontposition = { 0,0,0,0 };

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT direct3d_init(HWND hwnd);
void direct3d_render(HWND hwnd);
void direct3d_cleanup();
HRESULT object_init();
float getFps();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndclass = { 0 };
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = wndproc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "SimpleGame";

	if (!RegisterClassEx(&wndclass))
	{
		return -1;
	}

	HWND hwnd = CreateWindow("SimpleGame", WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	if (S_OK == direct3d_init(hwnd))
	{
		MessageBox(hwnd, "init successfully", "init successfully", 0);
	}
	else
	{
		MessageBox(hwnd, "init failed", "init failed", 0);
	}	
	MoveWindow(hwnd, 250, 80, SCREEN_WIDTH, SCREEN_HEIGHT, true);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);




	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			direct3d_render(hwnd);
		}
	}
	UnregisterClass("SimpleGame", wndclass.hInstance);
	return 0;
}

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		direct3d_render(hwnd);
		ValidateRect(hwnd, NULL);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		direct3d_cleanup();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

HRESULT direct3d_init(HWND hwnd)
{
	LPDIRECT3D9 pd3d = NULL;
	if (NULL==(pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
	D3DCAPS9 caps;
	int vp = 0;
	if (FAILED(pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &d3ddevice)))
	{
		return E_FAIL;
	}

	if (!(S_OK == object_init()))
	{
		return E_FAIL;
	}

	SAFE_RELEASE(pd3d);

	return S_OK;
}

HRESULT object_init()
{
	if (FAILED(D3DXCreateFont(d3ddevice, 30, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("ËÎÌו"), &pfont)))
	{
		return E_FAIL;
	}
	fontposition.top = 9;
	fontposition.left = 0;
	fontposition.right = SCREEN_WIDTH;
	fontposition.bottom = SCREEN_HEIGHT;

	return S_OK;
}

void direct3d_render(HWND hwnd)
{
	d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	RECT formatrect;
	GetClientRect(hwnd, &formatrect);

	d3ddevice->BeginScene();

	fontposition.top = 100;
	pfont->DrawTextA(0, _T("simplegame"), -1, &fontposition, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
	
	fontposition.top = 400;
	char strFPS[50];
	int charcount = sprintf_s(strFPS, _T("FPS:%0.3f"), getFps());
	pfont->DrawTextA(NULL, strFPS, charcount, &formatrect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(168, 39, 136));

	d3ddevice->EndScene();
	d3ddevice->Present(NULL, NULL, NULL, NULL);
}

void direct3d_cleanup()
{
	SAFE_RELEASE(d3ddevice);
	SAFE_RELEASE(pfont);
}

float getFps()
{
	static float framecount = 0;
	static float fps = 0;
	static float lasttime = 0.0f;
	static float currenttime = 0.0f;

	framecount++;
	currenttime = timeGetTime()*0.001f;
	if (currenttime - lasttime > 1.0f)
	{
		fps = (float)framecount / (currenttime - lasttime);
		lasttime = currenttime;
		framecount = 0;
	}
	return fps;
}