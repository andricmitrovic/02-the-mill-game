#include "board.h"
#include "ui_board.h"
#include "GraphicPiece.h"
#include <iostream>

// indeksi za drugu fazu igre, za sad globalne
int moveFrom = -1, moveTo = -1;

Board::Board(QWidget * parent): QMainWindow(parent), ui(new Ui::Board)
{
    ui -> setupUi(this);

    HumanPlayer p1(FIELDSTATE::PLAYER_1, QString("Marija"));
    HumanPlayer p2(FIELDSTATE::PLAYER_2, QString("Mrc"));

    game = new GameAI(p1, p2);

    game -> setup_graphical(); //prva faza

    std::pair<int,int> ret = game->max(game->maxDepthAI);
    std::cout<<ret.first<<" "<<ret.second<<std::endl;
    /*std::pair<int,int> ret = botina->max(maxDepthAI);
    std::cout<<ret.first<<" "<<ret.second<<std::endl;*/


    /* Postavlja scenu da bude preko celog pogleda, vrlo je cudno ponasanje kad se ovo ne postavi
     * ili neke druge dimenzije, bas nemam ideju sta su mu radili.
     * Ovo prvo bolje sljaka, sa drugim izadju scrollbarovi iz nekog razloga.
     * */
    //m_scene.setSceneRect(m_scene.itemsBoundingRect());
    //qDebug()<<this->width();
    m_scene.setSceneRect(0, 0, this -> width(), this -> height());

    game -> gameMap -> printMap(m_scene);

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

GameAI * Board::getGame() {
    return game;
}

void Board::onFieldSelection(QPointF pos) {

    auto item = m_scene.itemAt(pos, QTransform());
    if (item == nullptr)
        return;

    int index = game -> gameMap -> indexByPos(item -> pos());

    game -> playMove(game -> getCurrentPlayer(), index, m_scene);

    // ovde kad kliknem kao i kad pocne potez drugog igraca da nadjem najbolji potez za njega
    if(game->m_p1.turn() && !game->mill_occured)
    {
        //zovi bota da uradi potez
        int depth = std::min(game->maxDepthAI, game->boardPieces);
        std::pair<int,int> ret = game->max(depth);
        std::cout<<ret.first<<" "<<ret.second<<std::endl;
    }

    ui -> graphicsView -> viewport() -> update();
}

void Board::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);

    float scale = this -> height() / SCALE_MULTIPLIER;
    game -> gameMap -> setScale(scale);
    game -> gameMap -> recalculateOffset();

    m_scene.setSceneRect(-this -> width() / 2 + 6.5 * scale, 0, this -> width(), this -> height());
    ui -> graphicsView -> setFixedSize(ui -> graphicsView -> scene() -> width(), ui -> graphicsView -> scene() -> height());
    ui -> leGameMessage -> setGeometry(this -> width() / 2 - 6.5 * scale, this -> height() - 100, 13 * scale, 30);
    game -> gameMap -> printMap(m_scene);
    ui -> graphicsView -> viewport() -> update();
}

void Board::writeGameMessage() {
    ui -> leGameMessage -> setText(game -> getMessage());
}

void Board::test() {

}
