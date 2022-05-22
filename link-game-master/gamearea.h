#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMap>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtAlgorithms>
//行数和列数
const int ROW_COUNT=10;
const int COLUMN_COUNT=10;
//图片高度和宽度
const int IMAGE_WIDHT=32;
const int IMAGE_HEIGHT=32;


class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = nullptr);
    //绘图时间
    void paintEvent(QPaintEvent *e);
    //点击开始后，加载游戏区域
    void newGame();
    //初始化数据
    void initData();
    //判断是否赢得游戏
    bool isWin();
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件 释放时，判断是否赢得游戏
    void mouseReleaseEvent(QMouseEvent *e);
    //获取进度
    int getProgress();
    //是否可以连接
    bool canBeLinked(int row1,int col1,int row2,int col2);

    //在一条直线上
    bool inOneLine(int row1,int col1,int row2,int col2);
    //在两条折线上
    bool inTwoLine(int row1,int col1,int row2,int col2);
    //在三条折线上  个人觉得两条折线连接就能玩赢了，这个函数可以不要,用来增加难度
    //可以在canBeLinked中修改连接判断条件，加上三条折线连接
    bool inThreeLine(int row1,int col1,int row2,int col2);

private:
    bool showGameArea;
    int PixmapData[ROW_COUNT][COLUMN_COUNT];
    QVector<QVector<bool>>* isEmpty;
    int clickCount;
    int firstClickX;
    int firstClickY;
signals: void restart();
        void hasWin();
        void updateProgress();
        void winCancel();
public slots:
};

#endif // GAMEAREA_H
