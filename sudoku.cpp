#include "sudoku.h"
#include "ui_sudoku_mainform.h"
#include <QWidget>
#include <QKeyEvent>  //键盘事件监听
#include <QMouseEvent>  //鼠标事件监听
#include <QThread>  //多线程(没用上)
#include <QDebug>  //调试用
#include <QString>  //QT字符串
#include <QFileDialog>  //文件
#include <QMessageBox>  //提示窗
#include <QTimer>  //时钟周期
#include <QRandomGenerator>  //随机数生成

void Sudoku::keyPressEvent(QKeyEvent *event)  //从键盘读取当前候选数字
{
    switch (event->key()) {
    case Qt::Key_1:
        ui->NumberDisplay->setText("1");
        break;
    case Qt::Key_2:
        ui->NumberDisplay->setText("2");
        break;
    case Qt::Key_3:
        ui->NumberDisplay->setText("3");
        break;
    case Qt::Key_4:
        ui->NumberDisplay->setText("4");
        break;
    case Qt::Key_5:
        ui->NumberDisplay->setText("5");
        break;
    case Qt::Key_6:
        ui->NumberDisplay->setText("6");
        break;
    case Qt::Key_7:
        ui->NumberDisplay->setText("7");
        break;
    case Qt::Key_8:
        ui->NumberDisplay->setText("8");
        break;
    case Qt::Key_9:
        ui->NumberDisplay->setText("9");
        break;
    default:
        //ui->NumberDisplay->setText("");
        break;
    }
    //MyThread *thread = new MyThread;
    //thread->start();
}

void Sudoku::SelectedASolt(int x,int y)  //高亮提示方块
{
    //x = 5 ; y = 5
    //Cube55
    //15 25 35 45 55 65 75 85 95
    //51 52 53 54 55 56 57 58 59
    //转换  //xy
    //04 14 24 34 44 54 64 74 84
    //40 41 42 43 44 45 46 47 48
    //[4,4]
    if(x<1||x>9||y<1||y>9)
    {
        ClearASolt();
        return;
    }
    ClearASolt();

    QString cubeString = "cube";
    QString dataX = QString::number(x);
    QString dataY = QString::number(y);
    QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
    if(button->text()!="")
    {
        QString currentNumber = button->text();
        for(int i = 1;i<=9;i++)//清空先前的
        {
            for(int j = 1;j<=9;j++)
            {
                QString cubeString = "cube";
                QString dataX = QString::number(i);
                QString dataY = QString::number(j);
                //qDebug()<<cubeString + dataX + dataY;
                QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
                if(button->text()==currentNumber)
                    button->setAutoFillBackground(true);
            }
        }
        return;
    }

    for(int i = 1;i<=9;i++)
    {
        QString cubeString = "cube";
        QString dataX = QString::number(x);
        QString dataY = QString::number(i);
        //qDebug()<<cubeString + dataX + dataY;
        QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
        button->setAutoFillBackground(true);
    }

    for(int i = 1;i<=9;i++)
    {
        QString cubeString = "cube";
        QString dataX = QString::number(i);
        QString dataY = QString::number(y);
        QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
        button->setAutoFillBackground(true);
    }
}

void Sudoku::ClearASolt()  //熄灭所有提示方块
{
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QString cubeString = "cube";
            QString dataX = QString::number(i);
            QString dataY = QString::number(j);
            QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
            button->setAutoFillBackground(false);
        }
    }
}

void Sudoku::ClearANumber()  //关卡重置
{
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QString cubeString = "cube";
            QString dataX = QString::number(i);
            QString dataY = QString::number(j);
            QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
            button->setText("");
        }
    }
    this->setWindowTitle(mainWindowsTitle + " - "+ "请稍后...");
}

void Sudoku::SetButtonNumberWithAnswer(int x,int y, int data)  //给格子设置数字
{
    QString cubeString = "cube";
    QString dataX = QString::number(x);
    QString dataY = QString::number(y);
    QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
    if(button->text()=="")
    {
        button->setMinimumHeight(data);
        button->setText(QString::number(data));
    }
    if(data==0)
    {
        button->setMinimumHeight(0);
        button->setText("");
    }
}

