#include"headers.h" //�Դ�ͷ�ļ� ���������õ���ͷ�ļ�
#include"definitions.h"
//#include<iostream>
int main()
{
	initgraph(windows_width, windows_lenth + 30);
	setbkcolor(WHITE);				//���ñ���ɫ
	setfillcolor(WHITE);			//�������ɫ
	setbkmode(OPAQUE);				//���ñ������ģʽ

	gettextstyle(&textstyle);//��ȡ��ǰ�����ʽ
	textstyle.lfHeight = 50;//����һϵ�������ʽ��textstyle
	textstyle.lfWidth = 30;
	textstyle.lfQuality = ANTIALIASED_QUALITY;
	textstyle.lfWeight = 700;
	_tcscpy(textstyle.lfFaceName, _T("Aa���� (����ҵʹ��)"));
	settextstyle(&textstyle);//���������ʽ

	//�����ߵĸ�ʽ
	LINESTYLE linestyle;
	linestyle.thickness = 2;
	setlinestyle(&linestyle);
	initimg();
	initgridxy();

	while (1)
	{
		//����false�����û�����ˡ��˳���Ϸ��
		if (!start_menu())			
		{
			closegraph();
			return 0;
		}
		start_game();
		while (!flg);
	}

	_getch();
	closegraph();
}

//��ʼ�˵�����
bool start_menu()
{
	level = 1;
	prechoice = 0;
	flg = true;
	cleardevice();
	draw_start_menu();
	FlushMouseMsgBuffer();
	while (1)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			if (clk_labels(m, false) == 13)		//��ʼ��Ϸ
			{
				flg = false;
				return true;
			}
			else if (clk_labels(m, false) == 14)
			{
				rank_list();
				draw_start_menu();
			}

			else if (clk_labels(m, false) == 15)
			{
				return false;		//�û�����ˡ��˳���Ϸ��
			}
			else if (clk_labels(m, false) == 16)
			{
				setting();
				draw_start_menu();
			}
		}
	}
}

//������һ��
void start_game()
{
	while (!flg)
	{
		switch (level)
		{
		case 1:
			strcpy(fl_name, level1.fl_name);
			resttime = level1.t_limit;
			t_limit = resttime;
			n_img = level1.n_img;

			draw_game_window();
			initmap1();
			game_window();

			break;
		case 2:
			strcpy(fl_name, level2.fl_name);
			resttime = level2.t_limit;
			t_limit = resttime;
			n_img = level2.n_img;

			draw_game_window();
			initmap1();
			game_window();
			break;
		case 3:
			strcpy(fl_name, level3.fl_name);
			resttime = level3.t_limit;
			t_limit = resttime;
			n_img = level3.n_img;

			draw_game_window();
			initmap2();
			game_window();
			break;
		case 4:
			strcpy(fl_name, level4.fl_name);
			resttime = level4.t_limit;
			t_limit = resttime;
			n_img = level4.n_img;

			draw_game_window();
			initmap3();
			game_window();
			break;
		case 5:
			strcpy(fl_name, level5.fl_name);
			resttime = level5.t_limit;
			t_limit = resttime;
			n_img = level5.n_img;

			draw_game_window();
			initmap3();
			game_window();
			flg = true;//������ζ�Ҫ�������˵���
			return;
		}
	}
	//ѭ��������˵��flgΪtrue�ˣ����ز˵�����
	return;
}

