TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = cam_server

SOURCES += main.cpp \
    led.cpp \
    camera.cpp

HEADERS += \
    param.h \
    param_impl.h \
    led.h \
    camera.h