bool Sudoku::HasRepeat(QString solt[],int lenth)  //传进来的字符串数组有没有重复的元素
{
    for(int i = 0; i < lenth ; i++)
    {
        QString current = solt[i];
        if(current == "")
        {
            continue;
        }
        for(int j = i+1;j<lenth;j++)
        {
            if(j == lenth)
            {
                break;
            }
            if(solt[j] == "")
            {
                continue;
            }
            if(solt[j]==current)
            {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::IsSafe(int x,int y)  //检查数独可行性(行列宫无重复)
{
    if(IsSafeInCube(x,y)&&IsSafeInHorizontal(x,y)&&IsSafeInVertical(x,y))
        return true;
    else
        return false;
}

bool Sudoku::IsSafeInVertical(int x, int y)  //检查数独可行性(列无重复)
{
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 1;i<=9;i++)
    {
        QString cubeString = "cube";
        QString dataX = QString::number(x);
        QString dataY = QString::number(i);
        QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
        if(button->text()!="")
            currentNumber[i-1] = button->text();
    }
    return !HasRepeat(currentNumber,9);
}

bool Sudoku::IsSafeInHorizontal(int x, int y)  //检查数独可行性(行无重复)
{
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 1;i<=9;i++)
    {
        QString cubeString = "cube";
        QString dataX = QString::number(i);
        QString dataY = QString::number(y);
        QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
        if(button->text()!="")
            currentNumber[i-1] = button->text();
    }
    return !HasRepeat(currentNumber,9);
}

bool Sudoku::IsSafeInCube(int x, int y)  //检查数独可行性(宫无重复)
{
    int HasMore = x%3;
    int soltNumberH = x/3;
    if(HasMore)
    {
        soltNumberH++;
    }
    HasMore = y%3;
    int soltNumberV = y/3;
    if(HasMore)
    {
        soltNumberV++;
    }
    //qDebug()<<soltNumberH<<","<<soltNumberV;
    QString TargetX[3]={"1","2","3"};
    QString TargetY[3]={"1","2","3"};
    for(int i = 0;i<3;i++)
    {
        TargetX[i] = QString::number(TargetX[i].toInt()+(soltNumberH-1)*3);
        TargetY[i] = QString::number(TargetY[i].toInt()+(soltNumberV-1)*3);
        //qDebug()<<TargetX[i]<<","<<TargetY[i];
    }
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            QString cubeString = "cube";
            QString dataX = QString::number(TargetX[i].toInt());
            QString dataY = QString::number(TargetY[j].toInt());
            QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
            if(button->text()!="")
                currentNumber[3*i+j] = button->text();
            //qDebug()<<dataX<<","<<dataY;
        }
    }

    return !HasRepeat(currentNumber,9);

}

bool Sudoku::IsButtonEmpty(int x, int y)  //检查此坐标的单元格是否存在数据
{
    QString cubeString = "cube";
    QString dataX = QString::number(x);
    QString dataY = QString::number(y);
    QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
    if(button->text()=="")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Sudoku::HideAnswer(int x, int y)  //删除表面数据，min内存储的答案不删除
{
    QString cubeString = "cube";
    QString dataX = QString::number(x);
    QString dataY = QString::number(y);
    QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
    button->setText("");
}

void Sudoku::GenerateLevel(int difficulty)//难度1-81 空格子数量 随机生成关卡
{
    ClearANumber();
    this->update();
    for(int i = 1;i<=9;i++)
    {
        int ran1 = QRandomGenerator::global()->bounded(1, 4 + 1);
        int ran2 = QRandomGenerator::global()->bounded(1, 4 + 1);
        SetButtonNumberWithAnswer(ran1,ran2,i);
    }
    SolveSudoku();
    for(int i = 0; i<difficulty;i++)
    {
        int ran1 = QRandomGenerator::global()->bounded(1,9+1);
        int ran2 = QRandomGenerator::global()->bounded(1,9+1);
        if(!IsButtonEmpty(ran1,ran2))
        {
            HideAnswer(ran1,ran2);
        }
        else
        {
            i--;
            continue;
        }
    }
    EmptyLeft = difficulty;
}

bool Sudoku::SolveSudoku()  //生成数独
{
    QString empty = FindEmpty();
    if(empty == "")
    {
        return true;
    }
    //qDebug()<<empty;
    int position = empty.toInt();
    int y = position%10;
    int x = (position-y)/10;
    //qDebug()<<x<<","<<y;
    for(int i = 1;i<=9;i++)
    {
        SetButtonNumberWithAnswer(x,y,i);
        if(IsSafe(x,y))
        {
            if(SolveSudoku())
            {
                return true;
            }
            SetButtonNumberWithAnswer(x,y,0);
        }
        else
        {
            SetButtonNumberWithAnswer(x,y,0);
        }
    }
    return false;
}

QString Sudoku::FindEmpty()  //顺序查找空的单元格并返回坐标 例如x=3，y=4返回"34"
{
    QString result = "";
    QString cubeString = "cube";
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1; j<=9;j++)
        {
            QString dataX = QString::number(i);
            QString dataY = QString::number(j);
            QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
            if(button->text()=="")
            {
                result = dataX + dataY;
                return result;
                //qDebug()<<result;
            }
        }
    }
    return result;
}

