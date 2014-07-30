TEMPLATE = app
TARGET = 
VERSION = 1.0.0
DEPENDPATH += ./lib 	\
				$(QTDIR)/lib	
INCLUDEPATH += ../include 		\
				$(QTDIR)/include/QtCore 

DESTDIR += $(SolutionDir)/bin/$(ConfigurationName)
DEFINES += QT_NO_DEBUG NDEBUG _WINDOWS UNICODE WIN32 QT_LARGEFILE_SUPPORT QT_CORE_LIB _UNICODE QT_THREAD_SUPPORT QT_HAVE_MMX QT_HAVE_SSE QT_HAVE_MMXEXT QT_HAVE_SSE2
QMAKE_CXXFLAGS_RELEASE += -Os -Od
QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS
LIBS += "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\d2d1.lib" avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib swscale.lib swresample.lib
CONFIG(debug, debug|release) {
	LIBS += QtCored4.lib
} else {
	LIBS += QtCore4.lib
}

HEADERS += ffmpegutils.h	\
			utils.h				\
			MainApp.h
SOURCES += ffmpegutils.cpp		\
			MainApp.cpp