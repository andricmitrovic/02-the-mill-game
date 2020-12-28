cmake_minimum_required(VERSION 3.16)
project(TheMillGame, VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(SOURCES GraphicPiece.cpp MyGraphicsScene.cpp field.cpp game.cpp gameai.cpp gamemap.cpp main.cpp board.cpp graphicline.cpp multiplayermenu.cpp piece.cpp gamelocal.cpp gameserver.cpp mainmenu.cpp player.cpp tcpclient.cpp tcpserver.cpp)
set(HEADERS GraphicPiece.h MyGraphicsScene.h board.h field.h game.h gameai.h gamemap.h lib.h graphicline.h multiplayermenu.h piece.h gamelocal.h gameserver.h mainmenu.h player.h  tcpclient.h tcpserver.h)
set(UI board.ui mainmenu.ui multiplayermenu.ui tcpserver.ui)

find_package(Qt5Network REQUIRED)

add_executable(NineMensMorris ${SOURCES} ${HEADERS} ${UI})
qt5_use_modules(NineMensMorris Widgets)
target_link_libraries(NineMensMorris Qt5::Widgets Qt5::Core Qt5::Network ${QT_LIBRARIES})
