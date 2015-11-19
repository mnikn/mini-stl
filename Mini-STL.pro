TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11

SOURCES += main.cpp \

HEADERS += \
    Header\Alloc.h \
    Header/Allocator.h \
    Header/Construct.h \
    Header/Iterator.h \
    Header/Type_traits.h \
    Header/Algorithm.h \
    Header/Uninitialize_funtion.h \
    Header/Vector.h \
    Test/VectorTest.h

