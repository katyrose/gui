#include <Windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define RUN_BUTTON 5
#define PREVIEW_BUTTON 6
#define SCREEN_TAB 7
#define CHANNEL_TAB 8
#define TEST_TAB 9

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
//void loadImages();

HMENU hMenu;
HWND hEdit, hPreview;
//HBITMAP hPreviewImage;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;
	//WS_OVERLAPPEDWINDOW
	CreateWindowW(L"myWindowClass", L"My window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 750, 500, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	switch (msg)
	{
	case WM_COMMAND:	//Chooses betweens menu options:
		switch (wp)
		{
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			break;
		case FILE_MENU_OPEN:
			break;
		case CHANGE_TITLE:
			wchar_t text[100];
			GetWindowTextW(hEdit, text, 100);
			SetWindowText(hWnd, text);
			break;
		case RUN_BUTTON:		//NEEDS TO BE FILLED
			break;
		case PREVIEW_BUTTON:	//NEEDS TO BE FILLED
			break;
		}
		break;


	case WM_CREATE:		//Add all initilization here. Menus, options, boxes, ect:
		//loadImages();
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}

}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();	//Creating a  menu
	HMENU hFileMenu = CreateMenu();		//Creates a menu option for File
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, L"Change Window Name");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	//MF_String can be used as a bit map. Future testing
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");
	SetMenu(hWnd, hMenu);

}

void AddControls(HWND hWnd)
{
	CreateWindowW(L"Static", L"Enter text here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
		200, 100, 100, 50, hWnd, NULL, NULL, NULL);
	hEdit = CreateWindowW(L"Edit", L"XYZ?...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		305, 100, 50, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"Preview", WS_VISIBLE | WS_CHILD,
		580, 380, 60, 40, hWnd, (HMENU)PREVIEW_BUTTON, NULL, NULL);
	CreateWindowW(L"Button", L"Run", WS_VISIBLE | WS_CHILD,
		660, 380, 60, 40, hWnd, (HMENU)RUN_BUTTON, NULL, NULL);
	/*
	hPreview = CreateWindowW(L"Static",NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_BITMAP,
		50, 300, 200, 250, hWnd, NULL, NULL, NULL);
	SendMessageW(hPreview, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hPreviewImage);
	*/
}

/*
void loadImages()
{
									//First paramater will be used for
									//loading from a function!
	hPreviewImage = (HBITMAP)LoadImageW(NULL, L"bitmap3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

} 
*/