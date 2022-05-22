#pragma once
//2 储存
//类 0-71为连连看物品，72为游戏主界面，73为退出键
IMAGE img[76];		//图片类组
LOGFONT textstyle;	//字体格式
LINESTYLE linestyle; //线格式
struct gameMap
{
	short x = 0;
	short y = 0;
	//编号 -1 表示没有图片
	short colorNum = -1;
	short num = -1;
}gameMap[row][column];
struct  levels
{
	char _rankName[25];
	short _row;
	short _column;
	int _timeLimit;
	short _degree;
	short _repeTime;
	short _movePattern;
	char _levelName[20];
	int _plusPromptTime;
	int _plusShuffleTime;
};

/*
levels level1 = { "data\\level1Rank.txt",12,16,420,4,12,1, "第1关 入门尝试", 2, 0 }; 
levels level2 = { "data\\level2Rank.txt",12,20,420,5,12,1, "第2关 增加列数", 3, 1 };
levels level3 = { "data\\level3Rank.txt",12,20,420,4,10,1, "第3关 减少重复", 4, 1 };
levels level4 = { "data\\level4Rank.txt",12,20,420,4,10,2, "第4关 上下扩散", 4, 1 };
levels level5 = { "data\\level5Rank.txt",12,20,420,3,8,3, "第5关 左右扩散", 4, 1 };
levels level6 = { "data\\level6Rank.txt",12,20,420,3,8,4, "第6关 四周扩散", 4, 2 };
levels level7 = { "data\\level7Rank.txt",12,20,420,2,6,5, "第7关 向下聚集", 4, 2 };
levels level8 = { "data\\level8Rank.txt",12,20,420,2,6,6, "第8关 向左聚集", 4, 2 };
levels level9 = { "data\\level9Rank.txt",12,20,420,2,6,7, "第9关 中间聚集", 4, 2 };
levels level10 = { "data\\level10Rank.txt",16,18,420,1,4,4, "第10关 地狱难度", 6, 3 };
*/
levels level1 = { "data\\level1Rank.txt",4,4,420,4,8,1, "第1关 入门尝试", 2, 0 };
levels level2 = { "data\\level2Rank.txt",4,4,420,4,8,1, "第2关 增加列数", 3, 1 };
levels level3 = { "data\\level3Rank.txt",4,4,420,4,8,1, "第3关 减少重复", 4, 1 };
levels level4 = { "data\\level4Rank.txt",4,4,420,4,8,1, "第4关 上下扩散", 4, 1 };
levels level5 = { "data\\level5Rank.txt",4,4,420,4,8,1, "第5关 左右扩散", 4, 1 };
levels level6 = { "data\\level6Rank.txt",4,4,420,4,8,1, "第6关 四周扩散", 4, 2 };
levels level7 = { "data\\level7Rank.txt",4,4,420,4,8,1, "第7关 向下聚集", 4, 2 };
levels level8 = { "data\\level8Rank.txt",4,4,420,4,8,1, "第8关 向左聚集", 4, 2 };
levels level9 = { "data\\level9Rank.txt",4,4,420,4,8,1, "第9关 中间聚集", 4, 2 };
levels level10 = { "data\\level10Rank.txt",4,4,420,4,8,1, "第10关 地狱难度", 6, 3 };


levels levelNow = level1;
levels levelDisplay = level1;
levels levelswitch = level1;

