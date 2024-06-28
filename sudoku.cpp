#include "sudoku.h"
#include "ui_sudoku_mainform.h"
#include <QWidget>  //图形界面
#include <QKeyEvent>  //键盘事件监听
#include <QMouseEvent>  //鼠标事件监听
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
        break;
    }
}

void Sudoku::SelectedASolt(int x,int y)  //高亮提示方块
{
    ClearASolt();
    if(x<1||x>9||y<1||y>9)
    {
        return;  //参数非法返回
    }
    QPushButton *button = FindButtonByPosition(x,y);
    //如果这个方块 没有数字 那么让它的 横轴纵轴 全部高亮 ↓
    if(button->text()!="")
    {
        QString currentNumber = button->text();
        for(int i = 1;i<=9;i++)
        {
            for(int j = 1;j<=9;j++)
            {
                QPushButton *button = FindButtonByPosition(i,j);
                if(button->text()==currentNumber)
                    button->setAutoFillBackground(true);
            }
        }
    }
    else  //如果这个方块 有数字 那么让其他与之 数值相同 的方块全部高亮 ↓
    {
        for(int i = 1;i<=9;i++)
        {
            QPushButton *button = FindButtonByPosition(x,i);
            button->setAutoFillBackground(true);
        }

        for(int i = 1;i<=9;i++)
        {
            QPushButton *button = FindButtonByPosition(i,y);
            button->setAutoFillBackground(true);
        }
    }
}

void Sudoku::ClearASolt()  //顺序熄灭所有提示方块
{
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QPushButton *button = FindButtonByPosition(i,j);
            button->setAutoFillBackground(false);
        }
    }
}

void Sudoku::ClearANumber()  //关卡重置 让所有方块已存储的内容清空
{
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QPushButton *button = FindButtonByPosition(i,j);
            button->setText("");
            button->setMinimumHeight(0);
        }
    }
    this->setWindowTitle(mainWindowsTitle + " - "+ "请稍后...");
}

void Sudoku::SetButtonNumberWithAnswer(int x,int y, int data)  //给格子设置数字，data传入0则清空
{
    QPushButton *button = FindButtonByPosition(x,y);
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

bool Sudoku::HasRepeat(QString solt[],int lenth)  //传进来的字符串数组有没有重复的元素，有返回true 无返回false
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
    if(IsSafeInCube(x,y)&&IsSafeInHorizontal(y)&&IsSafeInVertical(x))
        return true;
    else
        return false;
}

bool Sudoku::IsSafeInVertical(int x)  //检查数独可行性(列无重复)
{
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 1;i<=9;i++)
    {
        QPushButton *button = FindButtonByPosition(x,i);
        if(button->text()!="")
            currentNumber[i-1] = button->text();  //for从1开始 字符串数组从0开始
    }
    return !HasRepeat(currentNumber,9);
}

bool Sudoku::IsSafeInHorizontal(int y)  //检查数独可行性(行无重复)
{
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 1;i<=9;i++)
    {
        QPushButton *button = FindButtonByPosition(i,y);
        if(button->text()!="")
            currentNumber[i-1] = button->text();  //for从1开始，字符串数组从0开始
    }
    return !HasRepeat(currentNumber,9);
}

bool Sudoku::IsSafeInCube(int x, int y)  //检查数独可行性(宫无重复)
{
    //将传入的 x*y = 9*9 的坐标转化为 soltNumberH*soltNumberV = 3*3 的坐标以表示3*3的宫
    //例如传入 x=4; y=1 计算后得到 soltNumberH=2; soltNumberV=1 以示坐标为(2，1)的宫
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
    //计算得到的宫的3个横轴纵轴坐标
    //例如上面传入后得到的(2,1)计算后得到TargetX={"4","5","6"}  TargetY={"1","2","3"}
    QString TargetX[3]={"1","2","3"};
    QString TargetY[3]={"1","2","3"};
    for(int i = 0;i<3;i++)
    {
        TargetX[i] = QString::number(TargetX[i].toInt()+(soltNumberH-1)*3);
        TargetY[i] = QString::number(TargetY[i].toInt()+(soltNumberV-1)*3);
        //qDebug()<<TargetX[i]<<","<<TargetY[i];
    }
    //将这个宫里的9个值拷到下面这个字符串数组里
    QString currentNumber[9] = {"","","","","","","","",""};
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            QPushButton *button = FindButtonByPosition(TargetX[i].toInt(),TargetY[j].toInt());
            if(button->text()!="")
                currentNumber[3*i+j] = button->text();
            //qDebug()<<dataX<<","<<dataY;
        }
    }
    return !HasRepeat(currentNumber,9);
}

