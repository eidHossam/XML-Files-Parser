TEMPLATE = app
TARGET = XML-Files-Parser
INCLUDEPATH += $$quote(E:/FEASU/Fall semester 2023 - on/DS/XML-Files-Parser/inc)
CONFIG += static
QT += core gui

# Input
HEADERS += inc/tree.h \
           inc/Node.h \
           inc/editwindow.h \
           inc/resultwindow.h \
           inc/tree.h \
           inc/XML_Compressor.h \
           inc/XML_Decompressor.h \
           inc/XML_to_json.h \
           inc/XML_Parser.h \
           inc/mainwindow.h \
           inc/TreeNode.h \
           inc/NetworkAnalysis.h \
           inc/GraphType.h \

SOURCES += src/main.cpp \
    src/Node.cpp \
           src/editwindow.cpp \
           src/resultwindow.cpp \
           src/tree.cpp \
           src/TreeNode.cpp \
           src/XML_Parser.cpp \
           src/mainwindow.cpp \
           src/XML_Compressor.cpp \
           src/XML_Decompressor.cpp \
           src/XML_to_json.cpp \
           src/NetworkAnalysis.cpp \
           src/GraphType.cpp \


INCLUDEPATH += "C:/Program Files/Graphviz/include"
LIBS += -L"C:/Program Files/Graphviz/lib" -lgvc

QT += widgets

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
