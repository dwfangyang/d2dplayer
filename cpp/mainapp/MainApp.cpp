#include "MainApp.h"
#include "swf.tlh"
#include "assert.h"
#include "atlbase.h"
#include "atlhost.h"
#include "utils.h"
#include "FString.h"
#include "SystemServiceCenter.h"
#include "strsafe.h"
using namespace std;
using ShockwaveFlashObjects::IShockwaveFlashPtr;
using ShockwaveFlashObjects::IShockwaveFlash;
using namespace Utils;

UINT MainApp::m_uWndWidth = 0;
UINT MainApp::m_uWndHeight = 0;
int		MainApp::m_iCxChar = 0;
int		MainApp::m_iCyChar = 0 ;
int		MainApp::m_iCxCap = 0 ;

MainApp::MainApp() :m_hwnd(NULL),m_pDirect2dFactory(NULL),m_pRenderTarget(NULL),m_pLightSlateGrayBrush(NULL),m_pCornflowerBlueBrush(NULL)
{
	//FString str("好的");
}

MainApp::~MainApp()
{
	releaseYellowBrush();
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}

void MainApp::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT MainApp::Initialize()
{
	HRESULT hr;
	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	hr = CreateDeviceIndependentResources();

	// Because the CreateWindow function takes its size in pixels,
	// obtain the system DPI and use it to scale the window size.
	FLOAT dpiX, dpiY;
	if ( SUCCEEDED( hr ) )
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = MainApp::WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = sizeof(LONG_PTR);
		wcex.hInstance     = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName  = NULL;
		//wcex.hIcon			= LoadIcon( HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_D2D) );
		wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
		wcex.hbrBackground = getYellowBrush();//( HBRUSH ) GetStockObject( LTGRAY_BRUSH );
		wcex.lpszClassName = L"D2DDemoApp";

		RegisterClassEx(&wcex);



		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
		//MessageBox(0,QString("dpix:%1,dpiy:%2").arg(dpiX).arg(dpiY).toStdWString().c_str(),0,0);		//本机跑为96，96
	}
	// Get desktop dc
	HDC desktophdc = GetDC(NULL);
	// Get native resolution
	dpiX = FLOAT(GetDeviceCaps(desktophdc,LOGPIXELSX));
	dpiY = FLOAT(GetDeviceCaps(desktophdc,LOGPIXELSY));
	// Create the window.
	UINT width = static_cast<UINT>(ceil(640.f * dpiX / 96.f));
	UINT height = static_cast<UINT>(ceil(480.f * dpiY / 96.f));
	m_hwnd = CreateWindow(
		L"D2DDemoApp",
		L"Direct2D Demo App",
		WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
		);

	hr = m_hwnd ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);
		//initQt();
	}

	//testFFmpeg();			//测试ffmpeg数据

	initFlash();

	return hr;
}

HRESULT MainApp::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}

HRESULT MainApp::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	CHECKVALIDRETURN( m_pRenderTarget, E_FAIL );

	RECT rc;
	GetClientRect(m_hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
		);

	// Create a Direct2D render target.
	hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, size),
		&m_pRenderTarget
		);

	CHECKEDCALL( hr, 	// Create a gray brush.
		m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightSlateGray),
		&m_pLightSlateGrayBrush
		)
	);
	CHECKEDCALL( hr, // Create a blue brush.
		m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
		&m_pCornflowerBlueBrush
		)
	);

	return hr;
}

void MainApp::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}

