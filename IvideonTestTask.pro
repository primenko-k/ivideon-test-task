TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = cam_server

LIBS += -lboost_filesystem -lboost_system -lboost_thread

SOURCES += main.cpp \
    led.cpp \
    camera.cpp \
    pipeline.cpp \
    client.cpp \
    server.cpp \
    commands.cpp

HEADERS += \
    param.h \
    param_impl.h \
    led.h \
    camera.h \
    pipeline.h \
    client.h \
    server.h \
    commands.h

OTHER_FILES += \
    cam_control
