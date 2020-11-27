#include "board.h"
#include "ui_board.h"

//TODO: remove later
#include <QDebug>

#include "GraphicPiece.h"

// indeksi za drugu fazu igre, za sad globalne
int moveFrom = -1 , moveTo = -1;

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
    // povezivanje za ispisivanje poruke
    connect(&m_scene, &QGraphicsScene::selectionChanged, this, &Board::writeGameMessage);



    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/

    m_scene.setBackgroundBrush(Qt::gray);

    ui->graphicsView->show();       // nije potrebno vrv, radi bez ovoga
}


Board::~Board()
{
    delete ui;
}

// sve se ovde oko igranja desava, poziva se na klik kvadrata

void Board::onFieldSelection()
{

    if( g->gameState == GAMESTATE::INIT)        // phase1
    {
        for (auto item : m_scene.selectedItems())   // bice jedan item ali ovako treba
        {

            int index = g->gameMap->indexByPos(item->pos());

            if(g->mill_occured && g->gameMap->boardFields[index].isOccupied()) // ako se mill desio onda polje mora da bude slobodno, mozda ne mora provera ovde jer ima posle
            {
                if (g->m_p1.turn())
                {
                    g->removeOpponentsPiece_graphic(g->m_p1, index);    // ne diramo poteze ovde jer ako dospemo ovde mill je napravio p2 i nakon ukljanja figure od p1, p1 treba da postavi svoju novu
                }
                else
                {
                    g->removeOpponentsPiece_graphic(g->m_p2, index);
                }
            }
            else if (!g->mill_occured && !g->gameMap->boardFields[index].isOccupied())  // nema milla i validno je polje onda postavljamo novu figuricu i obrcemo poteze
            {

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
            }


                g->checkPhase1End();                  // provera da li smo dosli do kraja igre

                ui->graphicsView->viewport()->update();

                //qDebug() << index;
                //qDebug() << item->pos();

        }

    }
    else { // ovo je faza 2
        // uzimamo indexe figure koju pomeramo
        // i polja na koje je pomeramo

        for (auto item : m_scene.selectedItems()){
           if (moveFrom == -1){
               moveFrom = g->gameMap->indexByPos(item->pos()); // uzimamo indeks pozicije sa koje pomeramo
           } else if (moveFrom != -1 && moveTo == -1) {
               moveTo = g->gameMap->indexByPos(item->pos()); //uzimamo indeks pozicije na koju pomeramo
               if (g->m_p1.turn()){
                               if(!g->makePlayMove_graphical(g->m_p1, moveFrom, moveTo)){
                                   //ako potez nije validan moramo ponovo da pokupimo indekse
                                   moveTo = -1;
                                   moveFrom = -1;
                               } else {
                                   g->m_p1.changeTurn();
                                   g->m_p2.changeTurn();
                                   ui->graphicsView->viewport()->update();
                               }
               } else {
                               if(!g->makePlayMove_graphical(g->m_p2, moveFrom, moveTo)){
                                   moveTo = -1;
                                   moveFrom = -1;
                               } else {
                                   g->m_p1.changeTurn();
                                   g->m_p2.changeTurn();
                                   ui->graphicsView->viewport()->update();
                               }
               }
               if (g->gameOver()){
                   if (g->getWinner() == FIELDSTATE::PLAYER_1){
                               g->setMesssage("Game over! PLAYER 1 is the winner");
                               return;
                   } else if (g->getWinner() == FIELDSTATE:: PLAYER_2) {
                               g->setMesssage("Game over! PLAYER 2 is the winner");
                               return;
                   }
                }

            }
        } //for

        // resetujemo indekse
        if (moveFrom != -1 && moveTo != -1){
            moveFrom = -1;
            moveTo = -1;
        }
    }
}


void Board::writeGameMessage()
{
    ui->leGameMessage->setText(g->getMessage());
}