LRESULT CALLBACK MainApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	static int iVscrollPos = 0;
	SCROLLINFO scrollinfo;
	int iPaintbeg = 0,iPaintend = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		MainApp *pDemoApp = (MainApp *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pDemoApp)
			);
		result = 1;
	}
	else
	{
		MainApp *pDemoApp = reinterpret_cast<MainApp *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA
			)));

		bool washandled = false;
		switch (message)
		{
		case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height  = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
				HDC hdc = GetDC( hwnd );
				FFont font(10);
				font.loadFont( hdc );
				textMetric( hdc , m_iCxChar, m_iCyChar, m_iCxCap );
				updateScroll( hwnd, width , height );
				ReleaseDC( hwnd, hdc );
				CHAR buf[1000];
				double a = SystemServiceCenter::getInstance()->getCurrentCpuUsageValue();
				//StringCbPrintf( buf, 1000*sizeof(TCHAR), TEXT("%10.5lf"), a );
				sprintf( buf, "%10.5lf", a );
				//buf[len] = '\0';
			}
			//PlaySound (TEXT("hellowin.wav"),NULL,SND_FILENAME|SND_ASYNC);
			washandled = true;	
			result = 0;
			break;

		case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			washandled = true;
			result = 0;
			break;

		case WM_PAINT:
			{
				//pDemoApp->OnRender();
				PAINTSTRUCT ps;
				/*RECT rect;
				GetClientRect( hwnd, &rect );*/
				//InvalidateRect( hwnd, &rect, false );
				HDC hdc = BeginPaint(hwnd,&ps);
				FFont font(10);
				font.loadFont( hdc );
				textMetric( hdc , m_iCxChar, m_iCyChar, m_iCxCap );
				scrollinfo.cbSize = sizeof(scrollinfo);
				scrollinfo.fMask = SIF_POS;
				GetScrollInfo( hwnd, SB_VERT, &scrollinfo );
				iVscrollPos = scrollinfo.nPos;
				iPaintbeg = max ( 0, iVscrollPos + ps.rcPaint.top / m_iCyChar );
				iPaintend = min ( NUMLINES - 1, iVscrollPos + ps.rcPaint.bottom / m_iCyChar );
				//DrawText( hdc, TEXT("hello, the world good or not, it is 1234"), -1, &rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
				//TextOut( hdc, 10,0, TEXT("hello, the world good or not, it is 1234"), wcslen(TEXT("hello, the world good or not, it is 1234")));
				//int linecount = NUMLINES;
				TCHAR szbuffer[1024];
				int mode = SetBkMode( hdc, TRANSPARENT );
				for( int i = iPaintbeg; i <= iPaintend; ++i )
				{ 
					int y = m_iCyChar * ( i - iVscrollPos );
					TextOut( hdc, 3 , y , systemmetrics[i].szLabel, wcslen( systemmetrics[i].szLabel ) );
					TextOut( hdc, 3 + 22 * m_iCxCap , y , systemmetrics[i].szDesc, wcslen( systemmetrics[i].szDesc) );
					SetTextAlign( hdc, TA_RIGHT | TA_TOP );
					TextOut( hdc, 3 + 54* m_iCxCap , y , szbuffer, wsprintf( szbuffer, TEXT("%5d"), ::GetSystemMetrics(systemmetrics[i].Index) ) );
					SetTextAlign( hdc, TA_LEFT | TA_TOP );
				}
				EndPaint( hwnd, &ps );
				if ( mode )
				{
					SetBkMode( hdc, mode );
				}
				result = 0;
			}
			washandled = true;
			break;
		case WM_VSCROLL:
			{
				scrollinfo.cbSize = sizeof(scrollinfo);
				scrollinfo.fMask = SIF_ALL;
				GetScrollInfo( hwnd, SB_VERT, &scrollinfo );
				iVscrollPos = scrollinfo.nPos;
				switch( LOWORD(wParam) )
				{
				case SB_TOP:
					scrollinfo.nPos = scrollinfo.nMin;
					break;
				case SB_BOTTOM:
					scrollinfo.nPos = scrollinfo.nMax;
					break;
				case SB_LINEUP:
					scrollinfo.nPos -= 1;
					break;
				case SB_LINEDOWN:
					scrollinfo.nPos += 1;
					break;
				case SB_PAGEUP:
					scrollinfo.nPos -= scrollinfo.nPage;
					break;
				case SB_PAGEDOWN:
					scrollinfo.nPos += scrollinfo.nPage;
					break;
				case SB_THUMBTRACK:
					scrollinfo.nPos = scrollinfo.nTrackPos;
					break;
				default:
					break;
				}
				scrollinfo.fMask = SIF_POS;
				SetScrollInfo( hwnd, SB_VERT, &scrollinfo, true );
				GetScrollInfo( hwnd, SB_VERT, &scrollinfo );
				if ( scrollinfo.nPos != iVscrollPos )
				{
					ScrollWindow( hwnd, 0, m_iCyChar*( iVscrollPos - scrollinfo.nPos ), NULL, NULL );
					UpdateWindow( hwnd );
				}
			}
			washandled = true;
			result = 0;
			break;

		case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			washandled = true;
			result = 1;
			break;
		}
		CHECKVALIDRETURN( washandled, DefWindowProc(hwnd, message, wParam, lParam));
	}

	return result;
}

