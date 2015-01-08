TEMPLATE = app
TARGET = mainapp
VERSION = 1.0.0
DEPENDPATH += 	$(QTDIR)/lib	
INCLUDEPATH += ../include/ 		\
				$(QTDIR)/include/QtGui \
				$(QTDIR)/include/QtCore \
				"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Include"
#MOC_DIR = ./bin/$(ConfigurationName)/moc/mainapp
#DESTDIR += ./bin/$(ConfigurationName)
DEFINES += QT_NO_DEBUG NDEBUG _WINDOWS UNICODE WIN32 QT_LARGEFILE_SUPPORT QT_CORE_LIB QT_GUI_LIB _UNICODE QT_SCRIPT_LIB QT_THREAD_SUPPORT QT_CORE_LIB QT_GUI_LIB QT_DLL
#QT_NO_DEBUG,NDEBUG,_WINDOWS,UNICODE,WIN32,QT_LARGEFILE_SUPPORT,QT_THREAD_SUPPORT,QT_DLL,QT_HAVE_MMX,QT_HAVE_SSE,QT_HAVE_MMXEXT,QT_HAVE_SSE2
QMAKE_CXXFLAGS += /Od /MP /Zc:wchar_t- /EHsc /MD /nologo /c /Zi /TP  /W1
QMAKE_CXXFLAGS_RELEASE += /Os /Od
QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS /DEBUG
LIBS += "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\d2d1.lib" -L"$(SolutionDir)/../d2dplayer/cpp/lib" avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib swscale.lib swresample.lib
CONFIG(debug, debug|release) {
	LIBS += QtCored4.lib QtGuid4.lib
} else {
	LIBS += QtCore4.lib QtGui4.lib
}
QMAKESPECS = win32-msvc2008
CONFIG += qt thread build_all windows
QT = core gui

HEADERS += ffmpegutils.h		\
			utils.h				\
			qtMainWnd.h			\
			SystemServiceCenter.h \
			MainApp.h			\
			swf.tlh				\
			FString.h			\
			fnetwork.h			\
			
SOURCES += ffmpegutils.cpp		\
			qtMainWnd.cpp		\
			SystemServiceCenter.cpp  \
			MainApp.cpp					\
			swf.tli					\
			FString.cpp				\
			utils.cpp				\
			fnetwork.cpp