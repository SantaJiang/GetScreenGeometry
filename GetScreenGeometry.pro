QT       += core gui

unix:!macx:{
    LIBS += -lX11
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GetScreenGeometry
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

RC_ICONS = logo.ico

RESOURCES += \
    root.qrc
