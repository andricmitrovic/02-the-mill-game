QT       += core gui network widgets

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
    gameai.cpp \
    gamemap.cpp \
    main.cpp \
    board.cpp \
    graphicline.cpp \
    multiplayermenu.cpp \
    piece.cpp \
    gamelocal.cpp \
    gameserver.cpp \
    mainmenu.cpp \
    player.cpp \
    tcpclient.cpp \
    tcpserver.cpp

HEADERS += \
    GraphicPiece.h \
    MyGraphicsScene.h \
    board.h \
    field.h \
    game.h \
    gameai.h \
    gamemap.h \
    lib.h \
    graphicline.h \
    multiplayermenu.h \
    piece.h \
    gamelocal.h \
    gameserver.h \
    mainmenu.h \
    player.h \
    tcpclient.h \
    tcpserver.h

FORMS += \
    board.ui \
    mainmenu.ui \
    multiplayermenu.ui \
    tcpserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/binq
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/circle.jpg
