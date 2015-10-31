TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11

SOURCES += main.cpp \
    Cpp/alloc.cpp

HEADERS += \
    Header/allocator.h \
    Header/alloc.h \
    Header/construct.h \
    Header/uninitializedFunction.h

