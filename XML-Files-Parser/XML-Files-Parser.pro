TEMPLATE = app
TARGET = XML-Files-Parser
INCLUDEPATH += $$quote(E:/FEASU/Fall semester 2023 - on/DS/XML-Files-Parser/inc)

# Input
HEADERS += inc/tree.h \
           inc/Node.h \
           inc/tree.h \
           inc/XML_Compressor.h \
           inc/XML_Decompressor.h \
           inc/XML_to_json.h \
           inc/Huffman_Coding.h \
           inc/mainwindow.h \
           inc/TreeNode.h \
           inc/XML_Parser.h
SOURCES += src/main.cpp \
           src/tree.cpp \
           src/TreeNode.cpp \
           src/XML_Parser.cpp \
           src/mainwindow.cpp \
           src/XML_Compressor.cpp \
           src/XML_Decompressor.cpp \
           src/XML_to_json.cpp \
           src/Huffman_Coding.cpp


QT += widgets

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
