QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/src/GameServer.cpp \
    code/src/GraphicLine.cpp \
    code/src/GraphicPiece.cpp \
    code/src/LocalGameMenu.cpp \
    code/src/MainMenu.cpp \
    code/src/MultiplayerMenu.cpp \
    code/src/MyGraphicsScene.cpp \
    code/src/Piece.cpp \
    code/src/Player.cpp \
    code/src/TcpClient.cpp \
    code/src/TcpServer.cpp \
    code/src/Field.cpp \
    code/src/Game.cpp \
    code/src/GameAi.cpp \
    code/src/GameMap.cpp \
    code/src/main.cpp \
    code/src/Board.cpp

HEADERS += \
    code/include/GameServer.h \
    code/include/GraphicLine.h \
    code/include/GraphicPiece.h \
    code/include/LocalGameMenu.h \
    code/include/MainMenu.h \
    code/include/MultiplayerMenu.h \
    code/include/MyGraphicsScene.h \
    code/include/Piece.h \
    code/include/Player.h \
    code/include/TcpClient.h \
    code/include/TcpServer.h \
    code/include/Field.h \
    code/include/Game.h \
    code/include/GameAi.h \
    code/include/GameMap.h \
    code/include/Board.h \
    code/include/Lib.h

FORMS += \
    code/forms/board.ui \
    code/forms/localgamemenu.ui \
    code/forms/mainmenu.ui \
    code/forms/multiplayermenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/binq
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    code/resources/images/circle.jpg \
    code/resources/images/blue_circle.png \
    code/resources/images/red_circle.png