void Sudoku::ChooseNewbee()  //难度选择萌新
{
    qDebug()<<"萌新";//27
    newgamewindow->close();
    //newgamewindow = new newgame;
    GenerateLevel(27);
    score = NewBeeMaxScore+1;
    this->setWindowTitle(mainWindowsTitle + " - " + "萌新");
    TimeCost = 0;
    timer->start(1000);
    updateClock();
}

void Sudoku::ChooseHigher()  //难度选择高手
{
    qDebug()<<"高手";//38 45  折中 //41
    newgamewindow->close();
    //newgamewindow = new newgame;
    GenerateLevel(41);
    score = HigherMaxScore+1;
    this->setWindowTitle(mainWindowsTitle + " - " + "高手");
    TimeCost = 0;
    timer->start(1000);
    updateClock();
}

void Sudoku::ChooseMaster()  //难度选择大师
{
    qDebug()<<"大师"; // 53
    newgamewindow->close();
    //newgamewindow = new newgame;
    GenerateLevel(53);
    score = MasterMaxScore+1;
    this->setWindowTitle(mainWindowsTitle + " - " + "大师");
    TimeCost = 0;
    timer->start(1000);
    updateClock();
}

void Sudoku::onButtonClicked()//鼠标左键单元格，插入数字用
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString NowTheNumber = ui->NumberDisplay->text();
        if(button->text()=="")
        {
            if(NowTheNumber == QString::number(button->minimumHeight()))
            {
                button->setText(NowTheNumber);
                EmptyLeft--;
                if(EmptyLeft==0)
                {
                    timer->stop();
                    this->setWindowTitle(this->windowTitle()+" - " + "完成: " + QString::number(TimeCost) + "秒");
                    QString Congrua = "成功通关\n您的成绩如下:\n" + ui->Score->text() + "分！\n" + "通关用时:\n"
                                      + QString::number(TimeCost) + "秒!";
                    QMessageBox::information(NULL,"恭喜", Congrua, QMessageBox::Ok);
                }
            }
            else if(timer->isActive())
            {
                timer->stop();
                ui->Score->setStyleSheet("color: red");
                ScoreDetal(-9);
                timer->start();
            }
        }
    }
}

void Sudoku::updateClock()  //时钟周期更新
{
    ui->Score->setStyleSheet(ui->ScoreBoard->styleSheet());
    TimeCost++;
    ScoreDetal(-1);
}

void Sudoku::ScoreDetal(int s)  //用于修改分数
{
    if(score<=0)
    {
        return;
    }
    score+=s;
    if(score<=0)
    {
        ui->Score->setText(QString::number(0));
        timer->stop();
        ui->Score->setStyleSheet("color: red");
        QMessageBox::critical(NULL,"你输了","游戏失败", QMessageBox::Ok);
    }
    else
    {
        ui->Score->setText(QString::number(score));
    }
}

