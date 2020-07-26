QT       += core gui widgets

TARGET = json-parser-visulizer
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        AbstractState.cpp \
        AfterNameState.cpp \
        AfterValueState.cpp \
        ArrayState.cpp \
        BeforeValueState.cpp \
        FalseState.cpp \
        InitialState.cpp \
        NameState.cpp \
        NullState.cpp \
        NumberState.cpp \
        ObjectState.cpp \
        StringState.cpp \
        TrueState.cpp \
        Parser.cpp \
        DataTree.cpp \
        datawindow.cpp

HEADERS += \
        mainwindow.h \
        dataTree.h \
        StateDefinitions.h \
        Parser.h \
        datawindow.h

FORMS += \
        mainwindow.ui

VPATH += \
        json-parser \
        json-parser/states

