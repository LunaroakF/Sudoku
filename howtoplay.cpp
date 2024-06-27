#include "howtoplay.h"
#include "ui_howtoplay.h"

HowToPlay::HowToPlay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HowToPlay)
{
    this->setFixedSize(573, 415);  //窗口固定大小
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);  //没有最小化按钮
}

HowToPlay::~HowToPlay()
{
    delete ui;
}
