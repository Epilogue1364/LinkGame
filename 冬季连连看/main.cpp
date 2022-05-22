#include"library.h"
#include"define.h"
#include"const.h"
#include"class.h"
#include"statement.h"

//������
int main() {
	int no_menu_bar_width = GetSystemMetrics(SM_CXFULLSCREEN);
	int no_menu_bar_height = GetSystemMetrics(SM_CYFULLSCREEN);
	//printf("�޲˵������ڴ�СΪ%d*%d\n", no_menu_bar_width, no_menu_bar_height);
	int have_menu_bar_width = GetSystemMetrics(SM_CXSCREEN);
	int have_menu_bar_height = GetSystemMetrics(SM_CYSCREEN);
	//printf("�޲˵������ڴ�СΪ%d*%d\n", have_menu_bar_width, have_menu_bar_height);
	//printf("���ڴ�СΪ%d*%d\n", windowWidth, windowHeight);
	//��ʼ��
	
	initimg();		//��ʼ��ͼƬ��
	gameMapxy();	//��ʼ����ͼ�����xy����
	readLocalData(); //��ʼ��level��promptTime��shuffleTime��remainTime
	//1 ����
	
	initgraph(windowWidth, windowHeight);
	//initgraph(windowWidth, windowHeight, SHOWCONSOLE);
	HWND hwnd = GetHWnd();
	SetWindowTextW(hwnd, L"����������");
	SetWindowPos(hwnd, HWND_TOP, (no_menu_bar_width-windowWidth)/2-8, 0, windowWidth, windowHeight, SWP_NOSIZE);
	//HICON hIcon = LoadIcon(NULL, (LPCTSTR)IDI_HOUSE);
	//SendMessage(hwnd,)
	
	//1.1��������ж�
	while (1)
	{
		do {
			printf("����main�е�ѭ��\n");
		} while (0);

		if (initvalue) {
			printf("�����ʼ��\n");
			//��ʼ��
			//������ɫ
			setbkcolor(WHITE);		//����ɫ����ʹ��cleardevice����ʱ��ʹ�ø���ɫ�����������
			setfillcolor(WHITE);	//����������ͼ�ε����ɫ ��Ϸ�����汳����ɫ

			//���������ʽ
			textstyle.lfHeight = 50;//����һϵ�������ʽ��textstyle
			textstyle.lfWidth = 30;
			textstyle.lfQuality = PROOF_QUALITY;
			textstyle.lfWeight = 700;//��������Ĵ�ϸ
			_tcscpy(textstyle.lfFaceName, _T("Aa���� (����ҵʹ��)"));
			settextstyle(&textstyle);

			//�����ߵĸ�ʽ
			
			linestyle.thickness = 4;
			setlinestyle(&linestyle);
			setlinecolor(choiceBoxColor);
			initvalue = 0;
		}

		if (!keysExecute()) {
			printf("�رմ��ڲ��������� \n");
			closegraph();
			return 0;
		}

	}
	return 0;
}
//�����水ťִ�в���
bool keysExecute()
{
	printf("����keysExecute()\n");
	cleardevice(); //����
	displayBegin();	//��ʾ��Ϸ������
	//FlushMouseMsgBuffer();	//�����껺��
	MOUSEMSG msg;
	int n = 0;
	while (1)
	{
		//FlushMouseMsgBuffer();	//�����껺��
		//Sleep(50);
		msg = GetMouseMsg();
		while (msg.mkLButton) {
			msg = GetMouseMsg();
			if (!msg.mkLButton) {
				printf("��Ϸ��������������ж�\n");
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
					printf("�˳���Ϸ\n");
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
//��������Ҫ�γɵ��Ƶ�������������������ظ�����Ϊreplication����
void setMap(int _row, int _column, int replication) {
	vector<int> map;	//��˳�򴢴�������
	srand(time(NULL));	//
	int n = 0;
	for (int i = 0; i < ((_row)*(_column) / replication); i++) {
		for (int j = 0; j < replication; j++) {
			map.push_back(i);
		}
	}
	//�ٴ�map�õ�gameMap��
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
				gameMap[i][j].num = map[index];//�����ȡ�ư�˳����뷽����
				map.erase(map.begin() + index);
			}
		}
	}
}
//���ư�˳���ӡ������̨
void printMap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%02d ", gameMap[i][j].num);
		}
		printf("\n");
	}
}
//��ʼ��ͼƬ�࣬����ͼƬ
void initimg() {
	/*
	
	vector<int> pic;	//��˳�򴢴�������
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
//��ʾ������
void displayBegin() {
	printf("����������\n");
	cleardevice();
	setbkcolor(WHITE);				//����ɫ
	setfillcolor(WHITE);	//����������ͼ�ε����ɫ ��Ϸ�����汳����ɫ
	solidrectangle(0, 0, windowWidth, windowHeight);//���Ʊ���ͼ�Ͳ������ɫ
	putimage((windowWidth - img[72].getwidth()) / 2, (windowHeight - img[72].getheight()) / 2, &img[72]);//������ʾ36.png
	//setbkcolor(keyFillColor);
	if (mylove)
	{
		setbkmode(TRANSPARENT);
		textstyle.lfHeight = 45;
		textstyle.lfWidth = 40;
		settextstyle(&textstyle);
		settextcolor(choiceBoxColor);
		drawtext(_T("����ר����"), &MyLoveTxt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		drawtext(_T("2022.05.20"), &MyLoveTxt2, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		setbkmode(OPAQUE);
	}
	
}
//��ʾ��Ϸ����
void displayGame() {
	//printf("������Ϸ����\n");
	BeginBatchDraw();
	//cleardevice();
	setbkcolor(BLACK);				//����ɫ
	setfillcolor(BLACK);	//����������ͼ�ε����ɫ
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
	drawtext(_T("����������"), &ReturnToMain, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Reset.left, Reset.top, Reset.right, Reset.bottom, 40, 40);
	drawtext(_T("ϴ��  "), &Reset, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Prompt.left, Prompt.top, Prompt.right, Prompt.bottom, 40, 40);
	drawtext(_T("��ʾ  "), &Prompt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	//fillroundrect(Pause.left, Pause.top, Pause.right, Pause.bottom, 40, 40);
	drawtext(_T("��ͣ"), &Pause, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
	displayPrompt();
	displayShuffle();
	//gameTimer(360, 360);
}
//������Ϸ
void beginGame() {
	printf("��ʼ��Ϸ\n");
	MOUSEMSG msg;
	bool pitch = false; //��ʾ��ѡ���˼������飬false��ʾδѡ��true��ʾѡ����һ����ѡ��һ������ѡ��һ����������ж���������Ӧ����
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0, xs1 = 0, xs2 = 0, ys1 = 0, ys2 = 0;
	int gameTime=0;
	score = 0;
	while (1) {
		if (levelSet)//���ݹؿ������ƶ�
		{
			printf("���ùؿ�\n");
			gamePromptTime = promptTime;
			gameShuffleTime = shuffleTime;
			printf("level=%d\n",level);
			levelSwitch(level);//����levelѡ�����levelNow�ṹ�ĸ�ֵ
			levelNow = levelswitch;
			degreeOfDifficulty(levelNow._row, levelNow._column);//�����Ѷ�ϵ��
			//printf("degree=%d\n", levelNow._degree);
			//setMap(levelNow._row, levelNow._column, degree[levelNow._degree]);//����ʵ����Ϸ����ֵ���Ƶ��ظ�����������ɷ��õ���ά������
			setMap(levelNow._row, levelNow._column, levelNow._repeTime);//����ʵ����Ϸ����ֵ���Ƶ��ظ�����������ɷ��õ���ά������
			printf("�ظ�����=%d\n", levelNow._repeTime);
			displayGame();	//��ʾ��Ϸ���н���
			if (!haveASolution(xs1, ys1, xs2, ys2))	//����������Ƿ��н⣬��û��������
			{
				do
				{
					shuffle();
				} while (!haveASolution(xs1, ys1, xs2, ys2));

			}
			printMap();		//�ڿ���̨��ӡ����ͼ��
			drawMap();		//����������ӡ����Ϸ����
			setlinecolor(choiceBoxColor);
			setfillcolor(WHITE);	//����������ͼƬ����ɫ
			timeLimit = levelNow._timeLimit+remainTime;
			gameTime = timeLimit;
			timeOld = time(0);
			scoreTimeOld = time(0);
			levelSet = false;//�������ùؿ�
			gameTimer(gameTime, timeLimit);
			displayShuffle();
			displayPrompt();
		}
		if (!UnlimitTime)//����ָ ����ʱ�俪����
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
		while (msg.mkLButton)//��������������
		{
			msg = GetMouseMsg();//����������
			if (!msg.mkLButton) {//������������ɿ�
				if (keyReturnToMain.cursorPos(msg)) {//�������������
					if (0 == PlaySound(TEXT("data\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC))
					{
						printf("music error");
					}
					printf("�˳�����������\n");
					return;
				}
				else if ((msg.x >= gameMap[1][1].x) && (msg.x <= (gameMap[row - 2][column - 2].x + gridSizeWidth + gap)) && (msg.y >= gameMap[1][1].y) && (msg.y <= (gameMap[row - 2][column - 2].y + gridSizeHeight + gap))) {
					//����������������������
					printf("(%d,%d)--��%d�У���%d��\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
					if (gameMap[msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap)][(msg.x - xSpace) / (gridSizeWidth + gap)].num != -1)
					{
						if (!pitch) {//��δѡȡ��һ����
							y1 = (msg.y - ySpace) / (gridSizeHeight + gap);
							x1 = (msg.x - xSpace) / (gridSizeWidth + gap);
							drawrectangle(y1, x1);
							pitch = true;

						}
						else {//��ѡȡһ����
							y2 = (msg.y - ySpace) / (gridSizeHeight + gap);
							x2 = (msg.x - xSpace) / (gridSizeWidth + gap);
							int x3 = x1, y3 = y1, x4 = x2, y4 = y2;
							if (x1 != x2 || y1 != y2)//����ڶ��ε���Ĳ��ǵ�һ�����������
							{
								drawrectangle(y2, x2);
								if (gameMap[y1][x1].num == gameMap[y2][x2].num && canClear(x1, y1, x2, y2, x3, y3, x4, y4))
								{//�����������
									//mciSendString(TEXT("play eliminate"), NULL, 0, NULL);
									if (0==PlaySound(TEXT("data\\eliminate.wav"), NULL, SND_FILENAME | SND_ASYNC))
									{
										printf("music error");
									}
									
									if (!UnlimitTime) {
										//���û�п��޵�ʱ������һ�μ�2s
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
									setfillcolor(WHITE);	//����������ͼƬ����ɫ
									solidroundrect(gameMap[y1][x1].x, gameMap[y1][x1].y, gameMap[y1][x1].x + gridSizeWidth, gameMap[y1][x1].y + gridSizeHeight, 5, 5);
									solidroundrect(gameMap[y2][x2].x, gameMap[y2][x2].y, gameMap[y2][x2].x + gridSizeWidth, gameMap[y2][x2].y + gridSizeHeight, 5, 5);
									drawAlpha(&img[gameMap[y1][x1].num], gameMap[y1][x1].x, gameMap[y1][x1].y);
									drawAlpha(&img[gameMap[y2][x2].num], gameMap[y2][x2].x, gameMap[y2][x2].y);
									gameMap[y1][x1].num = -1;
									gameMap[y2][x2].num = -1;

									//����Ƿ�����δ�����������ȫ������������һ��
									if (clearAllOrNot())//�������
									{
										if (0 == PlaySound(TEXT("data\\victory.wav"), NULL, SND_FILENAME | SND_ASYNC))
										{
											printf("music error");
										}
										promptTime = gamePromptTime;
										shuffleTime = gameShuffleTime;
										levelSet = true;
										Sleep(100);
										printMap();		//�ڿ���̨��ӡ����ͼ��
										drawMap();		//��������������
										//����ר��
										if (mylove)
										{
											displayLetter();
											displayGame();	//��ʾ��Ϸ���н���
											drawMap();		//��������������
										}
										recordScore();
										if (!UnlimitTime&&!UnlimitShuffle&&!UnlimitPrompt)//û������ָ������ʣ��ʱ�䡢���Ѻ�ϴ���ۼӽ���
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
											printf("ͨ������\n");

											level += 1;
											recordLevel();
											if (!informGoOnResult()) {//�������˳�
												return;
											}
										}
										else {//ͨ��
											printf("��ϲ������ͨ�أ�\n");
											level = 1;
											recordLevel();
											if (informFinishResult())
											{
												return;
											}
										}
										
										
										
									}
									else {//û��������
										movePattern(levelNow._movePattern);
										//movePattern(levelNow._movePattern);
										if (!haveASolution(xs1, ys1, xs2, ys2))	//����������Ƿ��н⣬��û��������
										{
											do
											{
												shuffle();
											} while (!haveASolution(xs1, ys1, xs2, ys2));

										}
										Sleep(100);
										printMap();		//�ڿ���̨��ӡ����ͼ��
										drawMap();		//��������������
									}
									
								}
								else {//��������Ա�����
									drawMap();		//��������������
									y1 = y2;
									x1 = x2;
									drawrectangle(y1, x1);//��ѡ�еĵ�һ���Ƹ�Ϊ�ڶ�����
								}
							}
						}
					}
				}
				else if (keyReset.cursorPos(msg))
				{
					//�����㷨
					printf("ϴ��\n");
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
						printMap();		//�ڿ���̨��ӡ����ͼ��
						drawMap();		//��������������
					}
					

				}
				else if (keyPrompt.cursorPos(msg))
				{
					//��ʾ�㷨
					printf("��ʾ\n");
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
					printf("��ͣ\n");
					pauseWindow();
					pitch = false;
					timeOld = time(0);
					scoreTimeOld = time(0);
					displayGame();	//��ʾ��Ϸ���н���
					gameTimer(gameTime, timeLimit);
					printMap();		//�ڿ���̨��ӡ����ͼ��
					drawMap();		//��������������
					
				}
				else {
					printf("(%d,%d)\n", msg.x, msg.y);
				}
			}
		}
		
	}
}
//���ý���
void setting() {
	printf("�������ý���\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - settingWidth) / 2, (windowHeight - settingHeight) / 2, (windowWidth + settingWidth) / 2, (windowHeight + settingHeight) / 2, 20, 20);
	drawAlpha(&img[73],windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + settingHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("ѡ��ؿ�"), &settingTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
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
				printf("(%d,%d)--��%d�У���%d��\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keySettingOut.cursorPos(msg)) {
					recordLevel();
					printf("�˳����ý���\n");
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
//���а����
void rankWindow() {
	printf("�������а����\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - rankWidth) / 2, (windowHeight - rankHeight) / 2, (windowWidth + rankWidth) / 2, (windowHeight + rankHeight) / 2, 20, 20);
	drawAlpha(&img[73], windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + rankHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("��߼�¼"), &rankTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
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
		sprintf(rankLevel, "��%d��", i+1);
		drawtext(CString(rankLevel), &rankLevelTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		levelSwitch(i + 1);
		levelDisplay = levelswitch;
		printf("%s\n", levelDisplay._rankName);
		
		if (!(pf = fopen(levelDisplay._rankName, "r")))
		{
			drawtext(_T("���޼�¼"), &rankScoreTxt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
				printf("(%d,%d)--��%d�У���%d��\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keySettingOut.cursorPos(msg)) {
					printf("�˳����ý���\n");
					return;
				}
			}
		}
	}
}
//��������ͼƬ����������Ƭ
void drawMap() {
	BeginBatchDraw();
	setfillcolor(BLACK);	//����������ͼ�ε����ɫ
	solidrectangle(gameMap[0][0].x-5, gameMap[0][0].y - 5, gameMap[row-1][column-1].x + gridSizeWidth + 5, gameMap[row - 1][column - 1].x + gridSizeHeight + 5); //����������ͼ����ֵķ���
	//solidrectangle(xSpace, ySpace, xSpace + bkWidth, ySpace + bkHeight);
	setfillcolor(WHITE);	//����������ͼƬ����ɫ
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			//putimage(j*gridSizeWidth + 25, i*gridSizeHeight + 25, gridSizeWidth, gridSizeHeight, &img[39],0,0);
			//putimage(j*gridSizeWidth + 25, i*gridSizeHeight + 25,  &img[gameMap[i][j]]);
			if (gameMap[i][j].num != -1) {
				//������ͼ
				solidroundrect(gameMap[i][j].x, gameMap[i][j].y, gameMap[i][j].x + gridSizeWidth, gameMap[i][j].y + gridSizeHeight, 5, 5);
				//��������ͼ
				drawAlpha(&img[gameMap[i][j].num], gameMap[i][j].x, gameMap[i][j].y);
			}
		}
	}
	setbkcolor(BLACK);				//����ɫ
	setfillcolor(BLACK);	//����������ͼ�ε����ɫ
	settextcolor(levelNameColor);
	textstyle.lfHeight = 45;
	textstyle.lfWidth = 35;
	settextstyle(&textstyle);
	drawtext(CString(levelNow._levelName), &levelNameAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	settextcolor(scoreTxtColor);
	drawtext(_T("�÷�"), &scoreTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_itot(score,scoreChar,10), &scoreAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	settextcolor(repeTimeColor);
	drawtext(_T("�ظ�����"), &repeTimTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_itot(levelNow._repeTime, repeTimeChar, 10), &repeTimeAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	EndBatchDraw();
}
//����ѡ���
void drawrectangle(short y, short x) {
	LINESTYLE linestyle;
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	setlinecolor(choiceBoxColor);
	rectangle(gameMap[y][x].x - 2, gameMap[y][x].y - 2, gameMap[y][x].x + 2 + gridSizeWidth, gameMap[y][x].y + 2 + gridSizeHeight);

}

// ����PNGͼ��ȥ͸������
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//����������xy��������
void gameMapxy() {
	for (int i = 0; i < row*column; i++) {
		gameMap[i / column][i%column].x = (i%column)*gridSizeWidth + xSpace + (i%column) * gap;
		gameMap[i / column][i%column].y = (i / column)* gridSizeHeight + ySpace + (i / column) * gap;
	}
}
//ϴ��
void shuffle() {
	vector<int> card;	//���ڴ�Ż�δ����������
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
//�����ͼ������ֵ�������Ѷ�����
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

//�ж����������Ƿ�������
bool canClear(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4) {
	if (x1 == x2 || y1 == y2)//1���������� 2�������ͨ��һ��ֱ������
	{
		if (oneLineCon(x1, y1, x2, y2))
		{
			return true;
		}
	}
	//3�������ͨ������ֱ������ 4�������ͨ������������ 
	if (twoLineCon(x1, y1, x2, y2, x3, y3) || threeLineCon(x1, y1, x2, y2, x3, y3, x4, y4)) {
		return true;
	}
	return false;
}
//�ж���һ�е����������Ƿ�������
bool rowDirectCon(int x1, int x2, int y) {//����y���ϵ���������
	int smaller = x1<x2 ? x1 : x2, bigger = x1>x2 ? x1 : x2;
	for (int i = smaller + 1; i < bigger; i++) {//���������֮���м������������Ƿ���δ��������
		if (gameMap[y][i].num != -1)//�����δ��������
			return false;
	}
	return true;//���������֮��û�м�������м����û������
}
//�ж���һ�е����������Ƿ�������
bool columnDirectCon(int y1, int y2, int x) {//����x���ϵ���������
	int smaller = y1<y2 ? y1 : y2, bigger = y1>y2 ? y1 : y2;
	for (int i = smaller + 1; i < bigger; i++) {//���������֮���м������������Ƿ���δ��������
		if (gameMap[i][x].num != -1)//�����δ��������
			return false;
	}
	return true;//���������֮��û�м�������м����û������
}
//�����ͬһ�л���ͬһ�У��ж��Ƿ���ͨ��һ��ֱ�����ӣ���������
bool oneLineCon(int x1, int y1, int x2, int y2) {
	if (x1 == x2)
	{
		if (columnDirectCon(y1, y2, x1))
			return true;
	}
	else {//����ͬһ�бض���ͬһ��
		if (rowDirectCon(x1, x2, y1))
			return true;
	}
	return false; //�޷�ͨ��һ��������
}
//�ж��Ƿ����ͨ������������
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
//�ж��Ƿ����ͨ������������
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
//�������������������ĵ���
void drawLine(short x1, short y1, short x2, short y2) {
	LINESTYLE linestyle;
	linestyle.thickness = 4;
	setlinestyle(&linestyle);
	//setlinecolor(choiceBoxColor);
	line(gameMap[y1][x1].x + gridSizeWidth / 2, gameMap[y1][x1].y + gridSizeHeight / 2, gameMap[y2][x2].x + gridSizeWidth / 2, gameMap[y2][x2].y + gridSizeHeight / 2);
}
//����level��ֵ������Ӧ�ṹ��Ϣ�levelNow
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

//����Ƿ�������һ����
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
	case 1://����

		break;
	case 2://��������ɢ
		topBottom();
		break;
	case 3://��������ɢ
		leftRight();
		break;
	case 4://��������ɢ
		topBottom();
		leftRight();
		break;
	case 5://���¾ۼ�
		goBottom();
		break;
	case 6://����ۼ�
		goLeft();
		break;
	case 7://�м�ۼ�
		leftRightGoCenter();
		topBottomGoCenter();
		break;
	}
}
void topBottom() {
	for (int j = (column - levelNow._column) / 2; j < column - (column - levelNow._column) / 2; j++)
	{
		for (int i = (row - levelNow._row) / 2; i < row / 2 - 1; i++) {
			if (gameMap[i][j].num == -1)//�����һ��λ�ó����˱���������
			{
				if (gameMap[i + 1][j].num != -1)//����������û�б���������������½�
				{
					gameMap[i][j].num = gameMap[i + 1][j].num;
					gameMap[i + 1][j].num = -1;
				}
				else if ((i + 2) <= (row / 2 - 1) && gameMap[i + 2][j].num != -1)//if(gameMap[i + 1][j].num == -1)//����������Ҳ��������
				{
					//���i+2û�г����м�������û������
					gameMap[i][j].num = gameMap[i + 2][j].num;//��i+2�����Ƶ�i��
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
			if (gameMap[i][j].num == -1)//�����һ��λ�ó����˱���������
			{
				if (gameMap[i + 1][j].num != -1)//����������û�б���������������½�
				{
					gameMap[i][j].num = gameMap[i + 1][j].num;
					gameMap[i + 1][j].num = -1;
				}
				else if ((i + 2) <= (row - (row - levelNow._row) / 2 - 1) && gameMap[i + 2][j].num != -1)//if(gameMap[i + 1][j].num == -1)//����������Ҳ��������
				{
					//���i+2û�г����м�������û������
					gameMap[i][j].num = gameMap[i + 2][j].num;//��i+2�����Ƶ�i��
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
bool clearAllOrNot() {//trueΪ����գ�falseΪδ���
	vector<int> remainCard;//���ڴ�Ż�δ����������
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
	drawtext(_T("��ϲͨ������"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	if (recordBreak)
	{
		drawtext(_T("���Ƽ�¼"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("��������"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("����"), &informGoOnTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("�˳�"), &informQuitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informGoOnResult() {
	informGoOn();//��ʾ֪ͨ��
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//��������������
		{
			msg = GetMouseMsg();//����������
			if (!msg.mkLButton) {//������������ɿ�
				if (keyQuit.cursorPos(msg)) {//�������������
					printf("���ټ���\n");
					return false;
				}
				else if (keyGoOn.cursorPos(msg))
				{
					printf("������Ϸ\n");
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
	drawtext(_T("��ϲͨ��"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	if (recordBreak)
	{
		drawtext(_T("���Ƽ�¼"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("��������"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("����������"), &informGoBack, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informFinishResult() {
	informFinish();//��ʾ֪ͨ��
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//��������������
		{
			msg = GetMouseMsg();//����������
			if (!msg.mkLButton) {//������������ɿ�
				if (keyGoBack.cursorPos(msg)) {//�������������
					printf("����������\n");
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
	drawtext(_T("ʱ�䵽"), &informTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("��Ϸ����"), &informTxt2, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	setbkcolor(settingTitleColor);
	settextcolor(WHITE);
	drawtext(_T("�ؿ�"), &informGoOnTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("�˳�"), &informQuitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();
}
bool informTimeOverResult() {
	informTimeOver();
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton)//��������������
		{
			msg = GetMouseMsg();//����������
			if (!msg.mkLButton) {//������������ɿ�
				if (keyQuit.cursorPos(msg)) {//�������������
					printf("ʱ�䵽����Ϸʧ�ܣ��˳�\n");
					return false;
				}
				else if (keyGoOn.cursorPos(msg))
				{
					printf("ʱ�䵽�����¿�ʼ��Ϸ\n");
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
	printf("��¼����\n");
	FILE *pf;
	int scrOldInt;
	char scrNow[10] = {'\0'}, scrOld[10] = { '\0' };
	pf = fopen(levelNow._rankName, "r");
	if (pf==NULL)
	{
		printf("�ļ�������\n");
		sprintf(scrNow, "%d", score);
		recordBreak = true;
	}
	else {
		printf("�ļ�����\n");
		//fread(scrOld, sizeof(scrOld), 1, pf);
		fgets(scrOld, 10, pf);
		printf("scrOld=%s\n", scrOld);
		scrOldInt = atoi(scrOld);
		pf = fopen(levelNow._rankName, "w");
		if (scrOldInt <score)
		{
			printf("���Ƽ�¼\n");
			sprintf(scrNow, "%d", score);
			recordBreak = true;
		}
		else {
			printf("û���Ƽ�¼\n");
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
	printf("�������ý���\n");
	BeginBatchDraw();
	setbkcolor(BLACK);
	setfillcolor(BLACK);	//����������ͼ�ε����ɫ
	settextcolor(levelNameColor);
	solidrectangle(0, 0, windowWidth, windowHeight); //����������ͼ����ֵķ���
	textstyle.lfHeight = 65;
	textstyle.lfWidth = 55;
	settextstyle(&textstyle);
	drawtext(_T("��Ϸ��ͣ"), &pauseTxtAre, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	textstyle.lfHeight = 35;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	settextcolor(scoreTxtColor);
	drawtext(_T("���������������Ϸ"), &pauseTxtAre2, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);
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
	printf("�������ָ����\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	solidroundrect((windowWidth - goldFingerWidth) / 2, (windowHeight - goldFingerHeight) / 2, (windowWidth + goldFingerWidth) / 2, (windowHeight + goldFingerHeight) / 2, 20, 20);
	drawAlpha(&img[73], windowWidth / 2 - img[73].getwidth() / 2, (windowHeight + goldFingerHeight) / 2 - 10 - img[73].getheight());
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 40;
	settextstyle(&textstyle);
	settextcolor(settingTitleColor);
	setbkcolor(WHITE);
	drawtext(_T("����ָ"), &goldFingerTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	char goldFingerName[3][10] = {'\0'};
	sprintf(goldFingerName[0], "��Ϸʱ��");
	sprintf(goldFingerName[1], "���Ѵ���");
	sprintf(goldFingerName[2], "ϴ�ƴ���");
	textstyle.lfHeight = 30;
	textstyle.lfWidth = 25;
	settextstyle(&textstyle);
	settextcolor(settingLevelColor);
	drawtext(_T("����"), &unlimitTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	drawtext(_T("����"), &initTxt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
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
		//���� ѡ���
		fillroundrect((windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth+50+ leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap)+ (levelHeight-goldFingerSwitchHeight)/2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50+goldFingerSwitchWidth + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + i * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2+ goldFingerSwitchHeight, 5, 5);
		//���� ����
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
				printf("(%d,%d)--��%d�У���%d��\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (goldFingerOut.cursorPos(msg)) {
					printf("�˳�����ָ����\n");
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
	printf("��ȡ��������\n");
	FILE *pf;
	//level
	int levelOldInt;
	char levelNow[10] = { '\0' }, levelOld[10] = { '\0' };
	pf = fopen("data\\level_record.txt", "r");
	if (pf == NULL)
	{
		printf("level�ļ�������\n");
	}
	else {
		printf("level�ļ�����\n");
		fgets(levelOld, 10, pf);
		printf("levelOld=%s\n", levelOld);
		level = atoi(levelOld);
	}
	sprintf(levelNow, "%d", level);//����ǰlevelд��������
	pf = fopen("data\\level_record.txt", "w");
	fwrite(levelNow, sizeof(levelNow), 1, pf);
	fclose(pf);
	//promptTime
	int promptTimeOldInt;
	char promptTimeNow[10] = { '\0' }, promptTimeOld[10] = { '\0' };
	pf = fopen("data\\promptTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("promptTime�ļ�������\n");
	}
	else {
		printf("promptTime�ļ�����\n");
		fgets(promptTimeOld, 10, pf);
		printf("promptTimeOld=%s\n", promptTimeOld);
		promptTime = atoi(promptTimeOld);
	}
	sprintf(promptTimeNow, "%d", promptTime);//����ǰlevelд��������
	pf = fopen("data\\promptTime_record.txt", "w");
	fwrite(promptTimeNow, sizeof(promptTimeNow), 1, pf);
	fclose(pf);
	
	//shuffleTime
	int shuffleTimeOldInt;
	char shuffleTimeNow[10] = { '\0' }, shuffleTimeOld[10] = { '\0' };
	pf = fopen("data\\shuffleTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("shuffleTime�ļ�������\n");
	}
	else {
		printf("shuffleTime�ļ�����\n");
		fgets(shuffleTimeOld, 10, pf);
		printf("shuffleTimeOld=%s\n", shuffleTimeOld);
		shuffleTime = atoi(shuffleTimeOld);
	}
	sprintf(shuffleTimeNow, "%d", shuffleTime);//����ǰlevelд��������
	pf = fopen("data\\shuffleTime_record.txt", "w");
	fwrite(shuffleTimeNow, sizeof(shuffleTimeNow), 1, pf);
	fclose(pf);
	//remainTime
	int remainTimeOldInt;
	char remainTimeNow[10] = { '\0' }, remainTimeOld[10] = { '\0' };
	pf = fopen("data\\remainTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("remainTime�ļ�������\n");
	}
	else {
		printf("remainTime�ļ�����\n");
		fgets(remainTimeOld, 10, pf);
		printf("remainTimeOld=%s\n", remainTimeOld);
		remainTime = atoi(remainTimeOld);
	}
	sprintf(remainTimeNow, "%d", remainTime);//����ǰlevelд��������
	pf = fopen("data\\remainTime_record.txt", "w");
	fwrite(remainTimeNow, sizeof(remainTimeNow), 1, pf);
	fclose(pf);
	
	//��ȡmyloveֵ
	int concealOldInt;
	char concealNow[10] = { '\0' }, concealOld[10] = { '\0' };
	pf = fopen("data\\conceal.txt", "r");
	if (pf == NULL)
	{
		printf("conceal�ļ�������\n");
		concealOldInt = 0;
	}
	else {
		printf("conceal�ļ�����\n");
		fgets(concealOld, 10, pf);
		printf("concealOld=%s\n", concealOld);
		concealOldInt = atoi(concealOld);
		if (concealOldInt == 500823)
		{
			mylove = true;
			printf("������ȷ\n");
		}
		else {
			mylove = false;
			printf("�������\n");
		}
	}
	sprintf(concealNow, "%d", concealOldInt);//����ǰlevelд��������
	pf = fopen("data\\conceal.txt", "w");
	fwrite(concealNow, sizeof(concealNow), 1, pf);
	fclose(pf);
	
}
void recordLevel() {
	printf("д��level������\n");
	FILE *pf;
	int levelOldInt;
	char levelNow[10] = { '\0' }, levelOld[10] = { '\0' };
	pf = fopen("data\\level_record.txt", "r");
	if (pf == NULL)
	{
		printf("�ļ�������\n");
		return;
	}
	else {
		printf("�ļ�����\n");
		sprintf(levelNow, "%d", level);//����ǰlevelд��������
		pf = fopen("data\\level_record.txt", "w");
		fwrite(levelNow, sizeof(levelNow), 1, pf);
		fclose(pf);
	}
	
}
void recordPromptTime() {
	printf("д��promptTime������\n");
	FILE *pf;
	int promptTimeOldInt;
	char promptTimeNow[10] = { '\0' }, promptTimeOld[10] = { '\0' };
	pf = fopen("data\\promptTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("promptTime�ļ�������\n");
		return;
	}
	else {
		printf("promptTime�ļ�����\n");
		sprintf(promptTimeNow, "%d", promptTime);//����ǰlevelд��������
		pf = fopen("data\\promptTime_record.txt", "w");
		fwrite(promptTimeNow, sizeof(promptTimeNow), 1, pf);
		fclose(pf);
	}
	
}
void recordShuffleTime() {
	printf("д��shuffleTime������\n");
	FILE *pf;
	int shuffleTimeOldInt;
	char shuffleTimeNow[10] = { '\0' }, shuffleTimeOld[10] = { '\0' };
	pf = fopen("data\\shuffleTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("�ļ�������\n");
		return;
	}
	else {
		printf("�ļ�����\n");
		sprintf(shuffleTimeNow, "%d", shuffleTime);//����ǰlevelд��������
		pf = fopen("data\\shuffleTime_record.txt", "w");
		fwrite(shuffleTimeNow, sizeof(shuffleTimeNow), 1, pf);
		fclose(pf);
	}

}
void recordRemainTime() {
	printf("д��remainTime������\n");
	FILE *pf;
	int remainTimeOldInt;
	char remainTimeNow[10] = { '\0' }, remainTimeOld[10] = { '\0' };
	pf = fopen("data\\remainTime_record.txt", "r");
	if (pf == NULL)
	{
		printf("�ļ�������\n");
		return;
	}
	else {
		printf("�ļ�����\n");
		sprintf(remainTimeNow, "%d", remainTime);//����ǰlevelд��������
		pf = fopen("data\\remainTime_record.txt", "w");
		fwrite(remainTimeNow, sizeof(remainTimeNow), 1, pf);
		fclose(pf);
	}
}
void recordConceal() {
	printf("д��conceal������\n");
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
	sprintf(shuffleTxt, "ϴ�� %d", gameShuffleTime);
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
	sprintf(promptTxt, "��ʾ %d", gamePromptTime);
	drawtext(CString(promptTxt), &Prompt, DT_VCENTER | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

}
void concealWindow() {//���ص�¼����
	printf("���ص�¼����\n");
	LPTSTR s= new char[10];
	InputBox(s, 10, "�������뿪�����ع���","��¼");
	long int password = atoi(s);
	printf("password=%d\n",password);
	if (password==20210122)
	{
		//����txt�ļ�������1
		printf("������ȷ\n");
		mylove = true;
	}
	else {
		//ɾ��txt�ļ�
		printf("�������\n");
		mylove = false;
	}
	recordConceal();
	delete[] s;
}
void displayLetter() {
	printf("�ż���ʾ\n");
	BeginBatchDraw();
	setfillcolor(WHITE);
	setbkcolor(WHITE);
	solidroundrect((windowWidth - letterWidth) / 2, (windowHeight - letterHeight) / 2, (windowWidth + letterWidth) / 2, (windowHeight + letterHeight) / 2, 20, 20);
	drawAlpha(&img[75], windowWidth / 2 - img[75].getwidth() / 2, (windowHeight + letterHeight) / 2 - 15 - img[75].getheight() );
	char letterName[10] = { '\0' }, letterContent[800] = { '\0' };
	switch (level)
	{
	case 1:
		sprintf(letterName, "�� Ļ");
		sprintf(letterContent, "      ��һ�꣬С�����뿪�����������İٹ���������ִ�ѧ��׼����ʼ�µ�ѧϰ������������С����һ����ʶ���˶�û�У�����Щ���ǡ����ǣ���������֯������뷨��С���������ͬ��ᡣ\n      ��Ⱥ���棬�кö����Լ����С����������졣С������Ȥ�ؿ����������죬ż��Ҳ����һ�¡�����������У�С����ע�⵽��һ���ɰ���Ů���ӡ���С���ӡ�С������Ⱥ����ɻ�Ծ�ˣ�һ����Ӧ����Ե�ر�ã�����С����ӡ��ʮ����̡���ʱ���С�����С���Ӷ�����֪�������ǵ�������Ե�Ӵ˿�ʼ��");
		break;
	case 2:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      ѧ����ʽ��ʼ������ѧ��ѧ���ǵĴ���������С���궼֪���˸������š���֯һ��һ�ȵ����¹������Ͼ�Ҫ��ʼ�ˡ�С������Щ��������Ȼ�Դ˺ܸ���Ȥ��������һ�˵������ǲ�̫����˼ȥ�μ����ԣ���������˼����������Լ��\n      ����С����������ͼ��ݣ�׼����㿴���顣������ʱ��Ⱥ��С���ӷ�����Ϣ��ԭ��С�������ڵĺ��ܲ������Ԯ��Ҳ��ʼ�����¹�����Ŀǰ���ڽ��ŵ����Ի��ڡ�С����ֻ����Ⱥ������̽��С�Դ�һ�£��͸�С����޶ס�ˣ���С���ӵ������£�С�������������Եص㡭��");
		break;
	case 3:
		sprintf(letterName, "�� ʶ");
		sprintf(letterContent, "      С�������������Եص㣬���Ժ����ؾ����˸�����Ϣ��������˸��ǰ����Ľ��������������������ͳ��ֻ���������ʱ��С�������Ʋ��һ��Ư������Ӱһ��һ��������������С��������һ��������~��ô���˳�����������Ҳ����ʶɶ��ѽ~��ô�죬��ô��~��\n      ��ԭ�������С����ѽ~��\n      С���껹�������µ�״̬�������Է����ܵ���������С����ѽ~��\n      ����֮ǰ�������������죬���ǵ�һ�μ������ˣ�ԭ��������С����ѽ~С���Ӻ�Ư��ѽ~���ñ�����������С����е����Ӻ����ˡ����������У�С����ֻ�ҵ���ͷ����ֻ�ǵ�С���������˵�������Ժ�·�ϼ����ң�Ҫ������������Ŷ~��");
		break;
	case 4:
		sprintf(letterName, "���� �ӡ�");
		sprintf(letterContent, "      ��Ϊ���ִ�ѧ�ĸĸС�����С���Ӷ����ֵ�������Ժ������������ʵ���ھӣ���Ϊ������Ů�ֲ㣬����С����ס��2¥����С����ס��5¥��������ˣ����������С����Ҳ�Ǿ�������С���ӡ�\n      ԭ��С���ӵ����Լ����ӣ�����·�Ͽ������ˣ����Խ�С���꿴���Լ�Ҫ���Լ�����û�뵽��С��������桰��Ϲ����С��������·�ϵ�ʱ�������ǡ����۲���·��������ǣ��󲿷�ʱ����С�����ȿ���С���꣬Ȼ����С����һ����~��֪���Ƕ�ʱ��������Щ�໹�����˵İ�ʾ��С�����Ȼ�����ε�С���ӳ����Լ���Ů����~");
		break;
	case 5:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      С������Ա���ʱ�򣬿�����һЩ��Ư�����������޷��壬���Ź�������һ����Ư�����������˺ü������뵽С����ס�ĺܽ�����һ��Ҳ��ϲ�����ַ��塣���ǣ��ڵ�����С���꼱æ��ϵС���ӣ��ʵ���������~����~�������������������Щ�ÿ���С��Ʒ���͸���һ��ѽ����С�������̻���Ϣ������ѽ��������¥���л�԰��~��С���꼱æ��¥����ȥ����ʱ̫�������Ѿ����£�С����һ�������ڿ��л�԰�������Լ������ȣ�������Щ���¡�С���꽫�����͸�С���Ӻ�����Ҫ��Ҫ��һ�ʣ��������û���ʳ��ڣ�һ�������ˡ���������ֻ��С��С���꣡");
		break;
	case 6:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      ��ٵ���~С�����С���Ӷ��ص��˼��硣��Ȼ����ס��һ�����У����ڴ�֮ǰ���ǲ�û���ڼ�������档��Ե�ɺ�֮�£�С�����С����Լ��һ��ȥ�����\n      С�������������ԶһЩ�����Ե���ʱ��С�����Ѿ�����һ���ˡ����Ʊ�����˽���װ�����������Ь����ʱ��֪�������˶�û�����������������������Ƶ��ߵ������ϡ�������������ϰ��С��������Ӧ���ڱ��滬�С���С���ӻ���̫�ҡ�����С������С����ץס�����ֱۣ���������С���ӻ�����������֪���ã���������ǣ�����֡�С����һ���Ļ�~��������������ԭ������С�����һ��ǣŮ���ӵ��֡���ʱ��С����о����쵽�����˹�����");
		break;
	case 7:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      С���굱Ȼ˳���ؼ����˺��ܲ������Ԯ�ţ������أ���������С���ӵĲ��ţ����������ڵ�ƽʱ������ǲ����������������и���������Ļ����һ��ͬѧȥ�����г�ȡһ��ֽ������������һ��ͬѧ�����֣�����Լ��������͸���һ��ͬѧ��\n      С���갲���صȴ��Լ������ֱ��е�����ʱ��С���ӱ�������ȥ���õ���������ţ���ȥ��ȡֽ������С����~�������ڽ�������ô��ѽ~С����ƨ��ƨ��������ȥ���ӹ���С���ӵ��������С���껹�ǵ�С���ӵ�������������ɫ���޲����֣����������ر�ǿ~ȴ��ȫ���ǵ��Լ�����ʲô�������˭��ͬʱ��С���껹���֣����ĵ�С������ͬһ��ͨҲһ�����͡�����С�����������");
		break;
	case 8:
		sprintf(letterName, "�� Լ");
		sprintf(letterContent, "      ʱ����úܿ죬ת�ۼ�С�����Ѵ����ִ�ѧ��ҵ���������׶����顣С������պúͽ�����Լ�õ��׶����棬������һ��������ͬһ�����С�\n      ������С�����С����Ҳ��ż���������һЩȤ�¡����ʱ�䣬������ͬһ�����У�С�����С���ӵ���ϵ������Ƶ������ࡣС���Ӹ���С�������ȥ�������ˣ������кóԵġ�С���������ķ���ѧУ�����飬��Ϊ��������û��ô����У�š�С�����뵽ǰһ��ʱ�����ѽ�����һ�Ҳ�����ζ��ͦ������Ȼ��Ҳ������ֻ֪����Ҳ��������С������ʱ�䣬������ȥ����������С����ʱ��̫����æ��������ǲ�û�����׶����档�������ھ�Ҫ���ˣ�����Լ���ڼ�������һ��~");
		break;
	case 9:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      �ص������С�����С����Լ��һ��ȥ�Լ�צ�ҡ�����С���ӵġ���ȷ�Ƶ�����С����׼ȷ���ҵ��˵ص㡣��ʱ��С�����С�����Ѿ�һ��û�м����ˡ���С����һ�۾Ϳ�����С���ӡ�\n      С���ӱ�����С���꣬���ı�Ӱ����С���꿴����Щ����С��������С���Ӷ����������������е��ޱȽ��źͺ��ߣ�����С�������ر�ã�������������������С�����������ࡣ���극������ͻ�����룬һ��ȥ��K��С������ŷ��֣�С���ӳ���Ҳ�ú���ѽ~���Ǹ���Ŷ��յ�С����ѽ��\n      С���곪�����һ�㣬���ⲻ������һչ���С��������ɵ����ţ�ֱ��������С�����֪������С���곪������ʱ��С���ӵ�����Ϸ�ǡ���磬�Լ��ˣ���ǹ����");
		break;
	case 10:
		sprintf(letterName, "�� ��");
		sprintf(letterContent, "      �ż��ڼҾ��ǻᾭ���о����ġ����磬С�����С���Ӹ��մ���һ���ϵ���Ϸ��Ҳ�����ˡ�С����ͻ�����룬���ȥ���ߡ������ϴξۻ�ľ�����С����Ҳ���ٺ��º�С������Լ�ˡ�����һ���ȥɢ�����Է���С����о���С������һ����ÿ���ѽ~\n      ���������С���궼�ر�����С�����棬�����֣��Լ�������С���ӡ����ǣ��ֲ�֪��С���ӵ��뷨��ûȷ����ϵ��С����Ҳ��̫�Ҿ�����С���ӳ�ȥ�档���ڣ���һ�κ�С���Ӽ�����������һ�������Ϸ��С�������������������ˣ���Ȼ�˴�֮ǰ���кøУ�������Ȼ��С������Щ���⡣С���ӵ��ĺܶ����飬С������ʾ���֭����С���ӵ����ǡ�С����֮ǰ��û�����Լ����Դ���Ȼ����ת����ô�죡���ڣ������粻��֮��İ����£�С�����С����������һ����~~~�����������ǵĹ��»��кܳ��ܳ�~������\n����������������Ұ�����~��");
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
				printf("(%d,%d)--��%d�У���%d��\n", msg.x, msg.y, (msg.y - ySpace) / (gridSizeHeight + gap) + 1, (msg.x - xSpace) / (gridSizeWidth + gap) + 1);
				if (keyLetterOut.cursorPos(msg)) {
					printf("�˳����ý���\n");
					return;
				}
			}
		}
	}
}

