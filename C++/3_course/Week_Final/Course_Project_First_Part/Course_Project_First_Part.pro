TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread
LIBS +=-lpthread

SOURCES += \
        main.cpp \
    parse.cpp \
    search_server.cpp

HEADERS += \
    iterator_range.h \
    parse.h \
    search_server.h \
    profile.h \
    test_runner.h
