#include "board.h"
#include "ui_board.h"
#include <iostream>

//TODO: remove later
#include <QDebug>

#include "GraphicPiece.h"


Board::Board(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Board)
    , gm(new GameMap())
{
    ui->setupUi(this);

    /* Postavlja scenu da bude preko celog pogleda, vrlo je cudno ponasanje kad se ovo ne postavi
     * ili neke druge dimenzije, bas nemam ideju sta su mu radili.
     * Ovo prvo bolje sljaka, sa drugim izadju scrollbarovi iz nekog razloga.
     * */
    m_scene.setSceneRect(m_scene.itemsBoundingRect());
    //m_scene.setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());


    gm->printMap(m_scene);

    // Connect scene to the view
    ui->graphicsView->setScene(&m_scene);

    // povezivanje scene i glavnog prozora radi registrovanja selekcije kvadrata
    connect(&m_scene, &QGraphicsScene::selectionChanged, this, &Board::onFieldSelection);


    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/

    m_scene.setBackgroundBrush(Qt::gray);

    ui->graphicsView->show();       // nije potrebno vrv, radi bez ovoga
}


Board::~Board()
{
    delete ui;
}

// Ova funkcija bi trebalo da oboji kvadrat kada se selektuje
// stavio sam da boji samo u boju prvog igraca radi isprobavanja
// NE FUNKCIONISE KAKO TREBA -- treba doraditi
void Board::onFieldSelection()
{

    for (auto item : m_scene.selectedItems()) {
        int index = gm->indexByPos(item->pos());
        if (!gm->boardFields[index].isOccupied()){
            gm->boardFields[index].occupy(VALUE::PLAYER_1);
            qDebug() << index;
        }

        //qDebug() << item->pos();
    }
}