bool Sudoku::IsButtonEmpty(int x, int y)  //检查此坐标的单元格是否不存在数据 不存在返回true 存在返回false
{
    QPushButton *button = FindButtonByPosition(x,y);
    if(button->text()=="")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Sudoku::HideAnswer(int x, int y)  //隐藏 删除按钮表面数据，min内存储的答案不删除
{
    QPushButton *button = FindButtonByPosition(x,y);
    button->setText("");
}

void Sudoku::GenerateLevel(int difficulty)//难度1-81 空格子数量 随机生成关卡
{
    ClearANumber();
    for(int i = 1;i<=9;i++)
    {
        //随机取(1,1)到(4,4)的格子进行顺序写入1-9
        int ran1 = QRandomGenerator::global()->bounded(1, 4 + 1);
        int ran2 = QRandomGenerator::global()->bounded(1, 4 + 1);
        SetButtonNumberWithAnswer(ran1,ran2,i);
    }
    //让计算机解这个已经写了9个数字的数独
    SolveSudoku();
    //随机隐藏difficulty个格子
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

bool Sudoku::SolveSudoku()  //回溯解数独
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

QPushButton *Sudoku::FindButtonByPosition(int x, int y)  //根据坐标返回按钮地址
{
    QString cubeString = "cube";
    QString dataX = QString::number(x);
    QString dataY = QString::number(y);
    //qDebug()<<cubeString + dataX + dataY;
    QPushButton *button = findChild<QPushButton*>(cubeString + dataX + dataY);
    return button;
}

QString Sudoku::FindEmpty()  //顺序查找空的单元格并返回坐标 例如x=3，y=4返回 "34"
{
    QString result = "";
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1; j<=9;j++)
        {
            QPushButton *button = FindButtonByPosition(i,j);
            if(button->text()=="")
            {
                result = QString::number(i) + QString::number(j);
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
    TimeCost--;
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
    TimeCost--;
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
    TimeCost--;
    timer->start(1000);
    updateClock();
}

void Sudoku::onButtonClicked()//鼠标左键单元格，插入数字用
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());  //获取是哪一个按钮按的
    if (button)
    {
        QString NowTheNumber = ui->NumberDisplay->text();  //存储当前候选数字
        if(button->text()=="")  //如果这个格子没有数字
        {
            if(NowTheNumber == QString::number(button->minimumHeight()))  //与存在minimumHeight里的答案对比
            {
                //对比成功 写入数据到按钮
                button->setText(NowTheNumber);
                EmptyLeft--;
                if(EmptyLeft==0  && score!=0)
                {
                    //如果全部解完了
                    timer->stop();
                    this->setWindowTitle(this->windowTitle()+" - " + "完成: " + QString::number(TimeCost) + "秒");
                    QString Congrua = "成功通关\n您的成绩如下:\n" + ui->Score->text() + "分！\n" + "通关用时:\n" + QString::number(TimeCost) + "秒!";
                    QMessageBox::information(NULL,"恭喜", Congrua, QMessageBox::Ok);
                }
            }
            else if(timer->isActive())  //如果游戏正在进行中
            {
                //扣分
                timer->stop();
                ui->Score->setStyleSheet("color: red");
                ScoreDetal(-9);
                if(score != 0)
                {
                    timer->start();
                }
            }
        }
    }
}

void Sudoku::updateClock()  //时钟周期更新
{
    ui->Score->setStyleSheet(ui->ScoreBoard->styleSheet());  //变成默认颜色
    TimeCost++;  //时间计时++
    ScoreDetal(-1);  //减一分
}

void Sudoku::ScoreDetal(int s)  //用于修改分数
{
    if(score<=0) //没分了还怎么扣
    {
        return;
    }
    score+=s;
    if(score<=0)
    {
        score = 0;
        ui->Score->setText(QString::number(0));
        timer->stop();
        ui->Score->setStyleSheet("color: red");
        this->setWindowTitle(this->windowTitle()+" - " + "失败");
        QMessageBox::critical(NULL,"你输了","游戏失败", QMessageBox::Ok);
    }
    else
    {
        ui->Score->setText(QString::number(score));
    }
}

void Sudoku::mousePressEvent(QMouseEvent *event)  //右键提示监听
{
    //12，82  游戏场景左上角坐标
    //409，478  游戏场景右下角坐标
    //397，396
    //9*44 = 396  一个格子占44*44个单位面积
    if(event->button() == Qt::RightButton)
    {
        //获取鼠标 XY 坐标
        int mouse_x = event->position().x();
        int mouse_y = event->position().y();
        //qDebug()<<mouse_x<<","<<mouse_y;
        //计算为单元格9*9坐标
        int y = (mouse_x-12)/44+1;
        int x = (mouse_y-82)/44+1;
        //qDebug()<<x<<","<<y;
        SelectedASolt(x,y);
    //qDebug()<<x<<";"<<y<<IsSafe(x,y);
    //qDebug()<<IsSafe(x,y);
    }
}

void Sudoku::mouseReleaseEvent(QMouseEvent *event)  //右键松开清空提示
{
    ClearASolt();
}

Sudoku::Sudoku(QWidget *parent)  //Classui构造
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    this->setFixedSize(421, 500);  //固定窗口大小
    ui->setupUi(this);
    //把 9*9=81个格子(以按钮QPushButton充当)Clicked()信号 全部绑定到onButtonClicked函数
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=9;j++)
        {
            QPushButton *button = FindButtonByPosition(i,j);
            connect(button, &QPushButton::pressed, this, &Sudoku::onButtonClicked);
        }
    }
    timer = new QTimer(this);  //初始化时钟

    connect(timer, &QTimer::timeout, this, &Sudoku::updateClock);  //时钟一周期运行updateClock()函数
    //绑定新窗口的按钮调用的函数
    connect(newgamewindow->ui->newbee,SIGNAL(clicked()),this,SLOT(ChooseNewbee()));  //难度窗口选择 萌新 按钮执行 ChooseNewbee()
    connect(newgamewindow->ui->higher,SIGNAL(clicked()),this,SLOT(ChooseHigher()));  //难度窗口选择 高手 按钮执行 ChooseHigher()
    connect(newgamewindow->ui->master,SIGNAL(clicked()),this,SLOT(ChooseMaster()));  //难度窗口选择 大师 按钮执行 ChooseMaster()
    connect(newgamewindow->ui->diy,SIGNAL(clicked()),this,SLOT(FileImport()));  //难度窗口选择 自定义 按钮执行 FileImport()
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
        //没选文件直接叉了
        return;
    }
    QFile file(fileName);

    try
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //如果以 只读 文本 的形式无法打开这个文件 那么
            throw std::runtime_error("打开失败");
        }
        //qDebug() << fileName;
        QTextStream in(&file);
        QChar ch;
        //顺序读9*9=81个数字进去到格子里
        for(int i = 1;i<=9&&!in.atEnd();i++)
        {
            for(int j = 1;j<=9&&!in.atEnd();j++)
            {
                in >> ch;
                if (in.status() != QTextStream::Ok) {
                    break;
                }
                //qDebug() << ch;
                QPushButton *button = FindButtonByPosition(i,j);
                if (button == nullptr) {
                    throw std::runtime_error("按钮空指针");
                }
                button->setText(ch);
            }
        }
        in>>ch;//去换行符
        EmptyLeft = 0;
        for(int i = 1;i<=9;i++)
        {
            for(int j = 1;j<=9;j++)
            {
                if(!IsSafe(i,j))
                {
                    throw std::runtime_error("数独无解");  //顺序排查无解
                }
            }
        }
        this->setWindowTitle(mainWindowsTitle + " - " + "自定义关卡");
        while(!in.atEnd())
        {
            QChar x,y;
            in >> x >> y;
            if (in.status() != QTextStream::Ok) {
                break;
            }
            //qDebug()<<cubeString + x + y;
            QPushButton *button = FindButtonByPosition(x.digitValue(),y.digitValue());

            if (button == nullptr) {
                throw std::runtime_error("按钮空指针");
            }
            EmptyLeft++;  //每读隐藏的2个字符就进1 说明有1个按钮被隐藏了
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
        ui->Score->setStyleSheet(ui->ScoreBoard->styleSheet());  //变成默认颜色
        QMessageBox::critical(NULL,  "错误",  "文件读取失败,可能有以下情况:\n1:文件不是关卡文件\n2:此关卡内数独无解", QMessageBox::Ok);
        this->setWindowTitle(mainWindowsTitle);
        return;
    }
    newgamewindow->close();
    ui->Score->setText(QString::number(MaxScore));
    ui->Score->setStyleSheet(ui->ScoreBoard->styleSheet());  //变成默认颜色
    QMessageBox::information(NULL,  "完成",  "文件导入关卡成功", QMessageBox::Ok);
    TimeCost = 0;
    TimeCost--;
    score = MaxScore+1;
    timer->start(1000);
    updateClock();
}

void Sudoku::on_pushButton_2_clicked()  //打开新关卡难度选择窗口
{
    newgamewindow->show();
}

void Sudoku::on_howtoplay_clicked()  //打开教程窗口
{
    newteachwindow->show();
}
