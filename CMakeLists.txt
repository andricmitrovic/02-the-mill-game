cmake_minimum_required(VERSION 3.16)
project(TheMillGame, VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "code/forms/")

set(SOURCES GraphicPiece.cpp MyGraphicsScene.cpp Field.cpp Game.cpp GameAi.cpp GameMap.cpp main.cpp Board.cpp GraphicLine.cpp MultiplayerMenu.cpp LocalGameMenu.cpp Piece.cpp GameServer.cpp MainMenu.cpp Player.cpp TcpClient.cpp TcpServer.cpp Help.cpp ../resources/icons.qrc)
set(HEADERS GraphicPiece.h MyGraphicsScene.h Board.h Field.h Game.h GameAi.h GameMap.h Lib.h GraphicLine.h MultiplayerMenu.h LocalGameMenu.h Piece.h GameServer.h MainMenu.h Player.h TcpClient.h TcpServer.h Help.h)
set(UI board.ui mainmenu.ui multiplayermenu.ui localgamemenu.ui help.ui)

list(TRANSFORM SOURCES PREPEND "code/src/")
list(TRANSFORM HEADERS PREPEND "code/include/")
list(TRANSFORM UI PREPEND "code/forms/")


find_package(Qt5Network REQUIRED)

add_executable(NineMensMorris ${SOURCES} ${HEADERS} ${UI})

qt5_use_modules(NineMensMorris Widgets)

target_link_libraries(NineMensMorris Qt5::Widgets Qt5::Core Qt5::Network ${QT_LIBRARIES})


