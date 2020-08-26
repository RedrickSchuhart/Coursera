TEMPLATE = app
CONFIG += c++1z
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -O2

SOURCES += \
        main.cpp

HEADERS += \
    test_runner.h \
    profile.h
