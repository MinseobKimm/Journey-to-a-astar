 /*
10.6 CIN �Ź� �����ߴ� �κ� �׳� �ּ�ó���س��� 
10.70 ���̽�Ÿ�� �����ϸ�..�̤� 
10.10 �׷��� �� ������ �������� ��ġ�� �� ��ȯ �� ��Ű�� �÷��̾� �̵����� ���ھ�� ��� �غ� �׸��� ���Ӽ� ��� ������ ������ 
10.17 ������ ���� �غ� ��! 
��ĥ�κ�:
1)���ھ� �������Ҷ� �ߺ�(�ϴ� �ּ��س���) ->�ذ� 
2)�� ���°� �ڿ������� ����->�ذ� 
3)���̽�Ÿ �� ���� ��ǥ�� ���̶�� �ߴ°��� ���ذ� �Ȱ� ->�ذ�
4)�� ����ְ� ���� �ʿ�->���� ���� 
5) ���� ����Ҽ��ִ� �� ���� 
6) ���ֱ� 
*/





#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <process.h>
#include <time.h>
#include "Astar.c"

#define GAME_WIDTH 80
#define GAME_HEIGHT 34
#define MAP_WIDTH  39
#define MAP_HEIGHT 39

#define MAXENEMY 10

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;

int size=40;
int start=2;
int score=0;
int wall_check=0;


int map[1000][1000]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	//---------------------------------------------------------------------------------�� �� ���� ����ó�� 
	
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,9,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},


}; 

int posx=1,posy=37;
int goalx=37,goaly=37;
int difficulty=1;
char mode='l'; 

struct enemies{
	int x;
	int y;
	int show;
}enemy[MAXENEMY];

