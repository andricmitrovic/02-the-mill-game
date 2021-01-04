#include "code/include/Board.h"
#include <ui_board.h>
#include "code/include/GraphicPiece.h"
#include <iostream>

// indeksi za drugu fazu igre, za sad globalne
int moveFrom = -1, moveTo = -1;

Board::Board(QWidget * parent, GAMEMODE gameMode, QString player1_name, QString player2_name)
    : QMainWindow(parent), ui(new Ui::Board), game_mode(gameMode)
{
    ui -> setupUi(this);

    if(gameMode==GAMEMODE::LOCAL) {
        Player* p1 = new Player(FIELDSTATE::PLAYER_1, player1_name);
        Player* p2 = new Player(FIELDSTATE::PLAYER_2, player2_name);
        game = new Game(p1, p2);

    }

    if(gameMode==GAMEMODE::AI) {
        Player* p1 = new Player(FIELDSTATE::PLAYER_1, player1_name);
        Player* p2 = new Player(FIELDSTATE::PLAYER_2, QString("AI"));
        game = new GameAI(p1, p2);
    }

    if(gameMode==GAMEMODE::SERVER) {

        TcpClient* p1 = new TcpClient(FIELDSTATE::PLAYER_1, player1_name);
        TcpClient* p2 = new TcpClient(FIELDSTATE::EMPTY, QString(""));
        connect(p1, SIGNAL(upd()), this, SLOT(up_scene()));

        game = new GameServer(this, p1, p2);

    }
    m_scene = new MyGraphicsScene();

    m_scene->setSceneRect(0, 0, this -> width(), this -> height());

    game -> getGameMap() -> printMap(m_scene);

    // Connect scene to the view
    ui -> graphicsView -> setScene(m_scene);

    // povezivanje scene i glavnog prozora radi registrovanja selekcije kvadrata
    connect(m_scene, & MyGraphicsScene::signalClickedSomething, this, & Board::onFieldSelection);

    // povezivanje za ispisivanje poruke
    connect(m_scene, & MyGraphicsScene::signalClickedSomething, this, & Board::writeGameMessage);
    connect(m_scene, & MyGraphicsScene::signalClickedSomething, this, & Board::writeErrorMessage);


    /* treba pokusati da stavimo view da bude fullscreen, prvo sto nece manuelno iz designa da ode skroz desno,
     *  a ima i u prozoru neko glupost dole sto blokira deo viewa vrv moze da se iskljuci negde.*/
    m_scene->setBackgroundBrush(Qt::white);

    ui -> graphicsView -> setFixedSize(ui -> graphicsView -> scene() -> width(), ui -> graphicsView -> scene() -> height());
    ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui -> graphicsView -> show(); // nije potrebno vrv, radi bez ovoga
}

Board::~Board() {
    delete ui;
    delete m_scene;
}

// sve se ovde oko igranja desava, poziva se na klik kvadrata

Game *Board::getGame() {
    return game;
}

void Board::onFieldSelection(QPointF pos) {

    auto item = m_scene->itemAt(pos, QTransform());
    if (item == nullptr)
        return;

    int index = game -> getGameMap() -> indexByPos(item -> pos());

    if (this->game_mode == GAMEMODE::SERVER && !static_cast<TcpClient *>(this->game->getPlayer1())->m_gameStart){
        this->getGame()->setGameMessage("Game has not started yet! Looking for another player!");
     }
    else
    {
            game -> playMove(game -> getCurrentPlayer(), index, m_scene);

            if(this->game_mode == GAMEMODE::AI && !this->game->getMillOccured())
            {
                m_scene->update();
                ui -> graphicsView -> viewport() -> update();
                ui-> graphicsView ->repaint();
                game -> playMove(game -> getCurrentPlayer(), index, m_scene);
            }
        }

    ui -> graphicsView -> viewport() -> update();
}

void Board::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);

    float scale = this -> height() / SCALE_MULTIPLIER;
    game -> getGameMap() -> setScale(scale);
    game -> getGameMap() -> recalculateOffset();

    m_scene->setSceneRect(-this -> width() / 2 + 6.5 * scale, 0, this -> width(), this -> height());
    ui -> graphicsView -> setFixedSize(ui -> graphicsView -> scene() -> width(), ui -> graphicsView -> scene() -> height());
    ui -> textBrowser -> setGeometry(this -> width() / 2 - 6.5 * scale, this -> height() - 130, 13 * scale, 90);
    game -> getGameMap() -> printMap(m_scene);
    ui -> graphicsView -> viewport() -> update();
}

void Board::writeGameMessage() {
    if (!game->getGameMessage().isEmpty())
        ui->textBrowser->append(game->getGameMessage());
    game->clearGameMessage();
}

void Board::writeErrorMessage() {
    if (!game->getErrorMessage().isEmpty())
        ui->textBrowser->append("<font color='red'>" + game -> getErrorMessage() + "</font>");
    game->clearErrorMessage();
}

void Board::up_scene()
{

    TcpClient *client1 = static_cast<TcpClient *>(this->game->getPlayer1());
    TcpClient *client2 = static_cast<TcpClient *>(this->game->getPlayer2());

    if (client1->getMove() == GAMEMOVE::INIT){
        game->setGameMessage("GAME HAS STARTED! It's your turn to play!");
        game->changeTurn();
    }
    if (client1->getMove() == GAMEMOVE :: PLACE){
        int index = client1->getToIndex();
        game->makeSetupMove(client2, index, m_scene);
    }

    if (client1->getMove() == GAMEMOVE :: REMOVE){
        game->removeOpponentsPiece(client2, client1->getFromIndex());
    }
    if (client1->getMove() == GAMEMOVE :: MOVE){
        game->makePlayMove(client2, client1->getFromIndex(), client1->getToIndex());
    }
    if (client1->getMove() == GAMEMOVE :: GAMEOVER){
        if (client1->getFromIndex() != -1 && client1->getToIndex() !=-1)
            game->makePlayMove(client2, client1->getFromIndex(),client2->getToIndex());
        else if (client1->getFromIndex() != -1)
            game->removeOpponentsPiece(client2, client1->getFromIndex());
        game->setGameMessage("GAME OVER! YOU LOST THIS ONE!");
    }
    if (client1->m_millOccured)
        game->setMillOccured(true);
    else
        game->changeTurn();

    game -> getGameMap() -> printMap(m_scene);
    ui -> graphicsView -> viewport() -> update();
}

void Board::on_btnHelp_clicked()
{
    help = new Help(this);
    help->show();
}

void Board::on_btnBack_clicked()
{
    emit clickedBack();
}

