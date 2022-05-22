#include"library.h"
#include"define.h"
#include"const.h"
#include"class.h"
#include"statement.h"

//主函数
int main() {
	int no_menu_bar_width = GetSystemMetrics(SM_CXFULLSCREEN);
	int no_menu_bar_height = GetSystemMetrics(SM_CYFULLSCREEN);
	//printf("无菜单栏窗口大小为%d*%d\n", no_menu_bar_width, no_menu_bar_height);
	int have_menu_bar_width = GetSystemMetrics(SM_CXSCREEN);
	int have_menu_bar_height = GetSystemMetrics(SM_CYSCREEN);
	//printf("无菜单栏窗口大小为%d*%d\n", have_menu_bar_width, have_menu_bar_height);
	//printf("窗口大小为%d*%d\n", windowWidth, windowHeight);
	//初始化
	
	initimg();		//初始化图片组
	gameMapxy();	//初始化地图矩阵的xy坐标
	readLocalData(); //初始化level，promptTime，shuffleTime，remainTime
	//1 窗口
	
	initgraph(windowWidth, windowHeight);
	//initgraph(windowWidth, windowHeight, SHOWCONSOLE);
	HWND hwnd = GetHWnd();
	SetWindowTextW(hwnd, L"苗苗连连看");
	SetWindowPos(hwnd, HWND_TOP, (no_menu_bar_width-windowWidth)/2-8, 0, windowWidth, windowHeight, SWP_NOSIZE);
	//HICON hIcon = LoadIcon(NULL, (LPCTSTR)IDI_HOUSE);
	//SendMessage(hwnd,)
	
	//1.1主界面的判定
	while (1)
	{
		do {
			printf("进入main中的循环\n");
		} while (0);

		if (initvalue) {
			printf("进入初始化\n");
			//初始化
			//设置颜色
			setbkcolor(WHITE);		//背景色，当使用cleardevice清屏时，使用该颜色填充整个画面
			setfillcolor(WHITE);	//设置所绘制图形的填充色 游戏主界面背景颜色

			//设置字体格式
			textstyle.lfHeight = 50;//设置一系列字体格式到textstyle
			textstyle.lfWidth = 30;
			textstyle.lfQuality = PROOF_QUALITY;
			textstyle.lfWeight = 700;//生成字体的粗细
			_tcscpy(textstyle.lfFaceName, _T("Aa方萌 (非商业使用)"));
			settextstyle(&textstyle);

			//设置线的格式
			
			linestyle.thickness = 4;
			setlinestyle(&linestyle);
			setlinecolor(choiceBoxColor);
			initvalue = 0;
		}

		if (!keysExecute()) {
			printf("关闭窗口并结束进程 \n");
			closegraph();
			return 0;
		}

	}
	return 0;
}
//主界面按钮执行操作
bool keysExecute()
{
	printf("进入keysExecute()\n");
	cleardevice(); //清屏
	displayBegin();	//显示游戏主界面
	//FlushMouseMsgBuffer();	//清空鼠标缓存
	MOUSEMSG msg;
	int n = 0;
	while (1)
	{
		//FlushMouseMsgBuffer();	//清空鼠标缓存
		//Sleep(50);
		msg = GetMouseMsg();
		while (msg.mkLButton) {
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("游戏主界面鼠标点击的判断\n");
				printf("(%d,%d)\n", msg.x, msg.y);
				if (keyBeginGame.cursorPos(msg)) {
					if (0 == PlaySound(TEXT("data\\begin.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					beginGame();
					levelSet = true;
					displayBegin();
				}
				else if (keyGameOver.cursorPos(msg))
				{
					printf("退出游戏\n");
					return false;
				}
				else if (keySetting.cursorPos(msg))
				{
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					setting();
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					displayBegin();
				}
				else if (keyRank.cursorPos(msg)) {
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					rankWindow();
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					displayBegin();

				}
				else if (keyGoldfinger.cursorPos(msg)) {
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					Goldfinger();
					if (0 == PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					displayBegin();
				}
				else if (keyConceal.cursorPos(msg))
				{
					concealWindow();
					displayBegin();
				}
			}
		}



	}

}
//输入所需要形成的牌的行数和列数随机生成重复次数为replication的牌
void setMap(int _row, int _column, int replication) {
	vector<int> map;	//按顺序储存所有牌
	srand(time(NULL));	//
	int n = 0;
	for (int i = 0; i < ((_row)*(_column) / replication); i++) {
		for (int j = 0; j < replication; j++) {
			map.push_back(i);
		}
	}
	//再从map拿到gameMap中
	int index = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i<(row - _row) / 2 || j<(column - _column) / 2 || i>(row - 1 - (row - _row) / 2) || j>(column - 1 - (column - _column) / 2))
			{
				gameMap[i][j].num = -1;
			}
			else {
				index = rand() % map.size();
				gameMap[i][j].num = map[index];//随机抽取牌按顺序放入方阵中
				map.erase(map.begin() + index);
			}
		}
	}
}
//将牌按顺序打印到控制台
void printMap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%02d ", gameMap[i][j].num);
		}
		printf("\n");
	}
}
//初始化图片类，载入图片
void initimg() {
	/*
	
	vector<int> pic;	//按顺序储存所有牌
	srand(time(NULL));	//
	int n = 0;
	for (int i = 0; i < 72; i++) {
		pic.push_back(i);
	}
	int picnum = 0;
	*/
	char imgName[12] = { 0 };
	for (int i = 0; i < 72; i++) {
		//picnum = rand() % pic.size();
		//sprintf(imgName, "imag\\%d.png", picnum);
		sprintf(imgName, "imag\\%d.png", i);
		//printf("imag\\%d.png\n", i);	//cout << imgName << endl;//printf("%s\n ",&imgName[i]);
		//CString inmaNameT= imgName;
		loadimage(&img[i], CString(imgName), gridSizeWidth, gridSizeHeight);
		//pic.erase(pic.begin() + picnum);
	}

	for (int i = 72; i < 76; i++) {
		sprintf(imgName, "imag\\%d.png", i);
		//CString inmaNameT = imgName;
		if (i == 72)
			loadimage(&img[i], CString(imgName), windowWidth, windowHeight);
		else if(i==73)
			loadimage(&img[i], CString(imgName), 80, 50);
		else if(i==74)
			loadimage(&img[i], CString(imgName), keyWidth, gridSizeHeight);
		else if (i == 75)
			loadimage(&img[i], CString(imgName), 80, 50);
	}

}
//显示主界面
void displayBegin() {
	printf("进入主界面\n");
	cleardevice();
	setbkcolor(WHITE);				//背景色
	setfillcolor(WHITE);	//设置所绘制图形的填充色 游戏主界面背景颜色
	solidrectangle(0, 0, windowWidth, windowHeight);//绘制背景图型并填充颜色
	putimage((windowWidth - img[72].getwidth()) / 2, (windowHeight - img[72].getheight()) / 2, &img[72]);//居中显示36.png
	//setbkcolor(keyFillColor);
	if (mylove)
	{
		setbkmode(TRANSPARENT);
		textstyle.lfHeight = 45;
		textstyle.lfWidth = 40;
		settextstyle(&textstyle);
		settextcolor(choiceBoxColor);
		drawtext(_T("苗苗专属版"), &MyLoveTxt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		drawtext(_T("2022.05.20"), &MyLoveTxt2, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		setbkmode(OPAQUE);
	}
	
}
//显示游戏界面
void displayGame() {
	//printf("进入游戏界面\n");
	BeginBatchDraw();
	//cleardevice();
	setbkcolor(BLACK);				//背景色
	setfillcolor(BLACK);	//设置所绘制图形的填充色
	solidrectangle(0, 0, windowWidth, windowHeight);
	//setlinecolor(keyFrameColor);
	putimage(ReturnToMain.left, ReturnToMain.top, &img[74]);
	putimage(Reset.left, Reset.top, &img[74]);
	putimage(Prompt.left, Prompt.top, &img[74]);
	putimage(Pause.left, Pause.top, &img[74]);
	setfillcolor(myloveFill);
	setbkcolor(myloveFill);
	textstyle.lfHeight = 25;
	textstyle.lfWidth = 20;
	settextstyle(&textstyle);
	settextcolor(myloveTC);
	//fillroundrect(ReturnToMain.left, ReturnToMain.top, ReturnToMain.right, ReturnToMain.bottom, 40, 40);
	drawtext(_T("返回主界面"), &ReturnToMain, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Reset.left, Reset.top, Reset.right, Reset.bottom, 40, 40);
	drawtext(_T("洗牌  "), &Reset, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Prompt.left, Prompt.top, Prompt.right, Prompt.bottom, 40, 40);
	drawtext(_T("提示  "), &Prompt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Pause.left, Pause.top, Pause.right, Pause.bottom, 40, 40);
	drawtext(_T("暂停"), &Pause, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
	displayPrompt();
	displayShuffle();
	//gameTimer(360, 360);
}
//进行游戏
void beginGame() {
	printf("开始游戏\n");
	MOUSEMSG msg;
	bool pitch = false; //表示所选择了几个方块，false表示未选择，true表示选择了一个，选择一个后再选择一个将会进行判定并进行相应操作
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0, xs1 = 0, xs2 = 0, ys1 = 0, ys2 = 0;
	int gameTime=0;
	score = 0;
	while (1) {
		if (levelSet)//根据关卡生成牌堆
		{
			printf("重置关卡\n");
			gamePromptTime = promptTime;
			gameShuffleTime = shuffleTime;
			printf("level=%d\n",level);
			levelSwitch(level);//根据level选择进行levelNow结构的赋值
			levelNow = levelswitch;
			degreeOfDifficulty(levelNow._row, levelNow._column);//计算难度系数
			//printf("degree=%d\n", levelNow._degree);
			//setMap(levelNow._row, levelNow._column, degree[levelNow._degree]);//根据实际游戏行列值和牌的重复次数随机生成放置到二维数组中
			setMap(levelNow._row, levelNow._column, levelNow._repeTime);//根据实际游戏行列值和牌的重复次数随机生成放置到二维数组中
			printf("重复次数=%d\n", levelNow._repeTime);
			displayGame();	//显示游戏进行界面
			if (!haveASolution(xs1, ys1, xs2, ys2))	//检查消除完是否还有解，若没有则重置
			{
				do
				{
					shuffle();
				} while (!haveASolution(xs1, ys1, xs2, ys2));

			}
			printMap();		//在控制台打印排列图组
			drawMap();		//把连连看打印到游戏界面
			setlinecolor(choiceBoxColor);
			setfillcolor(WHITE);	//设置连连看图片背景色
			timeLimit = levelNow._timeLimit+remainTime;
			gameTime = timeLimit;
			timeOld = time(0);
			scoreTimeOld = time(0);
			levelSet = false;//不再重置关卡
			gameTimer(gameTime, timeLimit);
			displayShuffle();
			displayPrompt();
		}
		if (!UnlimitTime)//金手指 无限时间开启处
		{
			timeNow = time(0);
			if (timeNow - timeOld >= 1)
			{
				timeLimit = timeLimit - (timeNow - timeOld);
				timeOld = time(0);
				gameTimer(gameTime, timeLimit);

			}
			if (timeLimit <= 0)
			{
				levelSet = true;
				if (0 == PlaySound(TEXT("data\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC))
				{
					printf("music error");
				}
				if (!informTimeOverResult())
				{
					return;
				}
			}
		}
		
		
		msg = GetMouseMsg();
		while (msg.mkLButton)//如果鼠标左键被点击
		{
			msg = GetMouseMsg();//持续监测鼠标
			if (!msg.mkLButton) {//如果鼠标左键被松开
				if (keyReturnToMain.cursorPos(msg)) {//点击返回主界面
					if (0 == PlaySound(TEXT("data\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					printf("退出连连看界面\n");
					return;
				}
				else if ((msg.x >= gameMap[1][1].x) && (msg.x <= (gameMap[row - 2][column - 2].x + gridSizeWidth + gap)) && (msg.y >= gameMap[1][1].y) && (msg.y <= (gameMap[row - 2][column - 2].y + gridSizeHeight + gap))) {
					//如果点击的是牌所处的区域
					printf("(%d,%d)--第%d行，第%d列\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
					if (gameMap[msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap)][(msg.x - xSpace) / (gridSizeWidth + gap)].num != -1)
					{
						if (!pitch) {//还未选取过一个牌
							y1 = (msg.y - ySpace) / (gridSizeHeight + gap);
							x1 = (msg.x - xSpace) / (gridSizeWidth + gap);
							drawrectangle(y1, x1);
							pitch = true;

						}
						else {//已选取一张牌
							y2 = (msg.y - ySpace) / (gridSizeHeight + gap);
							x2 = (msg.x - xSpace) / (gridSizeWidth + gap);
							int x3 = x1, y3 = y1, x4 = x2, y4 = y2;
							if (x1 != x2 || y1 != y2)//如果第二次点击的不是第一次所点击的牌
							{
								drawrectangle(y2, x2);
								if (gameMap[y1][x1].num == gameMap[y2][x2].num && canClear(x1, y1, x2, y2, x3, y3, x4, y4))
								{//如果可以消除
									//mciSendString(TEXT("play eliminate"), NULL, 0, NULL);
									if (0==PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
									{
										printf("music error");
									}
									
									if (!UnlimitTime) {
										//如果没有开无敌时间消除一次加2s
										gameTime += 2;
										timeLimit += 2;
									}
									scoreTimeNow = time(0);
									if (scoreTimeNow - scoreTimeOld>9)
									{
										score++;
									}
									else {
										score = score + (10 - (scoreTimeNow - scoreTimeOld));
									}
									scoreTimeOld = time(0);
									pitch = false;
									drawLine(x1, y1, x3, y3);
									drawLine(x3, y3, x4, y4);
									drawLine(x4, y4, x2, y2);
									setfillcolor(WHITE);	//设置连连看图片背景色
									solidroundrect(gameMap[y1][x1].x, gameMap[y1][x1].y, gameMap[y1][x1].x + gridSizeWidth, gameMap[y1][x1].y + gridSizeHeight, 5, 5);
									solidroundrect(gameMap[y2][x2].x, gameMap[y2][x2].y, gameMap[y2][x2].x + gridSizeWidth, gameMap[y2][x2].y + gridSizeHeight, 5, 5);
									drawAlpha(&img[gameMap[y1][x1].num], gameMap[y1][x1].x, gameMap[y1][x1].y);
									drawAlpha(&img[gameMap[y2][x2].num], gameMap[y2][x2].x, gameMap[y2][x2].y);
									gameMap[y1][x1].num = -1;
									gameMap[y2][x2].num = -1;

									//检查是否还有牌未被消除，如果全部消除完则到下一关
									if (clearAllOrNot())//消除完毕
									{
										if (0 == PlaySound(TEXT("data\\victory.wav"), NULL, SND_FILENAME | SND_ASYNC))
										{
											printf("music error");
										}
										promptTime = gamePromptTime;
										shuffleTime = gameShuffleTime;
										levelSet = true;
										Sleep(100);
										printMap();		//在控制台打印排列图组
										drawMap();		//把连连看贴出来
										//苗苗专属
										if (mylove)
										{
											displayLetter();
											displayGame();	//显示游戏进行界面
											drawMap();		//把连连看贴出来
										}
										recordScore();
										if (!UnlimitTime&&!UnlimitShuffle&&!UnlimitPrompt)//没开金手指，则获得剩余时间、提醒和洗牌累加奖励
										{
											remainTime = timeLimit;
											promptTime += levelNow._plusPromptTime;
											shuffleTime += levelNow._plusShuffleTime;
											recordRemainTime();
											recordPromptTime();
											recordShuffleTime();
										}
										


										if (level<10)
										{
											printf("通过本关\n");

											level += 1;
											recordLevel();
											if (!informGoOnResult()) {//如果点击退出
												return;
											}
										}
										else {//通关
											printf("恭喜，您已通关！\n");
											level = 1;
											recordLevel();
											if (informFinishResult())
											{
												return;
											}
										}
										
										
										
									}
									else {//没有消除完
										movePattern(levelNow._movePattern);
										//movePattern(levelNow._movePattern);
										if (!haveASolution(xs1, ys1, xs2, ys2))	//检查消除完是否还有解，若没有则重置
										{
											do
											{
												shuffle();
											} while (!haveASolution(xs1, ys1, xs2, ys2));

										}
										Sleep(100);
										printMap();		//在控制台打印排列图组
										drawMap();		//把连连看贴出来
									}
									
								}
								else {//如果不可以被消除
									drawMap();		//把连连看贴出来
									y1 = y2;
									x1 = x2;
									drawrectangle(y1, x1);//将选中的第一张牌改为第二张牌
								}
							}
						}
					}
				}
				else if (keyReset.cursorPos(msg))
				{
					//重置算法
					printf("洗牌\n");
					if (gameShuffleTime >0||UnlimitShuffle)
					{
						do
						{
							shuffle();
						} while (!haveASolution(xs1, ys1, xs2, ys2));
						if (!UnlimitShuffle)
						{
							gameShuffleTime--;
							displayShuffle();
						}
						printMap();		//在控制台打印排列图组
						drawMap();		//把连连看贴出来
					}
					

				}
				else if (keyPrompt.cursorPos(msg))
				{
					//提示算法
					printf("提示\n");
					if (gamePromptTime > 0 || UnlimitPrompt) {
						drawrectangle(ys1, xs1);
						drawrectangle(ys2, xs2);
						if (!UnlimitPrompt)
						{
							gamePromptTime--;
							displayPrompt();
						}
					}
					
				}
				else if (keyPause.cursorPos(msg))
				{
					printf("暂停\n");
					pauseWindow();
					pitch = false;
					timeOld = time(0);
					scoreTimeOld = time(0);
					displayGame();	//显示游戏进行界面
					gameTimer(gameTime, timeLimit);
					printMap();		//在控制台打印排列图组
					drawMap();		//把连连看贴出来
					
				}
				else {
					printf("(%d,%d)\n", msg.x, msg.y);
				}
			}
		}
		
	}
}
//设置界面
void setting() {
	printf("进入设置界面\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - settingWidth) / 2, (windowHeight - settingHeight) / 2, (windowWidth + settingWidth) / 2, (windowHeight + settingHeight) / 2, 20, 20);
	drawAlpha(&img[73],windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + settingHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("选择关卡"), &settingTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 40;
	textstyle.lfWidth = 33;
	settextstyle(&textstyle);
	settextcolor(settingLevelColor);
	for (int i = 0; i < 10; i++)
	{
		setfillcolor(settingFillBkColor);
		setbkcolor(settingFillBkColor);
		solidroundrect(windowWidth / 2 - settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 + settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap), 20, 20);
		RECT levelTxt = { windowWidth / 2 - settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 + settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap) };
		levelSwitch(i + 1);
		levelDisplay = levelswitch;
		drawtext(CString(levelDisplay._levelName), &levelTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	setlinecolor(choiceBoxColor);
	roundrect(windowWidth / 2 - settingWidth / 3 - 2, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + (level - 1) * (levelHeight + levelGap) + 2, windowWidth / 2 + settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + (level - 1) * (levelHeight + levelGap), 20, 20);
	EndBatchDraw();
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.mkLButton)
		{
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("(%d,%d)--第%d行，第%d列\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keySettingOut.cursorPos(msg)) {
					recordLevel();
					printf("退出设置界面\n");
					return;
				}
				else if (keyLevel1.cursorPos(msg) || keyLevel2.cursorPos(msg) || keyLevel3.cursorPos(msg) || keyLevel4.cursorPos(msg) || keyLevel5.cursorPos(msg) || keyLevel6.cursorPos(msg) || keyLevel7.cursorPos(msg) || keyLevel8.cursorPos(msg) || keyLevel9.cursorPos(msg) || keyLevel10.cursorPos(msg))
				{
					setlinecolor(WHITE);
					roundrect(windowWidth / 2 - settingWidth / 3 - 2, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + (level - 1) * (levelHeight + levelGap) + 2, windowWidth / 2 + settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + (level - 1) * (levelHeight + levelGap), 20, 20);
					if (keyLevel1.cursorPos(msg))
					{
						level = 1;
					}
					else if (keyLevel2.cursorPos(msg))
					{
						level = 2;
					}
					else if (keyLevel3.cursorPos(msg))
					{
						level = 3;
					}
					else if (keyLevel4.cursorPos(msg))
					{
						level = 4;
					}
					else if (keyLevel5.cursorPos(msg))
					{
						level = 5;
					}
					else if (keyLevel6.cursorPos(msg))
					{
						level = 6;
					}
					else if (keyLevel7.cursorPos(msg))
					{
						level = 7;
					}
					else if (keyLevel8.cursorPos(msg))
					{
						level = 8;
					}
					else if (keyLevel9.cursorPos(msg))
					{
						level = 9;
					}
					else if (keyLevel10.cursorPos(msg))
					{
						level = 10;
					}
					setlinecolor(choiceBoxColor);
					roundrect(windowWidth / 2 - settingWidth / 3 - 2, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + (level - 1) * (levelHeight + levelGap) + 2, windowWidth / 2 + settingWidth / 3, (windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + (level - 1) * (levelHeight + levelGap), 20, 20);
				}
			}
		}
	}
}
//排行榜界面
void rankWindow() {
	printf("进入排行榜界面\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - rankWidth) / 2, (windowHeight - rankHeight) / 2, (windowWidth + rankWidth) / 2, (windowHeight + rankHeight) / 2, 20, 20);
	drawAlpha(&img[73], windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + rankHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("最高纪录"), &rankTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 40;
	textstyle.lfWidth = 33;
	settextstyle(&textstyle);
	settextcolor(settingLevelColor);
	setfillcolor(settingFillBkColor);
	setbkcolor(settingFillBkColor);
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	setlinecolor(choiceBoxColor);
	FILE *pf;
	for (int i = 0; i < 10; i++)
	{
		
		solidroundrect(windowWidth / 2 - rankWidth / 3-10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 -10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap), 20, 20);
		RECT rankLevelTxt = { windowWidth / 2 - rankWidth / 3 - 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 - 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap) };
		solidroundrect(windowWidth / 2 + 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 + rankWidth/3 + 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap), 20, 20);
		RECT rankScoreTxt = { windowWidth / 2 + 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + i * (levelHeight + levelGap), windowWidth / 2 + rankWidth / 3 + 10, (windowHeight - rankHeight) / 2 + keyLevelinitHeight + levelHeight + i * (levelHeight + levelGap) };
		char rankLevel[10] = { '\0' }, rankScoreDis[10] = { '\0' };
		sprintf(rankLevel, "第%d关", i+1);
		drawtext(CString(rankLevel), &rankLevelTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		levelSwitch(i + 1);
		levelDisplay = levelswitch;
		printf("%s\n", levelDisplay._rankName);
		
		if (!(pf = fopen(levelDisplay._rankName, "r")))
		{
			drawtext(_T("暂无记录"), &rankScoreTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else {
			
			fgets(rankScoreDis, 10, pf);
			printf("scrOld=%s\n", rankScoreDis);
			drawtext(CString(rankScoreDis), &rankScoreTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			fclose(pf);
		}
		
	}
	
	EndBatchDraw();
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.mkLButton)
		{
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("(%d,%d)--第%d行，第%d列\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keySettingOut.cursorPos(msg)) {
					printf("退出设置界面\n");
					return;
				}
			}
		}
	}
}
//将连连看图片根据数组贴片
void drawMap() {
	BeginBatchDraw();
	setfillcolor(BLACK);	//设置所绘制图形的填充色
	solidrectangle(gameMap[0][0].x-5, gameMap[0][0].y - 5, gameMap[row-1][column-1].x + gridSizeWidth + 5, gameMap[row - 1][column - 1].x + gridSizeHeight + 5); //绘制连连看图组出现的方格
	//solidrectangle(xSpace, ySpace, xSpace + bkWidth, ySpace + bkHeight);
	setfillcolor(WHITE);	//设置连连看图片背景色
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			//putimage(j*gridSizeWidth + 25, i*gridSizeHeight + 25, gridSizeWidth, gridSizeHeight, &img[39],0,0);
			//putimage(j*gridSizeWidth + 25, i*gridSizeHeight + 25,  &img[gameMap[i][j]]);
			if (gameMap[i][j].num != -1) {
				//贴背景图
				solidroundrect(gameMap[i][j].x, gameMap[i][j].y, gameMap[i][j].x + gridSizeWidth, gameMap[i][j].y + gridSizeHeight, 5, 5);
				//贴连连看图
				drawAlpha(&img[gameMap[i][j].num], gameMap[i][j].x, gameMap[i][j].y);
			}
		}
	}
	setbkcolor(BLACK);				//背景色
	setfillcolor(BLACK);	//设置所绘制图形的填充色
	settextcolor(levelNameColor);
	textstyle.lfHeight = 45;
	textstyle.lfWidth = 35;
	settextstyle(&textstyle);
	drawtext(CString(levelNow._levelName), &levelNameAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	settextcolor(scoreTxtColor);
	drawtext(_T("得分"), &scoreTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_itot(score,scoreChar,10), &scoreAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	settextcolor(repeTimeColor);
	drawtext(_T("重复次数"), &repeTimTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_itot(levelNow._repeTime, repeTimeChar, 10), &repeTimeAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	EndBatchDraw();
}
//绘制选择框
void drawrectangle(short y, short x) {
	LINESTYLE linestyle;
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	setlinecolor(choiceBoxColor);
	rectangle(gameMap[y][x].x - 2, gameMap[y][x].y - 2, gameMap[y][x].x + 2 + gridSizeWidth, gameMap[y][x].y + 2 + gridSizeHeight);

}

// 载入PNG图并去透明部分
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//连连看矩阵xy坐标生成
void gameMapxy() {
	for (int i = 0; i < row*column; i++) {
		gameMap[i / column][i%column].x = (i%column)*gridSizeWidth + xSpace + (i%column) * gap;
		gameMap[i / column][i%column].y = (i / column)* gridSizeHeight + ySpace + (i / column) * gap;
	}
}
//洗牌
void shuffle() {
	vector<int> card;	//用于存放还未被消除的牌
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (gameMap[i][j].num != -1) {
				card.push_back(gameMap[i][j].num);
			}
		}
	}
	short index = 0;
	srand(time(NULL));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (gameMap[i][j].num != -1) {
				index = rand() % card.size();
				gameMap[i][j].num = card[index];
				card.erase(card.begin() + index);
			}
		}
	}
}
//输入地图的行列值，计算难度数组
void degreeOfDifficulty(int _row, int _column) {
	for (vector <int>::iterator iter = degree.begin(); iter != degree.end();)
	{
		iter = degree.erase(iter);
	}
	for (int i = 1; i < (_row*_column / 2); i++)
	{
		if (_row*_column % (2 * i) == 0) {
			degree.push_back(2 * i);
			printf("%d ", 2 * i);
		}
	}
	printf("\n");
}

//判断两个格子是否能连接
bool canClear(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4) {
	if (x1 == x2 || y1 == y2)//1两方块相邻 2两方块可通过一条直线连接
	{
		if (oneLineCon(x1, y1, x2, y2))
		{
			return true;
		}
	}
	//3两方块可通过两条直线连接 4两方块可通过三条线连接 
	if (twoLineCon(x1, y1, x2, y2, x3, y3) || threeLineCon(x1, y1, x2, y2, x3, y3, x4, y4)) {
		return true;
	}
	return false;
}
//判断在一行的两个格子是否能连接
bool rowDirectCon(int x1, int x2, int y) {//输入y行上的两个坐标
	int smaller = x1<x2 ? x1 : x2, bigger = x1>x2 ? x1 : x2;
	for (int i = smaller + 1; i < bigger; i++) {//如果两坐标之间有间隔，检查间隔上是否有未消除的牌
		if (gameMap[y][i].num != -1)//如果有未消除的牌
			return false;
	}
	return true;//如果两坐标之间没有间隔或者有间隔但没有牌则
}
//判断在一列的两个格子是否能连接
bool columnDirectCon(int y1, int y2, int x) {//输入x列上的两个坐标
	int smaller = y1<y2 ? y1 : y2, bigger = y1>y2 ? y1 : y2;
	for (int i = smaller + 1; i < bigger; i++) {//如果两坐标之间有间隔，检查间隔上是否有未消除的牌
		if (gameMap[i][x].num != -1)//如果有未消除的牌
			return false;
	}
	return true;//如果两坐标之间没有间隔或者有间隔但没有牌则
}
//如果在同一行或者同一列，判断是否能通过一条直线连接，包括相邻
bool oneLineCon(int x1, int y1, int x2, int y2) {
	if (x1 == x2)
	{
		if (columnDirectCon(y1, y2, x1))
			return true;
	}
	else {//不在同一列必定在同一行
		if (rowDirectCon(x1, x2, y1))
			return true;
	}
	return false; //无法通过一条线连接
}
//判断是否可以通过两条线连接
bool twoLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3) {
	if (gameMap[y2][x1].num == -1 && columnDirectCon(y1, y2, x1) && rowDirectCon(x1, x2, y2))
	{
		x3 = x1;
		y3 = y2;
		return true;
	}
	else if (gameMap[y1][x2].num == -1 && columnDirectCon(y1, y2, x2) && rowDirectCon(x1, x2, y1))
	{
		x3 = x2;
		y3 = y1;
		return true;
	}
	return false;
}
//判断是否可以通过三条线连接
bool threeLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4) {
	for (int i = x1 - 1; i >= 0; i--)
	{
		if (gameMap[y1][i].num == -1 && gameMap[y2][i].num == -1 && i != x1 && i != x2 && oneLineCon(x1, y1, i, y1) && oneLineCon(i, y1, i, y2) && oneLineCon(i, y2, x2, y2))
		{
			x3 = i;
			y3 = y1;
			x4 = i;
			y4 = y2;
			return true;
		}
	}
	for (int i = x1 + 1; i < column; i++)
	{
		if (gameMap[y1][i].num == -1 && gameMap[y2][i].num == -1 && i != x1 && i != x2 && oneLineCon(x1, y1, i, y1) && oneLineCon(i, y1, i, y2) && oneLineCon(i, y2, x2, y2))
		{
			x3 = i;
			y3 = y1;
			x4 = i;
			y4 = y2;
			return true;
		}
	}
	for (int j = y1 - 1; j >= 0; j--)
	{
		if (gameMap[j][x1].num == -1 && gameMap[j][x2].num == -1 && j != y1 && j != y2 && oneLineCon(x1, y1, x1, j) && oneLineCon(x1, j, x2, j) && oneLineCon(x2, j, x2, y2))
		{
			x3 = x1;
			y3 = j;
			x4 = x2;
			y4 = j;
			return true;
		}
	}
	for (int j = y1 + 1; j < row; j++)
	{
		if (gameMap[j][x1].num == -1 && gameMap[j][x2].num == -1 && j != y1 && j != y2 && oneLineCon(x1, y1, x1, j) && oneLineCon(x1, j, x2, j) && oneLineCon(x2, j, x2, y2))
		{
			x3 = x1;
			y3 = j;
			x4 = x2;
			y4 = j;
			return true;
		}
	}
	return false;
}
//绘制连接两个格子中心的线
void drawLine(short x1, short y1, short x2, short y2) {
	LINESTYLE linestyle;
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	//setlinecolor(choiceBoxColor);
	line(gameMap[y1][x1].x + gridSizeWidth / 2, gameMap[y1][x1].y + gridSizeHeight / 2, gameMap[y2][x2].x + gridSizeWidth / 2, gameMap[y2][x2].y + gridSizeHeight / 2);
}
//根据level的值，将对应结构信息填到levelNow
void levelSwitch(int levelNum) {
	switch (levelNum)
	{
	case 1:
		levelswitch = level1;
		break;
	case 2:
		levelswitch = level2;
		break;
	case 3:
		levelswitch = level3;
		break;
	case 4:
		levelswitch = level4;
		break;
	case 5:
		levelswitch = level5;
		break;
	case 6:
		levelswitch = level6;
		break;
	case 7:
		levelswitch = level7;
		break;
	case 8:
		levelswitch = level8;
		break;
	case 9:
		levelswitch = level9;
		break;
	case 10:
		levelswitch = level10;
		break;
	}
}

//检查是否有至少一个解
bool haveASolution(int &xs1, int &ys1, int &xs2, int &ys2) {
	int _x3, _y3, _x4, _y4;
	for (ys1 = 0; ys1 < row; ys1++)
	{
		for (xs1 = 0; xs1 < column; xs1++)
		{
			if (gameMap[ys1][xs1].num != -1)
			{
				for (ys2 = ys1; ys2 < row; ys2++)
				{
					for (xs2 = 0; xs2 < column; xs2++)
					{
						if (xs1 != xs2 || ys1 != ys2)
						{
							if (gameMap[ys1][xs1].num == gameMap[ys2][xs2].num&&canClear(xs1, ys1, xs2, ys2, _x3, _y3, _x4, _y4))
							{
								return true;
							}
						}

					}

				}
			}
		}
	}
	return false;
}
void movePattern(int patternValue) {
	switch (patternValue)
	{
	case 1://不变

		break;
	case 2://向上下扩散
		topBottom();
		break;
	case 3://向左右扩散
		leftRight();
		break;
	case 4://向四周扩散
		topBottom();
		leftRight();
		break;
	case 5://向下聚集
		goBottom();
		break;
	case 6://向左聚集
		goLeft();
		break;
	case 7://中间聚集
		leftRightGoCenter();
		topBottomGoCenter();
		break;
	}
}
void topBottom() {
	for (int j = (column - levelNow._column) / 2; j < column - (column - levelNow._column) / 2; j++)
	{
		for (int i = (row - levelNow._row) / 2; i < row / 2 - 1; i++) {
			if (gameMap[i][j].num == -1)//如果有一个位置出现了被消除的牌
			{
				if (gameMap[i + 1][j].num != -1)//如果下面的牌没有被消除则下面的牌下降
				{
					gameMap[i][j].num = gameMap[i + 1][j].num;
					gameMap[i + 1][j].num = -1;
				}
				else if ((i + 2) <= (row / 2 - 1) && gameMap[i + 2][j].num != -1)//if(gameMap[i + 1][j].num == -1)//如果下面的牌也被消除了
				{
					//如果i+2没有超过中间线且其没被消除
					gameMap[i][j].num = gameMap[i + 2][j].num;//则将i+2的牌移到i处
					gameMap[i + 2][j].num = -1;
				}
			}
		}
		for (int i = (row - (row - levelNow._row) / 2 - 1); i > row / 2; i--)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i - 1][j].num != -1)
				{
					gameMap[i][j].num = gameMap[i - 1][j].num;
					gameMap[i - 1][j].num = -1;
				}
				else if ((i - 2) >= (row / 2) && gameMap[i - 2][j].num != -1)
				{

					gameMap[i][j].num = gameMap[i - 2][j].num;
					gameMap[i - 2][j].num = -1;
				}
			}
		}
	}
}
void leftRight() {
	for (int i = (row - levelNow._row) / 2; i < row - (row - levelNow._row) / 2; i++)
	{
		for (int j = (column - levelNow._column) / 2; j < column / 2 - 1; j++)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i][j + 1].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 1].num;
					gameMap[i][j + 1].num = -1;
				}
				else if ((j + 2) <= (column / 2 - 1) && gameMap[i][j + 2].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 2].num;
					gameMap[i][j + 2].num = -1;
				}
			}
		}
		for (int j = (column - (column - levelNow._column) / 2 - 1); j > column / 2; j--)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i][j - 1].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j - 1].num;
					gameMap[i][j - 1].num = -1;
				}
				else if ((j - 2) >= (column / 2) && gameMap[i][j - 2].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j - 2].num;
					gameMap[i][j - 2].num = -1;
				}
			}
		}
	}
}
void goBottom() {
	for (int j = (column - levelNow._column) / 2; j < column - (column - levelNow._column) / 2; j++)
	{
		for (int i = (row - (row - levelNow._row) / 2 - 1); i > (row - levelNow._row) / 2; i--)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i - 1][j].num != -1)
				{
					gameMap[i][j].num = gameMap[i - 1][j].num;
					gameMap[i - 1][j].num = -1;
				}
				else if ((i - 2) >= (row - levelNow._row) / 2 && gameMap[i - 2][j].num != -1)
				{

					gameMap[i][j].num = gameMap[i - 2][j].num;
					gameMap[i - 2][j].num = -1;
				}
			}
		}
	}
}
void goLeft() {
	for (int i = (row - levelNow._row) / 2; i < row - (row - levelNow._row) / 2; i++)
	{
		for (int j = (column - levelNow._column) / 2; j < (column - (column - levelNow._column) / 2 - 1); j++)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i][j + 1].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 1].num;
					gameMap[i][j + 1].num = -1;
				}
				else if ((j + 2) <= (column - (column - levelNow._column) / 2 - 1) && gameMap[i][j + 2].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 2].num;
					gameMap[i][j + 2].num = -1;
				}
			}
		}
	}
}
void topBottomGoCenter() {
	for (int j = (column - levelNow._column) / 2; j < column - (column - levelNow._column) / 2; j++)
	{
		for (int i = row / 2; i < (row - (row - levelNow._row) / 2 - 1); i++) {
			if (gameMap[i][j].num == -1)//如果有一个位置出现了被消除的牌
			{
				if (gameMap[i + 1][j].num != -1)//如果下面的牌没有被消除则下面的牌下降
				{
					gameMap[i][j].num = gameMap[i + 1][j].num;
					gameMap[i + 1][j].num = -1;
				}
				else if ((i + 2) <= (row - (row - levelNow._row) / 2 - 1) && gameMap[i + 2][j].num != -1)//if(gameMap[i + 1][j].num == -1)//如果下面的牌也被消除了
				{
					//如果i+2没有超过中间线且其没被消除
					gameMap[i][j].num = gameMap[i + 2][j].num;//则将i+2的牌移到i处
					gameMap[i + 2][j].num = -1;
				}
			}
		}
		for (int i = row / 2 - 1; i > (row - levelNow._row) / 2; i--)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i - 1][j].num != -1)
				{
					gameMap[i][j].num = gameMap[i - 1][j].num;
					gameMap[i - 1][j].num = -1;
				}
				else if ((i - 2) >= (row - levelNow._row) / 2 && gameMap[i - 2][j].num != -1)
				{

					gameMap[i][j].num = gameMap[i - 2][j].num;
					gameMap[i - 2][j].num = -1;
				}
			}
		}
		
	}
}
void leftRightGoCenter() {
	for (int i = (row - levelNow._row) / 2; i < row - (row - levelNow._row) / 2; i++)
	{
		for (int j = column / 2; j < (column - (column - levelNow._column) / 2 - 1); j++)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i][j + 1].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 1].num;
					gameMap[i][j + 1].num = -1;
				}
				else if ((j + 2) <= (column - (column - levelNow._column) / 2 - 1) && gameMap[i][j + 2].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j + 2].num;
					gameMap[i][j + 2].num = -1;
				}
			}
		}
		for (int j = column / 2 - 1; j > (column - levelNow._column) / 2; j--)
		{
			if (gameMap[i][j].num == -1)
			{
				if (gameMap[i][j - 1].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j - 1].num;
					gameMap[i][j - 1].num = -1;
				}
				else if ((j - 2) >= (column - levelNow._column) / 2 && gameMap[i][j - 2].num != -1)
				{
					gameMap[i][j].num = gameMap[i][j - 2].num;
					gameMap[i][j - 2].num = -1;
				}
			}
		}
	}
}
bool clearAllOrNot() {//true为已清空，false为未清空
	vector<int> remainCard;//用于存放还未被消除的牌
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (gameMap[i][j].num != -1) {
				remainCard.push_back(gameMap[i][j].num);
			}
		}
	}
	if (remainCard.size()<1)
	{
		return true;
	}
	return false;
}

