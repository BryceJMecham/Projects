#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*
* Function title: main
* Summary: Creates a map the user can move around in.
* Author: Bryce Mecham
*
* Pseudocode:
// Begin
//	Print "Welcome to Game_1!\n"
//		"Try moving around with the a w s d keys."
//	Initializing the array to '.'
//	Print World (10x10 array)
//	loop getchar();
//		switch ();
//			case (a w s d):
//				move function;
//		Remove World
//		Print World
* End
*/

#define PICAXE 1
#define S_PICAXE 2
#define AXE 3
#define S_AXE 4
#define bear_attack 5
#define SPEAR 1
#define BOW 1

int tool=0, tool2=0, ps=0, p_hp=3, b_hp=5, xp=0;

void move_up(int a[][21][5],int *m,int *n, int *w, int *s, int *f); 
void move_down(int a[][21][5],int *m,int *n, int *w, int *s, int *f);
void move_left(int a[][21][5],int *m,int *n, int *w, int *s, int *f);
void move_right(int a[][21][5],int *m,int *n, int *w, int *s, int *f);
void wall_up(int a[][21][5], int *m, int *n);
void wall_down(int a[][21][5], int *m, int *n);
void wall_left(int a[][21][5], int *m, int *n);
void wall_right(int a[][21][5], int *m, int *n);
void door_up(int a[][21][5], int *m, int *n);
void door_down(int a[][21][5], int *m, int *n);
void door_left(int a[][21][5], int *m, int *n);
void door_right(int a[][21][5], int *m, int *n);
void tree_up(int a[][21][5], int *m, int *n);
void tree_down(int a[][21][5], int *m, int *n);
void tree_left(int a[][21][5], int *m, int *n);
void tree_right(int a[][21][5], int *m, int *n);
void bear(int a[][21][5], int *o, int *p, int *m, int *n, int *c, int *i, int *d);
void game_over(int a[][21][5], int *i);

// a[][][1] is object location
// a[][][0] is object HP

