#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

//导新窗口的两个东西
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
    void SelectedASolt(int x,int y);  //高亮提示方块
    void ClearASolt();  //顺序熄灭所有提示方块
    void ClearANumber();  //关卡重置 让所有方块已存储的内容清空
    void SetButtonNumberWithAnswer(int x,int y,int data);  //给格子设置数字，data传入0则清空
    bool HasRepeat(QString solt[],int lenth);  //传进来的字符串数组有没有重复的元素，有返回true 无返回false
    bool IsSafe(int x,int y);  //检查数独可行性(行列宫无重复)
    bool IsSafeInVertical(int x);  //检查数独可行性(列无重复)
    bool IsSafeInHorizontal(int y);  //检查数独可行性(行无重复)
    bool IsSafeInCube(int x,int y);  //检查数独可行性(宫无重复)
    bool IsButtonEmpty(int x,int y);  //检查此坐标的单元格是否不存在数据 不存在返回true 存在返回false
    void HideAnswer(int x,int y);  //隐藏 删除按钮表面数据，min内存储的答案不删除
    void GenerateLevel(int difficulty);  //难度1-81 空格子数量 随机生成关卡
    bool SolveSudoku();  //回溯解数独
    QPushButton *FindButtonByPosition(int x,int y);  //根据坐标返回按钮地址
    QString FindEmpty();  //顺序查找空的单元格并返回坐标 例如x=3，y=4返回 "34"
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

private slots:
    void onButtonClicked();  //鼠标左键单元格，插入数字用
    void updateClock();  //时钟周期更新
    void ChooseNewbee();  //难度选择萌新
    void ChooseHigher();  //难度选择高手
    void ChooseMaster();  //难度选择大师
    void on_pushButton_2_clicked();  //打开新关卡难度选择窗口
    void FileImport();  //以文件形式导入关卡
    void on_howtoplay_clicked();  //打开教程窗口

private:
    void ScoreDetal(int score);  //用于修改分数
    int MaxScore = 550;  //自定义游戏最大分数
    int NewBeeMaxScore = 800;  //萌新难度最大分数
    int HigherMaxScore = 1200;  //高手难度最大分数
    int MasterMaxScore = 1600;  //大师难度最大分数
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
