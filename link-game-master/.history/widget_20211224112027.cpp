#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("连连看");
    this->setWindowIcon(QIcon(":/image/app.ico"));
    this->myTimer=new QTimer(this);
    //初始化
    this->init();
    //计时，修改lcd
    connect(myTimer,&QTimer::timeout,[=](){
        --currentTime;
        ui->lcdNumber->display(currentTime);
        if(currentTime<=0)
        {
            bool youwin=ui->gameWidget->isWin();
            //计时结束，游戏失败
            if(!youwin){
                if(QMessageBox::Ok==QMessageBox::question(this,"You lose","What a pity! Do you want to try again?",
                                                          QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel))
                {
                    this->init();
                    ui->gameWidget->initData();
                    on_startBtn_clicked();
                }
                else{
                    this->init();
                    ui->gameWidget->initData();
                    ui->gameWidget->update();
                }
            }
        }

    });
    //赢了之后，选择继续游戏，则接收到restart信号
    connect(ui->gameWidget,&GameArea::restart,this,[=](){
        this->init();
        ui->gameWidget->initData();
        on_startBtn_clicked();
    });
    //赢了之后,选择取消,则接收到winCancel信号
    connect(ui->gameWidget,&GameArea::winCancel,this,[=](){
        this->init();
        ui->gameWidget->initData();
        ui->gameWidget->update();
    });
    //赢了之后，立马暂停计时器
    connect(ui->gameWidget,&GameArea::hasWin,this,[=](){
        this->myTimer->stop();
    });
    //gameWidget 鼠标释放后 发送更新进度信号
    connect(ui->gameWidget,&GameArea::updateProgress,this,[=](){
       int val=ui->gameWidget->getProgress();
       ui->progressBar->setValue(val);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    //初始化数据
    myTimer->stop();
    ui->progressBar->setValue(0);
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->display(MAX_GAME_TIME);
    this->currentTime=MAX_GAME_TIME;
    //过滤鼠标事件，不执行点击事件的函数
    ui->gameWidget->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}



void Widget::on_startBtn_clicked()
{
    //不过滤鼠标事件
    ui->gameWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    ui->gameWidget->newGame();
    myTimer->start(1000);
}

void Widget::on_stopBtn_clicked()
{
    myTimer->stop();
    //过滤鼠标事件，不执行点击事件的函数
    ui->gameWidget->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}
