#pragma once
//2 ����
//�� 0-71Ϊ��������Ʒ��72Ϊ��Ϸ�����棬73Ϊ�˳���
IMAGE img[76];		//ͼƬ����
LOGFONT textstyle;	//�����ʽ
LINESTYLE linestyle; //�߸�ʽ
struct gameMap
{
	short x = 0;
	short y = 0;
	//��� -1 ��ʾû��ͼƬ
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
levels level1 = { "data\\level1Rank.txt",12,16,420,4,12,1, "��1�� ���ų���", 2, 0 }; 
levels level2 = { "data\\level2Rank.txt",12,20,420,5,12,1, "��2�� ��������", 3, 1 };
levels level3 = { "data\\level3Rank.txt",12,20,420,4,10,1, "��3�� �����ظ�", 4, 1 };
levels level4 = { "data\\level4Rank.txt",12,20,420,4,10,2, "��4�� ������ɢ", 4, 1 };
levels level5 = { "data\\level5Rank.txt",12,20,420,3,8,3, "��5�� ������ɢ", 4, 1 };
levels level6 = { "data\\level6Rank.txt",12,20,420,3,8,4, "��6�� ������ɢ", 4, 2 };
levels level7 = { "data\\level7Rank.txt",12,20,420,2,6,5, "��7�� ���¾ۼ�", 4, 2 };
levels level8 = { "data\\level8Rank.txt",12,20,420,2,6,6, "��8�� ����ۼ�", 4, 2 };
levels level9 = { "data\\level9Rank.txt",12,20,420,2,6,7, "��9�� �м�ۼ�", 4, 2 };
levels level10 = { "data\\level10Rank.txt",16,18,420,1,4,4, "��10�� �����Ѷ�", 6, 3 };
*/
levels level1 = { "data\\level1Rank.txt",4,4,420,4,8,1, "��1�� ���ų���", 2, 0 };
levels level2 = { "data\\level2Rank.txt",4,4,420,4,8,1, "��2�� ��������", 3, 1 };
levels level3 = { "data\\level3Rank.txt",4,4,420,4,8,1, "��3�� �����ظ�", 4, 1 };
levels level4 = { "data\\level4Rank.txt",4,4,420,4,8,1, "��4�� ������ɢ", 4, 1 };
levels level5 = { "data\\level5Rank.txt",4,4,420,4,8,1, "��5�� ������ɢ", 4, 1 };
levels level6 = { "data\\level6Rank.txt",4,4,420,4,8,1, "��6�� ������ɢ", 4, 2 };
levels level7 = { "data\\level7Rank.txt",4,4,420,4,8,1, "��7�� ���¾ۼ�", 4, 2 };
levels level8 = { "data\\level8Rank.txt",4,4,420,4,8,1, "��8�� ����ۼ�", 4, 2 };
levels level9 = { "data\\level9Rank.txt",4,4,420,4,8,1, "��9�� �м�ۼ�", 4, 2 };
levels level10 = { "data\\level10Rank.txt",4,4,420,4,8,1, "��10�� �����Ѷ�", 6, 3 };


levels levelNow = level1;
levels levelDisplay = level1;
levels levelswitch = level1;

//��ť��
class keys
{
public:
	short left, top, right, bottom;
	keys() : left(0), top(0), right(5), bottom(5) {}
	keys(short _left, short _top, short _right, short _bottom) : left(_left), top(_top), right(_right), bottom(_bottom) {}
	//���ú���ʱ�����괦����Ӧ���򼴷���true
	bool cursorPos(MOUSEMSG m)
	{
		if (m.x > left && m.x< right && m.y > top && m.y < bottom)
			return true;
		else
			return false;
	}
private:
	
};
keys keyBeginGame(windowWidth / 2 - 90, windowHeight / 2 - 35, windowWidth / 2 + 90, windowHeight / 2 + 65);//����ʼ��Ϸ��������λ��
keys keyGameOver(windowWidth - 70, windowHeight - 130, windowWidth - 30, windowHeight - 10);//���˳���Ϸ������λ��
keys keySetting(windowWidth - 80, 5, windowWidth - 5, 65);//�����á�����λ��
keys keyGoldfinger = { 0,0,50,50 };//������ָ������λ��
keys keyConceal = { 0,windowHeight-50,50,windowHeight };//�����ع��ܵ�¼���桱����λ��
keys keyRank(windowWidth / 2 - 80, 5, windowWidth / 2 + 80, 55);//�����а񡱰���λ��
keys keySettingOut(windowWidth / 2 - 40, (windowHeight + settingHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + settingHeight) / 2 - 25);//���ý���ġ��˳���
keys keyReturnToMain(windowWidth - keyWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 1 * gap, windowWidth - gridSizeWidth, windowHeight - 1 * gridSizeHeight - 1 * gap);//��Ϸ����ġ����������桱
keys keyReset(windowWidth - keyWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 2 * gap, windowWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 2 * gap);//���õ�ͼ
keys keyPrompt(windowWidth - keyWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 3 * gap, windowWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 3 * gap);//��ʾ
keys keyPause = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 5 * gridSizeHeight - 4 * gap, windowWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 4 * gap };//��ͣ
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
keys goldFingerOut = { windowWidth / 2 - 40, (windowHeight + goldFingerHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + goldFingerHeight) / 2 - 25 };//���ý���ġ��˳���
keys keyLetterOut = { windowWidth / 2 - 40, (windowHeight + letterHeight) / 2 - 25 - 48, windowWidth / 2 + 40, (windowHeight + letterHeight) / 2 - 25 };
//RECT ={left,top,right,bottom};
//������
RECT ReturnToMain = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 1 * gap, windowWidth - gridSizeWidth, windowHeight - 1 * gridSizeHeight - 1 * gap };//��Ϸ����ġ����������桱
RECT Reset = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 2 * gap, windowWidth - gridSizeWidth, windowHeight - 2 * gridSizeHeight - 2 * gap };//���õ�ͼ
RECT Prompt = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 3 * gap, windowWidth - gridSizeWidth, windowHeight - 3 * gridSizeHeight - 3 * gap };//��ʾ
RECT Pause = { windowWidth - keyWidth - gridSizeWidth, windowHeight - 5 * gridSizeHeight - 4 * gap, windowWidth - gridSizeWidth, windowHeight - 4 * gridSizeHeight - 4 * gap };//��ͣ

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