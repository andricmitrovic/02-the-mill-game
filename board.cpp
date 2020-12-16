#include "board.h"
#include "ui_board.h"
#include "GraphicPiece.h"
#include <iostream>

// indeksi za drugu fazu igre, za sad globalne
int moveFrom = -1, moveTo = -1;

Board::Board(QWidget * parent, GAMEMODE gameMode): QMainWindow(parent), ui(new Ui::Board)
{
    ui -> setupUi(this);

    Player* p1 = new Player(FIELDSTATE::PLAYER_1, QString("Marija"));
    Player* p2 = new Player(FIELDSTATE::PLAYER_2, QString("Mrc"));

    // TODO
    if(gameMode==GAMEMODE::LOCAL)
        game = new GameLocal(p1, p2);

    if(gameMode==GAMEMODE::AI)
        game = new GameAI(p1, p2);

    // TODO
    if(gameMode==GAMEMODE::SERVER)
        game = new GameAI(p1, p2);

    m_scene.setSceneRect(0, 0, this -> width(), this -> height());

    game -> getGameMap() -> printMap(m_scene);

    // Connect scene to the view
    ui -> graphicsView -> setScene( & m_scene);

    // povezivanje scene i glavnog prozora radi registrovanja selekcije kvadrata
    connect( & m_scene, & MyGraphicsScene::signalClickedSomething, this, & Board::onFieldSelection);
    // povezivanje za ispisivanje poruke
    connect( & m_scene, & MyGraphicsScene::signalClickedSomething, this, & Board::writeGameMessage);

    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/
    m_scene.setBackgroundBrush(Qt::white);

    ui -> graphicsView -> setFixedSize(ui -> graphicsView -> scene() -> width(), ui -> graphicsView -> scene() -> height());
    ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui -> graphicsView -> show(); // nije potrebno vrv, radi bez ovoga
}

Board::~Board() {
    delete ui;
}

// sve se ovde oko igranja desava, poziva se na klik kvadrata

Game *Board::getGame() {
    return game;
}

void Board::onFieldSelection(QPointF pos) {

    auto item = m_scene.itemAt(pos, QTransform());
    if (item == nullptr)
        return;

    int index = game -> getGameMap() -> indexByPos(item -> pos());

    game -> playMove(game -> getCurrentPlayer(), index, m_scene);

    ui -> graphicsView -> viewport() -> update();
}

void Board::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);

    float scale = this -> height() / SCALE_MULTIPLIER;
    game -> getGameMap() -> setScale(scale);
    game -> getGameMap() -> recalculateOffset();

    m_scene.setSceneRect(-this -> width() / 2 + 6.5 * scale, 0, this -> width(), this -> height());
    ui -> graphicsView -> setFixedSize(ui -> graphicsView -> scene() -> width(), ui -> graphicsView -> scene() -> height());
    ui -> leGameMessage -> setGeometry(this -> width() / 2 - 6.5 * scale, this -> height() - 100, 13 * scale, 30);
    game -> getGameMap() -> printMap(m_scene);
    ui -> graphicsView -> viewport() -> update();
}

void Board::writeGameMessage() {
    ui -> leGameMessage -> setText(game -> getMessage());
}

void Board::test() {

}