void MainApp::OnResize(UINT width, UINT height)
{
	CHECKVALID( m_pRenderTarget );
	// Note: This method can fail, but it's okay to ignore the
	// error here, because the error will be returned again
	// the next time EndDraw is called.
	m_pRenderTarget->Resize(D2D1::SizeU(width, height));
}

HRESULT MainApp::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
		return hr;
	}

	CHECKVALIDRETURN( SUCCEEDED(hr), hr );
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pLightSlateGrayBrush,
			0.2f
			);
	}

	for (int y = 0; y < height; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pLightSlateGrayBrush,
			0.2f
			);
	}

	// Draw two rectangles.
	D2D1_RECT_F rectangle1 = D2D1::RectF(
		rtSize.width/2 - 50.0f,
		rtSize.height/2 - 50.0f,
		rtSize.width/2 + 50.0f,
		rtSize.height/2 + 50.0f
		);

	D2D1_RECT_F rectangle2 = D2D1::RectF(
		rtSize.width/2 - 100.0f,
		rtSize.height/2 - 100.0f,
		rtSize.width/2 + 100.0f,
		rtSize.height/2 + 100.0f
		);

	// Draw a filled rectangle.
	m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

	// Draw the outline of a rectangle.
	m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

	hr = m_pRenderTarget->EndDraw();

	return hr;
}

int MainApp::testFFmpeg()
{
	//MessageBox(0,L"pause",0,0);
	encoding_decoding("./ok.okd","h264");		//暂不支持h264
	AVFormatContext *fmt_ctx = NULL;
	AVIOContext *avio_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
	size_t buffer_size , avio_ctx_buffer_size = 4096;
	char *input_filename = NULL;
	int ret = 0;
	struct buffer_data bd = { 0 };
	
	/*if (argc != 2) {
		fprintf(stderr, "usage: %s input_file\n"
			"API example program to show how to read from a custom buffer "
			"accessed through AVIOContext.\n", argv[0]);
		return 1;
	}*/
	input_filename = "d:\\vs2008_Projects\\d2d\\Release\\GameofThronesS04E04.mp4";

	//if ( QString(input_filename).isEmpty() )
	//{
	//	MessageBox(0,L"empty filename",0,0);
	//}

	/* register codecs and formats and other lavf/lavc components*/
	av_register_all();

	/* slurp file content into buffer */
	ret = av_file_map(input_filename, &buffer, &buffer_size, 0, NULL);
	if (ret < 0)
		goto end;

	/* fill opaque structure used by the AVIOContext read callback */
	bd.ptr  = buffer;
	bd.size = buffer_size;

	if (!(fmt_ctx = avformat_alloc_context())) {
		ret = AVERROR(ENOMEM);
		goto end;
	}

	avio_ctx_buffer = (uint8_t*)(av_malloc(avio_ctx_buffer_size));
	if (!avio_ctx_buffer) {
		ret = AVERROR(ENOMEM);
		goto end;
	}
	avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,
		0, &bd, &read_packet, NULL, NULL);
	if (!avio_ctx) {
		ret = AVERROR(ENOMEM);
		goto end;
	}
	fmt_ctx->pb = avio_ctx;

	ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
	if (ret < 0) {
		//fprintf(stderr, "Could not open input\n");
		goto end;
	}

	ret = avformat_find_stream_info(fmt_ctx, NULL);
	if (ret < 0) {
		//fprintf(stderr, "Could not find stream information\n");
		goto end; 
	}

	av_dump_format(fmt_ctx, 0, input_filename, 0);
	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
	{
		printf("%s=%s\n", tag->key, tag->value);
		wstring key = FString(tag->key).toStdWString();
		wstring value = FString(tag->value).toStdWString();
		OutputDebugString(key.c_str()); wstring
		OutputDebugString(value.c_str());
	}

	end:
		avformat_close_input(&fmt_ctx);
		/* note: the internal buffer could have changed, and be != avio_ctx_buffer */
		if (avio_ctx) {
			av_freep(&avio_ctx->buffer);
			av_freep(&avio_ctx);
		}
		av_file_unmap(buffer, buffer_size);

		if (ret < 0) 
		{
			//fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
			//MessageBox(0,QString("error: %1").arg(ret).toStdWString().c_str(),0,0);
			return 1;
		}
	return 0;	
}

