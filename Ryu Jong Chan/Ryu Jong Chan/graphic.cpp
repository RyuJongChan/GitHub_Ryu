#include "graphic.h"
#include <math.h>

unsigned int BackBuffer[HEIGHT][WIDTH];

unsigned int rgb(int r, int g, int b)
{
	unsigned int rgb = ((unsigned int)r) << 16 | ((unsigned int)g) << 8 | ((unsigned int)b) << 0;
	return rgb;
}

void setPixel(int x, int y, unsigned int col)  
{
	if(0<=y  && y <HEIGHT) 
	{
		if(0<=x && x < WIDTH)
		{
			BackBuffer[y][x] = col;
		}
	}
}

void setPixel(int x, int y, int r, int g, int b)
{
	if (0 <= y && y <HEIGHT)  
	{
		if (0 <= x && x < WIDTH)
		{
			BackBuffer[y][x] = rgb(r,g,b);
		}
	}
}

unsigned int getPixel(int x, int y)
{	
	if (0 <= y && y <HEIGHT)  
	{
		if (0 <= x && x < WIDTH)
		{
			return BackBuffer[y][x];
		}
	}

	return 0;
}

void drawLine(int x0, int y0, int x1, int y1, unsigned int col)
{
	int temp1;
	int temp2;

	if(y0 == y1)
	{	
		if(x0 > x1)
		{
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}

		for(int x = x0; x <= x1; x++)
		{
			setPixel(x, y0, col);
		}
	}

	else if(x0 == x1)
	{
		if(y0 > y1)
		{
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}

		for(int y = y0; y <= y1; y++)
		{
			setPixel(x0, y, col); 
		}

	}
	
	else
	{
		float m = (float)(y1 - y0) / (float)(x1 - x0);

		if(-1<=m && m<=1)
		{		
			if(x0 > x1)
			{
				temp1 = x0;
				x0 = x1;
				x1 = temp1;

				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}
			
			for(int x = x0; x <= x1; x++)
			{
				setPixel(x, (int)( y0 + (x-x0)*m +0.5 ), col);

			}

		}
		
		else 
		{			
			if(y0 > y1)
			{
				temp1 = x0;
				x0 = x1;
				x1 = temp1;

				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}
		
			for(int y = y0; y <= y1; y++)
			{
				setPixel( (int)( x0 + (y-y0) * 1 / m + 0.5), y, col); 
			}

		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, int r, int g, int b)
{
	drawLine(x0, y0, x1, y1, rgb(r, g, b));
}

void drawRect(int x0, int y0, int x1, int y1, unsigned int rgb)
{
	drawLine(x0, y0, x1, y0, rgb);
	drawLine(x0, y1, x1, y1, rgb);
	drawLine(x0, y0, x0, y1, rgb);
	drawLine(x1, y0, x1, y1, rgb);
}

void drawRect(int x0, int y0, int x1, int y1, int r, int g, int b)
{
	drawRect(x0, y0, x1,y1, rgb(r,g,b));
}

void drawCircle(int cx, int cy, int r, unsigned int col)
{
	int x = 0, y = 0;

	for (x = 0; x <= y; x++)
	{
		//y 축 좌표 계산
		y = (int)(sqrt(r*r - x * x) + 0.5);

		//(1)계산된 (x,y) 좌표에 픽셀 출력
		//(2)픽셀의 출력은 원점(cx, cy) 만큼 평행 이동
		setPixel(cx + x, cy + y, col); 
		setPixel(cx + x, cy - y, col); 
		setPixel(cx - x, cy + y, col);
		setPixel(cx - x, cy - y, col);
		setPixel(cx + y, cy + x, col);
		setPixel(cx + y, cy - x, col);
		setPixel(cx - y, cy + x, col);
		setPixel(cx - y, cy - x, col);
	}
}

void drawCircle(int cx, int cy, int radius, int r, int g, int b)
{
	drawCircle(cx, cy, radius, rgb(r, g, b));
}

HWND hWnd = NULL;

void initGraphic()
{
	HWND GetConsoleHwnd();
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	
	hWnd = GetConsoleHwnd();
}

void clear(unsigned int col)
{
	for(int j = 0; j < HEIGHT; j++)
	{
		for(int i = 0; i < WIDTH; i++)
		{
			BackBuffer[j][i] = col;
		}
	}
}

void clear(int r, int g, int b)
{
	clear(rgb(r, g, b));
}

void render()
{
	HDC hDC, hMemDC;
	HBITMAP hBmp;
	void   * pBmp = NULL;
	int size;

	hDC = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	size = WIDTH  * HEIGHT * 4;

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = WIDTH;
	bi.bmiHeader.biHeight = -HEIGHT;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 0;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	hBmp = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, &pBmp, NULL, 0);
	SelectObject(hMemDC, hBmp);

	CopyMemory(pBmp, BackBuffer, size);

	BitBlt(hDC, STARTX, STARTY, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hBmp);
	DeleteDC(hMemDC);
	DeleteObject(hDC);
}

#ifdef GRAPHIC_MODE_0

HWND GetConsoleHwnd()
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	WCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										 // WindowTitle.
	WCHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										  // WindowTitle.

										  // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, L"%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}

#else

HWND GetConsoleHwnd()
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	CHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										 // WindowTitle.
	CHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										  // WindowTitle.

										  // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}


#endif