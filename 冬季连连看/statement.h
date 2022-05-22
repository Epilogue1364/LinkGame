#pragma once
//��ʼ��
void initimg();//��ʼ��img��
void gameMapxy();//gameMap��xy��������
void readLocalData();//��ȡ��������
void recordLevel();//���뵱ǰlevelѡ�񵽱���
void recordPromptTime();//�������Ѵ���������
void recordShuffleTime();//����ϴ�ƴ���������
void recordRemainTime();//����ʣ��ʱ�䵽����
void recordConceal();//�����Ƿ������صĲ���
//3 �������
vector<int> degree;	//���ڴ�Ż�δ����������
void degreeOfDifficulty(int _row, int _column);//��ȡ��Ϸ�Ѷ�ϵ����
void setMap(int _row, int _column, int replication); //�����ظ�����������������
void shuffle();//ϴ��
//4 ��ʾ
bool keysExecute();//�����水ťִ�в���
void displayBegin();//��ʾ��ʼҳ��
void printMap();//�ڿ���̨��ӡ������ͼ��
void levelSwitch(int levelNum);//����ѡ��Ĺؿ���ʼ��Ϸ
void beginGame(); //��ʼ��Ϸ
void displayGame();//��ʾ��Ϸ����
void setting();//��ʾ���ý���
void rankWindow();//��ʾ���а����
void pauseWindow();//��ͣ����
void Goldfinger();//��ʾ����ָ����
void concealWindow();//��ʾ���ص�¼����
void drawMap();//��������ͼƬ����������Ƭ
void drawrectangle(short y, short x);//����ѡ���
void drawLine(short x1, short y1, short x2, short y2);//����������
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //xΪҪ����ͼƬ��X���꣬yΪY����
void displayShuffle();//��ʾshuffle
void displayPrompt();//��ʾprompt
void displayLetter();//��ʾ��������ż�

void movePattern(int patternValue);//���õ�ͼ�仯ģʽ
void topBottom();//������ɢ
void leftRight();//������ɢ
void goBottom();//���¾ۼ�
void goLeft();//����ۼ�
void topBottomGoCenter();//�������м�ۼ�
void leftRightGoCenter();//�������м�ۼ�
void informGoOn();//֪ͨ��ѯ���Ƿ����
void informFinish();//֪ͨ��ͨ��
void informTimeOver();//֪ͨ����Ϸʱ�䵽
void gameTimer(int allTime, int nowHave);//��ʱ����ʾ


void recordScore();//��ȡ�����¼�����Աȣ���������������¼�򴴽���������������
//5�ж�
bool canClear(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);//�������������������������ж�
bool rowDirectCon(int x1, int x2, int y);//�ж���ͬһ���ϵ��������Ƿ�����ͨ
bool columnDirectCon(int y1, int y2, int x);//�ж���ͬһ���ϵ��������Ƿ�����ͨ
bool oneLineCon(int x1, int y1, int x2, int y2);//��ͨ��һ��ֱ�����ӣ���������
bool twoLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3);//��ͨ������������
bool threeLineCon(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);//��ͨ������������
bool haveASolution(int &xs1, int &ys1, int &xs2, int &ys2);//������һ����
bool clearAllOrNot();//����Ƿ�ȫ��������
bool informGoOnResult();//֪ͨ��ѡ����
bool informFinishResult();//��Ϸ����ѡ����
bool informTimeOverResult();//���ػ������¿�ʼ��Ϸ