void setColor(int text) {//0 = ������, 1 = �Ķ��� ,2 = �ʷϻ�,3 = ���� ,4 = ������,5 = ���ֻ� ,6 = �����,7 = ��� ,8 = ȸ��,9 = ���� �Ķ��� ,10 = ���� �ʷϻ�,11 = ���� ���� ,12 = ���� ������,13 = ���� ���ֻ� ,14 = ���� �����,15 = ���� ��� 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}
void printMap(int x,int y){
	gotoxy(x*2,y);
	if(map[y][x]==1)printf("��");
	else if(map[y][x]==9){
		setColor(6); 
		printf("��");
		setColor(7);
	}else printf("  ");
} 
void wallPut(int x,int y){
	if(wall_check){
			wall_check=0;
			map[y][x]=1;
			printMap(x,y);
		}
}        
void playerMove(){
	if(GetAsyncKeyState(VK_SPACE)){
			wall_check=1;
	}
	
	if(GetAsyncKeyState(VK_UP) < 0||GetAsyncKeyState(0x57)){
		if(posy-1<start||map[posy-1][posx]==1)return;//�� ������ ������ ��� üũ 
		player_draw(0);
		posy--;
		wallPut(posx,posy+1);
		player_draw(1);
		
		
	}
	if(GetAsyncKeyState(VK_RIGHT) < 0||GetAsyncKeyState(0x44)){
		if(posx+2>size-1||map[posy][posx+1]==1)return;
		player_draw(0);
		posx++;
		wallPut(posx-1,posy);
		player_draw(1);
		 
	}
	if(GetAsyncKeyState(VK_DOWN) < 0||GetAsyncKeyState(0x53)){
		if(posy+2>size-1||map[posy+1][posx]==1)return;
		player_draw(0);
		posy++;
		wallPut(posx,posy-1);
		player_draw(1);
	}
	if(GetAsyncKeyState(VK_LEFT) < 0||GetAsyncKeyState(0x41)){
		if(posx-1<0||map[posy][posx-1]==1)return;
		player_draw(0);
		posx--;
		wallPut(posx+1,posy);
		player_draw(1);
	}
	if(enemy[0].x==posx&&enemy[0].y==posy)GameOver("CRUSHED..");
	
}	
 
int player_draw(int type){//type 1: �÷��̾� ��ġ �̵�, type 0:������ ĭ �� ǥ�� 
	gotoxy(posx*2,posy);
	if(type==1){ 
		printf("��");
		
	}else{
		printMap(posx,posy);
	} 
}
int enemy_draw(int x,int y,int type){
	if(enemy[0].x==posx&&enemy[0].y==posy)GameOver("CRUSHED..");
	gotoxy(x*2,y);
	if(type==1){ 
		setColor(4);
		printf("##");
		setColor(7);
	}else{
		printMap(x,y);
	}
}

int gotoxy(int x, int y){
	COORD CursorPosition = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void init(){
	system("mode con cols=80lines=40 | title Journey to a star v.1.0.0");
	HANDLE hConsole; 
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT); //���콺 �Է¸��� �ٲ�
    DWORD CIN;
	DWORD mode;

	enemy[0].show=1;
    enemy[0].x=goalx;
    enemy[0].y=goaly;
}

void draw_map(){
	int i,j;
    gotoxy(0,0);
    for(i=0;i<size-1;i++){
			for(j=0;j<size-1;j++){
				gotoxy(j*2,i);
				if(i<start){
					printf("  ");
				}else{
					printMap(j,i);	
				}
				
			}
			printf("\n");
		}
}
int CustomGetMap( int x, int y )
{
	if( x < 0 ||
	    x >= MAP_WIDTH ||
		 y < 0 ||
		 y >= MAP_HEIGHT
	  )
	{
		return 1;	 
	}
	if(map[y][x]!=1)return 0;
	else return 1;
}

void enemyMove(int j){
	if(j==1)return;
	int i=0,move;
		if(enemy[i].show!=1)return;
		enemy_draw(enemy[i].x,enemy[i].y,0);
		if(enemy[i].x==posx&&enemy[i].y==posy)GameOver("CRUSHED..");
		move=Astar_return(enemy[i].x,enemy[i].y,posx,posy,CustomGetMap);
		
		if(move==-5)GameOver("NO POSSIBLE WAY");
		if(move<=0)return;
		if(map[move/40][move%40]==1)return;
		 enemy[i].x=move%40;
		 enemy[i].y=move/40;
	
}

void enemyRender(){
	int i;
	for(i=0;i<MAXENEMY;i++){
		if(enemy[i].show!=1)continue;
		enemy_draw(enemy[i].x,enemy[i].y,1);
	}
}

void GameOver(char a[]){
	system("cls");
	gotoxy(GAME_WIDTH / 2 - 3, GAME_HEIGHT / 2);
	printf("Game Over");
	gotoxy(GAME_WIDTH / 2 - 5, GAME_HEIGHT / 2+1);
	printf("%s",a);
	gotoxy(GAME_WIDTH / 2 - 8, GAME_HEIGHT / 2 + 2);
	printf("difficulty : %d Time : %d",difficulty,score);
	gotoxy(GAME_WIDTH / 2 + 20, GAME_HEIGHT - 2);
	printf("1306 ��μ�");
	gotoxy(0,50);
	Sleep(1000);
	exit(0);
}
void CheckGoal(){
	if(posx==goalx&&posy==goaly){
		system("cls");
    	End();
	}
}

void scoreRender(){
	gotoxy(GAME_WIDTH / 2-8,0);
	printf("Time : %3d",score++);
	if(score>10000)exit(0);
	gotoxy(63,1);
	printf("difficulty : %d",difficulty);
	
}

void ui(){
	
	printf("      _                                     _                    _       \n");
	printf("     | |                                   | |                  | |       \n");
	printf("     | | ___  _   _ _ __ _ __   ___ _   _  | |_ ___     __ _ ___| |_ __ _ _\n");
    printf(" _   | |/ _ \\| | | | '__| '_ \\ / _ \\ | | | | __/ _ \\   / _` / __| __/ _` | '__|\n");
    printf("| |__| | (_) | |_| | |  | | | |  __/ |_| | | || (_) | | (_| \\__ \\ || (_| | | \n");
    printf("  \____/ \\___/ \\__,_|_|  |_| |_|\\___|\\__, |  \\__\\___/   \\__,_|___/\\__\\__,_|_| \n");
    printf("                                     __/ |                                \n");
    printf("                                    |___/                              \n");
	gotoxy(GAME_WIDTH / 2 - 8, GAME_HEIGHT / 2 + 2);
	printf("~ Press Any Key ~");
	gotoxy(GAME_WIDTH / 2 - 12, GAME_HEIGHT / 2 + 4);
	printf("-Press 'h' to play HardMode");
	gotoxy(GAME_WIDTH / 2 + 20, GAME_HEIGHT - 2);
	printf("1306 ��μ�");
	        
	getch();
	if(GetAsyncKeyState(0x48))difficulty=2;
	while(GetAsyncKeyState(VK_SPACE)) 
	system("cls");
}
void End(){
	system("cls");
	gotoxy(GAME_WIDTH / 2 - 7, GAME_HEIGHT / 2);
	printf("Congratulations");
	gotoxy(GAME_WIDTH / 2 - 13, GAME_HEIGHT / 2+2);
	printf("difficulty : %d Time : %d",difficulty,score);
	gotoxy(GAME_WIDTH / 2 - 9, GAME_HEIGHT / 2 + 3);
	if(difficulty==1){
		if(score<=400)printf("Your Grade : S\n");
		else if(score<=450)printf("Your Grade : A\n");
		else if(score<=500)printf("Your Grade : B\n");
		else if(score<=550)printf("Your Grade : C\n");
		else if(score<=700)printf("Your Grade : D\n");
		else printf("Your Grade : E\n");
	}else{
		if(score<=450)printf("Your Grade : S\n");
		else if(score<=500)printf("Your Grade : A\n");
		else if(score<=550)printf("Your Grade : B\n");
		else if(score<=600)printf("Your Grade : C\n");
		else if(score<=650)printf("Your Grade : D\n");
		else printf("Your Grade : E\n");
	}
	gotoxy(GAME_WIDTH / 2 - 9, GAME_HEIGHT / 2 + 4);
	printf("Your Score : %d",difficulty*(10000-score));
	gotoxy(GAME_WIDTH / 2 + 20, GAME_HEIGHT - 2);
	printf("1306 ��μ�");
	gotoxy(0,50);
	Sleep(1000);
	exit(0);
}

/***
 *           _                                     _                    _             
 *          | |                                   | |                  | |            
 *          | | ___  _   _ _ __ _ __   ___ _   _  | |_ ___     __ _ ___| |_ __ _ _ __ 
 *      _   | |/ _ \| | | | '__| '_ \ / _ \ | | | | __/ _ \   / _` / __| __/ _` | '__|
 *     | |__| | (_) | |_| | |  | | | |  __/ |_| | | || (_) | | (_| \__ \ || (_| | |   
 *      \____/ \___/ \__,_|_|  |_| |_|\___|\__, |  \__\___/   \__,_|___/\__\__,_|_|   
 *                                          __/ |                                     
 *                                         |___/                                      
 */


void update(int j){
	enemyMove(j);
	playerMove();
	CheckGoal();
	scoreRender();
} 
void render(){
	enemyRender();
}
 
int main(){
	int delay=50,j=1;
	init();
	ui(); 
    draw_map();
    player_draw(1);
	while (1){
    	update(j++);
    	render();
    	Sleep(delay);
    	if(j>difficulty+3)j=1;
    }
    return 0;

}


