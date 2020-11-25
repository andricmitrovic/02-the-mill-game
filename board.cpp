#include "board.h"
#include "ui_board.h"

//TODO: remove later
#include <QDebug>

#include "GraphicPiece.h"



Board::Board(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Board)
    //, gm(new GameMap())
{
    ui->setupUi(this);

    HumanPlayer p1(FIELDSTATE::PLAYER_1, std::string("Marija"));
    HumanPlayer p2(FIELDSTATE::PLAYER_2, std::string("Mrc"));

    std::cout << p1.getName()<< std::endl;
    g = new Game(p1, p2);
    g->setup_graphical(); //prva faza

    /* Postavlja scenu da bude preko celog pogleda, vrlo je cudno ponasanje kad se ovo ne postavi
     * ili neke druge dimenzije, bas nemam ideju sta su mu radili.
     * Ovo prvo bolje sljaka, sa drugim izadju scrollbarovi iz nekog razloga.
     * */
    m_scene.setSceneRect(m_scene.itemsBoundingRect());
    //m_scene.setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    g->gameMap->printMap(m_scene);
    //g->Gamgm->printMap(m_scene);

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

void Board::onFieldSelection()
{
    if( g->gameState == GAMESTATE::INIT)
    {
        for (auto item : m_scene.selectedItems()) {

            int index = g->gameMap->indexByPos(item->pos());

            if (!g->gameMap->boardFields[index].isOccupied()){

                if (g->m_p1.turn())
                {
                    while(!g->makeSetupMove_graphical(g->m_p1, index));
                    g->m_p1.changeTurn();
                    g->m_p2.changeTurn();
                }
                else
                {
                    while(!g->makeSetupMove_graphical(g->m_p2, index));
                    g->m_p1.changeTurn();
                    g->m_p2.changeTurn();
                }

                g->check_phase1_end();
                ui->graphicsView->viewport()->update();


            }

            qDebug() << index;
            qDebug() << item->pos();
        }
    }
    else
    {
        // nece da mi ispise iz buffera pa sam morao da flushujem
        std::cout<<"Phase2 to be implemented...."<<std::endl<<std::flush;
    }
}

