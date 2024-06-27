#include "newgame.h"
#include "sudoku.h"
#include "ui_newgame.h"

newgame::newgame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newgame)
{
    this->setFixedSize(216, 273);  //窗口固定大小
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);  //没有最小化按钮
}

newgame::~newgame()
{
    delete ui;
}


