#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QHBoxLayout>
#include <QPixmap>

#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QMainWindow
{
    Q_OBJECT
    QPushButton *buttons[24];


public:
    Board(QWidget *parent = nullptr);
    ~Board();

private:
    Ui::Board *ui;
    std::vector<QGraphicsItem*> m_field;
    std::vector<QGraphicsItem*> m_player1_pieces;            // ovo moze u player klasi da stoji, prototip za sad samo
    std::vector<QGraphicsItem*> m_player2_pieces;            // ovo moze u player klasi da stoji, prototip za sad samo
    QGraphicsScene m_scene;
};
#endif // BOARD_H