void informGoOn() {
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - informWidth) / 2, (windowHeight - informHeight) / 2, (windowWidth + informWidth) / 2, (windowHeight + informHeight) / 2, 20, 20);
	setfillcolor(settingTitleColor);
	solidroundrect((windowWidth - informWidth) / 2 + 25, (windowHeight - informHeight) / 2 + 140, (windowWidth) / 2 - 25, (windowHeight - informHeight) / 2 + 180, 20, 20);
	solidroundrect((windowWidth) / 2 + 25, (windowHeight - informHeight) / 2 + 140, (windowWidth) / 2 + 125, (windowHeight - informHeight) / 2 + 180, 20, 20);
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 35;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("恭喜通过本关"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	if (recordBreak)
	{
		drawtext(_T("打破记录"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("继续加油"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("继续"), &informGoOnTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("退出"), &informQuitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informGoOnResult() {
	informGoOn();//显示通知框
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//如果鼠标左键被点击
		{
			msg = GetMouseMsg();//持续监测鼠标
			if (!msg.mkLButton) {//如果鼠标左键被松开
				if (keyQuit.cursorPos(msg)) {//点击返回主界面
					printf("不再继续\n");
					return false;
				}
				else if (keyGoOn.cursorPos(msg))
				{
					printf("继续游戏\n");
					return true;
				}
			}
		}
	}
}
void informFinish() {
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - informWidth) / 2, (windowHeight - informHeight) / 2, (windowWidth + informWidth) / 2, (windowHeight + informHeight) / 2, 20, 20);
	setfillcolor(settingTitleColor);
	solidroundrect((windowWidth) / 2 - 75, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 75, (windowHeight - informHeight) / 2 + keyHeight2, 20, 20);
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 35;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("恭喜通关"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	if (recordBreak)
	{
		drawtext(_T("打破记录"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("继续加油"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("返回主界面"), &informGoBack, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informFinishResult() {
	informFinish();//显示通知框
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//如果鼠标左键被点击
		{
			msg = GetMouseMsg();//持续监测鼠标
			if (!msg.mkLButton) {//如果鼠标左键被松开
				if (keyGoBack.cursorPos(msg)) {//点击返回主界面
					printf("返回主界面\n");
					return true;
				}
				
			}
		}
	}
}
void informTimeOver() {
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - informWidth) / 2, (windowHeight - informHeight) / 2, (windowWidth + informWidth) / 2, (windowHeight + informHeight) / 2, 20, 20);
	setfillcolor(settingTitleColor);
	solidroundrect((windowWidth - informWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 - 25, (windowHeight - informHeight) / 2 + keyHeight2, 20, 20);
	solidroundrect((windowWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 125, (windowHeight - informHeight) / 2 + keyHeight2, 20, 20);
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 35;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("时间到"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("游戏结束"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("重开"), &informGoOnTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("退出"), &informQuitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informTimeOverResult() {
	informTimeOver();
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//如果鼠标左键被点击
		{
			msg = GetMouseMsg();//持续监测鼠标
			if (!msg.mkLButton) {//如果鼠标左键被松开
				if (keyQuit.cursorPos(msg)) {//点击返回主界面
					printf("时间到，游戏失败，退出\n");
					return false;
				}
				else if (keyGoOn.cursorPos(msg))
				{
					printf("时间到，重新开始游戏\n");
					return true;
				}
			}
		}
	}
}
void gameTimer(int allTime, int nowHave) {
	BeginBatchDraw();
	linestyle.thickness = 2;
	setlinestyle(&linestyle);
	setlinecolor(timeBoxColor);
	setfillcolor(BLACK);
	setbkcolor(BLACK);
	fillroundrect(timexSpace, timeySpace, timexSpace+ timeBarWidth, timeySpace+timeBarHeight, 7, 7);
	setfillcolor(timeFillColor);
	int nowHeight = nowHave * timeBarHeight / allTime;
	solidroundrect(timexSpace+2, timeySpace + timeBarHeight- nowHeight+2, timexSpace + timeBarWidth-3, timeySpace + timeBarHeight-3, 6, 6);
	setfillcolor(WHITE);
	textstyle.lfHeight = 25;
	textstyle.lfWidth = 20;
	settextstyle(&textstyle);
	settextcolor(scoreTxtColor);
	drawtext(_itot(nowHave, countdown, 10), &timeDisAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();

}
void recordScore() {
	printf("记录数据\n");
	FILE *pf;
	int scrOldInt;
	char scrNow[10] = {'\0'}, scrOld[10] = { '\0' };
	pf = fopen(levelNow._rankName, "r");
	if (pf==NULL)
	{
		printf("文件不存在\n");
		sprintf(scrNow, "%d", score);
		recordBreak = true;
	}
	else {
		printf("文件存在\n");
		//fread(scrOld, sizeof(scrOld), 1, pf);
		fgets(scrOld, 10, pf);
		printf("scrOld=%s\n", scrOld);
		scrOldInt = atoi(scrOld);
		pf = fopen(levelNow._rankName, "w");
		if (scrOldInt <score)
		{
			printf("打破纪录\n");
			sprintf(scrNow, "%d", score);
			recordBreak = true;
		}
		else {
			printf("没打破纪录\n");
			sprintf(scrNow, "%d", scrOldInt);
			recordBreak = false;
		}
	}
	pf = fopen(levelNow._rankName, "w");
	//sprintf(scr, "%d", score);
	fwrite(scrNow, sizeof(scrNow), 1, pf);
	fclose(pf);
	score = 0;
}
void pauseWindow() {
	printf("进入设置界面\n");
	BeginBatchDraw();
	setbkcolor(BLACK);
	setfillcolor(BLACK);	//设置所绘制图形的填充色
	settextcolor(levelNameColor);
	solidrectangle(0, 0, windowWidth, windowHeight); //绘制连连看图组出现的方格
	textstyle.lfHeight = 65;
	textstyle.lfWidth = 55;
	settextstyle(&textstyle);
	drawtext(_T("游戏暂停"), &pauseTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	settextcolor(scoreTxtColor);
	drawtext(_T("点击鼠标左键继续游戏"), &pauseTxtAre2, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	settextstyle(&textstyle);
	EndBatchDraw();
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.mkLButton)
		{
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				return;
			}
		}
	}
}
void Goldfinger() {
	printf("进入金手指界面\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - goldFingerWidth) / 2, (windowHeight - goldFingerHeight) / 2, (windowWidth + goldFingerWidth) / 2, (windowHeight + goldFingerHeight) / 2, 20, 20);
	drawAlpha(&img[73], windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + goldFingerHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("金手指"), &goldFingerTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	char goldFingerName[3][10] = {'\0'};
	sprintf(goldFingerName[0], "游戏时间");
	sprintf(goldFingerName[1], "提醒次数");
	sprintf(goldFingerName[2], "洗牌次数");
	textstyle.lfHeight = 30;
	textstyle.lfWidth = 25;
	settextstyle(&textstyle);
	settextcolor(settingLevelColor);
	drawtext(_T("无限"), &unlimitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("重置"), &initTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	for (int i = 0; i < 3; i++)
	{
		textstyle.lfHeight = 40;
		textstyle.lfWidth = 33;
		settextstyle(&textstyle);
		settextcolor(settingLevelColor);
		linestyle.thickness = 4;
		setlinestyle(&linestyle);
		setlinecolor(choiceBoxColor);
		setfillcolor(settingFillBkColor);
		setbkcolor(settingFillBkColor);
		solidroundrect((windowWidth-goldFingerWidth)/2+50, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap),(windowWidth - goldFingerWidth) / 2 + 50+goldFingerBoxWidth, (windowHeight - goldFingerHeight) / 2 + upHeight + levelHeight + i * (levelHeight + levelGap), 20, 20);
		setfillcolor(WHITE);
		//无限 选择框
		fillroundrect((windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth+50+ leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap)+ (levelHeight-goldFingerSwitchHeight)/2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50+goldFingerSwitchWidth + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2+ goldFingerSwitchHeight, 5, 5);
		//重置 按键
		fillroundrect((windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight, 5, 5);

		RECT levelTxt = { (windowWidth - goldFingerWidth) / 2 + 50, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap),(windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth, (windowHeight - goldFingerHeight) / 2 + upHeight + levelHeight + i * (levelHeight + levelGap) };
		drawtext(CString(goldFingerName[i]), &levelTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (UnlimitTime) {
		setfillcolor(settingTitleColor);
		solidroundrect(keyUnlimitTime.left + 4, keyUnlimitTime.top+ 4, keyUnlimitTime.right - 5, keyUnlimitTime.bottom - 5, 5, 5);
	}
	if (UnlimitPrompt) {
		setfillcolor(settingTitleColor);
		solidroundrect(keyUnlimitPrompt.left + 4, keyUnlimitPrompt.top + 4, keyUnlimitPrompt.right - 5, keyUnlimitPrompt.bottom - 5, 5, 5);

	}
	if (UnlimitShuffle) {
		setfillcolor(settingTitleColor);
		solidroundrect(keyUnlimitShuffle.left + 4, keyUnlimitShuffle.top + 4, keyUnlimitShuffle.right - 5, keyUnlimitShuffle.bottom - 5, 5, 5);

	}
	setfillcolor(WHITE);
	solidroundrect(keyInitUnlimitTime.left + 4, keyInitUnlimitTime.top + 4, keyInitUnlimitTime.right - 5, keyInitUnlimitTime.bottom - 5, 5, 5);
	solidroundrect(keyInitUnlimitPrompt.left + 4, keyInitUnlimitPrompt.top + 4, keyInitUnlimitPrompt.right - 5, keyInitUnlimitPrompt.bottom - 5, 5, 5);
	solidroundrect(keyInitUnlimitShuffle.left + 4, keyInitUnlimitShuffle.top + 4, keyInitUnlimitShuffle.right - 5, keyInitUnlimitShuffle.bottom - 5, 5, 5);

	EndBatchDraw();
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.mkLButton)
		{
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("(%d,%d)--第%d行，第%d列\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (goldFingerOut.cursorPos(msg)) {
					printf("退出金手指界面\n");
					return;
				}else if (keyUnlimitTime.cursorPos(msg))
				{
					UnlimitTime = !UnlimitTime;
					if (UnlimitTime) {
						setfillcolor(settingTitleColor);
					}
					else {
						setfillcolor(WHITE);
					}
					solidroundrect(keyUnlimitTime.left + 4, keyUnlimitTime.top + 4, keyUnlimitTime.right - 5, keyUnlimitTime.bottom - 5, 5, 5);

				}
				else if (keyUnlimitPrompt.cursorPos(msg))
				{
					UnlimitPrompt = !UnlimitPrompt;
					if (UnlimitPrompt) {
						setfillcolor(settingTitleColor);
					}
					else {
						setfillcolor(WHITE);
					}
					solidroundrect(keyUnlimitPrompt.left + 4, keyUnlimitPrompt.top + 4, keyUnlimitPrompt.right - 5, keyUnlimitPrompt.bottom - 5, 5, 5);

				}
				else if (keyUnlimitShuffle.cursorPos(msg))
				{
					UnlimitShuffle = !UnlimitShuffle;
					if (UnlimitShuffle) {
						setfillcolor(settingTitleColor);
					}
					else {
						setfillcolor(WHITE);
					}
					solidroundrect(keyUnlimitShuffle.left + 4, keyUnlimitShuffle.top + 4, keyUnlimitShuffle.right - 5, keyUnlimitShuffle.bottom - 5, 5, 5);
				}
				else if (keyInitUnlimitTime.cursorPos(msg))
				{
					
					remainTime = 0;
					recordRemainTime();
					setfillcolor(settingTitleColor);
					solidroundrect(keyInitUnlimitTime.left + 4, keyInitUnlimitTime.top + 4, keyInitUnlimitTime.right - 5, keyInitUnlimitTime.bottom - 5, 5, 5);
					Sleep(200);
					setfillcolor(WHITE);
					solidroundrect(keyInitUnlimitTime.left + 4, keyInitUnlimitTime.top + 4, keyInitUnlimitTime.right - 5, keyInitUnlimitTime.bottom - 5, 5, 5);

				}
				else if (keyInitUnlimitPrompt.cursorPos(msg))
				{
					promptTime = 2;
					recordPromptTime();
					setfillcolor(settingTitleColor);
					solidroundrect(keyInitUnlimitPrompt.left + 4, keyInitUnlimitPrompt.top + 4, keyInitUnlimitPrompt.right - 5, keyInitUnlimitPrompt.bottom - 5, 5, 5);
					Sleep(200);
					setfillcolor(WHITE);
					solidroundrect(keyInitUnlimitPrompt.left + 4, keyInitUnlimitPrompt.top + 4, keyInitUnlimitPrompt.right - 5, keyInitUnlimitPrompt.bottom - 5, 5, 5);
				}
				else if (keyInitUnlimitShuffle.cursorPos(msg))
				{
					shuffleTime = 1;
					recordShuffleTime();
					setfillcolor(settingTitleColor);
					solidroundrect(keyInitUnlimitShuffle.left + 4, keyInitUnlimitShuffle.top + 4, keyInitUnlimitShuffle.right - 5, keyInitUnlimitShuffle.bottom - 5, 5, 5);
					Sleep(200);
					setfillcolor(WHITE);
					solidroundrect(keyInitUnlimitShuffle.left + 4, keyInitUnlimitShuffle.top + 4, keyInitUnlimitShuffle.right - 5, keyInitUnlimitShuffle.bottom - 5, 5, 5);
				}
			}
		}
	}
}
void readLocalData() {
	printf("读取本地数据\n");
	FILE *pf;
	//level
	int levelOldInt;
	char levelNow[10] = { '\0' }, levelOld[10] = { '\0' };
	pf = fopen("data\\level_record.txt", "r");
	if (pf == NULL)
	{
		printf("level文件不存在\n");
	}
	else {
		printf("level文件存在\n");
		fgets(levelOld, 10, pf);
		printf("levelOld=%s\n", levelOld);
		level = atoi(levelOld);
	}
	sprintf(levelNow, "%d", level);//将当前level写入代存变量
	pf = fopen("data\\level_record.txt", "w");
	fwrite(levelNow, sizeof(levelNow), 1, pf);
	fclose(pf);
	//promptTime
	int promptTimeOldInt;
	char promptTimeNow[10] = { '\0' }, promptTimeOld[10] = { '\0' };
	pf = fopen("data\\promptTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("promptTime文件不存在\n");
	}
	else {
		printf("promptTime文件存在\n");
		fgets(promptTimeOld, 10, pf);
		printf("promptTimeOld=%s\n", promptTimeOld);
		promptTime = atoi(promptTimeOld);
	}
	sprintf(promptTimeNow, "%d", promptTime);//将当前level写入代存变量
	pf = fopen("data\\promptTime_record.txt", "w");
	fwrite(promptTimeNow, sizeof(promptTimeNow), 1, pf);
	fclose(pf);
	
	//shuffleTime
	int shuffleTimeOldInt;
	char shuffleTimeNow[10] = { '\0' }, shuffleTimeOld[10] = { '\0' };
	pf = fopen("data\\shuffleTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("shuffleTime文件不存在\n");
	}
	else {
		printf("shuffleTime文件存在\n");
		fgets(shuffleTimeOld, 10, pf);
		printf("shuffleTimeOld=%s\n", shuffleTimeOld);
		shuffleTime = atoi(shuffleTimeOld);
	}
	sprintf(shuffleTimeNow, "%d", shuffleTime);//将当前level写入代存变量
	pf = fopen("data\\shuffleTime_record.txt", "w");
	fwrite(shuffleTimeNow, sizeof(shuffleTimeNow), 1, pf);
	fclose(pf);
	//remainTime
	int remainTimeOldInt;
	char remainTimeNow[10] = { '\0' }, remainTimeOld[10] = { '\0' };
	pf = fopen("data\\remainTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("remainTime文件不存在\n");
	}
	else {
		printf("remainTime文件存在\n");
		fgets(remainTimeOld, 10, pf);
		printf("remainTimeOld=%s\n", remainTimeOld);
		remainTime = atoi(remainTimeOld);
	}
	sprintf(remainTimeNow, "%d", remainTime);//将当前level写入代存变量
	pf = fopen("data\\remainTime_record.txt", "w");
	fwrite(remainTimeNow, sizeof(remainTimeNow), 1, pf);
	fclose(pf);
	
	//读取mylove值
	int concealOldInt;
	char concealNow[10] = { '\0' }, concealOld[10] = { '\0' };
	pf = fopen("data\\conceal.txt", "r");
	if (pf == NULL)
	{
		printf("conceal文件不存在\n");
		concealOldInt = 0;
	}
	else {
		printf("conceal文件存在\n");
		fgets(concealOld, 10, pf);
		printf("concealOld=%s\n", concealOld);
		concealOldInt = atoi(concealOld);
		if (concealOldInt == 500823)
		{
			mylove = true;
			printf("密码正确\n");
		}
		else {
			mylove = false;
			printf("密码错误\n");
		}
	}
	sprintf(concealNow, "%d", concealOldInt);//将当前level写入代存变量
	pf = fopen("data\\conceal.txt", "w");
	fwrite(concealNow, sizeof(concealNow), 1, pf);
	fclose(pf);
	
}
void recordLevel() {
	printf("写入level到本地\n");
	FILE *pf;
	int levelOldInt;
	char levelNow[10] = { '\0' }, levelOld[10] = { '\0' };
	pf = fopen("data\\level_record.txt", "r");
	if (pf == NULL)
	{
		printf("文件不存在\n");
		return;
	}
	else {
		printf("文件存在\n");
		sprintf(levelNow, "%d", level);//将当前level写入代存变量
		pf = fopen("data\\level_record.txt", "w");
		fwrite(levelNow, sizeof(levelNow), 1, pf);
		fclose(pf);
	}
	
}
void recordPromptTime() {
	printf("写入promptTime到本地\n");
	FILE *pf;
	int promptTimeOldInt;
	char promptTimeNow[10] = { '\0' }, promptTimeOld[10] = { '\0' };
	pf = fopen("data\\promptTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("promptTime文件不存在\n");
		return;
	}
	else {
		printf("promptTime文件存在\n");
		sprintf(promptTimeNow, "%d", promptTime);//将当前level写入代存变量
		pf = fopen("data\\promptTime_record.txt", "w");
		fwrite(promptTimeNow, sizeof(promptTimeNow), 1, pf);
		fclose(pf);
	}
	
}
void recordShuffleTime() {
	printf("写入shuffleTime到本地\n");
	FILE *pf;
	int shuffleTimeOldInt;
	char shuffleTimeNow[10] = { '\0' }, shuffleTimeOld[10] = { '\0' };
	pf = fopen("data\\shuffleTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("文件不存在\n");
		return;
	}
	else {
		printf("文件存在\n");
		sprintf(shuffleTimeNow, "%d", shuffleTime);//将当前level写入代存变量
		pf = fopen("data\\shuffleTime_record.txt", "w");
		fwrite(shuffleTimeNow, sizeof(shuffleTimeNow), 1, pf);
		fclose(pf);
	}

}
void recordRemainTime() {
	printf("写入remainTime到本地\n");
	FILE *pf;
	int remainTimeOldInt;
	char remainTimeNow[10] = { '\0' }, remainTimeOld[10] = { '\0' };
	pf = fopen("data\\remainTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("文件不存在\n");
		return;
	}
	else {
		printf("文件存在\n");
		sprintf(remainTimeNow, "%d", remainTime);//将当前level写入代存变量
		pf = fopen("data\\remainTime_record.txt", "w");
		fwrite(remainTimeNow, sizeof(remainTimeNow), 1, pf);
		fclose(pf);
	}
}
void recordConceal() {
	printf("写入conceal到本地\n");
	FILE *pf;
	int concealOldInt;
	char concealNow[10] = { '\0' }, concealOld[10] = { '\0' };
	if (mylove)
	{
		
		sprintf(concealNow, "500823");
		
	}
	else {
		
		sprintf(concealNow, "0");
	}
	pf = fopen("data\\conceal.txt", "w");
	fwrite(concealNow, sizeof(concealNow), 1, pf);
	fclose(pf);
}
void displayShuffle() {
	setfillcolor(myloveFill);
	setbkcolor(myloveFill);
	textstyle.lfHeight = 25;
	textstyle.lfWidth = 20;
	settextstyle(&textstyle);
	settextcolor(myloveTC);
	putimage(Reset.left, Reset.top, &img[74]);
	char shuffleTxt[10];
	sprintf(shuffleTxt, "洗牌 %d", gameShuffleTime);
	drawtext(CString(shuffleTxt), &Reset, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void displayPrompt() {
	setfillcolor(myloveFill);
	setbkcolor(myloveFill);
	textstyle.lfHeight = 25;
	textstyle.lfWidth = 20;
	settextstyle(&textstyle);
	settextcolor(myloveTC);
	putimage(Prompt.left, Prompt.top, &img[74]);
	char promptTxt[10];
	sprintf(promptTxt, "提示 %d", gamePromptTime);
	drawtext(CString(promptTxt), &Prompt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

}
void concealWindow() {//隐藏登录界面
	printf("隐藏登录界面\n");
	LPTSTR s= new char[10];
	InputBox(s, 10, "输入密码开启隐藏功能","登录");
	long int password = atoi(s);
	printf("password=%d\n",password);
	if (password==20210122)
	{
		//生成txt文件并输入1
		printf("密码正确\n");
		mylove = true;
	}
	else {
		//删除txt文件
		printf("密码错误\n");
		mylove = false;
	}
	recordConceal();
	delete[] s;
}
void displayLetter() {
	printf("信件显示\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	setbkcolor(WHITE);
	solidroundrect((windowWidth - letterWidth) / 2, (windowHeight - letterHeight) / 2, (windowWidth + letterWidth) / 2, (windowHeight + letterHeight) / 2, 20, 20);
	drawAlpha(&img[75], windowWidth / 2 - img[75].getwidth() / 2, (windowHeight + letterHeight) / 2 - 15 - img[75].getheight() );
	char letterName[10] = { '\0' }, letterContent[800] = { '\0' };
	switch (level)
	{
	case 1:
		sprintf(letterName, "序 幕");
		sprintf(letterContent, "      这一年，小狐狸离开家乡来到了四百公里外的深林大学，准备开始新的学习生活。刚来到这里，小狐狸一个认识的人都没有，他有些担忧。于是，本着向组织看齐的想法，小狐狸加入了同乡会。\n      在群里面，有好多来自家乡的小伙伴们在聊天。小狐狸有趣地看着他们聊天，偶尔也参与一下。在这个过程中，小狐狸注意到了一个可爱的女孩子——小兔子。小兔子在群里面可活跃了，一呼百应，人缘特别好，这让小狐狸印象十分深刻。这时候的小狐狸和小兔子都还不知道，他们的奇妙姻缘从此开始了");
		break;
	case 2:
		sprintf(letterName, "怂 恿");
		sprintf(letterContent, "      学期正式开始，经过学长学姐们的大力宣传，小狐狸都知道了各个社团、组织一年一度的招新工作马上就要开始了。小狐狸有些认生，虽然对此很感兴趣，但孤身一人的他还是不太好意思去参加面试，更不好意思和其他人邀约。\n      于是小狐狸来到了图书馆，准备随便看看书。正在这时，群里小兔子发来消息。原来小兔子所在的胡萝卜公益救援团也开始了招新工作，目前正在紧张的面试环节。小狐狸只是在群里悄悄探出小脑袋一下，就给小兔子薅住了！在小兔子的怂恿下，小狐狸来到了面试地点……");
		break;
	case 3:
		sprintf(letterName, "初 识");
		sprintf(letterContent, "      小狐狸来到了面试地点，迷迷糊糊地就填了个人信息表，随后找了个角安静的角落坐了下来。正打算掏出手机缓解尴尬时，小狐狸余光撇到一个漂亮的身影一蹦一跳地向他走来。小狐狸心里一惊，“啊~怎么有人朝我走来，我也不认识啥人呀~怎么办，怎么办~”\n      “原来你就是小狐狸呀~”\n      小狐狸还处于懵懵的状态，听到对方介绍道：“我是小兔子呀~”\n      啊，之前都是在网上聊天，这是第一次见到真人，原来她就是小兔子呀~小兔子好漂亮呀~这让本来就认生的小狐狸感到更加害羞了。随后的聊天中，小狐狸只敢低着头……只记得小兔子在最后说道：“以后路上见到我，要大声喊我苗苗哦~”");
		break;
	case 4:
		sprintf(letterName, "“邻 居”");
		sprintf(letterContent, "      因为深林大学的改革，小狐狸和小兔子都被分到了新书院，成了名不副实的邻居，因为……男女分层，所以小狐狸住在2楼，而小兔子住在5楼。尽管如此，随后的日子里，小狐狸也是经常遇到小兔子。\n      原本小兔子担心自己近视，走在路上看不清人，所以叫小狐狸看到自己要叫自己，可没想到，小狐狸才是真“眼瞎”。小狐狸走在路上的时候，往往是“两眼不看路旁物”。于是，大部分时候都是小兔子先看到小狐狸，然后吓小狐狸一大跳~不知是那段时间相遇有些多还是命运的暗示，小狐狸居然做梦梦到小兔子成了自己的女朋友~");
		break;
	case 5:
		sprintf(letterName, "风 铃");
		sprintf(letterContent, "      小狐狸逛淘宝的时候，看到了一些很漂亮的晴天娃娃风铃，想着挂在宿舍一定很漂亮，于是买了好几个。想到小兔子住的很近，她一定也很喜欢这种风铃。于是，在到货后小狐狸急忙联系小兔子，问道：“苗苗~苗苗~你在宿舍吗？我最近买了些好看的小物品，送给你一个呀！”小兔子立刻回消息：“在呀！我在五楼空中花园呐~”小狐狸急忙爬楼梯上去。此时太阳公公已经落下，小兔子一个人坐在空中花园，抱着自己的腿腿，好像有些心事。小狐狸将风铃送个小兔子后，想着要不要问一问，但最后还是没敢问出口，一溜烟跑了。啊！真是只胆小的小狐狸！");
		break;
	case 6:
		sprintf(letterName, "溜 冰");
		sprintf(letterContent, "      暑假到啦~小狐狸和小兔子都回到了家乡。虽然他们住在一个城市，但在此之前他们并没有在家乡见过面。机缘巧合之下，小狐狸和小兔子约好一起去溜冰。\n      小狐狸离溜冰场稍远一些，所以到的时候小兔子已经等了一会了。买好票后，两人进入装备区换上溜冰鞋。这时才知道，两人都没溜过真冰……于是两人慢悠悠的走到冰面上。随着慢慢的练习，小狐狸逐渐适应了在冰面滑行。但小兔子还不太敢。于是小狐狸让小兔子抓住他的手臂，慢慢带着小兔子滑了起来。不知怎得，两人慢慢牵到了手。小狐狸一阵心慌~啊啊啊啊啊啊，原来这是小狐狸第一次牵女孩子的手。此时的小狐狸感觉脸红到耳根了哈哈哈");
		break;
	case 7:
		sprintf(letterName, "活 动");
		sprintf(letterContent, "      小狐狸当然顺利地加入了胡萝卜公益救援团，不过呢，他并不在小兔子的部门，所以在团内的平时活动中他们并不多见。最近团内有个传递礼物的活动，上一个同学去盒子中抽取一个纸条，上面是下一个同学的名字，随后将自己的礼物送给下一个同学。\n      小狐狸安静地等待自己的名字被叫到。这时，小兔子被叫了上去，拿到了礼物。接着，她去抽取纸条。“小狐狸~”啊，在叫我吗？这么巧呀~小狐狸屁颠屁颠走了上去，接过了小兔子的礼物。至今小狐狸还记得小兔子的礼物是两个黑色的棉布口罩，御寒能力特别强~却完全不记得自己送了什么礼物给了谁。同时，小狐狸还发现，粗心的小兔子连同一卡通也一并“送”给了小狐狸哈哈哈哈");
		break;
	case 8:
		sprintf(letterName, "相 约");
		sprintf(letterContent, "      时间过得很快，转眼间小狐狸已从深林大学毕业，来到了首都读书。小兔子则刚好和姐妹们约好到首都游玩，他们又一次来到了同一个城市。\n      往常，小狐狸和小兔子也会偶尔互相分享一些趣事。这段时间，由于在同一个城市，小狐狸和小兔子的联系比以往频繁了许多。小兔子告诉小狐狸最近去哪里玩了，哪里有好吃的。小狐狸则更多的分享学校的事情，因为……他还没怎么出过校门。小狐狸想到前一段时间朋友介绍了一家餐厅，味道挺不错，当然，也可能他只知道这家餐厅。如果小兔子有时间，就请她去尝尝。但因小兔子时间太过匆忙，最后他们并没有在首都见面。不过假期就要到了，他们约好在家乡见面聚一下~");
		break;
	case 9:
		sprintf(letterName, "相 聚");
		sprintf(letterContent, "      回到家乡后，小狐狸和小兔子约了一起去吃鸡爪煲。根据小兔子的“精确制导”，小狐狸准确地找到了地点。此时，小狐狸和小兔子已经一年没有见面了。但小狐狸一眼就看到了小兔子。\n      小兔子背对着小狐狸，她的背影都让小狐狸看得有些出神。小狐狸来到小兔子对面坐了下来。他感到无比紧张和害羞，好在小兔子人特别好，慢慢重新熟络起来，小狐狸放松了许多。吃完饭后，两人突发奇想，一起去唱K。小狐狸这才发现，小兔子唱歌也好好听呀~真是个多才多艺的小兔子呀！\n      小狐狸唱歌则很一般，但这不妨碍他一展歌喉，小兔子则乖巧地听着，直到后来，小狐狸才知道，当小狐狸唱的难听时，小兔子地内心戏是“大哥，自己人，别开枪！”");
		break;
	case 10:
		sprintf(letterName, "相 恋");
		sprintf(letterContent, "      放假在家就是会经常感觉无聊。上午，小狐狸和小兔子隔空打了一早上的游戏，也玩腻了。小兔子突发奇想，想出去走走。有了上次聚会的经历，小狐狸也不再害怕和小兔子相约了。他们一起出去散步，吃饭。小狐狸感觉和小兔子在一起玩好开心呀~\n      随后的日子里，小狐狸都特别想找小兔子玩，他发现，自己爱上了小兔子。但是，又不知道小兔子的想法。没确定关系，小狐狸也不太敢经常找小兔子出去玩。终于，在一次和小兔子及其他朋友们一起打完游戏后，小狐狸鼓足了勇气，告白了！虽然彼此之前都有好感，但这仍然让小兔子有些意外。小兔子担心很多事情，小狐狸则绞尽脑汁消除小兔子的疑虑。小狐狸之前从没发现自己的脑袋居然可以转得这么快！终于，在三寸不烂之舌的帮助下，小狐狸和小兔子终于在一起了~~~（宝贝，我们的故事还有很长很长~等我以\n后继续讲给你听！我爱你呦~）");
		break;

	}
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	drawtext(CString(letterName), &letterNameTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	textstyle.lfHeight = 32;
	textstyle.lfWidth = 28;
	settextstyle(&textstyle);
	settextcolor(settingLevelColor);
	drawtext(CString(letterContent), &letterTxt, DT_TOP | DT_WORDBREAK | DT_LEFT);

	EndBatchDraw();
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.mkLButton)
		{
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("(%d,%d)--第%d行，第%d列\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keyLetterOut.cursorPos(msg)) {
					printf("退出设置界面\n");
					return;
				}
			}
		}
	}
}

