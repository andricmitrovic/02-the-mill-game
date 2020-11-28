#include "board.h"
#include "ui_board.h"
//TODO: remove later
#include <QDebug>
#include "GraphicPiece.h"

// indeksi za drugu fazu igre, za sad globalne
int moveFrom = -1, moveTo = -1;

Board::Board(QWidget * parent): QMainWindow(parent), ui(new Ui::Board)
//, gm(new GameMap())
{
    ui -> setupUi(this);

    HumanPlayer p1(FIELDSTATE::PLAYER_1, std::string("Marija"));
    HumanPlayer p2(FIELDSTATE::PLAYER_2, std::string("Mrc"));

    std::cout << p1.getName() << std::endl;
    game = new Game(p1, p2);
    game -> setup_graphical(); //prva faza

    /* Postavlja scenu da bude preko celog pogleda, vrlo je cudno ponasanje kad se ovo ne postavi
     * ili neke druge dimenzije, bas nemam ideju sta su mu radili.
     * Ovo prvo bolje sljaka, sa drugim izadju scrollbarovi iz nekog razloga.
     * */
    m_scene.setSceneRect(m_scene.itemsBoundingRect());
    //m_scene.setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    game -> gameMap -> printMap(m_scene);

    // Connect scene to the view
    ui -> graphicsView -> setScene( & m_scene);

    // povezivanje scene i glavnog prozora radi registrovanja selekcije kvadrata
    connect( & m_scene, & QGraphicsScene::selectionChanged, this, & Board::onFieldSelection);
    // povezivanje za ispisivanje poruke
    connect( & m_scene, & QGraphicsScene::selectionChanged, this, & Board::writeGameMessage);

    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/
    m_scene.setBackgroundBrush(Qt::gray);

    ui -> graphicsView -> show(); // nije potrebno vrv, radi bez ovoga
}

Board::~Board() {
    delete ui;
}

// sve se ovde oko igranja desava, poziva se na klik kvadrata

Game * Board::getGame() {
    return game;
}

void Board::onFieldSelection() {
    if (game -> gameState == GAMESTATE::INIT) {
        for (auto item: m_scene.selectedItems()) {
            int index = game -> gameMap -> indexByPos(item -> pos());

            if (game -> mill_occured && game -> gameMap -> getBoardFields()[index].isOccupied()) { // ako se mill desio onda polje mora da bude slobodno, mozda ne mora provera ovde jer ima posle
                if (game -> m_p1.turn()) {
                    game -> removeOpponentsPiece_graphic(game -> m_p1, index); // ne diramo poteze ovde jer ako dospemo ovde mill je napravio p2 i nakon ukljanja figure od p1, p1 treba da postavi svoju novu
                } else {
                    game -> removeOpponentsPiece_graphic(game -> m_p2, index);
                }
            } else if (!game -> mill_occured && !game -> gameMap -> getBoardFields()[index].isOccupied()) { // nema milla i validno je polje onda postavljamo novu figuricu i obrcemo poteze
                if (game -> m_p1.turn()) {
                    while (!game -> makeSetupMove_graphical(game -> m_p1, index));
                    game -> changeTurn();
                } else {
                    while (!game -> makeSetupMove_graphical(game -> m_p2, index));
                    game -> changeTurn();
                }
            }

            game -> checkPhase1End(); // provera da li smo dosli do kraja igre
            ui -> graphicsView -> viewport() -> update();
        }
    } else { // ovo je faza 2
        // uzimamo indexe figure koju pomeramo
        // i polja na koje je pomeramo

        for (auto item: m_scene.selectedItems()) {
            if (moveFrom == -1) {
                moveFrom = game -> gameMap -> indexByPos(item -> pos()); // uzimamo indeks pozicije sa koje pomeramo
            } else if (moveFrom != -1 && moveTo == -1) {
                moveTo = game -> gameMap -> indexByPos(item -> pos()); //uzimamo indeks pozicije na koju pomeramo
                if (game -> m_p1.turn()) {
                    if (!game -> makePlayMove_graphical(game -> m_p1, moveFrom, moveTo)) {
                        //ako potez nije validan moramo ponovo da pokupimo indekse
                        moveTo = -1;
                        moveFrom = -1;
                    } else {
                        game -> changeTurn();
                        ui -> graphicsView -> viewport() -> update();
                    }
                } else {
                    if (!game -> makePlayMove_graphical(game -> m_p2, moveFrom, moveTo)) {
                        moveTo = -1;
                        moveFrom = -1;
                    } else {
                        game -> changeTurn();
                        ui -> graphicsView -> viewport() -> update();
                    }
                }
                if (game -> gameOver()) {
                    if (game -> getWinner() == FIELDSTATE::PLAYER_1) {
                        game -> setMesssage("Game over! PLAYER 1 is the winner");
                        return;
                    } else if (game -> getWinner() == FIELDSTATE::PLAYER_2) {
                        game -> setMesssage("Game over! PLAYER 2 is the winner");
                        return;
                    }
                }
            }
        }

        // resetujemo indekse
        if (moveFrom != -1 && moveTo != -1) {
            moveFrom = -1;
            moveTo = -1;
        }
    }
}

void Board::writeGameMessage() {
    ui -> leGameMessage -> setText(game -> getMessage());
}
