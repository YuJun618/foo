#-------------------------------------------------
#
# Project created by QtCreator 2020-05-29T16:37:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_testproj
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    switchcontrol.cpp \
    plottestdlg.cpp

HEADERS  += dialog.h \
    switchcontrol.h \
    plottestdlg.h

FORMS    += dialog.ui \
    plottestdlg.ui


INCLUDEPATH +="E:\open_source\qwt-6.1.4\qwt-6.1.4\export\include"

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
LIBS +=E:\open_source\qwt-6.1.4\qwt-6.1.4\export\lib\qwtd.lib
unix|win32: LIBS += Qt5Cored.lib
unix|win32: LIBS += Qt5Guid.lib

} else {
LIBS +=E:\open_source\qwt-6.1.4\qwt-6.1.4\export\lib\qwt.lib
unix|win32: LIBS += Qt5Core.lib
unix|win32: LIBS += Qt5Gui.lib
}
