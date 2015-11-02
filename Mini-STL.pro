TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11

SOURCES += main.cpp \
    Cpp/alloc.cpp \
    Cpp/vector.cpp

HEADERS += \
    Header/allocator.h \
    Header/alloc.h \
    Header/construct.h \
    Header/uninitializedFunction.h \
    Header/auto_ptr.h \
    Header/iterator.h \
    Header/type_traits.h \
    Header/vector.h