//按钮类
class keys
{
public:
	short left, top, right, bottom;
	keys() : left(0), top(0), right(5), bottom(5) {}
	keys(short _left, short _top, short _right, short _bottom) : left(_left), top(_top), right(_right), bottom(_bottom) {}
	//调用函数时如果鼠标处于相应区域即返回true
	bool cursorPos(MOUSEMSG m)
	{
		if (m.x > left && m.x< right && m.y > top && m.y < bottom)
			return true;
		else
			return false;
	}
private:
	
};
keys keyBeginGame(windowWidth / 2 - 90, windowHeight / 2 - 35, windowWidth / 2 + 90, windowHeight / 2 + 65);//“开始游戏”按键的位置
keys keyGameOver(windowWidth - 70, windowHeight - 130, windowWidth - 30, windowHeight - 10);//“退出游戏”按键位置
keys keySetting(windowWidth - 80, 5, windowWidth - 5, 65);//“设置”按键位置
keys keyGoldfinger = { 0,0,50,50 };//“金手指”按键位置
keys keyConceal = { 0,windowHeight-50,50,windowHeight };//“隐藏功能登录界面”按键位置
keys keyRank(windowWidth / 2 - 80, 5, windowWidth / 2 + 80, 55);//“排行榜”按键位置
keys keySettingOut(windowWidth / 2 - 40, (windowHeight + settingHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + settingHeight) / 2 - 25);//设置界面的“退出”
keys keyReturnToMain(windowWidth - keyWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 1 * gap, windowWidth - gridSizeWidth, windowHeight - 1 * gridSizeHeight - 1 * gap);//游戏界面的“返回主界面”
keys keyReset(windowWidth - keyWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 2 * gap, windowWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 2 * gap);//重置地图
keys keyPrompt(windowWidth - keyWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 3 * gap, windowWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 3 * gap);//提示
keys keyPause = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 5 * gridSizeHeight - 4 * gap, windowWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 4 * gap };//暂停
keys keyLevel1 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 0 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 0 * (levelHeight + levelGap) };
keys keyLevel2 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 1 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 1 * (levelHeight + levelGap) };
keys keyLevel3 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 2 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 2 * (levelHeight + levelGap) };
keys keyLevel4 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 3 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 3 * (levelHeight + levelGap) };
keys keyLevel5 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 4 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 4 * (levelHeight + levelGap) };
keys keyLevel6 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 5 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 5 * (levelHeight + levelGap) };
keys keyLevel7 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 6 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 6 * (levelHeight + levelGap) };
keys keyLevel8 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 7 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 7 * (levelHeight + levelGap) };
keys keyLevel9 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 8 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 8 * (levelHeight + levelGap) };
keys keyLevel10 = { windowWidth / 2 - settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + 9 * (levelHeight + levelGap) ,windowWidth / 2 + settingWidth / 3,(windowHeight - settingHeight) / 2 + keyLevelinitHeight + levelHeight + 9 * (levelHeight + levelGap) };
keys keyGoOn = { (windowWidth - informWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 - 25, (windowHeight - informHeight) / 2 + keyHeight2 };
keys keyQuit = { (windowWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 125, (windowHeight - informHeight) / 2 + keyHeight2 };
keys keyGoBack = { (windowWidth) / 2 - 75, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 75, (windowHeight - informHeight) / 2 + keyHeight2 };
keys keyUnlimitTime = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 0 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 0 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys keyUnlimitPrompt = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys keyUnlimitShuffle = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 2 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + leftMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 2 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys keyInitUnlimitTime = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 0 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2, (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 0 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys keyInitUnlimitPrompt = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2, (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys keyInitUnlimitShuffle = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 2 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2, (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + rightMove, (windowHeight - goldFingerHeight) / 2 + upHeight + 2 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight };
keys goldFingerOut = { windowWidth / 2 - 40, (windowHeight + goldFingerHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + goldFingerHeight) / 2 - 25 };//设置界面的“退出”
keys keyLetterOut = { windowWidth / 2 - 40, (windowHeight + letterHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + letterHeight) / 2 - 25 };
//RECT ={left,top,right,bottom};
//区域类
RECT ReturnToMain = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 1 * gap, windowWidth - gridSizeWidth, windowHeight - 1 * gridSizeHeight - 1 * gap };//游戏界面的“返回主界面”
RECT Reset = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 2 * gap, windowWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 2 * gap };//重置地图
RECT Prompt = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 3 * gap, windowWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 3 * gap };//提示
RECT Pause = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 5 * gridSizeHeight - 4 * gap, windowWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 4 * gap };//暂停

