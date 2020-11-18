#include "board.h"
#include "ui_board.h"

#include "PlayerPiece.h"

Board::Board(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);

    m_scene.setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    m_pieces.reserve(23*sizeof(PlayerPiece*));

    for( int i=0; i<=23; i++)
    {
        m_pieces[i] = new PlayerPiece();
        m_scene.addItem(m_pieces[i]);

        m_pieces[0]->setPos(0, 0);
    }

    m_pieces[0]->setPos(0, 1*30);
    m_pieces[1]->setPos(0, 7*30);
    m_pieces[2]->setPos(0, 13*30);

    m_pieces[3]->setPos(2*30, 3*30);
    m_pieces[4]->setPos(2*30, 7*30);
    m_pieces[5]->setPos(2*30, 11*30);

    m_pieces[6]->setPos(4*30, 5*30);
    m_pieces[7]->setPos(4*30, 7*30);
    m_pieces[8]->setPos(4*30, 9*30);

    m_pieces[9]->setPos(6*30, 1*30);
    m_pieces[10]->setPos(6*30, 3*30);
    m_pieces[11]->setPos(6*30, 5*30);
    m_pieces[12]->setPos(6*30, 9*30);
    m_pieces[13]->setPos(6*30, 11*30);
    m_pieces[14]->setPos(6*30, 13*30);

    m_pieces[15]->setPos(8*30, 5*30);
    m_pieces[16]->setPos(8*30, 7*30);
    m_pieces[17]->setPos(8*30, 9*30);

    m_pieces[18]->setPos(10*30, 3*30);
    m_pieces[19]->setPos(10*30, 7*30);
    m_pieces[20]->setPos(10*30, 11*30);

    m_pieces[21]->setPos(12*30, 1*30);
    m_pieces[22]->setPos(12*30, 7*30);
    m_pieces[23]->setPos(12*30, 13*30);



    ui->graphicsView->setScene(&m_scene);
    m_scene.setBackgroundBrush(Qt::gray);

    ui->graphicsView->show();       // ne treba vrv


  }


Board::~Board()
{
    delete ui;
}

