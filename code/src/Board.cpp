#include "code/include/Board.h"
#include <ui_board.h>
#include "code/include/GraphicPiece.h"
#include <iostream>

Board::Board(QWidget *parent, GAMEMODE gameMode, QString player1_name, QString player2_name)
        : QMainWindow(parent), ui(new Ui::Board), game_mode(gameMode) {
    ui->setupUi(this);

    if (gameMode == GAMEMODE::LOCAL) {
        Player *p1 = new Player(FIELDSTATE::PLAYER_1, player1_name);
        Player *p2 = new Player(FIELDSTATE::PLAYER_2, player2_name);
        game = new Game(p1, p2, gameMode);
    }

    if (gameMode == GAMEMODE::AI) {
        Player *p1 = new Player(FIELDSTATE::PLAYER_1, player1_name);
        Player *p2 = new Player(FIELDSTATE::PLAYER_2, QString("AI"));
        game = new GameAI(p1, p2, gameMode);
    }

    if (gameMode == GAMEMODE::SERVER) {
        TcpClient *p1 = new TcpClient(FIELDSTATE::PLAYER_1, player1_name);
        TcpClient *p2 = new TcpClient(FIELDSTATE::EMPTY, QString(""));
        connect(p1, SIGNAL(upd()), this, SLOT(up_scene()));

        game = new GameServer(this, p1, p2, gameMode);
    }
    m_scene = new MyGraphicsScene();
    m_scene->setSceneRect(0, 0, this->width(), this->height());
    game->getGameMap()->printMap(m_scene);

    ui->graphicsView->setScene(m_scene);

    // Connect the scene and the main window for registering click signals
    connect(m_scene, &MyGraphicsScene::signalClickedSomething, this, &Board::onFieldSelection);

    // Connect to message signal
    connect(m_scene, &MyGraphicsScene::signalClickedSomething, this, &Board::writeGameMessage);
    connect(m_scene, &MyGraphicsScene::signalClickedSomething, this, &Board::writeErrorMessage);
    connect(this, &Board::sendServerMessage, this, &Board::writeServerMessage);

    m_scene->setBackgroundBrush(Qt::white);

    ui->graphicsView->setFixedSize(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->show();
}

Board::~Board() {
    delete ui;
    delete m_scene;
    delete help;
}

Game *Board::getGame() {
    return game;
}

void Board::onFieldSelection(QPointF pos) {

    auto item = m_scene->itemAt(pos, QTransform());
    if (item == nullptr)
        return;

    int index = game->getGameMap()->indexByPos(item->pos());

    if (this->game_mode == GAMEMODE::SERVER && !static_cast<TcpClient *>(this->game->getPlayer1())->m_gameStart) {
        this->getGame()->setGameMessage("Game has not started yet! Looking for another player!");
    } else {
        game->playMove(game->getCurrentPlayer(), index, m_scene);

        if (this->game_mode == GAMEMODE::AI && !this->game->getMillOccurred()) {
            m_scene->update();
            ui->graphicsView->viewport()->update();
            ui->graphicsView->repaint();
            game->playMove(game->getCurrentPlayer(), index, m_scene);
        }
    }

    ui->graphicsView->viewport()->update();
}

void Board::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    float scale = this->height() / SCALE_MULTIPLIER;
    game->getGameMap()->setScale(scale);
    game->getGameMap()->recalculateOffset();
    m_scene->setSceneRect(-this->width() / 2 + 6.5 * scale, 0, this->width(), this->height());
    ui->graphicsView->setFixedSize(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    ui->textBrowser->setGeometry(this->width() / 2 - 6.5 * scale, this->height() - 130, 13 * scale, 90);
    game->getGameMap()->printMap(m_scene);
    ui->graphicsView->viewport()->update();
}

void Board::writeGameMessage() {
    if (!game->getGameMessage().isEmpty())
        ui->textBrowser->append(game->getGameMessage());
    game->clearGameMessage();
}

void Board::writeErrorMessage() {
    if (!game->getErrorMessage().isEmpty())
        ui->textBrowser->append("<font color='red'>" + game->getErrorMessage() + "</font>");
    game->clearErrorMessage();
}

void Board::writeServerMessage(QString message) {
    ui->textBrowser->append(message);
}

void Board::up_scene() {
    TcpClient *client1 = static_cast<TcpClient *>(this->game->getPlayer1());
    TcpClient *client2 = static_cast<TcpClient *>(this->game->getPlayer2());

    if (client1->getMove() == GAMEMOVE::INIT) {
        game->changeTurn();
    }
    if (client1->getMove() == GAMEMOVE::PLACE) {
        int index = client1->getToIndex();
        game->makeSetupMove(client2, index, m_scene);
        if (game->getBoardPieces() == 0 && !client1->m_millOccured) {
            emit sendServerMessage("The game has been set up! Move your pieces around");
        } else if (!client1->m_millOccured)
            emit sendServerMessage("It's your turn. Choose a field to place your piece!");
    }

    if (client1->getMove() == GAMEMOVE::REMOVE) {
        game->removeOpponentsPiece(client2, client1->getFromIndex());
        emit sendServerMessage("You lost a piece! It's your turn now");
    }

    if (client1->getMove() == GAMEMOVE::MOVE) {
        game->makePlayMove(client2, client1->getFromIndex(), client1->getToIndex());
        if (!client1->m_millOccured)
            emit sendServerMessage("It's your turn. Move one of your pieces");
    }

    if (client1->getMove() == GAMEMOVE::GAMEOVER) {
        if (client1->getFromIndex() != -1 && client1->getToIndex() != -1)
            game->makePlayMove(client2, client1->getFromIndex(), client2->getToIndex());
        else if (client1->getFromIndex() != -1)
            game->removeOpponentsPiece(client2, client1->getFromIndex());
        emit sendServerMessage("GAME OVER! YOU LOST! :(");
    }

    if (client1->m_millOccured)
        game->setMillOccurred(true);
    else
        game->changeTurn();

    game->getGameMap()->printMap(m_scene);
    ui->graphicsView->viewport()->update();
}

void Board::on_btnHelp_clicked() {
    help = new Help(this);
    help->show();
}

void Board::on_btnBack_clicked() {
    emit clickedBack();
}
