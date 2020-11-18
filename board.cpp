#include "board.h"
#include "ui_board.h"

#include "PlayerPiece.h"

Board::Board(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);

    /* Postavlja scenu da bude preko celog pogleda, vrlo je cudno ponasanje kad se ovo ne postavi
     * ili neke druge dimenzije, bas nemam ideju sta su mu radili.
     * Ovo prvo bolje sljaka, sa drugim izadju scrollbarovi iz nekog razloga.
     * */
    m_scene.setSceneRect(m_scene.itemsBoundingRect());
    //m_scene.setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    // Allocate board markers for pieces and add them to the scene
    m_field.reserve(23*sizeof(PlayerPiece*));
    for( int i=0; i<=23; i++)
    {
        m_field[i] = new PlayerPiece(VALUE::EMPTY);

        m_scene.addItem(m_field[i]);
    }


    // Proba postavljanja player1 i player2 figurica koje se mogu pomerati
    m_player1_pieces.push_back(new PlayerPiece(VALUE::PLAYER_1));
    m_scene.addItem(m_player1_pieces[0]);
    m_player1_pieces[0]->setFlag(QGraphicsItem::ItemIsMovable);
    m_player1_pieces[0]->setFlag(QGraphicsItem::ItemIsSelectable);
    m_player1_pieces[0]->setPos(0, 1*30);

    m_player2_pieces.push_back(new PlayerPiece(VALUE::PLAYER_2));
    m_scene.addItem(m_player2_pieces[0]);
    m_player2_pieces[0]->setFlag(QGraphicsItem::ItemIsMovable);
    m_player2_pieces[0]->setFlag(QGraphicsItem::ItemIsSelectable);
    m_player2_pieces[0]->setPos(0, 7*30);



    // Ovo ce morati pametnije nekako da bi bilo skalabilno u nekom trenutku
    ////////////////////////////////////////////////////
    m_field[0]->setPos(0, 1*30);
    m_field[1]->setPos(0, 7*30);
    m_field[2]->setPos(0, 13*30);

    m_field[3]->setPos(2*30, 3*30);
    m_field[4]->setPos(2*30, 7*30);
    m_field[5]->setPos(2*30, 11*30);

    m_field[6]->setPos(4*30, 5*30);
    m_field[7]->setPos(4*30, 7*30);
    m_field[8]->setPos(4*30, 9*30);

    m_field[9]->setPos(6*30, 1*30);
    m_field[10]->setPos(6*30, 3*30);
    m_field[11]->setPos(6*30, 5*30);
    m_field[12]->setPos(6*30, 9*30);
    m_field[13]->setPos(6*30, 11*30);
    m_field[14]->setPos(6*30, 13*30);

    m_field[15]->setPos(8*30, 5*30);
    m_field[16]->setPos(8*30, 7*30);
    m_field[17]->setPos(8*30, 9*30);

    m_field[18]->setPos(10*30, 3*30);
    m_field[19]->setPos(10*30, 7*30);
    m_field[20]->setPos(10*30, 11*30);

    m_field[21]->setPos(12*30, 1*30);
    m_field[22]->setPos(12*30, 7*30);
    m_field[23]->setPos(12*30, 13*30);
    //////////////////////////////////////////////////////

    // Connect scene to the view
    ui->graphicsView->setScene(&m_scene);

    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/

    m_scene.setBackgroundBrush(Qt::gray);

    ui->graphicsView->show();       // nije potrebno vrv, radi bez ovoga
}


Board::~Board()
{
    delete ui;
}

