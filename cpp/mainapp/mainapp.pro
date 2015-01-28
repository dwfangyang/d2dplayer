TEMPLATE = app
TARGET = mainapp
VERSION = 1.0.0
INCLUDEPATH += ../include/ 		\
				"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Include"
INCLUDEPATH -= %QTDIr%
DEFINES += NDEBUG _WINDOWS UNICODE WIN32
QMAKE_CXXFLAGS += /Od /MP /Zc:wchar_t- /EHsc /MD /nologo /c /Zi /TP  /W1
QMAKE_CXXFLAGS_RELEASE += /Os /Od
QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS /DEBUG
LIBS += "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\d2d1.lib" -L"$(SolutionDir)/../d2dplayer/cpp/lib" 			\
		avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib swscale.lib swresample.lib winmm.lib ws2_32.lib		\
		pdh.lib
LIBS -= qtmain.lib

QMAKESPECS = win32-msvc2008

QT -= core gui

HEADERS += ffmpegutils.h		\
			utils.h				\
			SystemServiceCenter.h \
			MainApp.h			\
			swf.tlh				\
			FString.h			\
			fnetwork.h			\
			
SOURCES += ffmpegutils.cpp		\
			SystemServiceCenter.cpp  \
			MainApp.cpp					\
			swf.tli					\
			FString.cpp				\
			utils.cpp				\
			fnetwork.cpp