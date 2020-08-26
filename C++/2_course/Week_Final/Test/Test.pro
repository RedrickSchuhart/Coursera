TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    token.cpp \
    condition_parser.cpp \
    condition_parser_test.cpp

HEADERS += \
    token.h \
    condition_parser.h
