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
    Test/VectorTest.h \
    Header/List.h \
    Detail/Vector.impl.h \
    Detail/List.impl.h \
    Test/ListTest.h \
    Header/Deque.h \
    Detail/Deque.impl.h \
    Header/Auto_ptr.h \
    Header/Shared_ptr.h \
    Header/Memory.h \
    Header/String.h \
    Detail/String.impl.h \
    Test/StringTest.h \
    Test/AlgorithmTest.h \
    Test/DequeTest.h