//��Ϸ����
void game_window()
{
	flg = false;
	t = -5;
	nhint = 2;
	nshuffle = 1;
	score = 0;
	combo = 2;
	t_start = time(0);
	long t_now = t_start;
	//	_beginthread(&draw_timer, 0, NULL);
	BeginBatchDraw();
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);
	char level_name[10];
	sprintf(level_name, "��%d�ص÷�", level);
	RECT rr = { 650, 35, 870, 120 };
	drawtext(CString(level_name), &rr, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	setfillcolor(BGR(0xF7E085));
	solidroundrect(17, windows_lenth - 3, windows_width - 17, windows_lenth + 23, 6, 6);
	setfillcolor(BGR(0xAD4560));
	solidroundrect(20, windows_lenth, windows_width - 20, windows_lenth + 20, 6, 6);
	setfillcolor(WHITE);
	EndBatchDraw();
	setlinecolor(BGR(0xF7E085));

	FlushMouseMsgBuffer();
	settextcolor(BLACK);

	bool clked = false;						//��¼�Ƿ��Ѿ�ѡ����һ��ͼƬ
	short x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	short lenth;
	while (1)
	{
		if (t_now != time(0))
		{
			BeginBatchDraw();
			setfillcolor(BGR(0xF7E085));
			solidroundrect(17, windows_lenth - 3, windows_width - 17, windows_lenth + 23, 6, 6);
			setfillcolor(BGR(0xAD4560));
			lenth = resttime * (windows_width - 40) / t_limit;
			solidroundrect(20, windows_lenth, 20 + lenth, windows_lenth + 20, 6, 6);
			setfillcolor(WHITE);
			EndBatchDraw();
			resttime--;
			t_now = time(0);
		}
		//ʱ�䵽
		if (!resttime)
		{

			game_over();
			flg = true;
			Sleep(2 * 1000);
			return;
		}
		short tmpx1 = 0, tmpy1 = 0, tmpx2 = 0, tmpy2 = 0;
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				if (clk_labels(m, true) == 17 && nshuffle)
				{
					nshuffle--;
					char s[10];
					sprintf(s, "%c / 1 ��", nshuffle + '0');
					settextcolor(BLACK);
					drawtext(CString(s), &rtshuffle, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
					srand((unsigned)time(0));
					shuffle();
					draw_map();
					continue;
				}
				else if (clk_labels(m, true) == 18 && nhint)
				{
					nhint--;
					char s[10];
					sprintf(s, "%c / 2 ��", nhint + '0');
					settextcolor(BLACK);
					drawtext(CString(s), &rthint, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
					hint();
					continue;
				}
				else if (clk_labels(m, true) == 19)
				{
					flg = true;
					return;					//bk_to_menu
				}
				else if (clk_labels(m, true) == 0)		//�����������
				{
					if (clked)
					{
						x2 = (m.x - x0) / grid_size;
						y2 = (m.y - y0) / grid_size;

						short x3 = x1;
						short y3 = y1;
						short x4 = x2;
						short y4 = y2;
						if (x1 == x2 && y1 == y2)
						{
							clked = false;
							combo = 2;
							putimage(grid[y1][x1].x, grid[y1][x1].y, &img[grid[y1][x1].img_num]);

						}
						//�ܹ�����
						else if (is_connected(x1, y1, x2, y2, x3, y3, x4, y4))
						{
							n_img -= 2;
							short tmpt = (short)(time(0) - t_start);
							if (tmpt - t < 2)
								combo = combo * 2;
							else
								combo = 2;
							t = tmpt;
							score += combo;
							print_score(score);
							setlinecolor(BGR(0xF7E085));

							drawrectangle(x1, y1);
							drawrectangle(x2, y2);
							drawline(x1, y1, x3, y3);
							drawline(x3, y3, x4, y4);
							drawline(x4, y4, x2, y2);

							Sleep(300);

							BeginBatchDraw();

							setlinecolor(WHITE);
							drawrectangle(x1, y1);
							drawrectangle(x2, y2);
							drawsolidrectangle(x1, y1);
							drawsolidrectangle(x2, y2);
							drawline(x1, y1, x3, y3);
							drawline(x3, y3, x4, y4);
							drawline(x4, y4, x2, y2);

							EndBatchDraw();

							setlinecolor(BGR(0xF7E085));

							grid[y1][x1].img_num = -1;
							grid[y2][x2].img_num = -1;
							if (judge())
							{
								return;
							}
							clked = false;
						}
						//��������
						else
						{
							putimage(grid[y1][x1].x, grid[y1][x1].y, &img[grid[y1][x1].img_num]);
							x1 = x2;
							y1 = y2;
							combo = 2;
							drawrectangle(x1, y1);
						}
					}
					else
					{
						x1 = (m.x - x0) / grid_size;
						y1 = (m.y - y0) / grid_size;
						drawrectangle(x1, y1);
						clked = true;
					}
				}
				else if (clk_labels(m, true) == -1)		//��û�е��labelsҲû�е���������򣬰����ѱ����������򣡣���					
				{
					continue;
				}
			}
		}
	}
}

