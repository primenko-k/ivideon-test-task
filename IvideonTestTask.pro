TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = cam_server

SOURCES += main.cpp \
    led.cpp

HEADERS += \
    param.h \
    param_impl.h \
    led.h
