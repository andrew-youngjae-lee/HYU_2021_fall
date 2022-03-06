#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define SPACE 32
#define ENTER 10
/* ASCII 코드*/

void DrawDinosaur(int);
/* key에서  입력받아서 점프 구현*/ 
int _kbhit(void); /* keyboard hit */
int GetKeyDown();

void DrawGameOver(const int score, const int winWidth, const int winHeight)
{
	clear();
	int x = winWidth / 2;
	int y = winHeight / 2;

	move(y-2,x-13);
	printw("===========================");
	move(y-1,x-13);
	printw("======G A M E O V E R======");
	move(y,x-13);
	printw("===========================");
	move(y+1,x-6);
	printw("SCORE : %d", score);
	
	system("pause");
}

void DrawVictory(const int score, const int winWidth, const int winHeight)
{
	clear();
	int x = winWidth / 2;
	int y = winHeight / 2;

	move(y-2,x-12);
	printw("=========================");
	move(y-1,x-12);
	printw("======V I C T O R Y======");
	move(y,x-12);
	printw("=========================");
	move(y+1,x-6);
	printw("SCORE : %d", score);

	system("pause");
}

void DrawScoreBox(int score, int speed, const int winWidth)
{
	int x = winWidth / 2;
	move(0,x-3);
	printw("Score : %d ", score);
	move(1,x-3);
	printw("Speed : %d ", speed);
}

void DrawCactus(int cactusHead, int cactusPos)
{
	move(cactusHead, cactusPos);
	printw("$$$$");
	move(cactusHead+1, cactusPos);
        printw(" $$ ");
	move(cactusHead+2, cactusPos);
        printw(" $$ ");
 	move(cactusHead+3, cactusPos);
        printw(" $$ ");
 	move(cactusHead+4, cactusPos);
        printw(" $$ ");
}
int _kbhit(void)
{
	struct timeval tv = {0L, 0L};/* long type zero*/
	fd_set fds;
	/* linux에서는 모든 것을 파일로 관리(모든 연결, 파일, 장치)
	file desciptor로 관리 => 파일에 대한 정보를 담은 메타데이터를
	숫자로 관리 = file descriptor*/

	FD_ZERO(&fds); /* fd 0 = keybord input = stdin*/
	FD_SET(0, &fds);

	return select(1, &fds, NULL, NULL, &tv);
}

int GetKeyDown()
{
	if(_kbhit()){ 
		return getch(); /*get char = char를 입력받겠다*/
	}
	return 1;
}

void DrawDinosaur(int dinosaurHead)
{
	move(dinosaurHead, 0); /*(y,x) 좌표 */
	static bool legDraw = true;
	
	printw("        &&&&&&& \n");
	printw("       && &&&&&&\n");
	printw("       &&&&&&&&&\n");
	printw("&      &&&      \n");
	printw("&&     &&&&&&&  \n");
	printw("&&&   &&&&&     \n");
	printw(" &&  &&&&&&&&&& \n");
	printw(" &&&&&&&&&&&    \n");
	printw("   &&&&&&&&&    \n");
	printw("    &&&&&&&     \n");

	if(legDraw){
		printw("     &    &&&     \n");
		printw("     &&           ");
		legDraw = false;
	}
	else{
		printw("     &&&  &       \n");
		printw("          &&      ");
		legDraw = true;
	}

}

bool isClash(const int cactusPos, const int dinosaurHead, const int winHeight, const int speed)
{
	if (cactusPos <= 10 && cactusPos >= 3  && dinosaurHead > winHeight - 18){
		return true;
	}
	return false;
}
int main(int argc, char* argv[])
{
	int idx = 0;
	int winWidth = 0, winHeight = 0;
	int dinosaurHead = 0; /* 머리를 어디서부터 그릴지(좌표) */
	int cactusHead = 0, cactusPos = 0;
	int getKey = 0;
	int score = 0;
	int speed = 3;
	int checkSpeed = 0;
	bool isJumping = false;
	bool isBottom = true;

	initscr();	
	getmaxyx(stdscr, winHeight, winWidth); /* ncurses header file */
	/* stdscr = standard screen - information of screen(terminal) */

	dinosaurHead = winHeight - 13;
	cactusHead = winHeight - 5;
	cactusPos = winWidth - 20;
	/* initscr();*/	

	while(true){

		if(isClash(cactusPos, dinosaurHead, winHeight, speed))
		{
			DrawGameOver(score, winWidth, winHeight);
			refresh();
			sleep(5);
			break;
		}

		if(speed > 7)
		{
			DrawVictory(score, winWidth, winHeight);
			refresh();
			sleep(5);
			break;
		}

		getKey = GetKeyDown(); /*어떤 키보드가 눌렸는지 반환*/

		if((SPACE == getKey) && isBottom){
			//
			isJumping = true;
			isBottom = false;

		} else if(ENTER == getKey){
			break;
		}
		if(isJumping){
			dinosaurHead -= speed; //위로 올라감
		}else{
			dinosaurHead += speed; //밑으로 내려감
		}
		//winHeaight = terminal의 바닥
		if(winHeight <= dinosaurHead + 13){
			//공룡의 발이 바닥보다 아래로 내려가면
			dinosaurHead = winHeight - 13;
			//무조건 바닥을 걷는 것으로 설정
			isBottom = true;
		}
		// dinsaurHead가 천장 위로 올라가지 않도록
		if(dinosaurHead <= 0){
			isJumping = false;
		}

		cactusPos = cactusPos - speed; // 우에서 좌로 계속 움직임

		if(cactusPos <= 0){
			score++;
			cactusPos = winWidth - 20;
		}

		if(score / 10 == checkSpeed + 1)
		{
			speed++;
			checkSpeed++;
		}
		
		DrawScoreBox(score, speed, winWidth);
		DrawDinosaur(dinosaurHead);
		DrawCactus(cactusHead, cactusPos);
		usleep(100000);
		refresh();
		idx++;
		clear();
	}

	endwin();

	return 0;
}

