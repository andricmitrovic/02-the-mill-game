#include "board.h"
#include "ui_board.h"

Board::Board(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);


    for(int i = 0; i < 24; i++)
    {
      buttons[i] = new QPushButton("", this);
      buttons[i]->setFixedHeight(50);
      buttons[i]->setFixedWidth(50);
      buttons[i]->setObjectName("empty");
    }

    QGridLayout *boardLayout = new QGridLayout();


    boardLayout->setSpacing(0);



    boardLayout->addWidget(buttons[0], 0, 1);
    boardLayout->addWidget(buttons[1], 0, 7);
    boardLayout->addWidget(buttons[2], 0, 13);

    boardLayout->addWidget(buttons[3], 2, 3);
    boardLayout->addWidget(buttons[4], 2, 7);
    boardLayout->addWidget(buttons[5], 2, 11);

    boardLayout->addWidget(buttons[6], 4, 5);
    boardLayout->addWidget(buttons[7], 4, 7);
    boardLayout->addWidget(buttons[8], 4, 9);

    boardLayout->addWidget(buttons[9], 6, 1);
    boardLayout->addWidget(buttons[10], 6, 3);
    boardLayout->addWidget(buttons[11], 6, 5);
    boardLayout->addWidget(buttons[12], 6, 9);
    boardLayout->addWidget(buttons[13], 6, 11);
    boardLayout->addWidget(buttons[14], 6, 13);

    boardLayout->addWidget(buttons[15], 8, 5);
    boardLayout->addWidget(buttons[16], 8, 7);
    boardLayout->addWidget(buttons[17], 8, 9);

    boardLayout->addWidget(buttons[18], 10, 3);
    boardLayout->addWidget(buttons[19], 10, 7);
    boardLayout->addWidget(buttons[20], 10, 11);

    boardLayout->addWidget(buttons[21], 12, 1);
    boardLayout->addWidget(buttons[22], 12, 7);
    boardLayout->addWidget(buttons[23], 12, 13);


    QHBoxLayout *mainLayout = new QHBoxLayout();

    QSpacerItem *spacer2 = new QSpacerItem(50,100);

    mainLayout->addLayout(boardLayout);
    mainLayout->addSpacerItem(spacer2);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);



    setLayout(mainLayout);

  }


Board::~Board()
{
    delete ui;
}

