#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

/* MACRO */
#define EXIT	27
#define PAUSE	112

#define MAP_INIT_POS_X	3
#define MAP_INIT_POS_Y	2
#define MAP_WIDTH	30
#define MAP_HEIGHT	20

#define INIT_SPEED	200000

/* GLOBAL */
int snakePosX[100];
int snakePosY[100];
int snakeLen;

int speed;
int score;
int bestScore = 0;
int lastScore = 0;
int key;
int direction;

int foodPosX;
int foodPosY;

/* METHOD */
void Start();
void Reset();
void DrawMap();
void Move(int);
void Pause();
void GameOver();
void CreateFood();
void Debug();
int  _kbhit();	// Modify a Windows Func
void gotoxy(int, int, const char*); // Modify a ~~
void SetColor();
void Food();

void gotoxy(int y, int x, const char* msg)
{
	move(y, x*2);
	printw("%s",msg);
}

int _kbhit(void)
{
	struct timeval tv = {0L, 0L};
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(0, &fds);

	return select(1, &fds, NULL, NULL, &tv);
}

void Start()
{
	int colorFlag = 1;

	while(_kbhit()){ getch(); }

	DrawMap();

	attron(COLOR_PAIR(3));

	gotoxy(MAP_INIT_POS_Y + 5, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "+--------------------------+");
	gotoxy(MAP_INIT_POS_Y + 6, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "         SNAKE GAME         ");
	gotoxy(MAP_INIT_POS_Y + 7, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "+--------------------------+");

	gotoxy(MAP_INIT_POS_Y + 11, MAP_INIT_POS_X + (MAP_WIDTH / 2) - 11, "PRESS THE ARROW KEYS TO PROCEED WITH THE GAME");

	gotoxy(MAP_INIT_POS_Y + 12, MAP_INIT_POS_X + (MAP_WIDTH / 2) - 7, "P : PAUSE");
	gotoxy(MAP_INIT_POS_Y + 13, MAP_INIT_POS_X + (MAP_WIDTH / 2) - 7, "ESC : EXIT");
	
	//usleep(800);

	while(_kbhit()){
		
		key = getch();

		if(EXIT == key){
			endwin(), exit(0);
		}else{
			break;
		}
		
		attron(COLOR_PAIR(colorFlag));
		gotoxy(MAP_INIT_POS_Y + 9, MAP_INIT_POS_X + (MAP_WIDTH / 2) - 7, "PRESS ANY KEY TO START");
		usleep(200000);

		refresh();

		colorFlag = colorFlag % 7 + 1;
	}

	Reset();
}

void Reset()
{
	int idx = 0;

	clear();

	DrawMap();

	while(_kbhit()) { getch(); }

	direction = KEY_LEFT;
	speed = INIT_SPEED;
	snakeLen = 5;
	score = 0;

	for(; idx<snakeLen; idx++){
		snakePosX[idx] = MAP_WIDTH / 2 + idx;
		snakePosY[idx] = MAP_HEIGHT / 2;

		gotoxy(MAP_INIT_POS_Y + snakePosY[idx], MAP_INIT_POS_X + snakePosX[idx], "O");
	}

	gotoxy(MAP_INIT_POS_Y + snakePosY[0], MAP_INIT_POS_X + snakePosX[0], "@");
	CreateFood();
}

void DrawMap()
{
	int idx = 0;

	for(;idx<MAP_WIDTH; idx++){
		gotoxy(MAP_INIT_POS_Y, MAP_INIT_POS_X + idx, (const char*)&"#");
	}

	for(idx=MAP_INIT_POS_Y; idx<MAP_INIT_POS_Y + MAP_HEIGHT - 1; idx++){
		gotoxy(idx, MAP_INIT_POS_X, (const char*)&"#");
		gotoxy(idx, MAP_INIT_POS_X + MAP_WIDTH - 1, (const char*)&"#");
	}

	for(idx=0; idx<MAP_WIDTH; idx++){
		gotoxy(MAP_INIT_POS_Y + MAP_HEIGHT - 1, MAP_INIT_POS_X + idx, (char*)&"#");
	}
}

