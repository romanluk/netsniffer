TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lws2_32

SOURCES += main.cpp \
    rawsocket.cpp \
    ipheader.cpp

HEADERS += \
    rawsocket.h \
    ipheader.h
