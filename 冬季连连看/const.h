#pragma once
//��������
const short column = 22;	//����ͼ����
const short row = 18;		//����ͼ����
const short gridSizeWidth = 35;	//�����
const short gridSizeHeight = 35;	//�����
const short xSpace = 60;		//���򵥱߿հ�
const short ySpace = 0;		//���򵥱߿հ�
const short gap = 5;		//�����϶
const short bkWidth = column * gridSizeWidth + (column - 1)*gap; //��������Ŀ�
const short bkHeight = row * gridSizeHeight + (row - 1)*gap; //��������Ŀ�
const short noticeBoard = 250;	//��ʾ�ƿ��
const short otherHeight = 0;	//���ȸ���ֵ
const short keyWidth = 120;
//���մ��ڴ�СΪ900*520
//const short windowWidth = 900 *1.2;
//const short windowHeight = 520 * 1.2;
short windowWidth = xSpace * 2 + gridSizeWidth * column + (column - 1)*gap + noticeBoard; //���ڿ�
short windowHeight = ySpace * 2 + gridSizeHeight * row + (row - 1)*gap + otherHeight;//���ڸ�
const short settingWidth = 400, settingHeight = 700;
const short goldFingerWidth = 400, goldFingerHeight = 400, goldFingerBoxWidth=200;
const short goldFingerSwitchWidth = 30, goldFingerSwitchHeight = 30;
const short rankWidth = 400, rankHeight = 700;
const short levelHeight = 40, levelGap = 15;
const short levelNameAreWidth = 300, levelNameAreHeight = 45;
const short informWidth = 300, informHeight = 200;
const short informTxtHeight1 = 20, informTxtHeight2 = 70;
const short informTxt2Height1 = 80, informTxt2Height2 = 130;
const short keyLevelinitHeight = 90;
const short scoreTxtAreWidth = 80, scoreTxtAreHeight = 45;
const short keyHeight1 = 140, keyHeight2 = 180;
const short myloveWidth = 200, myloveHeight = 50;
const short letterWidth = 800, letterHeight = 620;
//���й����еĲ���
short initvalue = 1;//Ϊ1���ʼ����ز���
short level = 1;//�ؿ��ȼ�
char rankName[30] = "data\\level1Rank.txt";//����rank��¼�ļ�
int timeLimit=0, timeNow=0, timeOld=0, scoreTimeNow=0, scoreTimeOld=0;//��Ϸ��ֹʱ��
short timexSpace=20,timeySpace=50, timeBarHeight = 650, timeBarWidth = 20;
short upHeight = 110, leftMove = -25, rightMove = 30;
int score = 0;//�÷�
int promptTime = 2, gamePromptTime;//���Ѵ���
int shuffleTime = 1, gameShuffleTime;//ϴ�ƴ���
int remainTime = 0;//ʣ��ʱ�� ����ʱ���ۼ�
TCHAR scoreChar[7];
TCHAR repeTimeChar[7];
TCHAR countdown[7];
bool levelSet = true;//�ؿ���ʼ��
bool recordBreak = false;//δ���Ƽ�¼
bool pause = false;//��ͣ
bool UnlimitTime = false;//����ָ��������ʱ��
bool UnlimitPrompt = false;//����ָ������������
bool UnlimitShuffle = false;//����ָ��������ϴ��
bool mylove = false;//true�������ع���