void MainApp::initFlash()
{
	IShockwaveFlash* flash = NULL;
	IID flashid;
	if ( SUCCEEDED( CLSIDFromProgID(L"ShockwaveFlash.ShockwaveFlash",&flashid)) )
	{
		if(SUCCEEDED(CoCreateInstance(flashid, NULL, CLSCTX_INPROC_SERVER,__uuidof(IShockwaveFlash), (void **)&flash)))
		{
			IViewObject2* ivo2 = NULL;
			//IID iid_ivo2;
			//IIDFromString(__uuidof(IViewObject2),&iid_ivo2);
			if ( SUCCEEDED(flash->QueryInterface(__uuidof(IViewObject2),(void**)&ivo2)) )
			{
				//if( SUCCEEDED(AtlAxAttachControl(ivo2,m_hwnd,NULL) ))
				//{
				//	//::MessageBox(0,L"attach",0,0);
				//}
			}
			//if ( SUCCEEDED(flash->LoadMovie(0,L"F:\\ok.swf")) )
			//{
			//	if( flash->FlashVersion()  ) 
			//	{
			//		MessageBox(0,QString::number(flash->FlashVersion()).toStdWString().c_str(),0,0);
			//	}
			//}
		}
	}
}

void CDECL MainApp::MessageBoxPrintf( PTSTR caption, PTSTR szFormat,... )
{
	TCHAR buf[1024];
	va_list arglist;
	va_start(arglist,szFormat);
	size_t size = sizeof(buf)/sizeof(TCHAR);
	_vsntprintf_s(buf,size,szFormat,arglist);
	MessageBox(0,buf,caption,0);
	va_end(arglist);
}

void MainApp::textMetric(  HDC hdc ,  int& cxchar, int& cychar, int& cxcap )
{
	CHECKVALID( hdc );
	TEXTMETRIC tm;
	GetTextMetrics( hdc, &tm );
	cxchar = tm.tmAveCharWidth;
	cychar = tm.tmHeight + tm.tmExternalLeading;
	cxcap = ( tm.tmPitchAndFamily & 1 ? 3 : 2 )  * cxchar / 2;
}

HBRUSH MainApp::getYellowBrush()
{
	m_bYellowBrush = CreateSolidBrush( 0x00ffff );
	return m_bYellowBrush;
}

void MainApp::releaseYellowBrush()
{
	DeleteObject( m_bYellowBrush );
}

