#ifndef __MAINAPP_SRC_MAINAPP_H
#define __MAINAPP_SRC_MAINAPP_H

#include "utils.h"
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>
#include "ffmpegutils.h"
#include <atlcomcli.h>

template<class Interface>
inline void SafeRelease(
						Interface **ppInterfaceToRelease
						)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

//#ifndef Assert
//#if defined( DEBUG ) || defined( _DEBUG )
//#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
//#else
//#define Assert(b)
//#endif //DEBUG || _DEBUG
//#endif
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class MainApp
{
public:
	MainApp();
	~MainApp();

	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();

	// Process and dispatch messages
	void RunMessageLoop();
	void static CDECL MessageBoxPrintf(PTSTR caption, PTSTR szFormat,...);
	static void textMetric( HDC hdc , int& cxchar, int& cychar, int& cxcap );
private:
	HBRUSH	getYellowBrush();
	static HFONT getFont( HDC hdc );
	void releaseFont();
	void			releaseYellowBrush();
	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Draw content.
	HRESULT OnRender();

	// Resize the render target.
	void OnResize(
		UINT width,
		UINT height
		);

	//Test ffmpeg
	int testFFmpeg();
	//flash com
	void initFlash();

	// The windows procedure.
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
		);
	static void CALLBACK updateScroll( HWND hwnd, UINT wndWidth, UINT wndHeight );
private:
	static int		m_iCxChar;
	static int		m_iCyChar;
	static int		m_iCxCap;
	static UINT 	m_uWndWidth;
	static UINT	m_uWndHeight;
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;

	HBRUSH									m_bYellowBrush;
	//QPointer<QWidget>					m_pWidget;
};



#define NUMLINES ( (int) (sizeof systemmetrics /sizeof systemmetrics[0]))
struct {
	int Index;
	TCHAR* szLabel;
	TCHAR* szDesc;
}
systemmetrics[] = {
	SM_CXSCREEN, TEXT("SM_CXSCREEN"),TEXT("Screen width in pixels"),
	SM_CYSCREEN,TEXT("SM_CYSCREEN"),TEXT("Screen height in pixels"),
	SM_CXVSCROLL,TEXT("SM_CXVSCROLL"),TEXT("Vertical scroll width"),
	SM_CYHSCROLL,TEXT("SM_CYHSCROLL"),TEXT("horizontal scroll width"),
	SM_CYCAPTION,TEXT("SM_CYCAPTION"),TEXT("Caption bar height"),
	SM_CXBORDER,TEXT("SM_CXBORDER"),TEXT("Window border width"),
	SM_CYBORDER,TEXT("SM_CYBORDER"),TEXT("Window border height"),
	SM_CXFIXEDFRAME,TEXT("SM_CXFIXEDFRAME"),TEXT("Dialog window frame width"),
	SM_CYFIXEDFRAME,TEXT("SM_CYFIXEDFRAME"),TEXT("Dialog window frame height"),
	SM_CYVTHUMB,TEXT("SM_CYVTHUMB"),TEXT("垂直滚动条卷动方块高度"),
	SM_CXHTHUMB,TEXT("SM_CXHTHUMB"),TEXT("水平滚动条卷动方块宽度"),
	SM_CXICON,TEXT("SM_CXICON"),TEXT("Icon width"),
	SM_CYICON,TEXT("SM_CYICON"),TEXT("Icon height"),
	SM_CXCURSOR,TEXT("SM_CXCURSOR"),TEXT("cursor width"),
	SM_CYCURSOR,TEXT("SM_CYCURSOR"),TEXT("cursor height"),
	SM_CYMENU,TEXT("SM_CYMENU"),TEXT("菜单条高度"),
	SM_CXFULLSCREEN,TEXT("SM_CXFULLSCREEN"),TEXT("全屏客户端区域宽度"),
	SM_CYFULLSCREEN,TEXT("SM_CYFULLSCREEN"),TEXT("全屏客户端区域高度"),
	SM_CYKANJIWINDOW,TEXT("SM_CYKANJIWINDOW"),TEXT("kanji 窗口height"),
	SM_MOUSEPRESENT,TEXT("SM_MOUSEPRESENT"),TEXT("mouse present flag"),
	SM_CYVSCROLL,TEXT("SM_CYVSCROLL"),TEXT("垂直滚动条arrow高"),
	SM_CXHSCROLL,TEXT("SM_CXHSCROLL"),TEXT("水平滚动条arrow高"),
	SM_DEBUG,TEXT("SM_DEBUG"),TEXT("debug 版本 flag"),
	SM_SWAPBUTTON,TEXT("SM_SWAPBUTTON"),TEXT("鼠标按钮 swapped flag"),
	SM_CXMIN,TEXT("SM_CXMIN"),TEXT("最小窗口宽度"),
	SM_CYMIN,TEXT("SM_CYMIN"),TEXT("最小窗口高度"),
	SM_CXSIZE,TEXT("SM_CXSIZE"),TEXT("最小/最大/关闭按钮宽度"),
	SM_CYSIZE,TEXT("SM_CYSIZE"),TEXT("最小/最大/关闭按钮高度"),
	SM_CXSIZEFRAME,TEXT("SM_CXSIZEFRAME"),TEXT("windows sizing frame width"),
	SM_CYSIZEFRAME,TEXT("SM_CYSIZEFRAME"),TEXT("windows sizing frame height"),
	SM_CXMINTRACK,TEXT("SM_CXMINTRACK"),TEXT("Minimum window tracking width"),
	SM_CYMINTRACK,TEXT("SM_CYMINTRACK"),TEXT("Minimum window tracking height"),
};
#endif