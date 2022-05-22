#pragma once
#define column 16		//����
#define row 12			//����
#define grid_size 40	//�����С
#define x0 5			//��ʼλ�ã���
#define y0 5			//��ʼλ�ã���
#define gap 0			//����֮��ļ�϶����
const short windows_width = 2 * x0 + grid_size * column + gap * (column - 1) + 250;
const short windows_lenth = 2 * y0 + grid_size * row + gap * (row - 1);

//img[13] ��ʼ�˵�����, img[14] ��Ϸ���汳��, img[15] ���а����ý���ġ��˳�����ť
IMAGE img[16];	//����easyx�е�IMAGE ����һ��ͼƬ����
LOGFONT textstyle;	//�����ʽ
//Ϊ�������˵�����
bool flg = true;		
short nhint = 2;
short nshuffle = 1;
int combo = 2;
int score = 0;
long t_start;
short resttime = 360;
short t_limit = 360;
//t������Ϸ��ʼ����һ�������ɹ�����ˣ�t��ʼ��Ϊ-5��Ϊ�˷�ֹ��һ������������Ϊcombo
short t = -5;
short n_img = (column - 2) * (row - 2);	//����ͼƬ������-2������Ϊ���������ո������ж��������ߵ�����
short level = 1;
//�����ý����¼֮ǰ�Ƿ��Ѿ�ѡ���һ���ؿ�
short prechoice = 0;			
char fl_name[20] = "rank_list1.txt";//��λ��¼����

class labels
{
public:
	labels() : x(0), y(0), w(200), h(60), n(13) {}
	labels(short _x, short _y, short _w, short _h, short _n) : x(_x), y(_y), w(_w), h(_h), n(_n) {}
	//�ж��Ƿ����˸ð�ť
	bool init(MOUSEMSG m)
	{
		if (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h)
			return true;
		else
			return false;
	}
private:
	short x, y, w, h, n;
};
labels lstart_game(250, 270, 400, 80, 13);	//��������ͼƬ��ť��label �����ж��Ƿ񱻰���
labels lrank_list(380, 5, 140, 40, 14);
labels lexit_game(760, 460, 120, 40, 15);
labels lsetting(855, 5, 40, 40, 16);
labels lshuffle(646, 287, 79, 46, 17);
labels lhint(646, 207, 79, 46, 18);
labels lbk_to_menu(720, 392, 79, 46, 19);
labels lclose_rank(410, 440, 79, 46, 20);

RECT rthint = { 631, 200, 870, 260 };
RECT rtshuffle = { 631, 280, 870, 340 };
RECT rlhint = { 646, 207, 725, 253 };
RECT rlshuffle = { 646, 287, 725, 333 };
RECT rbk_to_menu = { 720, 392, 799, 438 };
RECT rscores = { 650, 85, 870, 175 };
//��������а������ֵľ��Σ������á�������Ҳ���������
RECT rrank_name = { 235, 25, 665, 120 };
RECT rrank1 = { 235, 25, 665, 120 };
RECT rrank2 = { 235, 125, 665, 425 };
RECT R = { 0, 5, windows_width, 45 };

struct grids
{
	short x = 0;
	short y = 0;
	//��� -1 ��ʾû��ͼƬ
	short img_num = -1;				
}grid[row][column];

struct levels
{
	char fl_name[20];
	short n_img;
	short t_limit;
};
struct levels level1 = { "rank_list1.txt", 140, 360 };	//����ÿ���ؿ��Ļ����ı���ͼƬ����������ʱ��
struct levels level2 = { "rank_list2.txt", 140, 150 };
struct levels level3 = { "rank_list3.txt",  80, 150 };
struct levels level4 = { "rank_list4.txt", 110, 200 };
struct levels level5 = { "rank_list5.txt", 110, 150 };

int Rand(int i)
{
	return rand() % i; //����һ����0��i-1�������
}

void initgridxy();
void initimg();
void initmap1();
void initmap2();
void initmap3();
void draw_start_menu();
void draw_game_window();

void rank_list();
void setting();
void hint();
void shuffle();
bool ten_solutions();

bool start_menu();
void start_game();
void game_window();
void game_over();
bool judge();
void save_memory();

void draw_map();
void drawline(short x1, short y1, short x2, short y2);
void drawrectangle(short x, short y);
void drawsolidrectangle(short x, short y);
void print_score(int scores);

bool is_solution(short &solution_x1, short &solution_y1, short &solution_x2, short &solution_y2);
bool x_no_dots_between(short x1, short x2, short y);
bool y_no_dots_between(short y1, short y2, short x);
bool is_connected(short x1, short y1, short x2, short y2, short &x3, short &y3, short &x4, short &y4);
bool no_turn(short x1, short y1, short x2, short y2);
bool one_turn(short x1, short y1, short x2, short y2, short &x3, short &y3);
bool two_turns(short x1, short y1, short x2, short y2, short &x3, short &y3, short &x4, short &y4);

bool cmp(short a, short b)
{
	return a > b;
}

/*����label��ţ�label��ż�Ϊ��Ӧ��img[]���;
	false�����ڿ�ʼ�˵����棬true��������Ϸ���� */
short clk_labels(MOUSEMSG m, bool flg);
//ѡ���ĸ��ؿ�
void clk_levels(MOUSEMSG m);