void Sudoku::mousePressEvent(QMouseEvent *event)  //右键提示监听
{
    //12，82
    //409，478
    //397，396
    //9*44 = 396
    int mouse_x = event->position().x();
    int mouse_y = event->position().y();
    //qDebug()<<mouse_x<<","<<mouse_y;
    int y = (mouse_x-12)/44+1;
    int x = (mouse_y-82)/44+1;
    //qDebug()<<x<<","<<y;
    SelectedASolt(x,y);
    //qDebug()<<x<<";"<<y<<IsSafe(x,y);
    //qDebug()<<IsSafe(x,y);
}

void Sudoku::mouseReleaseEvent(QMouseEvent *event)  //右键松开清空提示
{
    ClearASolt();
}

Sudoku::Sudoku(QWidget *parent)  //Classui构造
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    this->setFixedSize(421, 500);
    ui->setupUi(this);
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QString cubeString = "cube";
            QString dataX = QString::number(i);
            QString dataY = QString::number(j);
            //qDebug()<<cubeString + dataX + dataY;
            QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
            connect(button, &QPushButton::pressed, this, &Sudoku::onButtonClicked);
        }
    }
    timer = new QTimer(this);
    //绑定新窗口的按钮调用的函数
    connect(timer, &QTimer::timeout, this, &Sudoku::updateClock);
    connect(newgamewindow->ui->newbee,SIGNAL(clicked()),this,SLOT(ChooseNewbee()));
    connect(newgamewindow->ui->higher,SIGNAL(clicked()),this,SLOT(ChooseHigher()));
    connect(newgamewindow->ui->master,SIGNAL(clicked()),this,SLOT(ChooseMaster()));
    connect(newgamewindow->ui->diy,SIGNAL(clicked()),this,SLOT(FileImport()));
    //timer->start(1000);
    //updateClock();

}

Sudoku::~Sudoku()  //析构
{
    delete ui;
}

void Sudoku::FileImport()  //以文件形式导入关卡
{

    QString fileName = QFileDialog::getOpenFileName(nullptr, QObject::tr("打开已存储的关卡"), "", QObject::tr("LRX存档文件 (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    //qDebug() << fileName;
    QTextStream in(&file);
    QChar ch;
    try
    {
        for(int i = 1;i<=9&&!in.atEnd();i++)
        {
            for(int j = 1;j<=9&&!in.atEnd();j++)
            {
                in >> ch;
                if (in.status() != QTextStream::Ok) {
                    break;
                }
                //qDebug() << ch;
                QString cubeString = "cube";
                QString dataX = QString::number(i);
                QString dataY = QString::number(j);
                //qDebug()<<cubeString + dataX + dataY;
                QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
                if (button == nullptr) {
                    throw std::runtime_error("按钮空指针");
                }
                button->setText(ch);
            }
        }
        in>>ch;//去换行符
        EmptyLeft = 0;
        this->setWindowTitle(mainWindowsTitle + " - " + "自定义关卡");
        while(!in.atEnd())
        {
            QChar x,y;
            in >> x >> y;
            if (in.status() != QTextStream::Ok) {
                break;
            }
            QString cubeString = "cube";
            //qDebug()<<cubeString + x + y;
            QPushButton *button = findChild<QPushButton*>(cubeString + x + y);
            if (button == nullptr) {
                throw std::runtime_error("按钮空指针");
            }
            EmptyLeft++;
            button->setMinimumHeight(button->text().toInt());
            button->setText("");
        }
        file.close();

        timer->stop();
    }
    catch (...)
    {
        file.close();
        ClearANumber();
        EmptyLeft = 0;
        timer->stop();
        ui->Score->setText("等待游戏...");
        this->setWindowTitle(mainWindowsTitle + " - "+ "错误");
        QMessageBox::critical(NULL,  "错误",  "文件读取失败", QMessageBox::Ok);
        this->setWindowTitle(mainWindowsTitle);

        return;
    }
    newgamewindow->close();
    QMessageBox::information(NULL,  "完成",  "文件导入关卡成功", QMessageBox::Ok);
    TimeCost = 0;
    score = MaxScore+1;
    timer->start(1000);
    updateClock();
}

void Sudoku::on_pushButton_2_clicked()  //新关卡难度选择
{
    newgamewindow->show();
}

void Sudoku::on_howtoplay_clicked()
{
    newteachwindow->show();
}
