#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QTimer>

namespace Ui {
class Widget;
}


const int MAX_GAME_TIME=300;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();

private:
    Ui::Widget *ui;
    QTimer *myTimer;
    int currentTime;
};

#endif // WIDGET_H