//��Ϸ����ġ��жϡ�ģ��
//����true������Ϸ�ɹ���false���ǲо�
bool judge()			
{

	//�ж��Ƿ��ڹ涨ʱ����ȫ�����������Ƿ�ɹ����أ�
	if (!n_img && resttime)
	{
		save_memory();
		
		setbkmode(TRANSPARENT);

		BeginBatchDraw();
		if (level != 5)
			drawtext(_T("��Ϸ�ɹ���2s�������һ��..."), &R, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		else
			drawtext(_T("��ϲ���Ѿ�ͨ�أ�2s�󷵻ز˵�����..."), &R, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		EndBatchDraw();

		setbkmode(OPAQUE);

		flg = false;
		Sleep(2 * 1000);
		level++;
		return true;
	}

	//�о�
	short tmpx1, tmpy1, tmpx2, tmpy2;
	if (!is_solution(tmpx1, tmpy1, tmpx2, tmpy2))
	{

		shuffle();
		flg = false;
		return false;
	}
	return false;
}

//��Ϸʧ�ܣ������ʾ����
void game_over()
{

	setfillcolor(WHITE);
	settextcolor(BGR(0xAD4560));

	setbkmode(TRANSPARENT);

	BeginBatchDraw();
	drawtext(_T("ʱ�䵽����Ϸʧ�ܣ�2s�󷵻ز˵�����..."), &R, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndBatchDraw();

	setbkmode(OPAQUE);
}

//��Ϸ����
//������Ϸ���������״������
void draw_game_window()
{
	setbkcolor(WHITE);				//����ɫ
	setfillcolor(WHITE);
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);

	BeginBatchDraw();

	putimage(0, 0, &img[14]);
	setfillcolor(WHITE);
	solidroundrect(22, 22, 628, 468, 15, 15);
	print_score(0);
	settextcolor(BLACK);
	drawtext(_T("2 / 2 ��"), &rthint, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("1 / 1 ��"), &rtshuffle, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	EndBatchDraw();
}

//��ʾ�÷�
void print_score(int score)
{
	char sscore[10];
	itoa(score, sscore, 10);
	settextcolor(BGR(0xAD4560));
	drawtext(CString(sscore), &rscores, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//��Ϸ���棬��ʾ
void hint()
{
	short s_x1 = 1, s_y1 = 1, s_x2 = 1, s_y2 = 1;
	setlinecolor(BGR(0x41BFDA));

	if (is_solution(s_x1, s_y1, s_x2, s_y2))
	{
		BeginBatchDraw();

		drawrectangle(s_x1, s_y1);
		drawrectangle(s_x2, s_y2);

		EndBatchDraw();

		Sleep(5 * 100);

		BeginBatchDraw();

		putimage(grid[s_y1][s_x1].x, grid[s_y1][s_x1].y, &img[grid[s_y1][s_x1].img_num]);
		putimage(grid[s_y2][s_x2].x, grid[s_y2][s_x2].y, &img[grid[s_y2][s_x2].img_num]);

		EndBatchDraw();

		setlinecolor(BGR(0xF7E085));
		return;
	}
	//��ʵһ�����н�ģ�����������ɾ��
	else
		return;
}

//���ý���
void setting()
{
	BeginBatchDraw();

	setfillcolor(WHITE);
	solidroundrect(225, 20, 675, 500, 20, 20);

	textstyle.lfHeight = 70;
	textstyle.lfWidth = 50;
	settextstyle(&textstyle);
	settextcolor(BGR(0xfed9db));
	setbkcolor(WHITE);
	drawtext(_T("����"), &rrank1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	putimage(410, 440, &img[15]);

	settextcolor(BGR(0x94b7bd));
	textstyle.lfHeight = 45;
	textstyle.lfWidth = 28;
	settextstyle(&textstyle);
	for (short i = 0; i < 5; i++)
	{
		setfillcolor(BGR(0xf9f0e8));
		setbkcolor(BGR(0xf9f0e8));

		solidroundrect(330, 180 + (i - 1) * 60, 570, 180 + (i - 1) * 60 + 50, 10, 10);

		RECT tmpr = { 330, 180 + (i - 1) * 60, 570, 180 + (i - 1) * 60 + 50 };

		char sscr[10], clevel[10];

		sprintf(clevel, "��%d��", i + 1);
		drawtext(CString(clevel), &tmpr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setlinecolor(BGR(0xF7E085));
	roundrect(330 + 1, 180 + (prechoice - 1) * 60 - 1, 570 + 1, 180 + (prechoice - 1) * 60 + 50 - 1, 10, 10);
	
	EndBatchDraw();

	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			if (m.mkLButton && lclose_rank.init(m))
				return;
			else
				clk_levels(m);
		}
	}
}

//���ý��棬�ж�ѡ�������һ��
void clk_levels(MOUSEMSG m)
{
	for (short i = 0; i < 5; i++)
	{
		if (m.x > 330 && m.x < 570
			&& m.y < 180 + (i - 1) * 60 + 50 && m.y > 180 + (i - 1) * 60)
		{
			setlinecolor(BGR(0xf9f0e8));
			roundrect(330 + 1, 180 + (prechoice - 1) * 60 - 1, 570 + 1, 180 + (prechoice - 1) * 60 + 50 - 1, 10, 10);
			prechoice = i;
			level = i + 1;
			setlinecolor(BGR(0xF7E085));
			roundrect(330 + 1, 180 + (i - 1) * 60 - 1, 570 + 1, 180 + (i - 1) * 60 + 50 - 1, 10, 10);
		}
	}
	return;
}

//���а����
void rank_list()
{
	FILE *fp;
	short scr;

	setfillcolor(WHITE);
	solidroundrect(225, 20, 675, 500, 20, 20);//(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);

	textstyle.lfHeight = 70;
	textstyle.lfWidth = 50;
	settextstyle(&textstyle);
	settextcolor(BGR(0xfed9db));
	setbkcolor(WHITE);
	drawtext(_T("���а�"), &rrank1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	putimage(410, 440, &img[15]);

	settextcolor(BGR(0x94b7bd));
	textstyle.lfHeight = 50;
	textstyle.lfWidth = 30;
	settextstyle(&textstyle);

	BeginBatchDraw();

	for (short i = 0; i < 5; i++)
	{
		sprintf(fl_name, "rank_list%d.txt", i + 1);//�����������д�뵽fl_mame
		setfillcolor(WHITE);
		setbkcolor(WHITE);
		if (!(i % 2))
		{
			setfillcolor(BGR(0xf9f0e8));
			setbkcolor(BGR(0xf9f0e8));
		}

		solidroundrect(240, 180 + (i - 1) * 60, 360, 180 + i * 60, 10, 10);
		solidroundrect(380, 180 + (i - 1) * 60, 665, 180 + i * 60, 10, 10);

		RECT tmpr1 = { 240, 180 + (i - 1) * 60, 360, 180 + i * 60 };
		RECT tmpr2 = { 380, 180 + (i - 1) * 60, 665, 180 + i * 60 };

		char sscr[10], clevel[10];

		sprintf(clevel, "��%d��", i + 1);
		drawtext(CString(clevel), &tmpr1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		if (!(fp = fopen(fl_name, "r")))
			drawtext(_T("�����ϰ�"), &tmpr2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
		{
			fread(&scr, sizeof(scr), 1, fp);
			itoa(scr, sscr, 10);
			drawtext(CString(sscr), &tmpr2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			fclose(fp);
		}
	}
	EndBatchDraw();

	MOUSEMSG m;

	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton && lclose_rank.init(m))
			return;
	}
}

//���غ�浵
void save_memory()
{
	FILE *fp;
	short i = 0;
	short scr;
	sprintf(fl_name, "rank_list%d.txt", level);
	if (fp = fopen(fl_name, "r"))
	{
		fread(&scr, sizeof(scr), 1, fp);
		if (scr < score)
			scr = score;
		fclose(fp);
		remove(fl_name);
	}
	else
	{
		scr = score;
	}
	fp = fopen(fl_name, "w+");
	fwrite(&scr, sizeof(scr), 1, fp);
	fclose(fp);
}

//������״
void drawsolidrectangle(short  x, short y)
{
	setfillcolor(WHITE);
	solidrectangle(grid[y][x].x, grid[y][x].y, grid[y][x].x + grid_size, grid[y][x].y + grid_size);
}

void drawrectangle(short x, short y)
{
	rectangle(grid[y][x].x + 1, grid[y][x].y + 1, grid[y][x].x + grid_size - 2, grid[y][x].y + grid_size - 2);
}

void drawline(short x1, short y1, short x2, short y2)
{

	LINESTYLE linestyle;
	linestyle.thickness = 3;
	setlinestyle(&linestyle);

	line(grid[y1][x1].x + grid_size / 2, grid[y1][x1].y + grid_size / 2, grid[y2][x2].x + grid_size / 2, grid[y2][x2].y + grid_size / 2);
}

//����ʼ�˵�
void draw_start_menu()
{
	putimage(0, 0, &img[13]);
}

short clk_labels(MOUSEMSG m, bool _flg)
{
	short x = (m.x - x0) / grid_size;
	short y = (m.y - y0) / grid_size;

	if (!_flg)
	{
		if (lstart_game.init(m))
			return 13;
		else if (lrank_list.init(m))
			return 14;
		else if (lexit_game.init(m))
			return 15;
		else if (lsetting.init(m))
			return 16;
	}
	else if (_flg)
	{
		if (lshuffle.init(m))
			return 17;
		else if (lhint.init(m))
			return 18;
		else if (lbk_to_menu.init(m))
			return 19;
		else if (x > -1 && y > -1 && x < column && y < row && grid[y][x].img_num != -1)
			return 0;
		else
			return -1;
	}
}

//��ʼ��grid[][].img_num
//��һ�����ص�ͼ  �Ȱ���һ������������  ��ϴ�ƴ���˳��
void initmap1()
{
	for (int i = 0; i < column; i++)
	{
		grid[0][i].img_num = -1;
		grid[row - 1][i].img_num = -1;
	}
	for (int j = 0; j < row; j++)
	{
		grid[j][0].img_num = -1;
		grid[j][column - 1].img_num = -1;
	}
	srand(unsigned(time(0)));
	for (int j = 1; j < row / 2; j++)
		for (int i = 1; i < column - 1; i++)
		{
			grid[j][i].img_num = rand() % 13;
			grid[j + row / 2 - 1][i].img_num = grid[j][i].img_num;
		}

	do
	{
		srand((unsigned)time(0));
		for (int i = 1; i < level1.n_img + 1; i++)
		{
			shuffle();
		}
	} while (!ten_solutions());

	draw_map();
}

//�����ص�ͼ����ʮ����
void initmap2()
{
	for (int i = 0; i < column; i++)
	{
		grid[0][i].img_num = -1;
		grid[row - 1][i].img_num = -1;
	}
	for (int j = 0; j < row; j++)
	{
		grid[j][0].img_num = -1;
		grid[j][column - 1].img_num = -1;
	}
	for (short j = 1; j < 4; j++)
		for (short i = 1; i < 6; i++)
		{
			grid[j][i].img_num = -1;

		}
	for (short j = 1; j < 4; j++)
		for (short i = 10; i < 15; i++)
		{
			grid[j][i].img_num = -1;

		}
	for (short j = 8; j < 11; j++)
		for (short i = 10; i < 15; i++)
		{
			grid[j][i].img_num = -1;

		}
	for (short j = 8; j < 11; j++)
		for (short i = 1; i < 6; i++)
		{
			grid[j][i].img_num = -1;

		}

	srand(unsigned(time(0)));
	for (int j = 4; j < 6; j++)
		for (int i = 1; i < column - 1; i++)
		{
			grid[j][i].img_num = rand() % 13;
			grid[j + 2][i].img_num = grid[j][i].img_num;
		}
	for (int j = 1; j < 4; j++)
		for (int i = 6; i < 10; i++)
		{
			grid[j][i].img_num = rand() % 13;
			grid[j + 7][i].img_num = grid[j][i].img_num;

		}

	do
	{
		srand((unsigned)time(0));
		for (int i = 1; i < level2.n_img + 1; i++)
		{
			shuffle();
		}
	} while (!ten_solutions());

	draw_map();
}

//���ġ���ص�ͼ�����Խ��߸���Ϊ��
void initmap3()
{
	for (short k = 12; k < 15; k++)
		for (short j = 1; j < row - 1; j++)
		{
			short i = k - j;
			grid[j][i].img_num = -1;
		}
	for (int i = 0; i < column; i++)
	{
		grid[0][i].img_num = -1;
		grid[row - 1][i].img_num = -1;
	}
	for (int j = 0; j < row; j++)
	{
		grid[j][0].img_num = -1;
		grid[j][column - 1].img_num = -1;
	}

	srand(unsigned(time(0)));
	for (short k = 2; k < 12; k++)
		for (short j = 1; j < k; j++)
		{
			grid[j][k - j].img_num = rand() % 13;
			grid[11 - j][15 - k + j].img_num = grid[j][k - j].img_num;

		}

	do
	{
		srand((unsigned)time(0));
		for (int i = 1; i < level3.n_img + 1; i++)
		{
			shuffle();
		}
	} while (!ten_solutions());

	draw_map();
}

//��ͼƬ���
void draw_map()
{
	BeginBatchDraw();

	setfillcolor(WHITE);
	for (short j = 1; j < row - 1; j++)
		for (short i = 1; i < column - 1; i++)
		{
			if (grid[j][i].img_num != -1)
				putimage(grid[j][i].x, grid[j][i].y, &img[grid[j][i].img_num]);
			else
				drawsolidrectangle(i, j);
		}

	EndBatchDraw();
}

//��ʼ����֤������ʮ��ͼ����������
bool ten_solutions()
{
	short tmpx1, tmpy1, tmpx2, tmpy2, nsolution = 0, tmpx3, tmpy3, tmpx4, tmpy4;
	for (tmpy1 = 1; tmpy1 < row - 1; tmpy1++)
		for (tmpx1 = 1; tmpx1 < column - 1; tmpx1++)
			for (tmpy2 = tmpy1; tmpy2 < row - 1; tmpy2++)
				for (tmpx2 = 1; tmpx2 < column - 1; tmpx2++)
				{
					if (grid[tmpy1][tmpx1].img_num != -1 && grid[tmpy2][tmpx2].img_num != -1
						&& is_connected(tmpx1, tmpy1, tmpx2, tmpy2, tmpx3, tmpy3, tmpx4, tmpy4))
					{
						nsolution++;
						if (nsolution >= 10)
							return true;
					}
				}
	return false;
}

//ϴ�ƣ�ֱ���н�
void shuffle()
{
	short tmpx1 = 0, tmpy1 = 0, tmpx2 = 0, tmpy2 = 0, tmp_imgn = -1;

	do
	{
		do
		{
			tmpx1 = rand() % column;
			tmpy1 = rand() % row;
		} while (grid[tmpy1][tmpx1].img_num == -1);
		do
		{
			tmpx2 = rand() % column;
			tmpy2 = rand() % row;
		} while (grid[tmpy2][tmpx2].img_num == -1);
		tmp_imgn = grid[tmpy1][tmpx1].img_num;
		grid[tmpy1][tmpx1].img_num = grid[tmpy2][tmpx2].img_num;
		grid[tmpy2][tmpx2].img_num = tmp_imgn;
	} while (grid[tmpy1][tmpx1].img_num == grid[tmpy2][tmpx2].img_num
		|| !is_solution(tmpx1, tmpy1, tmpx2, tmpy2));
}

//��ʼ��grid[][].x, grid[][].y
void initgridxy()
{
	for (int j = 0; j < row; j++)
		for (int i = 0; i < column; i++)
		{
			grid[j][i].x = x0 + i*(grid_size + gap);
			grid[j][i].y = y0 + j*(grid_size + gap);
		}
}

//����ͼ��
void initimg()
{
	char img_name[16];
	for (int i = 0; i < 10; i++)
	{
		sprintf(img_name, "imag\\%c.png", i + '0');
		loadimage(&img[i], CString(img_name), grid_size, grid_size);
	}
	for (int i = 0; i < 3; i++)
	{
		sprintf(img_name, "imag\\1%c.png", i + '0');
		loadimage(&img[i + 10], CString(img_name), grid_size, grid_size);
	}
	loadimage(&img[13], _T("imag\\13.png"));
	loadimage(&img[14], _T("imag\\14.png"));
	loadimage(&img[15], _T("imag\\15.jpg"), 79, 46);
}

//�м��Ƿ���������,��֤l < r
bool x_no_dots_between(short x1, short x2, short y)
{
	short l = x1 < x2 ? x1 : x2, r = x1 > x2 ? x1 : x2;
	for (int i = l + 1; i < r; i++)
	{
		if (grid[y][i].img_num != -1)
			return false;
	}
	return true;
}

//�м��Ƿ���������,��֤t < b
bool y_no_dots_between(short y1, short y2, short x)
{
	short t = y1 < y2 ? y1 : y2, b = y1 > y2 ? y1 : y2;
	for (int i = t + 1; i < b; i++)
	{
		if (grid[i][x].img_num != -1)
			return false;
	}
	return true;
}

//�ж���ͨ���
bool is_connected(short x1, short y1, short x2, short y2, short &x3, short &y3, short &x4, short &y4)
{
	if (grid[y1][x1].img_num == grid[y2][x2].img_num && grid[y1][x1].img_num != -1)
	{
		if (x1 == x2 && y1 == y2)
			return false;
		if (x1 == x2 || y1 == y2)
		{
			if (no_turn(x1, y1, x2, y2))
			{
				return true;
			}
			if (two_turns(x1, y1, x2, y2, x3, y3, x4, y4))
			{
				return true;
			}
		}
		else
		{
			if (one_turn(x1, y1, x2, y2, x3, y3))
			{
				return true;
			}
			if (two_turns(x1, y1, x2, y2, x3, y3, x4, y4))
			{
				return true;
			}
		}
	}
	return false;
}

//�������յ�ֱ����ͨ
bool no_turn(short x1, short y1, short x2, short y2)
{
	if (y1 == y2)
	{
		if (x_no_dots_between(x1, x2, y1))
			return true;
	}
	else
	{
		if (y_no_dots_between(y1, y2, x1))
			return true;
	}
	return false;
}

//����һ���յ�
bool one_turn(short x1, short y1, short x2, short y2, short &x3, short &y3)
{
	if (grid[y1][x2].img_num == -1 && no_turn(x1, y1, x2, y1) && no_turn(x2, y1, x2, y2))
	{
		x3 = x2;
		y3 = y1;
		return true;
	}
	if (grid[y2][x1].img_num == -1 && no_turn(x1, y1, x1, y2) && no_turn(x1, y2, x2, y2))
	{
		x3 = x1;
		y3 = y2;
		return true;
	}
	return false;
}

//���������յ�
bool two_turns(short x1, short y1, short x2, short y2, short &x3, short &y3, short &x4, short &y4)
{
	for (int i = 0; i < column; i++)
		if (i != x1 && i != x2 && grid[y1][i].img_num == -1 && grid[y2][i].img_num == -1)
			//��д��no_turn && one_turn��Ϊ�˱�����ont_turn �������֮һ�ظ�
			if (no_turn(x1, y1, i, y1) && no_turn(i, y1, i, y2) && no_turn(i, y2, x2, y2))
			{
				x3 = i;
				y3 = y1;
				x4 = i;
				y4 = y2;
				return true;
			}

	for (int i = 0; i < row; i++)
		if (i != y1 && i != y2 && grid[i][x1].img_num == -1 && grid[i][x2].img_num == -1)
			if (no_turn(x1, y1, x1, i) && no_turn(x1, i, x2, i) && no_turn(x2, i, x2, y2))
			{
				x3 = x1;
				y3 = i;
				x4 = x2;
				y4 = i;
				return true;
			}
	return false;
}

//���޽�
bool is_solution(short &x1, short &y1, short &x2, short &y2)
{
	short tmpx3, tmpy3, tmpx4, tmpy4;
	for (y1 = 1; y1 < row - 1; y1++)
		for (x1 = 1; x1 < column - 1; x1++)
			for (y2 = y1; y2 < row - 1; y2++)
				for (x2 = 1; x2 < column - 1; x2++)
				{
					if (grid[y1][x1].img_num != -1)
						if (grid[y2][x2].img_num != -1)
							if (grid[y1][x1].img_num == grid[y2][x2].img_num)
								if (is_connected(x1, y1, x2, y2, tmpx3, tmpy3, tmpx4, tmpy4))
									return true;
				}
	return false;
}
