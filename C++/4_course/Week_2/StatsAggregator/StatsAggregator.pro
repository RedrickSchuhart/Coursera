TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    stats_aggregator.cpp \
    aggregator_test.cpp \
    stats_aggregator_test.cpp

HEADERS += \
    test_runner.h \
    stats_aggregator.h
