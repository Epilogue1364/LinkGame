#pragma once
//常量定义
const short column = 22;	//最大地图列数
const short row = 18;		//最大地图行数
const short gridSizeWidth = 35;	//网格宽
const short gridSizeHeight = 35;	//网格宽
const short xSpace = 60;		//横向单边空白
const short ySpace = 0;		//纵向单边空白
const short gap = 5;		//网格间隙
const short bkWidth = column * gridSizeWidth + (column - 1)*gap; //背景方格的宽
const short bkHeight = row * gridSizeHeight + (row - 1)*gap; //背景方格的宽
const short noticeBoard = 250;	//提示牌宽度
const short otherHeight = 0;	//长度附加值
const short keyWidth = 120;
//最终窗口大小为900*520
//const short windowWidth = 900 *1.2;
//const short windowHeight = 520 * 1.2;
short windowWidth = xSpace * 2 + gridSizeWidth * column + (column - 1)*gap + noticeBoard; //窗口宽
short windowHeight = ySpace * 2 + gridSizeHeight * row + (row - 1)*gap + otherHeight;//窗口高
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
//运行过程中的参数
short initvalue = 1;//为1则初始化相关参数
short level = 1;//关卡等级
char rankName[30] = "data\\level1Rank.txt";//本地rank记录文件
int timeLimit=0, timeNow=0, timeOld=0, scoreTimeNow=0, scoreTimeOld=0;//游戏截止时间
short timexSpace=20,timeySpace=50, timeBarHeight = 650, timeBarWidth = 20;
short upHeight = 110, leftMove = -25, rightMove = 30;
int score = 0;//得分
int promptTime = 2, gamePromptTime;//提醒次数
int shuffleTime = 1, gameShuffleTime;//洗牌次数
int remainTime = 0;//剩余时间 用于时间累计
TCHAR scoreChar[7];
TCHAR repeTimeChar[7];
TCHAR countdown[7];
bool levelSet = true;//关卡初始化
bool recordBreak = false;//未打破纪录
bool pause = false;//暂停
bool UnlimitTime = false;//金手指——无限时间
bool UnlimitPrompt = false;//金手指——无限提醒
bool UnlimitShuffle = false;//金手指——无限洗牌
bool mylove = false;//true则开启隐藏功能