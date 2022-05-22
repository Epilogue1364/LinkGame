#pragma once
//初始化
void initimg();//初始化img类
void gameMapxy();//gameMap的xy坐标生成
void readLocalData();//读取本地数据
void recordLevel();//存入当前level选择到本地
void recordPromptTime();//存入提醒次数到本地
void recordShuffleTime();//存入洗牌次数到本地
void recordRemainTime();//存入剩余时间到本地
void recordConceal();//存入是否开启隐藏的参数
//3 随机生成
vector<int> degree;	//用于存放还未被消除的牌
void degreeOfDifficulty(int _row, int _column);//获取游戏难度系数组
void setMap(int _row, int _column, int replication); //根据重复数生成连连看矩阵
void shuffle();//洗牌
//4 显示
bool keysExecute();//主界面按钮执行操作
void displayBegin();//显示开始页面
void printMap();//在控制台打印连连看图组
void levelSwitch(int levelNum);//根据选择的关卡开始游戏
void beginGame(); //开始游戏
void displayGame();//显示游戏界面
void setting();//显示设置界面
void rankWindow();//显示排行榜界面
void pauseWindow();//暂停界面
void Goldfinger();//显示金手指界面
void concealWindow();//显示隐藏登录界面
void drawMap();//将连连看图片根据数组贴片
void drawrectangle(short y, short x);//绘制选择框
void drawLine(short x1, short y1, short x2, short y2);//绘制连接线
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //x为要载入图片的X坐标，y为Y坐标
void displayShuffle();//显示shuffle
void displayPrompt();//显示prompt
void displayLetter();//显示给苗苗的信件

void movePattern(int patternValue);//设置地图变化模式
void topBottom();//上下扩散
void leftRight();//左右扩散
void goBottom();//向下聚集
void goLeft();//向左聚集
void topBottomGoCenter();//上下向中间聚集
void leftRightGoCenter();//左右向中间聚集
void informGoOn();//通知框，询问是否继续
void informFinish();//通知框，通关
void informTimeOver();//通知框，游戏时间到
void gameTimer(int allTime, int nowHave);//计时器显示


void recordScore();//读取往届记录并做对比，如果不存在往届记录则创建，如果大于则替代
//5判定
bool canClear(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);//输入两个方块的坐标进行连接判定
bool rowDirectCon(int x1, int x2, int y);//判断在同一行上的两个点是否能连通
bool columnDirectCon(int y1, int y2, int x);//判定在同一列上的两个点是否能连通
bool oneLineCon(int x1, int y1, int x2, int y2);//可通过一条直线连接，包括相邻
bool twoLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3);//可通过两条线连接
bool threeLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);//可通过三条线连接
bool haveASolution(int &xs1, int &ys1, int &xs2, int &ys2);//至少有一个解
bool clearAllOrNot();//检查是否全部消除完
bool informGoOnResult();//通知框选择结果
bool informFinishResult();//游戏结束选择结果
bool informTimeOverResult();//返回或者重新开始游戏