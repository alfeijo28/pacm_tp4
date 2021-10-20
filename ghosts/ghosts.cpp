#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

unsigned char ENEMIES_MAP[17][17] ={
	"1111111111111111",
	"1200002112000021",
	"1011112002111101",
	"1011110110111101",
	"1200002112000021",
	"1011110110111101",
	"1012022002202101",
	"1010103553010101",
	"1010103333010101",
	"1010100000010101",
	"1010101111010101",
	"1202020020202021",
	"1011101100011101",
	"1202101221012021",
	"1010100011010101",
	"1202020200202021",
	"1111111111111111"
};

void looking(bool movement[], char img[]){
	if(movement[0] == true) strcpy(img, "brocolis2.tga");
	else if(movement[1] == true) strcpy(img, "brocolis1.tga");
	else if(movement[2] == true) strcpy(img, "brocolis4.tga");
	else if(movement[3] == true) strcpy(img, "brocolis3.tga");
}

void ghosts_move(unsigned char &posx_1, unsigned char &posy_1, unsigned char &posx_2, unsigned char &posy_2, unsigned char &posx_3, unsigned char &posy_3, 
	unsigned char &posx_4, unsigned char &posy_4, bool movement_1[], bool movement_2[], bool movement_3[], bool movement_4[]){

	srand (time(NULL));

    move(posx_1, posy_1, movement_1);
    move(posx_2, posy_2, movement_2);
    move(posx_3, posy_3, movement_3);
    move(posx_4, posy_4, movement_4);
}

void ghosts_redraw(unsigned char &posx_1, unsigned char &posy_1, unsigned char &posx_2, unsigned char &posy_2, unsigned char &posx_3, unsigned char &posy_3, 
	unsigned char &posx_4, unsigned char &posy_4, bool movement_1[], bool movement_2[], bool movement_3[], bool movement_4[], ALLEGRO_BITMAP *ghost1, 
	ALLEGRO_BITMAP *ghost2, ALLEGRO_BITMAP *ghost3, ALLEGRO_BITMAP *ghost4){

	char img[] = "brocolis1.tga";

    looking(movement_1, img);
    ghost1 = al_load_bitmap(img);
    looking(movement_2, img);
    ghost2 = al_load_bitmap(img);
    looking(movement_3, img);
    ghost3 = al_load_bitmap(img);    
    looking(movement_4, img);
    ghost4 = al_load_bitmap(img);

	al_draw_bitmap(ghost1, (int)posx_1, (int)posy_1,0);
	al_draw_bitmap(ghost2, (int)posx_2, (int)posy_2,0);
	al_draw_bitmap(ghost3, (int)posx_3, (int)posy_3,0);
	al_draw_bitmap(ghost4, (int)posx_4, (int)posy_4,0);

}

bool killed(unsigned char &posx_1, unsigned char &posy_1, unsigned char &posx_2, unsigned char &posy_2, unsigned char &posx_3, unsigned char &posy_3, 
	unsigned char &posx_4, unsigned char &posy_4, int x, int y){

	if(x == posx_1 && y == posy_1) return true;
	else if(x == posx_2 && y == posy_2) return true;
	else if(x == posx_3 && y == posy_3) return true;
	else if(x == posx_4 && y == posy_4) return true;

	return false;
}

bool possible(bool movs[], bool intention[], unsigned char n){
	unsigned char oposite;

	switch(n){
		case 0:
			oposite = 2;
			break;
		case 1:
			oposite = 3;
			break;
		case 2: 
			oposite = 0;
			break;
		case 3:
			oposite = 1;
			break;
	}

	if(movs[(short int)oposite] == intention[(short int)n]) return false;

	return true;
}

void move(unsigned char &posx, unsigned char &posy, bool movs[], short int &started){
	short int x, y;
	x = posx/15;
	y = posy/15;

	if(ENEMIES_MAP[y][x] == '0' && started == 4){
		if(movs[0] == true) posy -= 15;
		else if(movs[1] == true) posx += 15;
		else if(movs[2] == true) posy += 15;
		else if(movs[3] == true) posx -= 15;
	}

	else{
		bool possible_movs[4] = {false, false, false, false};
		unsigned char randChoice;

		if(ENEMIES_MAP[y][x] == '2'){
				if(ENEMIES_MAP[y-1][x] == '0' || ENEMIES_MAP[y-1][x] == '2')
					possible_movs[0] = true;

				if(ENEMIES_MAP[y][x+1] == '0' || ENEMIES_MAP[y][x+1] == '2')
					possible_movs[1] = true;

				if(ENEMIES_MAP[y+1][x] == '0' || ENEMIES_MAP[y+1][x] == '2')
					possible_movs[2] = true;

				if(ENEMIES_MAP[y][x-1] == '0' || ENEMIES_MAP[y][x-1] == '2')
					possible_movs[3] = true;


			do{
				randChoice = (unsigned char)rand()%4;
			}while(possible_movs[(short int)randChoice] == false || !possible(movs, possible_movs, randChoice));

			switch(randChoice){
				case 0:
					posy -= 15;
					movs[0] = true;
					movs[1] = false;
					movs[2] = false;
					movs[3] = false;				
					break;
				case 1:
					posx += 15;
					movs[0] = false;
					movs[1] = true;
					movs[2] = false;
					movs[3] = false;
					break;
				case 2:
					posy += 15;
					movs[0] = false;
					movs[1] = false;
					movs[2] = true;
					movs[3] = false;
					break;
				case 3:
					posx -= 15;
					movs[0] = false;
					movs[1] = false;
					movs[2] = false;
					movs[3] = true;
					break;
				}	
		}

		else if (ENEMIES_MAP[y][x] == '3'){
			if(ENEMIES_MAP[y][x+1] == '5')
				posx += 15;
			else if(ENEMIES_MAP[y][x-1] == '5')
				posx -= 15;
		}

		else if(ENEMIES_MAP[y][x] == '5') posy -= 15;
		else if(x == 8 && y == 6){
			posx += 15;
			started++;
		}
		else if(x == 7 && y == 6){
			posx -= 15;
			started++;
		}
	}
}