void SetColor()
{
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void Move(int dir)
{
	int idx = 0;

	if(snakePosX[0] == foodPosX && snakePosY[0] == foodPosY){
		score += 5;
		CreateFood();
		snakeLen++;
		snakePosX[snakeLen-1] = snakePosX[snakeLen-2];
		snakePosY[snakeLen-1] = snakePosY[snakeLen-2];
	}


	if(snakePosX[0] == 0 || snakePosX[0] == MAP_WIDTH - 1 || snakePosY[0] == 0 || snakePosY[0] == MAP_HEIGHT - 1){
		GameOver();
		return;
	}

	for(int i = 1; i < snakeLen; i++){
		if(snakePosX[0] == snakePosX[i] && snakePosY[0] == snakePosY[i]){
			GameOver();
			return;
		}
	}

	gotoxy(MAP_INIT_POS_Y + snakePosY[snakeLen - 1], MAP_INIT_POS_X + snakePosX[snakeLen - 1], " ");
	
	for(idx = snakeLen - 1; 0 < idx; idx--){
		snakePosX[idx] = snakePosX[idx - 1];
		snakePosY[idx] = snakePosY[idx - 1];
	}

	gotoxy(MAP_INIT_POS_Y + snakePosY[0], MAP_INIT_POS_X + snakePosX[0], "O");

	if(KEY_LEFT == dir){ --(snakePosX[0]); }
	if(KEY_RIGHT == dir) { ++(snakePosX[0]); }
	if(KEY_UP == dir) { --(snakePosY[0]); }
	if(KEY_DOWN == dir) { ++(snakePosY[0]); }

	gotoxy(MAP_INIT_POS_Y + snakePosY[idx], MAP_INIT_POS_X + snakePosX[idx], "@");

	refresh();
}

void CreateFood(void)
{
	int i;

	int food_on_snake = 0;

	int randval = 0;

	gotoxy(MAP_INIT_POS_Y + MAP_HEIGHT, MAP_INIT_POS_X,"YOUR SCORE : ");
	printw("%3d | LAST SCORE : %3d | BEST SCORE : %3d", score, lastScore, bestScore);

	while(1){
		food_on_snake = 0;
		srand((unsigned)time(NULL)+randval);
		foodPosX = (rand()%(MAP_WIDTH -2))+1;
		foodPosY = (rand()%(MAP_HEIGHT -2))+1;

		for(int i=0; i<snakeLen; i++){
			if(foodPosX == snakePosX[i] && foodPosY == snakePosY[i]){
				food_on_snake = 1;
				randval++;
				break;
			}
		}

		if(food_on_snake == 1) continue;

		gotoxy(MAP_INIT_POS_Y + foodPosY, MAP_INIT_POS_X + foodPosX, "%");
		speed -= 3;
		break;
	}
}

void GameOver(void)
{
	gotoxy(MAP_INIT_POS_Y + 5, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "+--------------------------+");
	gotoxy(MAP_INIT_POS_Y + 6, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "          GAME OVER         ");
	gotoxy(MAP_INIT_POS_Y + 7, MAP_INIT_POS_X + (MAP_WIDTH / 2) -7, "+--------------------------+");
	gotoxy(MAP_INIT_POS_Y + 8, MAP_INIT_POS_X + (MAP_WIDTH / 2) -4, "YOUR SCORE : ");
	printw("%d", lastScore = score);
	
	gotoxy(MAP_INIT_POS_Y + 11, MAP_INIT_POS_X + (MAP_WIDTH / 2) - 6, "PRESS ANY KEY TO RESTART");
	
	if(score > bestScore){
		bestScore = score;
		gotoxy(MAP_INIT_POS_Y + 10, MAP_INIT_POS_X + (MAP_WIDTH/2) - 4, "**BEST SCORE**");
	}
	usleep(500);
	
	while(_kbhit()) getch();
	key = getch();
	Start();
}

int main(int argc, char* argv[])
{
	initscr();

	noecho();

	keypad(stdscr, TRUE);

	SetColor();

	Start();

	while(1){
		
		if(_kbhit()){ key = getch(); }

		usleep(speed);

		switch(key){
			
			case KEY_LEFT :
			case KEY_RIGHT :
			case KEY_DOWN :
			case KEY_UP :
				if((KEY_LEFT == direction && KEY_RIGHT != key) || 
				(KEY_RIGHT == direction && KEY_LEFT != key) ||
				(KEY_UP == direction && KEY_DOWN != key) ||
				(KEY_DOWN == direction && KEY_UP != key)){
					direction = key;
				}
				key = 0;
				break;
			case PAUSE :
				//Pause();
				break;
			case EXIT :
				endwin();
				exit(0);
		}

		Move(direction);

	}

	//attron(COLOR_PAIR(5));

	//DrawMap();

	//getch();

	endwin();

	return 0;
}