RECT settingTxt = { (windowWidth - 250) / 2,30,(windowWidth + 250) / 2,80 };
RECT rankTxt = { (windowWidth - 250) / 2,30,(windowWidth + 250) / 2,80 };
RECT levelNameAre = { (windowWidth - levelNameAreWidth - 5), 5, (windowWidth - 5),5 + levelNameAreHeight };
RECT informTxt = { (windowWidth - (informWidth - 50)) / 2, (windowHeight - informHeight) / 2 + informTxtHeight1, (windowWidth + (informWidth - 50)) / 2,  (windowHeight - informHeight) / 2 + informTxtHeight2 };
RECT informTxt2 = { (windowWidth - (informWidth - 50)) / 2, (windowHeight - informHeight) / 2 + informTxt2Height1, (windowWidth + (informWidth - 50)) / 2,  (windowHeight - informHeight) / 2 + informTxt2Height2 };
RECT informGoOnTxt = { (windowWidth - informWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 - 25, (windowHeight - informHeight) / 2 + keyHeight2 };
RECT informQuitTxt = { (windowWidth) / 2 + 25, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 125, (windowHeight - informHeight) / 2 + keyHeight2 };
RECT informGoBack = { (windowWidth) / 2 - 75, (windowHeight - informHeight) / 2 + keyHeight1, (windowWidth) / 2 + 75, (windowHeight - informHeight) / 2 + keyHeight2 };
RECT scoreAre =    { windowWidth - scoreTxtAreWidth - 5, 5 + 2* (levelNameAreHeight + 10),windowWidth - 5,5 + 2*(levelNameAreHeight + 10) + scoreTxtAreHeight };
RECT scoreTxtAre = { (windowWidth - 2 * scoreTxtAreWidth - 5), 5 + 2 * (levelNameAreHeight + 10),(windowWidth - scoreTxtAreWidth - 5),5 + 2 * (levelNameAreHeight + 10) + scoreTxtAreHeight };
RECT repeTimeAre = { windowWidth - scoreTxtAreWidth - 5, 5 + levelNameAreHeight + 10,windowWidth - 5,5 + levelNameAreHeight + 10 + scoreTxtAreHeight };
RECT repeTimTxtAre = { (windowWidth - 3 * scoreTxtAreWidth - 5), 5 + levelNameAreHeight + 10,(windowWidth - scoreTxtAreWidth - 5),5 + levelNameAreHeight + 10 + scoreTxtAreHeight };
RECT pauseTxtAre = { windowWidth / 2 - 300,windowHeight / 2 - 70,windowWidth / 2 + 300,windowHeight / 2  };
RECT pauseTxtAre2 = { windowWidth / 2 - 200,windowHeight / 2 ,windowWidth / 2 + 200,windowHeight / 2 + 40 };
RECT timeDisAre = { timexSpace-10,10,timexSpace+timeBarWidth+10,40 };
RECT goldFingerTxt = { (windowWidth - 250) / 2,(windowHeight - goldFingerHeight) / 2+20,(windowWidth + 250) / 2,(windowHeight - goldFingerHeight) / 2+70 };
RECT unlimitTxt = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + leftMove-20, (windowHeight - goldFingerHeight) / 2 +10 + upHeight + -1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + leftMove+20, (windowHeight - goldFingerHeight) / 2 + upHeight + -1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight +10};
RECT initTxt = { (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + rightMove - 20, (windowHeight - goldFingerHeight) / 2 + 10 + upHeight + -1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 , (windowWidth - goldFingerWidth) / 2 + 50 + goldFingerBoxWidth + 50 + goldFingerSwitchWidth + rightMove + 20, (windowHeight - goldFingerHeight) / 2 + upHeight + -1 * (levelHeight + levelGap) + (levelHeight - goldFingerSwitchHeight) / 2 + goldFingerSwitchHeight + 10 };
RECT MyLoveTxt = { windowWidth - myloveWidth-200, (windowHeight - myloveHeight) / 2-30,windowWidth-200, (windowHeight + myloveHeight) / 2-30 };
RECT MyLoveTxt2 = { 10, (windowHeight - myloveHeight)-10,10+ myloveWidth, windowHeight -10 };
RECT letterNameTxt = { (windowWidth - 250) / 2,(windowHeight - letterHeight) / 2 + 10,(windowWidth + 250) / 2,(windowHeight - letterHeight) / 2 + 60 };
RECT letterTxt = { (windowWidth ) / 2 - 350,(windowHeight - letterHeight) / 2 + 70,(windowWidth) / 2 + 350,(windowHeight + letterHeight) / 2 - 15 - 60 };
RECT windowOrigin = { 0, 0,0,0 };