TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    database.cpp \
    date.cpp \
    condition_parser.cpp \
    node.cpp \
    test_runner.cpp \
    token.cpp

HEADERS += \
    database.h \
    date.h \
    condition_parser.h \
    node.h \
    test_runner.h \
    token.h
