#include "MainApp.h"
#include <QtCore/QString>
#include <QApplication>
#include "qtMainWnd.h"
using namespace std;
//
//static int read_packet(void *opaque, uint8_t *buf, int buf_size)
//{
//	struct buffer_data *bd = (struct buffer_data *)opaque;
//	buf_size = FFMIN(buf_size, int(bd->size));
//
//	printf("ptr:%p size:%zu\n", bd->ptr, bd->size);
//
//	/* copy internal buffer data to buf */
//	memcpy(buf, bd->ptr, buf_size);
//	bd->ptr  += buf_size;
//	bd->size -= buf_size;
//
//	return buf_size;
//}
//
//MainApp::MainApp() :
//m_hwnd(NULL),
//m_pDirect2dFactory(NULL),
//m_pRenderTarget(NULL),
//m_pLightSlateGrayBrush(NULL),
//m_pCornflowerBlueBrush(NULL)
//{
//}
//
//MainApp::~MainApp()
//{
//	SafeRelease(&m_pDirect2dFactory);
//	SafeRelease(&m_pRenderTarget);
//	SafeRelease(&m_pLightSlateGrayBrush);
//	SafeRelease(&m_pCornflowerBlueBrush);
//}
//
//void MainApp::RunMessageLoop()
//{
//	MSG msg;
//
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//}
//
//HRESULT MainApp::Initialize()
//{
//	HRESULT hr;
//
//	// Initialize device-indpendent resources, such
//	// as the Direct2D factory.
//	hr = CreateDeviceIndependentResources();
//
//	if (SUCCEEDED(hr))
//	{
//		// Register the window class.
//		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
//		wcex.style         = CS_HREDRAW | CS_VREDRAW;
//		wcex.lpfnWndProc   = MainApp::WndProc;
//		wcex.cbClsExtra    = 0;
//		wcex.cbWndExtra    = sizeof(LONG_PTR);
//		wcex.hInstance     = HINST_THISCOMPONENT;
//		wcex.hbrBackground = NULL;
//		wcex.lpszMenuName  = NULL;
//		wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
//		wcex.lpszClassName = L"D2DDemoApp";
//
//		RegisterClassEx(&wcex);
//
//
//		// Because the CreateWindow function takes its size in pixels,
//		// obtain the system DPI and use it to scale the window size.
//		FLOAT dpiX, dpiY;
//
//		// The factory returns the current system DPI. This is also the value it will use
//		// to create its own windows.
//		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
//		//MessageBox(0,QString("dpix:%1,dpiy:%2").arg(dpiX).arg(dpiY).toStdWString().c_str(),0,0);		//本机跑为96，96
//
//		// Create the window.
//		m_hwnd = CreateWindow(
//			L"D2DDemoApp",
//			L"Direct2D Demo App",
//			WS_OVERLAPPEDWINDOW,
//			CW_USEDEFAULT,
//			CW_USEDEFAULT,
//			static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
//			static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
//			NULL,
//			NULL,
//			HINST_THISCOMPONENT,
//			this
//			);
//		hr = m_hwnd ? S_OK : E_FAIL;
//		if (SUCCEEDED(hr))
//		{
//			ShowWindow(m_hwnd, SW_SHOWNORMAL);
//			UpdateWindow(m_hwnd);
//			//initQt();
//		}
//	}
//	
//	testFFmpeg();			//测试ffmpeg数据
//
//	return hr;
//}
//
//void MainApp::initQt()
//{
//	m_pWidget = new QWidget(NULL,Qt::Window);
//	SetParent(m_pWidget->winId(),m_hwnd);
//	QGraphicsView* view = new QGraphicsView(m_pWidget);
//	m_pScene = new QGraphicsScene(view);
//	view->setScene(m_pScene);
//}
//
//void MainApp::addItem()
//{
//	initQt();
//	QGraphicsTextItem* item = new QGraphicsTextItem();
//	m_pScene->addItem(item);
//	item->setPlainText("iewok");
//	item->show();
//}
//
//HRESULT MainApp::CreateDeviceIndependentResources()
//{
//	HRESULT hr = S_OK;
//
//	// Create a Direct2D factory.
//	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
//
//	return hr;
//}
//
//HRESULT MainApp::CreateDeviceResources()
//{
//	HRESULT hr = S_OK;
//
//	if (!m_pRenderTarget)
//	{
//		RECT rc;
//		GetClientRect(m_hwnd, &rc);
//
//		D2D1_SIZE_U size = D2D1::SizeU(
//			rc.right - rc.left,
//			rc.bottom - rc.top
//			);
//
//		// Create a Direct2D render target.
//		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
//			D2D1::RenderTargetProperties(),
//			D2D1::HwndRenderTargetProperties(m_hwnd, size),
//			&m_pRenderTarget
//			);
//
//
//		if (SUCCEEDED(hr))
//		{
//			// Create a gray brush.
//			hr = m_pRenderTarget->CreateSolidColorBrush(
//				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
//				&m_pLightSlateGrayBrush
//				);
//		}
//		if (SUCCEEDED(hr))
//		{
//			// Create a blue brush.
//			hr = m_pRenderTarget->CreateSolidColorBrush(
//				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
//				&m_pCornflowerBlueBrush
//				);
//		}
//	}
//
//	return hr;
//}
//
//void MainApp::DiscardDeviceResources()
//{
//	SafeRelease(&m_pRenderTarget);
//	SafeRelease(&m_pLightSlateGrayBrush);
//	SafeRelease(&m_pCornflowerBlueBrush);
//}
//
//LRESULT CALLBACK MainApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	LRESULT result = 0;
//
//	if (message == WM_CREATE)
//	{
//		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
//		MainApp *pDemoApp = (MainApp *)pcs->lpCreateParams;
//
//		::SetWindowLongPtrW(
//			hwnd,
//			GWLP_USERDATA,
//			PtrToUlong(pDemoApp)
//			);
//		result = 1;
//	}
//	else
//	{
//		MainApp *pDemoApp = reinterpret_cast<MainApp *>(static_cast<LONG_PTR>(
//			::GetWindowLongPtrW(
//			hwnd,
//			GWLP_USERDATA
//			)));
//
//		bool wasHandled = false;
//
//		if (pDemoApp)
//		{
//			switch (message)
//			{
//			case WM_SIZE:
//				{
//					UINT width = LOWORD(lParam);
//					UINT height = HIWORD(lParam);
//					pDemoApp->OnResize(width, height);
//				}
//				result = 0;
//				wasHandled = true;
//				break;
//
//			case WM_DISPLAYCHANGE:
//				{
//					InvalidateRect(hwnd, NULL, FALSE);
//				}
//				result = 0;
//				wasHandled = true;
//				break;
//
//			case WM_PAINT:
//				{
//					pDemoApp->OnRender();
//					ValidateRect(hwnd, NULL);
//					result = 0;
//					wasHandled = true;
//					pDemoApp->addItem();
//				}
//				break;
//
//			case WM_DESTROY:
//				{
//					PostQuitMessage(0);
//				}
//				result = 1;
//				wasHandled = true;
//				break;
//			}
//		}
//
//		if (!wasHandled)
//		{
//			result = DefWindowProc(hwnd, message, wParam, lParam);
//		}
//	}
//
//	return result;
//}
//
//void MainApp::OnResize(UINT width, UINT height)
//{
//	if (m_pRenderTarget)
//	{
//		// Note: This method can fail, but it's okay to ignore the
//		// error here, because the error will be returned again
//		// the next time EndDraw is called.
//		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
//	}
//}
//
//HRESULT MainApp::OnRender()
//{
//	HRESULT hr = S_OK;
//
//	hr = CreateDeviceResources();
//
//	if (SUCCEEDED(hr))
//	{
//		m_pRenderTarget->BeginDraw();
//
//		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
//
//		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
//
//		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
//		// Draw a grid background.
//		int width = static_cast<int>(rtSize.width);
//		int height = static_cast<int>(rtSize.height);
//
//		for (int x = 0; x < width; x += 10)
//		{
//			m_pRenderTarget->DrawLine(
//				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
//				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
//				m_pLightSlateGrayBrush,
//				0.2f
//				);
//		}
//
//		for (int y = 0; y < height; y += 10)
//		{
//			m_pRenderTarget->DrawLine(
//				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
//				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
//				m_pLightSlateGrayBrush,
//				0.2f
//				);
//		}
//
//		// Draw two rectangles.
//		D2D1_RECT_F rectangle1 = D2D1::RectF(
//			rtSize.width/2 - 50.0f,
//			rtSize.height/2 - 50.0f,
//			rtSize.width/2 + 50.0f,
//			rtSize.height/2 + 50.0f
//			);
//
//		D2D1_RECT_F rectangle2 = D2D1::RectF(
//			rtSize.width/2 - 100.0f,
//			rtSize.height/2 - 100.0f,
//			rtSize.width/2 + 100.0f,
//			rtSize.height/2 + 100.0f
//			);
//
//		// Draw a filled rectangle.
//		m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);
//
//		// Draw the outline of a rectangle.
//		m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);
//
//		hr = m_pRenderTarget->EndDraw();
//	}
//
//	if (hr == D2DERR_RECREATE_TARGET)
//	{
//		hr = S_OK;
//		DiscardDeviceResources();
//	}
//
//	return hr;
//}
//
//int MainApp::testFFmpeg()
//{
//	//MessageBox(0,L"pause",0,0);
//		//encoding_decoding("./ok.okd","h264");		//暂不支持h264
//		AVFormatContext *fmt_ctx = NULL;
//		AVIOContext *avio_ctx = NULL;
//		AVDictionaryEntry *tag = NULL;
//		uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
//		size_t buffer_size , avio_ctx_buffer_size = 4096;
//		char *input_filename = NULL;
//		int ret = 0;
//		struct buffer_data bd = { 0 };
//		
//		/*if (argc != 2) {
//			fprintf(stderr, "usage: %s input_file\n"
//				"API example program to show how to read from a custom buffer "
//				"accessed through AVIOContext.\n", argv[0]);
//			return 1;
//		}*/
//		input_filename = "d:\\vs2008_Projects\\d2d\\Release\\GameofThronesS04E04.mp4";
//
//		if ( QString(input_filename).isEmpty() )
//		{
//			MessageBox(0,L"empty filename",0,0);
//		}
//
//		/* register codecs and formats and other lavf/lavc components*/
//		av_register_all();
//
//		/* slurp file content into buffer */
//		ret = av_file_map(input_filename, &buffer, &buffer_size, 0, NULL);
//		if (ret < 0)
//			goto end;
//
//		/* fill opaque structure used by the AVIOContext read callback */
//		bd.ptr  = buffer;
//		bd.size = buffer_size;
//
//		if (!(fmt_ctx = avformat_alloc_context())) {
//			ret = AVERROR(ENOMEM);
//			goto end;
//		}
//
//		avio_ctx_buffer = (uint8_t*)(av_malloc(avio_ctx_buffer_size));
//		if (!avio_ctx_buffer) {
//			ret = AVERROR(ENOMEM);
//			goto end;
//		}
//		avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,
//			0, &bd, &read_packet, NULL, NULL);
//		if (!avio_ctx) {
//			ret = AVERROR(ENOMEM);
//			goto end;
//		}
//		fmt_ctx->pb = avio_ctx;
//
//		ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
//		if (ret < 0) {
//			//fprintf(stderr, "Could not open input\n");
//			goto end;
//		}
//
//		ret = avformat_find_stream_info(fmt_ctx, NULL);
//		if (ret < 0) {
//			//fprintf(stderr, "Could not find stream information\n");
//			goto end; 
//		}
//
//		av_dump_format(fmt_ctx, 0, input_filename, 0);
//		while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
//			printf("%s=%s\n", tag->key, tag->value);
//
//	end:
//		avformat_close_input(&fmt_ctx);
//		/* note: the internal buffer could have changed, and be != avio_ctx_buffer */
//		if (avio_ctx) {
//			av_freep(&avio_ctx->buffer);
//			av_freep(&avio_ctx);
//		}
//		av_file_unmap(buffer, buffer_size);
//
//		if (ret < 0) 
//		{
//			//fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
//			MessageBox(0,QString("error: %1").arg(ret).toStdWString().c_str(),0,0);
//			return 1;
//		}
//	return 0;	
//}
//
//int WINAPI WinMain(
//				   HINSTANCE /* hInstance */,
//				   HINSTANCE /* hPrevInstance */,
//				   LPSTR  /*lpCmdLine*/ ,
//				   int /* nCmdShow */
//				   )
//{
//	 /*Use HeapSetInformation to specify that the process should
//	 terminate if the heap manager detects an error in any heap used
//	 by the process.
//	 The return value is ignored, because we want to continue running in the
//	 unlikely event that HeapSetInformation fails.*/
//	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
//
//	if (SUCCEEDED(CoInitialize(NULL)))
//	{
//		{
//			MainApp app;
//
//			if (SUCCEEDED(app.Initialize()))
//			{
//				app.RunMessageLoop();
//			}
//		}
//		CoUninitialize();
//	}
//	//char ** param = NULL;
//	//int i = 0;
//	//qtMainWnd * wnd = new qtMainWnd(i,param);
//	//_asm INT 3;
//	return 0;
//}

int WINAPI WinMain(
				   HINSTANCE /* hInstance */,
				   HINSTANCE /* hPrevInstance */,
				   LPSTR  /*lpCmdLine*/ ,
				   int /* nCmdShow */
				   )
{   
	QApplication app(__argc,__argv);
	qtMainWnd wnd;
	wnd.setFixedSize(480,360);
	//wnd.setWindowTitle(title);
	QPalette palette;
	palette.setColor(wnd.backgroundRole(),QColor(Qt::red));
	wnd.setPalette(palette);
	wnd.setWindowOpacity(0.5);
	wnd.setWindowFlags(Qt::Window);
	wnd.setWindowFlags(Qt::FramelessWindowHint);
	wnd.setPos(qtMainWnd::POS_SCREENCENTER);
	wnd.show();
	//wnd.showMinimized();
	return app.exec();
}