int main(void){
	int a[20][21][5]={0}, c=1, c1=1, c2=1, c3=1, d=4, i, j, k, m, n, o, p, o1, p1, o2, p2, o3, p3, W=0, S=0, F=0, high_score, score_2, score_3;
	int weap = 0, weap1 = 0, arrow = 0, attack, attack_m = 0;
	char tools[13], tools2[10];

struct termios terminal_info;
tcgetattr(STDIN_FILENO, &terminal_info);
terminal_info.c_lflag &= ~ICANON;
tcsetattr(STDIN_FILENO, TCSANOW, &terminal_info);
	srand(time(NULL));
//	Print "Welcome to Game_1!\n"
	printf("\n\t\t\tWelcome to Game_1!\n");
//		"Try moving around with the a w s d keys."
	printf("\tYou are the @ symbol in the bottom middle.\n");
	printf("\tTry moving around with the a w s d keys!\n\t(1 will exit the program)\n");
//	Initializing the array to '.'
	for (i=0; i<20; i++){
		for (j=0; j<20; j++) {
			a[i][j][1]='.';
		}
	}
	m = 19;
	n = 9;
	a[m][n][1]='@';
	a[m][n][0]= p_hp;
	for (i=0; i<=5; i++){
	o = rand() % 20;
	p = rand() % 20;
	if (a[o][p][1] != '@' && a[o][p][1] != 'S'){
		a[o][p][1] = 'T';
		a[o][p][0] = 30;
	}
	o = rand() % 20;
	p = rand() % 20;
	if (a[o][p][1] != '@' && a[o][p][1] != 'T'){
		a[o][p][1] = 'S';
		a[o][p][0] = 50;
	}
	}
	o = rand() % 20;
	p = rand() % 20;
	if (o>= 13){
		o -= 10;
	}
	a[o][p][1]= 'B';
	a[o][p][0]= b_hp; // I need to make this HP count follow where the bear is
	
//	Print World (10x10 array)
	for (i=0; i<20; i++){
		printf("\t");
		for (j=0; j<20; j++){
			if (a[i][j][1]=='.'){
				printf("\033[0;33m"); // Yellow
				printf(" %c ", a[i][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[i][j][1]=='T' || a[i][j][1]=='D'){
				printf("\033[0;32m"); // Green
				printf(" %c ", a[i][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[i][j][1]=='S'|| a[i][j][1]=='W'){
				printf(" %c ", a[i][j][1]); // Black(white)
			}
			if (a[i][j][1]=='B'){
				printf("\033[0;31m"); // Red
				printf(" %c ", a[i][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[i][j][1]=='@'){
				printf("\033[0;34m"); // Blue
				printf(" %c ", a[i][j][1]);
				printf("\033[0m"); // Reset
			}
		}
		printf("\n");
	}
	if (tool2 == 0){
		strcpy(tools2, "None");
	}	
	if (tool == 0){
		strcpy(tools, "None");
	}
	printf("\tBag: (Wood: %d  Stone: %d  Fruit: %d)\t\tXP: %d\n", W, S, F, xp);
	printf("\t     (Tools: %s", tools);
	if(tool2 > 0){
		printf(", %s", tools2);
	}
	printf(")\n");
	printf("\tPlayer HP: %d", p_hp);
	if (a[o][p][0] > 0){
		printf("\tBear #1 HP: %d\n", b_hp);
	}
//	loop getchar();
	for (;i!='1';){
		ps = 0;
		scanf("%c", &i);
		//getchar();
//		switch ();
		switch (i){
//			case (a w s d):
			case 'a':
//				move function;
				move_left(a, &m, &n, &W, &S, &F);
				xp++;
				break;
			case 's':
				move_down(a, &m, &n, &W, &S, &F);
				xp++;
				break;
			case 'd':
				move_right(a, &m, &n, &W, &S, &F);
				xp++;
				break;
			case 'w':
				move_up(a, &m, &n, &W, &S, &F);
				xp++;
				break;
//				fast move function;
			case 'A':
				move_left(a, &m, &n, &W, &S, &F);
				if (F > 0) {
					move_left(a, &m, &n, &W, &S, &F);
					F -= 1; 
					xp += 5;
				}
				break;
			case 'S':
				move_down(a, &m, &n, &W, &S, &F);
				if (F > 0) {
					move_down(a, &m, &n, &W, &S, &F);
					F -= 1; 
					xp += 5;
				}
				break;
			case 'D':
				move_right(a, &m, &n, &W, &S, &F);
				if (F > 0) {
					move_right(a, &m, &n, &W, &S, &F);
					F -= 1; 
					xp += 5;
				}
				break;
			case 'W':
				move_up(a, &m, &n, &W, &S, &F);
				if (F > 0) {
					move_up(a, &m, &n, &W, &S, &F);
					F -= 1; 
					xp += 5;
				}
				break;	
			case 'q':
					attack = 0;
					attack_m = 0;
					if (weap == SPEAR || weap1 == BOW){
						if (weap == SPEAR && weap1 != BOW){
							for (j=0; j<=2; j++){
							if (a[m-j][n][1] == 'B' && attack == 0){
								a[m-j][n][0] -= 2;
								attack++;
							}
							if (a[m+j][n][1] == 'B' && attack == 0){
								a[m+j][n][0] -= 2;
								attack++;
							}
							if (a[m][n-j][1] == 'B' && attack == 0){
								a[m][n-j][0] -= 2;
								attack++;
							}
							if (a[m][n+j][1] == 'B' && attack == 0){
								a[m][n+j][0] -= 2;
								attack++;
							}
							}	//end loop
							if (attack == 0){
								attack_m = 1;
							}
						}
						if (weap != SPEAR && weap1 == BOW){
							if (arrow == 0){
								attack_m = 2;
								attack++;
							}
							
								for (j=0; j<=8 && attack == 0; j++){
							if (a[m-j][n][1] == 'B' && attack == 0){
								a[m-j][n][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m+j][n][1] == 'B' && attack == 0){
								a[m+j][n][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m][n-j][1] == 'B' && attack == 0){
								a[m][n-j][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m][n+j][1] == 'B' && attack == 0){
								a[m][n+j][0] -= 1;
								attack++;
								arrow--;
							}
							}	//end loop
							
							if (attack == 0){
								attack_m = 1;
								arrow--;
							}	
						}
						if (weap == SPEAR && weap1 == BOW){
							for (j=0, k=0; j<=2; j++){
							if (a[m-j][n][1] == 'B' && attack == 0 ){ //if j > 1 ...&& a[m-j-k][n][1] == '.' so you can't hit through walls
								a[m-j][n][0] -= 2;
								attack++;
							}
							if (a[m+j][n][1] == 'B' && attack == 0){
								a[m+j][n][0] -= 2;
								attack++;
							}
							if (a[m][n-j][1] == 'B' && attack == 0){
								a[m][n-j][0] -= 2;
								attack++;
							}
							if (a[m][n+j][1] == 'B' && attack == 0){
								a[m][n+j][0] -= 2;
								attack++;
							}
							}	//end loop
							if (arrow == 0 && attack == 0){
								attack_m = 2;
								attack++;
							}
			
								for (j=0; j<=8 && attack == 0; j++){
							if (a[m-j][n][1] == 'B' && attack == 0){
								a[m-j][n][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m+j][n][1] == 'B' && attack == 0){
								a[m+j][n][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m][n-j][1] == 'B' && attack == 0){
								a[m][n-j][0] -= 1;
								attack++;
								arrow--;
							}
							if (a[m][n+j][1] == 'B' && attack == 0){
								a[m][n+j][0] -= 1;
								attack++;
								arrow--;
							}
							}	//end loop
								
							if (attack == 0){
								attack_m = 1;
							}
						}
					}
					break;	
			case 'e':
				if (p_hp < 3){
					printf("\tGain 1 Health: f (cost: 10 Fruit)\n");
				}
				printf("\tBuild a wall: w (cost: 5 Stone)\n\tBuild a door: d (cost: 10 Wood)\n\tRemove an object: r\n");
				printf("\tPlant a tree: t (cost: 8 Fruit)\n");
				if (tool == 0){
					printf("\tCraft Picaxe (Used to collect Stone): p (cost: 20 Wood)\n");
				}
				if (tool == PICAXE){
					printf("\tCraft Stone Picaxe (Increases Stone collection): p (cost: 20 Wood, 10 Stone)\n");
				}
				if (tool2 == 0){
					printf("\tCraft Axe (Increases Wood collection): a (cost: 20 Wood)\n");
				}
				if (tool2 == AXE){
					printf("\tCraft Stone Axe (Increases Wood collection): a (cost: 20 Wood, 10 Stone)\n");
				}
				if (weap == 0){
					printf("\tCraft Spear (Range: 2 spaces; Weapon Strength: 2): s (cost: 50 Wood, 10 Stone)\n");
				}
				if (weap1 == 0){
					printf("\tCraft Bow (Range: 8 spaces; Weapon Strength: 1): b (cost: 100 Wood, 20 Stone)\n");
				}
				if (weap1 == BOW){
					printf("\tCraft Arrow: b (cost: 10 Wood, 5 Stone)\n");
				}
				printf("What do you want to do?: ");
				scanf("%c", &i);
			//	getchar();
				switch (i){
				case 'f':
					if (F>=10 && p_hp < 3){
						p_hp++;
					}
					break;
				case 'w':
				case 'W':
					if (S >= 5){
						printf("\nWhich direction do you want to build a wall? (a w s d): "); 
						scanf("%c", &i);
					//	getchar();
						switch (i){
						case 'w':	
							if (a[m-1][n][1]=='.'){
							wall_up(a, &m, &n);
							S -= 5;
							xp += 10;
							}
							break;
						case 's':	
							if (a[m+1][n][1]=='.'){
							wall_down(a, &m, &n);
							S -= 5;
							xp += 10;
							}
							break;
						case 'a':	
							if (a[m][n-1][1]=='.'){
							wall_left(a, &m, &n);
							S -= 5;
							xp += 10;
							}
							break;
						case 'd':	
							if (a[m][n+1][1]=='.'){
							wall_right(a, &m, &n);
							S -= 5;
							xp += 10;
							}
							break;
						}
					}
					break;
				case 'd':
				case 'D':
					if (W >= 20){
						printf("\nWhich direction do you want to build a door? (a w s d): ");
						scanf("%c", &i);
					//	getchar();
						switch (i){
						case 'w':
							if (a[m-1][n][1]=='.'){
							door_up(a, &m, &n);
							W -= 20;
							xp += 10;
							}
							break;
						
						case 's':
							if (a[m+1][n][1]=='.'){
							door_down(a, &m, &n);
							W -= 20;
							xp += 10;
							}
							break;
						
						case 'a':
							if (a[m][n-1][1]=='.'){
							door_left(a, &m, &n);
							W -= 20;
							xp += 10;
							}
							break;
						
						case 'd':
							if (a[m][n+1][1]=='.'){
							door_right(a, &m, &n);
							W -= 20;
							xp += 10;
							}
							break;
						}
					}
				
				break;
				case 'r':
				case 'R':
					printf("\nWhich direction do you want to remove? (a w s d): ");
					scanf("%c", &i);
				//	getchar();
					switch (i){
						case 'w':	
							if (a[m-1][n][1]!='B'){
							a[m-1][n][1]='.';
							a[m-1][n][0]=0;
							xp += 10;
							}
							break;
						
						case 's':	
							if (a[m+1][n][1]!='B'){
							a[m+1][n][1]='.';
							a[m+1][n][0]=0;
							xp += 10;
							}
							break;
						
						case 'a':	
							if (a[m][n-1][1]!='B'){
							a[m][n-1][1]='.';
							a[m][n-1][0]=0;
							xp += 10;
							}
							break;
						
						case 'd':	
							if (a[m][n+1][1]!='B'){
							a[m][n+1][1]='.';
							a[m][n+1][0]=0;
							xp += 10;
							}
							break;
						}
					break;
				case 't':
				case 'T':
					if (F >= 8){
						printf("\nWhich direction do you want to plant a tree? (a w s d): "); //copy for building trees
						scanf("%c", &i);
					//	getchar();
						switch (i){
						case 'w':	
							if (a[m-1][n][1]=='.'){
							tree_up(a, &m, &n);
							F -= 8;
							xp += 10;
							}
							break;
						case 's':	
							if (a[m+1][n][1]=='.'){
							tree_down(a, &m, &n);
							F -= 8;
							xp += 10;
							}
							break;
						case 'a':	
							if (a[m][n-1][1]=='.'){
							tree_left(a, &m, &n);
							F -= 8;
							xp += 10;
							}
							break;
						case 'd':	
							if (a[m][n+1][1]=='.'){
							tree_right(a, &m, &n);
							F -= 8;
							xp += 10;
							}
							break;
						}
					}
					break;	
				case 'p':
					if (W>= 20 && tool == 0){
						tool = PICAXE;
						W -= 20;
						xp += 20;
					}
					if (W>= 20 && S>= 10 && tool == PICAXE){
						tool = S_PICAXE;
						W -= 20;
						S -= 10;
						xp += 50;
					}
					break;
				case 'a':
					if (W>=20 && tool2 == 0){
						tool2 = AXE;
						W -= 20;
						xp += 20;
						i = '2';
					}
					if (W>= 20 && S>=10 && tool2 == AXE && i != '2'){
						tool2 = S_AXE;
						W -= 20;
						S -=10;
						xp += 50;
					}
					break;
				case 'b':
					if (W>=100 && S>=20 && weap1 == 0) {
						weap1 = BOW;
						W -= 100;
						S -= 20;
						xp += 50;
						i = '2';
					}
					if(W>=10 && S>=5 && weap1 == BOW && i != '2'){
						arrow += 1;
						W -= 10;
						S -= 5;
						xp += 5;
					}				
					break;
				case 's':
					if (W>=50 && S>=10 && weap == 0){
						weap = SPEAR;
						W -= 50;
						S -= 10;
						xp += 25;
					}
					break;
				}  //end of case e switch statments
		}
		if (xp%100==0){
			d++;
			b_hp++;
		}
		bear(a, &o, &p, &m, &n, &c, &i, &d);
		if (xp > 250){
			bear(a, &o1, &p1, &m, &n, &c1, &i, &d);
		}
		if (xp > 550){
			bear(a, &o2, &p2, &m, &n, &c2, &i, &d);
		}
		if (xp > 850){
			bear(a, &o3, &p3, &m, &n, &c3, &i, &d);
		}
//		Remove World
		for (j=0; j<10; j++){
			printf("\n");
		}
		//	Print World (10x10 array)
		if (xp<50){
			printf("\tT stands for Tree. S stands for Stone.\n\tTry walking into one!\n\tB stands for Bear. If he catches you, Game Over!\n\t(1 will exit the program)\n");
		}
		if (F>=4 && xp<100){
			printf("\tUsing captial A W S D will allow you to move faster at the cost of 1 fruit!\n");
		}
		if ((S>=5 || W>=10)){
			printf("\tUse the e key to open the build menu.\n");
		}
		if (weap == SPEAR || weap1 == BOW){
			printf("\tUse the q key to attack. Make sure you are lined up horizontal\n or vertical for your attack to hit!\n");
		}
		if(S>=5 && xp<100){
			printf("\tYou can place a wall (W) above your character at the cost of 5 Stone!\n");
		}
		if (W>=10 && xp<100){
			printf("\tYou can place a door (D) above your character at the cost of 20 Wood!\n");
		}
		for (k=0; k<20; k++){
			printf("\t");
			for (j=0; j<20; j++){
				if (a[k][j][1]=='.'){
				printf("\033[0;33m"); // Yellow
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if ((a[k][j][1]=='T' && a[k][j][0]>10) || (a[k][j][1]=='D' && a[k][j][0]>30)){
				printf("\033[0;32m"); // Green
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if ((a[k][j][1]=='T' && a[k][j][0]<11) || (a[k][j][1]=='D' && a[k][j][0]<31)){
				printf("\033[0;36m"); // Cyan
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if ((a[k][j][1]=='S' && a[k][j][0]>10) || (a[k][j][1]=='W' && a[k][j][0]>30)){
				printf(" %c ", a[k][j][1]); // Black(white)
			}
			if ((a[k][j][1]=='S' && a[k][j][0]<11) || (a[k][j][1]=='W' && a[k][j][0]<31)){
				printf("\033[0;36m"); // Cyan
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[k][j][1]=='B'){
				printf("\033[0;31m"); // Red
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[k][j][1]=='@'){
				printf("\033[0;34m"); // Blue
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			if (a[k][j][1]=='_' || a[k][j][1]=='|'){
				printf("\033[0;35m"); // Purple
				printf(" %c ", a[k][j][1]);
				printf("\033[0m"); // Reset
			}
			}
			printf("\n");
		}
		if (tool == PICAXE){
			strcpy(tools, "Picaxe");
		}
		if (tool == S_PICAXE){
			strcpy(tools, "Stone Picaxe");
		}
		if (tool2 == AXE){
			strcpy(tools2, "Axe");
		}
		if (tool2 == S_AXE){
			strcpy(tools2, "Stone Axe");
		}
		printf("\tBag: (Wood: %d  Stone: %d  Fruit: %d)\t\tXP: %d\n", W, S, F, xp);
		printf("\t     (Tools:");
		if (tool == 0 && tool2 == 0){
			printf(" None");
		}
		if (tool > 0){
			printf(" %s", tools);
		}
		if (tool > 0 && tool2 > 0){
			printf(",");
		}
		if (tool2 > 0){
			printf(" %s", tools2);
		}
		if (tool > 0 && (weap > 0 || weap1 > 0)){
			printf(",");
		}
		if (weap > 0){
			printf(" Spear");
		}
		if (tool > 0 && weap > 0 && weap1 > 0){
			printf(",");
		}
		if (weap1 > 0){
			printf(" Bow, Arrow(s): %d", arrow);
		}
		printf(")\n");
		
		printf("\tPlayer HP: %d", p_hp);
		if (a[o][p][0] > 0){
			printf("\tBear #1 HP: %d", a[o][p][0]);
		}
		if (a[o1][p1][0] > 0 && xp > 299){
			printf("\tBear #2 HP: %d", a[o1][p1][0]);
		}
		if (a[o2][p2][0] > 0 && xp > 599){
			printf("\tBear #3 HP: %d", a[o2][p2][0]);
		}
		if (a[o3][p3][0] > 0 && xp > 899){
			printf("\tBear #4 HP: %d", a[o3][o3][0]);
		}
		printf("\n");
		if (ps == 1){
			printf("You need a Picaxe to collect Stone!\n");
		}
		if (attack_m == 1){
			printf("Attack missed!");
			attack_m = 0;
		}
		if (attack_m ==2){
			printf("Your quiver is empty!");
		}
	}

//		Print World

	high_score = 2230;
	score_2 = 1006;
	score_3 = 987;
	int score_4 = 530;

	if (xp >= high_score){
		printf("\n\n\t\tNEW HIGH SCORE!! \n\t\t    %d", xp);
	}
	
	printf("\nHigh Scores:\nBryce\t%d xp\nTy\t%d xp\nEmma\t%d xp\nMckenna\t%d xp", high_score, score_2, score_3, score_4); 
	
	return 0;
}


void move_up(int a[][21][5], int *m, int *n, int *w, int *s, int *f){
	int move;
	move = 0;
	if (a[*m-1][*n][1]=='T'){
		(*w)++;
		if (tool2 == AXE){
			(*w) += 2;
		}
		if (tool2 == S_AXE){
			(*w) += 4;
		}
		if(rand()%3==0){
			(*f)++;
		}
		(a[*m-1][*n][0])--;
		if (a[*m-1][*n][0] == 0){
			a[*m-1][*n][1] = '.';
			move++;
		}
	}
	if (a[*m-1][*n][1]=='S'){ 
	if (tool == PICAXE || tool == S_PICAXE){
		if (tool == PICAXE){
			(*s)++;
		}
		else {
			(*s) += 3;
		}
		(a[*m-1][*n][0])--;
		if (a[*m-1][*n][0] == 0){
			a[*m-1][*n][1] = '.';
			move++;
		}
	}
	else{
		ps = 1;
	}
	}
	if (move == 0 && a[*m-1][*n][1]!='S' && a[*m-1][*n][1]!='T' && a[*m-1][*n][1] != 'W' && a[*m-1][*n][1] != 'D' && *m>0 && a[*m-1][*n][1]!='B'){
	if(a[*m][*n][1] != 'B'){
		a[*m][*n][1]= '.';
		}
	a[*m][*n][0]= 0;
	a[*m-1][*n][1]='@';
	
	(*m)--;
	move++;
	}
	if (a[*m-1][*n][1]=='D' && a[*m-2][*n][1]== '.' && move == 0){
		a[*m][*n][1]= '.';
		a[*m][*n][0]= 0;
		a[*m-2][*n][1]='@';
		
		(*m) -= 2;
	}
}
void move_down(int a[][21][5], int *m, int *n, int *w, int *s, int *f){
	int move;
	move = 0;
	if (a[*m+1][*n][1]=='T'){
		(*w)++;
		if (tool2 == AXE){
			(*w) += 2;
		}
		if (tool2 == S_AXE){
			(*w) += 4;
		}
		if(rand()%3==0){
			(*f)++;
		}
		(a[*m+1][*n][0])--;
		if (a[*m+1][*n][0] == 0){
			a[*m+1][*n][1] = '.';
			move++;
		}
	}
	if (a[*m+1][*n][1]=='S'){ 
	if (tool == PICAXE || tool == S_PICAXE){
		if (tool == PICAXE){
			(*s)++;
		}
		else {
			(*s) += 3;
		}
		(a[*m+1][*n][0])--;
		if (a[*m+1][*n][0] == 0){
			a[*m+1][*n][1] = '.';
			move++;
		}
	}
	else{
		ps = 1;
	}
	}
	if (move == 0 && a[*m+1][*n][1]!='S' && a[*m+1][*n][1]!='T' && a[*m+1][*n][1] != 'W' && a[*m+1][*n][1] != 'D' && *m<19 && a[*m+1][*n][1]!='B'){
		if(a[*m][*n][1] != 'B'){
		a[*m][*n][1]= '.';
		}
		a[*m][*n][0]= 0;
		a[*m+1][*n][1]='@';
	
		(*m)++;
		move++;
	}
	if (a[*m+1][*n][1]=='D' && a[*m+2][*n][1]== '.' && move == 0){
		a[*m][*n][1]='.';
		a[*m][*n][0]= 0;
		a[*m+2][*n][1]= '@';
	
		(*m) += 2;
	}
}
void move_left(int a[][21][5], int *m, int *n, int *w, int *s, int *f){
	int move;
	move = 0;
	if (a[*m][*n-1][1]=='T'){
		(*w)++;
		if (tool2 == AXE){
			(*w) += 2;
		}
		if (tool2 == S_AXE){
			(*w) += 4;
		}
		if(rand()%3==0){
			(*f)++;
		}
		(a[*m][*n-1][0])--;
		if (a[*m][*n-1][0] == 0){
			a[*m][*n-1][1] = '.';
			move++;
		}
	}
	if (a[*m][*n-1][1]=='S'){
	if(tool == PICAXE || tool == S_PICAXE){
		if (tool == PICAXE){
			(*s)++;
		}
		else {
			(*s) += 3;
		}
		(a[*m][*n-1][0])--;
		if (a[*m][*n-1][0] == 0){
			a[*m][*n-1][1] = '.';
			move++;
		}
	}
	else{
		ps = 1;
	}
	}
	if (move == 0 && a[*m][*n-1][1]!='S' && a[*m][*n-1][1]!='T' && a[*m][*n-1][1] != 'W' && a[*m][*n-1][1] != 'D' && *n>0 && a[*m][*n-1][1]!='B'){
		if(a[*m][*n][1] != 'B'){
		a[*m][*n][1]= '.';
		}
		a[*m][*n][0]= 0;
		a[*m][*n-1][1]='@';
	
		(*n)--;
		move++;
	}
	if (a[*m][*n-1][1]=='D' && a[*m][*n-2][1]== '.' && move == 0){
		a[*m][*n][1]='.';
		a[*m][*n][0]= 0;
		a[*m][*n-2][1]= '@';
	
		(*n) -= 2;
	}
}
void move_right(int a[][21][5], int *m, int *n, int *w, int *s, int *f){
	int move;
	move = 0;
	if (a[*m][*n+1][1]=='T'){
		(*w)++;
		if (tool2 == AXE){
			(*w) += 2;
		}
		if (tool2 == S_AXE){
			(*w) += 4;
		}
		if(rand()%3==0){
			(*f)++;
		}
		(a[*m][*n+1][0])--;
		if (a[*m][*n+1][0] == 0){
			a[*m][*n+1][1] = '.';
			move++;
		}
	}
	if (a[*m][*n+1][1]=='S'){ 
	if (tool == PICAXE || tool == S_PICAXE){
		if (tool == PICAXE){
			(*s)++;
		}
		else {
			(*s) += 3;
		}
		(a[*m][*n+1][0])--;
		if (a[*m][*n+1][0] == 0){
			a[*m][*n+1][1] = '.';
			move++;
		}
	}
	else{
		ps = 1;
	}
	}
	if (move == 0 && a[*m][*n+1][1]!='S' && a[*m][*n+1][1]!='T' && a[*m][*n+1][1] != 'W' && a[*m][*n+1][1] != 'D' && *n<19 && a[*m][*n+1][1]!='B'){
		if(a[*m][*n][1] != 'B'){
		a[*m][*n][1]= '.';
		}
		a[*m][*n][0]= 0;
		a[*m][*n+1][1]='@';
	
		(*n)++;
		move++;
	}
	if (a[*m][*n+1][1]=='D' && a[*m][*n+2][1]== '.' && move == 0){
		a[*m][*n][1]='.';
		a[*m][*n][0]= 0;
		a[*m][*n+2][1]= '@';
	
		(*n) += 2;
	}
}

void wall_up(int a[][21][5], int *m, int *n){
	if (a[*m-1][*n][1]!='S' && a[*m-1][*n][1]!='T' && a[*m-1][*n][1] != 'W' && a[*m-1][*n][1] != 'D' && *m>0){
		a[*m-1][*n][1] = 'W';
		a[*m-1][*n][0] = 100;
	}
}
void wall_down(int a[][21][5], int *m, int *n){
	if (a[*m+1][*n][1]!='S' && a[*m+1][*n][1]!='T' && a[*m+1][*n][1] != 'W' && a[*m+1][*n][1] != 'D' && *m>0){
		a[*m+1][*n][1] = 'W';
		a[*m+1][*n][0] = 100;
	}
}
void wall_left(int a[][21][5], int *m, int *n){
	if (a[*m][*n-1][1]!='S' && a[*m][*n-1][1]!='T' && a[*m][*n-1][1] != 'W' && a[*m][*n-1][1] != 'D' && *m>0){
		a[*m][*n-1][1] = 'W';
		a[*m][*n-1][0] = 100;
	}
}
void wall_right(int a[][21][5], int *m, int *n){
	if (a[*m][*n+1][1]!='S' && a[*m][*n+1][1]!='T' && a[*m][*n+1][1] != 'W' && a[*m][*n+1][1] != 'D' && *m>0){
		a[*m][*n+1][1] = 'W';
		a[*m][*n+1][0] = 100;
	}
}

void door_up(int a[][21][5], int *m, int *n){
	if (a[*m-1][*n][1]!='S' && a[*m-1][*n][1]!='T' && a[*m-1][*n][1] != 'W' && a[*m-1][*n][1] != 'D' && *m>0){
		a[*m-1][*n][1] = 'D';
		a[*m-1][*n][0] = 100;
	}
}
void door_down(int a[][21][5], int *m, int *n){
	if (a[*m+1][*n][1]!='S' && a[*m+1][*n][1]!='T' && a[*m+1][*n][1] != 'W' && a[*m+1][*n][1] != 'D' && *m>0){
		a[*m+1][*n][1] = 'D';
		a[*m+1][*n][0] = 100;
	}
}
void door_left(int a[][21][5], int *m, int *n){
	if (a[*m][*n-1][1]!='S' && a[*m][*n-1][1]!='T' && a[*m][*n-1][1] != 'W' && a[*m][*n-1][1] != 'D' && *m>0){
		a[*m][*n-1][1] = 'D';
		a[*m][*n-1][0] = 100;
	}
}
void door_right(int a[][21][5], int *m, int *n){
	if (a[*m][*n+1][1]!='S' && a[*m][*n+1][1]!='T' && a[*m][*n+1][1] != 'W' && a[*m][*n+1][1] != 'D' && *m>0){
		a[*m][*n+1][1] = 'D';
		a[*m][*n+1][0] = 100;
	}
}
//Tree
void tree_up(int a[][21][5], int *m, int *n){
	if (a[*m-1][*n][1]!='S' && a[*m-1][*n][1]!='T' && a[*m-1][*n][1] != 'W' && a[*m-1][*n][1] != 'D' && *m>0){
		a[*m-1][*n][1] = 'T';
		a[*m-1][*n][0] = 30;
	}
}
void tree_down(int a[][21][5], int *m, int *n){
	if (a[*m+1][*n][1]!='S' && a[*m+1][*n][1]!='T' && a[*m+1][*n][1] != 'W' && a[*m+1][*n][1] != 'D' && *m>0){
		a[*m+1][*n][1] = 'T';
		a[*m+1][*n][0] = 30;
	}
}
void tree_left(int a[][21][5], int *m, int *n){
	if (a[*m][*n-1][1]!='S' && a[*m][*n-1][1]!='T' && a[*m][*n-1][1] != 'W' && a[*m][*n-1][1] != 'D' && *m>0){
		a[*m][*n-1][1] = 'T';
		a[*m][*n-1][0] = 30;
	}
}
void tree_right(int a[][21][5], int *m, int *n){
	if (a[*m][*n+1][1]!='S' && a[*m][*n+1][1]!='T' && a[*m][*n+1][1] != 'W' && a[*m][*n+1][1] != 'D' && *m>0){
		a[*m][*n+1][1] = 'T';
		a[*m][*n+1][0] = 30;
	}
}

void bear(int a[][21][5], int *o, int *p, int *m, int *n, int *c, int *i, int *d){  // Idea: make the bear smarter as the player gains more xp
	int hp;
	
	hp = a[*o][*p][0];
	if (a[*o][*p][0] <= 0 && a[*o][*p][1] != '.'){
		a[*o][*p][1] = '.';
		*o = 0;
		*p = 21;
		xp += 20;
	}
	if (a[*o][*p][1] == 'B'){
	int move, dv, dh; 
	dv = *m - *o;
	dh = *n - *p;
	move=0;
	if (dv == 0 && dh == 0){  //If the player doesn't move away
		p_hp--;
		if (p_hp == 0){
			game_over(a, i);
		}
		move++;
	}
	if (abs(dv)<=2 && abs(dh)<=2 && *d<8){
		*c=2;
	}
	if (abs(dv)<=1 && abs(dh)<=1){
		*c=2;
	}
	if (abs(dv)>=6 && abs(dh)>=6){
		*c=1;
	}
	if ((abs(dv)<=*d) && (abs(dh)<=*d) && rand() % *c==0){
		if (abs(dv) >= abs(dh)){
		if (dv<0 && move == 0 && a[*o-1][*p][1]!='S' && a[*o-1][*p][1]!='T' && a[*o-1][*p][1] != 'W' && a[*o-1][*p][1] != 'D' && a[*o-1][*p][1] != 'B'){
			//bear is below
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o-1][*p][1]='B';
			a[*o-1][*p][0]= hp;
			(*o)--;
			move++;
		}
		if (dv>0 && move == 0 && a[*o+1][*p][1]!='S' && a[*o+1][*p][1]!='T' && a[*o+1][*p][1] != 'W' && a[*o+1][*p][1] != 'D' && a[*o+1][*p][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o+1][*p][1]='B';
			a[*o+1][*p][0]= hp;
			(*o)++;
			move++;
		}
		}
		if (dh<0 && move == 0 && a[*o][*p-1][1]!='S' && a[*o][*p-1][1]!='T' && a[*o][*p-1][1] != 'W' && a[*o][*p-1][1] != 'D' && a[*o][*p-1][1] != 'B'){
			//bear is to the right
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o][*p-1][1]='B';
			a[*o][*p-1][0]= hp;
			(*p)--;
			move++;
		}
		if (dh>0 && move == 0 && a[*o][*p+1][1]!='S' && a[*o][*p+1][1]!='T' && a[*o][*p+1][1] != 'W' && a[*o][*p+1][1] != 'D' && a[*o][*p+1][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o][*p+1][1]='B';
			a[*o][*p+1][0]= hp;
			(*p)++;
			move++;
		}
		
		if (a[*o-1][*p][0] >= bear_attack && move == 0 && a[*o-1][*p][1] != 'B' && a[*o-1][*p][1] != '@'){
			a[*o-1][*p][0] -= bear_attack;
			move++;
			if (a[*o-1][*p][0] == 0){
				a[*o-1][*p][1] = '.';
			}
		}
		if (a[*o-1][*p][0] < bear_attack && a[*o-1][*p][0] > 0 && move == 0 && a[*o-1][*p][1] != 'B' && a[*o-1][*p][1] != '@'){
			a[*o-1][*p][0] = 0;
			move++;
			if (a[*o-1][*p][0] == 0){
				a[*o-1][*p][1] = '.';
			}
		}
		
		if (a[*o+1][*p][0] >= bear_attack && move == 0 && a[*o+1][*p][1] != 'B' && a[*o+1][*p][1] != '@'){
			a[*o+1][*p][0] -= bear_attack;
			move++;
			if (a[*o+1][*p][0] == 0){
				a[*o+1][*p][1] = '.';
			}
		}
		if (a[*o+1][*p][0] < bear_attack && a[*o+1][*p][0] > 0 && move == 0 && a[*o+1][*p][1] != 'B' && a[*o+1][*p][1] != '@'){
			a[*o+1][*p][0] = 0;
			move++;
			if (a[*o+1][*p][0] == 0){
				a[*o+1][*p][1] = '.';
			}
		}
		
		if (a[*o][*p-1][0] >= bear_attack && move == 0 && a[*o][*p-1][1] != 'B' && a[*o][*p-1][1] != '@'){
			a[*o][*p-1][0] -= bear_attack;
			move++;
			if (a[*o][*p-1][0] == 0){
				a[*o][*p-1][1] = '.';
			}
		}
		if (a[*o][*p-1][0] < bear_attack && a[*o][*p-1][0] > 0 && move == 0 && a[*o][*p-1][1] != 'B' && a[*o][*p-1][1] != '@'){
			a[*o][*p-1][0] = 0;
			move++;
			if (a[*o][*p-1][0] == 0){
				a[*o][*p-1][1] = '.';
			}
		}
		
		if (a[*o][*p+1][0] >= bear_attack && move == 0 && a[*o][*p+1][1] != 'B' && a[*o][*p+1][1] != '@'){
			a[*o][*p+1][0] -= bear_attack;
			move++;
			if (a[*o][*p+1][0] == 0){
				a[*o][*p+1][1] = '.';
			}
		}
		if (a[*o][*p+1][0] < bear_attack && a[*o][*p+1][0] > 0 && move == 0 && a[*o][*p+1][1] != 'B' && a[*o][*p+1][1] != '@'){
			a[*o][*p+1][0] = 0;
			move++;
			if (a[*o][*p+1][0] == 0){
				a[*o][*p+1][1] = '.';
			}
		}
		
		dv = *m - *o;
		dh = *n - *p;
		if (dv == 0 && dh == 0){ 
			p_hp--;
			if (p_hp == 0){
			game_over(a, i);
			}
		}
	}
	//Bear movement if not following player
	else{
	move = rand() % 4;
	if (move == 0){
		if (*o>0 && a[*o-1][*p][1]!='S' && a[*o-1][*p][1]!='T' && a[*o-1][*p][1] != 'W' && a[*o-1][*p][1] != 'D' && a[*o-1][*p][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o-1][*p][1]='B';
			a[*o-1][*p][0]= hp;
			(*o)--;
		}
	}
	if (move == 1){
		if (*o<19 && a[*o+1][*p][1]!='S' && a[*o+1][*p][1]!='T' && a[*o+1][*p][1] != 'W' && a[*o+1][*p][1] != 'D' && a[*o+1][*p][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o+1][*p][1]='B';
			a[*o+1][*p][0]= hp;
			(*o)++;
		}
	}
	if (move == 2){
		if (*p>0 && a[*o][*p-1][1]!='S' && a[*o][*p-1][1]!='T' && a[*o][*p-1][1] != 'W' && a[*o][*p-1][1] != 'D' && a[*o][*p-1][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o][*p-1][1]='B';
			a[*o][*p-1][0]= hp;
			(*p)--;
		}
	}
	if (move == 3){
		if (*p<19 && a[*o][*p+1][1]!='S' && a[*o][*p+1][1]!='T' && a[*o][*p+1][1] != 'W' && a[*o][*p+1][1] != 'D' && a[*o][*p+1][1] != 'B'){
			a[*o][*p][1]='.';
			a[*o][*p][0]= 0;
			a[*o][*p+1][1]='B';
			a[*o][*p+1][0]= hp;
			(*p)++;
		}
	}
	}
	}
	else{
		if (a[*o][*p][3] != 1){
		a[*o][*p][2] = 50;
		a[*o][*p][3] = 1;
		}
		a[*o][*p][2] -= 1;
		if (a[*o][*p][2] == 0){
			a[*o][*p][3] = 0;
			*o = 0;
			*p = 0;
			a[*o][*p][1] = 'B';
			a[*o][*p][0] = b_hp;
		}
	}
}

void game_over(int a[][21][5], int *i){
	//G
			a[3][3][1]='_';
			a[3][2][1]='_';
			a[4][1][1]='|';
			a[5][1][1]='|';
			a[6][1][1]='|';
			a[7][2][1]='_';
			a[7][3][1]='_';
			a[6][4][1]='|'; 
			a[5][3][1]='_';
			//A
			a[3][7][1]='_';
			a[3][6][1]='_';
			a[5][7][1]='_';
			a[5][6][1]='_';
			a[4][5][1]='|';
			a[5][5][1]='|';
			a[6][5][1]='|';
			a[7][5][1]='|';
			a[4][8][1]='|';
			a[5][8][1]='|';
			a[6][8][1]='|';
			a[7][8][1]='|';
			//M
			a[3][11][1]='_';
			a[3][13][1]='_';
			a[4][10][1]='|';
			a[5][10][1]='|';
			a[6][10][1]='|';
			a[7][10][1]='|';
			a[4][12][1]='|';
			a[5][12][1]='|';
			a[6][12][1]='|';
			a[7][12][1]='|';
			a[4][14][1]='|';
			a[5][14][1]='|';
			a[6][14][1]='|';
			a[7][14][1]='|';
			//E
			a[3][17][1]='_';
			a[3][18][1]='_';
			a[5][17][1]='_';
			a[5][18][1]='_';
			a[7][17][1]='_';
			a[7][18][1]='_';
			a[4][16][1]='|';
			a[5][16][1]='|';
			a[6][16][1]='|';
			a[7][16][1]='|';
			
			//O
			a[11][3][1]='_';
			a[11][2][1]='_';
			a[12][1][1]='|';
			a[13][1][1]='|';
			a[14][1][1]='|';
			a[15][2][1]='_';
			a[15][3][1]='_';
			a[14][4][1]='|'; 
			a[13][4][1]='|';
			a[12][4][1]='|';
			//V
			a[12][5][1]='|';
			a[13][5][1]='|';
			a[14][5][1]='|';
			a[15][6][1]='_';
			a[14][7][1]='|';
			a[13][8][1]='|';
			a[12][8][1]='|';
			//E
			a[11][12][1]='_';
			a[11][13][1]='_';
			a[13][12][1]='_';
			a[13][13][1]='_';
			a[15][12][1]='_';
			a[15][13][1]='_';
			a[12][11][1]='|';
			a[13][11][1]='|';
			a[14][11][1]='|';
			a[15][11][1]='|';
			//R
			a[11][17][1]='_';
			a[11][16][1]='_';
			a[13][17][1]='_';
			a[13][16][1]='_';
			a[12][15][1]='|';
			a[13][15][1]='|';
			a[14][15][1]='|';
			a[15][15][1]='|';
			a[12][18][1]='|';
			a[13][18][1]='|';
			a[14][17][1]='|';
			a[15][18][1]='|';
			*i='1';
}