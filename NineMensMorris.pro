QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GraphicPiece.cpp \
    MyGraphicsScene.cpp \
    field.cpp \
    game.cpp \
    gamemap.cpp \
    humanplayer.cpp \
    main.cpp \
    board.cpp \
    graphicline.cpp \
    piece.cpp

HEADERS += \
    GraphicPiece.h \
    MyGraphicsScene.h \
    board.h \
    field.h \
    game.h \
    gamemap.h \
    humanplayer.h \
    lib.h \
    graphicline.h \
    piece.h

FORMS += \
    board.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/binq
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/circle.jpg
