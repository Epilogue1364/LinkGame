#include "gamearea.h"

GameArea::GameArea(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(COLUMN_COUNT*IMAGE_WIDHT,ROW_COUNT*IMAGE_HEIGHT);
    initData();
}

void GameArea::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);

    //点击按钮后 显示游戏区域
    if(showGameArea)
    {
        for(int i=0;i<ROW_COUNT;++i)
            for(int j=0;j<COLUMN_COUNT;++j)
            {
                if(!(*isEmpty)[i][j])
                painter.drawPixmap(j*IMAGE_WIDHT,i*IMAGE_HEIGHT,IMAGE_WIDHT,IMAGE_HEIGHT,
                                   QPixmap(QString(":/image/%1.png").arg(PixmapData[i][j])));
            }
    }
}

void GameArea::newGame()
{
    showGameArea=true;
    update();
}

//初始化数据
void GameArea::initData()
{
    showGameArea=false;
    //生成的数据必须成对,可以先生成一半，后一半通过前一半得到
    QVector<int>*hasExist=new QVector<int>(ROW_COUNT/2*COLUMN_COUNT,0);
    for(int i=0;i<ROW_COUNT/2;++i)
        for(int j=0;j<COLUMN_COUNT;++j){
            int type=QRandomGenerator::global()->generate()%10;
            //先生成前一半
            PixmapData[i][j]=type;
            //生成后一半
            while(true)
            {
                //生成后一半的随机数 如 50~99
                int tempIndex=QRandomGenerator::global()->generate()%(ROW_COUNT/2*COLUMN_COUNT)+
                        ROW_COUNT/2*COLUMN_COUNT;
                //判断是否出现过 没有出现，则赋值
                if((*hasExist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]==0)
                {
                    PixmapData[tempIndex/ROW_COUNT][tempIndex%ROW_COUNT]=type;

                    (*hasExist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]=1;
                    break;
                }
            }
        }
    //测试数据是否成对  a^0=a; a^a=0;  如果成对，输出则为0
//    int temp=0;
//    for(int i=0;i<ROW_COUNT;++i)
//        for(int j=0;j<COLUMN_COUNT;++j){
//            temp=temp^PixmapData[i][j];
//        }
//    qDebug()<<temp;


    isEmpty=new QVector<QVector<bool>>(ROW_COUNT,QVector<bool>(COLUMN_COUNT,false));
    clickCount=0;
    firstClickX=-1;
    firstClickY=-1;
}

bool GameArea::isWin()
{
    for(int i=0;i<ROW_COUNT;++i)
        for(int j=0;j<COLUMN_COUNT;++j)
        {   //不为空 则返回false
            if(!(*isEmpty)[i][j])
                return false;
        }
    return true;
}
void GameArea::mousePressEvent(QMouseEvent *e)
{
    int currentX=e->x()/IMAGE_WIDHT;
    int currentY=e->y()/IMAGE_HEIGHT;
    //如果点击的图片是空，那就直接返回
    if((*isEmpty)[currentY][currentX])
        return ;
    ++clickCount;
    //第一次点击
    if(clickCount%2!=0)
    {
        firstClickX=currentX;
        firstClickY=currentY;
        qDebug()<<"第一次点击"<<firstClickY<<","<<firstClickX<<"图片类型是"<<PixmapData[currentY][currentX];
    }

    //如果是第二次点击
    else if(clickCount%2==0){

        qDebug()<<"第二次点击"<<currentY<<" ,"<<currentX<<"图片类型是"<<PixmapData[currentY][currentX];
        //若图片类型不同或者点击位置相同直接return
        if(PixmapData[firstClickY][firstClickX]!=PixmapData[currentY][currentX]||
                (currentY==firstClickY&&currentX==firstClickX))
            return ;
        //判断是否可以连接
        bool flag=canBeLinked(firstClickY,firstClickX,currentY,currentX);
        qDebug()<<"判断连接"<<flag;
        //可以 则first current对应的isEmpty修改为true
        if(flag)
        {
            qDebug()<<"修改数组";
            (*isEmpty)[firstClickY][firstClickX]=true;
            (*isEmpty)[currentY][currentX]=true;
            update();
        }


    }

}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    //发送更新进度条信号
    emit updateProgress();
    bool youWin=isWin();
    if(youWin)
    {
        //赢了之后，得先暂停计时器
        emit hasWin();
        //询问是否继续游戏
        if(QMessageBox::Ok==QMessageBox::question(this,"You win","Congratulation! Do you want to continue the game",
                                                  QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel))
        {
            emit restart();
        }
        else{
            emit winCancel();
        }
    }
}

int GameArea::getProgress()
{
    double done=0;
    for(int i=0;i<ROW_COUNT;++i)
        for(int j=0;j<COLUMN_COUNT;++j)
        {   //不为空 则返回false
            if((*isEmpty)[i][j])
                done++;
        }
    return static_cast<int>(done/ROW_COUNT/COLUMN_COUNT*100);
}

bool GameArea::canBeLinked(int row1, int col1, int row2, int col2)
{
    //return inOneLine(row1, col1, row2, col2)||inTwoLine(row1, col1, row2, col2);
   return inOneLine(row1, col1, row2, col2)||inTwoLine(row1, col1, row2, col2)||inThreeLine(row1, col1, row2, col2);
}

bool GameArea::inOneLine(int row1, int col1, int row2, int col2)
{
    bool flag=true;
    //在一条直线上  判断两点连线之间有没有物体存在
    //行相同
    if(row1==row2)
    {
        for(int i=qMin(col1,col2)+1;i<qMax(col1,col2);++i){
            //qDebug()<<row1<<","<<i<<" "<<(*isEmpty)[row1][i];
            if(!(*isEmpty)[row1][i])
            {
                flag=false;
                break;
            }
        }
        if(flag)
            return true;
    }
    //列相同
    else if(col1==col2)
    {
        for(int i=qMin(row1,row2)+1;i<qMax(row1,row2);i++)
        {
            qDebug()<<i<<","<<col1<<" "<<(*isEmpty)[row1][i];
            if(!(*isEmpty)[i][col1])
            {
                return false;
            }
        }

        return true;
    }
    //都不相同直接返回false
    return false;
}

bool GameArea::inTwoLine(int row1, int col1, int row2, int col2)
{
    //两点之间，构成的矩形，以左上和右下作为中转点判断一条直线
    bool flag1=inOneLine(row1,col1,row1,col2)&&inOneLine(row1,col2,row2,col2);
    bool flag2=inOneLine(row1,col1,row2,col1)&&inOneLine(row2,col1,row2,col2);

    return ( flag1 && (*isEmpty)[row1][col2] ) || ( flag2 && (*isEmpty)[row2][col1] );

}

bool GameArea::inThreeLine(int row1, int col1, int row2, int col2)
{
    //以一点的横竖两轴每点作为中转点寻找路径
    //选择点(row1,col1)
    //先选择横轴,即固定行
    bool flag=false;
    for(int i=0;i<COLUMN_COUNT;i++)
    {
        if(i==col1)
            continue;

        if((*isEmpty)[row1][i]){
            flag=inOneLine(row1,i,row1,col1)&&inTwoLine(row1,i,row2,col2);
        }
        if(flag)
            return true;
    }
    //固定列
    for(int i=0;i<ROW_COUNT;i++)
    {
        if(i==row1)
            continue;

        if((*isEmpty)[i][col1]){
            flag=inOneLine(i,col1,row1,col1)&&inTwoLine(i,col1,row2,col2);
        }
        if(flag)
            return true;
    }
    return false;
}