HFONT MainApp::getFont( HDC hdc )
{
	int nHeight = -MulDiv(18, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	HFONT font = CreateFont( nHeight,0, 0,0, FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,_T("simhei") );
	return font;
}

void CALLBACK MainApp::updateScroll( HWND hwnd, UINT wndWidth, UINT wndHeight )
{
	CHECKVALID( ( m_uWndWidth != wndWidth ) && ( m_uWndWidth != wndHeight ) && wndWidth && wndHeight );
	m_uWndWidth = wndWidth;
	m_uWndHeight = wndHeight;
	SCROLLINFO scrollinfo;
	scrollinfo.cbSize = sizeof(SCROLLINFO);
	scrollinfo.fMask = SIF_PAGE|SIF_RANGE;
	scrollinfo.nMin = 0;
	scrollinfo.nMax = NUMLINES - 1;
	scrollinfo.nPage = m_uWndHeight/m_iCyChar;
	SetScrollInfo( hwnd, SB_VERT, &scrollinfo, true );
	/*scrollinfo.cbSize = sizeof( SCROLLINFO );
	scrollinfo.fMask = SIF_RANGE|SIF_PAGE;
	scrollinfo.nMin = 0;
	scrollinfo.nMax = 3 + iMaxWidth / cxChar;
	SetScrollInfo( hwnd, SB_HORZ, &scrollinfo, true );*/
}

int WINAPI WinMain(
				   HINSTANCE /* hInstance */,
				   HINSTANCE /* hPrevInstance */,
				   LPSTR  /*lpCmdLine*/ ,
				   int /* nCmdShow */
				   )
{
	 /*Use HeapSetInformation to specify that the process should
	 terminate if the heap manager detects an error in any heap used
	 by the process.
	 The return value is ignored, because we want to continue running in the
	 unlikely event that HeapSetInformation fails.*/
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			MainApp app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop(); 
				//MainApp::MessageBoxPrintf(TEXT("targetsize"),TEXT("screen is %1 pixels wide, %2 pixels wide"),10,20);
			}
		}
		CoUninitialize();
	}
	//string c = "A";
	//BYTE i = FNetWork::pop_byte( c.data() );
	//FString ab = FString::number( i );
	//MessageBox(0,ab.toStdWString().c_str(),TEXT("title"),MB_YESNO);
	//char ** param = NULL;
	//int i = 0;
	//qtMainWnd * wnd = new qtMainWnd(i,param);
	return 0;
}

//int WINAPI WinMain(
//				   HINSTANCE /* hInstance */,
//				   HINSTANCE /* hPrevInstance */,
//				   LPSTR  /*lpCmdLine*/ ,
//				   int /* nCmdShow */
//				   )
//{
//	//DebugBreak();
//	//throw 2;
//	IShockwaveFlashPtr flash = NULL;
//	////CoCreateInstance()
//	//CoInitialize(NULL);
	//IID flashid;
	//if ( SUCCEEDED( CLSIDFromProgID(L"ShockwaveFlash.ShockwaveFlash",&flashid)) )
	//{
	//	CoCreateInstance(flashid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IUnknown), (void **)&flash);
	//}
//	//IIDFromString(L"D27CDB6E-AE6D-11cf-96B8-444553540000",&flashid);//LPCOLESTR
//	//CoCreateInstance(flashid,NULL,CLSCTX_INPROC_SERVER,)
//	//QApplication app(__argc,__argv);
//	//qtMainWnd wnd;
//	//wnd.setFixedSize(480,360);
//	////wnd.setWindowTitle(title);
//	//QPalette palette;
//	//palette.setColor(wnd.backgroundRole(),QColor(Qt::red));
//	//wnd.setPalette(palette);
//	//wnd.setWindowOpacity(0.5);
//	//wnd.setWindowFlags(Qt::Window);
//	//wnd.setWindowFlags(Qt::FramelessWindowHint);
//	//wnd.setPos(qtMainWnd::POS_SCREENCENTER);
//	//wnd.show();
//	////wnd.showMinimized();
//	//return app.exec();
//}
