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

bool chase(unsigned char &gx, unsigned char &gy, int px, int py, bool movement [], bool chasing[]){
	chasing[0] = chasing[1];

	if(pow(gx/15-px, 2) + pow(gy/15 - py, 2) <= 18 && (ENEMIES_MAP[gy/15][gx/15] == '0' || ENEMIES_MAP[gy/15][gx/15] == '2')){
		
		short int cont = 0;
		char char_chase_movs[] = {'L', 'R', 'U', 'D'};
		short int chase_movs[4] = {5, 5, 5, 5};

		if(px < gx && ENEMIES_MAP[gy][gx-1] != '1') chase_movs[0] = gx - px;
		else if(px > gx && ENEMIES_MAP[gy][gx+1] != '1') chase_movs[1] = px - gx;

		if(py < gy && ENEMIES_MAP[gy-1][gx] != '1') chase_movs[2] = gy - py;
		else if(py > gy && ENEMIES_MAP[gy+1][gx] != '1') chase_movs[3] = py - gy;

	    for (unsigned char i = 0; i < 4; i++){
	    	if(chase_movs[i] == 0) cont++;
		    for (unsigned char j = 0; j < 3-i; j++)
		        if (chase_movs[j] > chase_movs[j+1]){
		        	short int aux = chase_movs[j];
		        	chase_movs[j] = chase_movs[j+1];
		        	chase_movs[j+1] = chase_movs[j];

		        	char charAux = char_chase_movs[j];
		        	char_chase_movs[j] = char_chase_movs[j+1];
		        	char_chase_movs[j+1] = char_chase_movs[j];
		        }
		}

		if(cont == 4){	
			chasing[1] = false;
			return false;
		}
		
		switch(char_chase_movs[0]){
			case 'U':
				gy -= 15;
				movement[0] = true;
				movement[1] = false;
				movement[2] = false;
				movement[3] = false;				
				break;

			case 'L':
				gx += 15;
				movement[0] = false;
				movement[1] = true;
				movement[2] = false;
				movement[3] = false;
				break;

			case 'D':
				gy += 15;
				movement[0] = false;
				movement[1] = false;
				movement[2] = true;
				movement[3] = false;
				break;

			case 'R':
				gx -= 15;
				movement[0] = false;
				movement[1] = false;
				movement[2] = false;
				movement[3] = true;
				break;
			}


		chasing[1] = true;
		return true;	

	}


	else{
		chasing[1] = false;
		return false;
	}
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


void move(unsigned char &posx, unsigned char &posy, bool movs[], short int &started, bool chasing[]){
	short int x, y;
	x = posx/15;
	y = posy/15;

	if(ENEMIES_MAP[y][x] == '0' && started == 4 && !(chasing[1] == false && chasing[0] == true)){
		if(movs[0] == true) posy -= 15;
		else if(movs[1] == true) posx += 15;
		else if(movs[2] == true) posy += 15;
		else if(movs[3] == true) posx -= 15;
	}

	else{
		bool possible_movs[4] = {false, false, false, false};
		unsigned char randChoice;

		if(ENEMIES_MAP[y][x] == '2' || (chasing[1] == false && chasing[0] == true)){
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

void looking(bool movement[], char img[]){
	if(movement[0] == true) strcpy(img, "brocolis2.tga");
	else if(movement[1] == true) strcpy(img, "brocolis1.tga");
	else if(movement[2] == true) strcpy(img, "brocolis4.tga");
	else if(movement[3] == true) strcpy(img, "brocolis3.tga");
}

void ghosts_move(unsigned char &posx_1, unsigned char &posy_1, unsigned char &posx_2, unsigned char &posy_2, unsigned char &posx_3, unsigned char &posy_3, 
	unsigned char &posx_4, unsigned char &posy_4, bool movement_1[], bool movement_2[], bool movement_3[], bool movement_4[], short int &started, int px, int py,
	bool chasing_1[], bool chasing_2[], bool chasing_3[], bool chasing_4[]){

    if(!chase(posx_1, posy_1, px, py, movement_1, chasing_1)) move(posx_1, posy_1, movement_1, started, chasing_1);
    if(!chase(posx_2, posy_2, px, py, movement_2, chasing_2)) move(posx_2, posy_2, movement_2, started, chasing_2);
    if(!chase(posx_3, posy_3, px, py, movement_3, chasing_3)) move(posx_3, posy_3, movement_3, started, chasing_3);
    if(!chase(posx_4, posy_4, px, py, movement_4, chasing_4)) move(posx_4, posy_4, movement_4, started, chasing_4);
}

bool killed(unsigned char &posx_1, unsigned char &posy_1, unsigned char &posx_2, unsigned char &posy_2, unsigned char &posx_3, unsigned char &posy_3, 
	unsigned char &posx_4, unsigned char &posy_4, int x, int y){

	if(x == posx_1 && y == posy_1) return true;
	else if(x == posx_2 && y == posy_2) return true;
	else if(x == posx_3 && y == posy_3) return true;
	else if(x == posx_4 && y == posy_4) return true;

	return false;
}

