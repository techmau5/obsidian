#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T12:30:43
#
#-------------------------------------------------

QT       += core gui
QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = obsidian
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    favorite.cpp \
    browserdatamanager.cpp \
    favoriteedit.cpp

HEADERS  += mainwindow.h \
    favorite.h \
    browserdatamanager.h \
    favoriteedit.h

FORMS    += mainwindow.ui \
    favoriteedit.ui

DISTFILES += \
    Obsidian.ico

win32:RC_ICONS += Obsidian.ico

