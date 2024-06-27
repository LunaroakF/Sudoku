#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

#include "newgame.h"
#include "ui_newgame.h"
#include "howtoplay.h"
#include "ui_howtoplay.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Sudoku;
}
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
    Q_OBJECT

protected:
    virtual void keyPressEvent(QKeyEvent *event);  //键盘事件监听
    virtual void mousePressEvent(QMouseEvent *event);  //鼠标按下事件监听
    virtual void mouseReleaseEvent(QMouseEvent *event);  //鼠标放开事件监听


public:
    void SelectedASolt(int x,int y);
    void ClearASolt();
    void ClearANumber();
    void SetButtonNumberWithAnswer(int x,int y,int data);
    bool HasRepeat(QString solt[],int lenth);
    bool IsSafe(int x,int y);
    bool IsSafeInVertical(int x,int y);
    bool IsSafeInHorizontal(int x,int y);
    bool IsSafeInCube(int x,int y);
    bool IsButtonEmpty(int x,int y);
    void HideAnswer(int x,int y);
    void GenerateLevel(int difficulty);
    bool SolveSudoku();
    QString FindEmpty();
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

private slots:
    void onButtonClicked();
    void updateClock();
    void ScoreDetal(int score);
    void ChooseNewbee();
    void ChooseHigher();
    void ChooseMaster();
    void on_pushButton_2_clicked();
    void FileImport();
    void on_howtoplay_clicked();

private:
    int MaxScore = 550;  //自定义游戏最大分数
    int NewBeeMaxScore = 800;
    int HigherMaxScore = 1200;
    int MasterMaxScore = 1600;
    int score = MaxScore;  //当前分数
    int EmptyLeft = 0;  //剩余解密数量
    int TimeCost = 0;  //用时
    QString mainWindowsTitle = "Sudoku";  //窗口默认名
    QTimer *timer;  //时钟
    newgame *newgamewindow = new newgame;  //难度选择子窗口
    HowToPlay *newteachwindow = new HowToPlay;  //教程窗口
    Ui::Sudoku *ui;
};
#endif // SUDOKU_H
