TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread
LIBS +=-lpthread

SOURCES += \
        main.cpp

HEADERS += \
    profile.h \
    test_runner.h
