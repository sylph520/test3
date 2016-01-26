#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T16:58:05
#
#-------------------------------------------------

QT       += core gui \
                xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test3
TEMPLATE = app


SOURCES += main.cpp\
        diagramtext.cpp \
    parsetext.cpp \
    parseimage.cpp \
    filtertext.cpp

HEADERS  += diagramtext.h \
    geometry.h \
    filtertext.h \
    parseimage.h \
    xmlconfig.h

FORMS    += diagramtext.ui
