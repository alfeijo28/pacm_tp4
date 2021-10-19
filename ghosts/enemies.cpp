#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

const float FPS = 6;
const int SCREEN_W = 240;
const int SCREEN_H = 255;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

ALLEGRO_BITMAP *map_bmp  = NULL;
ALLEGRO_BITMAP *ghost1   = NULL;
ALLEGRO_BITMAP *ghost2   = NULL;
ALLEGRO_BITMAP *ghost3   = NULL;
ALLEGRO_BITMAP *ghost4   = NULL;

unsigned char posy_1 = 105;
unsigned char posx_1 = 90;
bool movement_1[] = {false, false, false, false};

unsigned char posy_2 = 105;
unsigned char posx_2 = 105;
bool movement_2[] = {false, false, false, false};

unsigned char posy_3 = 105;
unsigned char posx_3 = 120;
bool movement_3[] = {false, false, false, false};

unsigned char posy_4 = 105;
unsigned char posx_4 = 135;
bool movement_4[] = {false, false, false, false};

bool key[4] = { false, false, false, false};
bool redraw = true;
bool sair = false;

short int started = 0;

int inicializa();
void move(unsigned char &, unsigned char &, bool[]);
void looking(bool [], char img[]);

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

int main(){
	char img[] = "brocolis1.tga";
	srand (time(NULL));
    if(!inicializa()) return -1;

    while(!sair){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
        	cout << "Hello World" << endl;
        	move(posx_1, posy_1, movement_1);
        	move(posx_2, posy_2, movement_2);
            move(posx_3, posy_3, movement_3);
        	move(posx_4, posy_4, movement_4);

        	redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
    
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

        	looking(movement_1, img);
        	looking(movement_2, img);
        	looking(movement_3, img);
        	looking(movement_4, img);

        	ghost1 = al_load_bitmap(img);
        	ghost2 = al_load_bitmap(img);
        	ghost3 = al_load_bitmap(img);
        	ghost4 = al_load_bitmap(img);


            al_clear_to_color(al_map_rgb(0,0,0));

            al_draw_bitmap(map_bmp,0,0,0);

		    al_draw_bitmap(ghost1, (int)posx_1, (int)posy_1,0);
		    al_draw_bitmap(ghost2, (int)posx_2, (int)posy_2,0);
		    al_draw_bitmap(ghost3, (int)posx_3, (int)posy_3,0);
		    al_draw_bitmap(ghost4, (int)posx_4, (int)posy_4,0);

            al_flip_display();
        }
    }

    al_destroy_bitmap(map_bmp);
    al_destroy_bitmap(ghost1);
    al_destroy_bitmap(ghost2);
    al_destroy_bitmap(ghost3);
    al_destroy_bitmap(ghost4);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

void move(unsigned char &posx, unsigned char &posy, bool possible_movs[]){
	short int x, y;
	x = posx/15;
	y = posy/15;

	cout << x << " " << y << ": " << ENEMIES_MAP[y][x] << endl;

	if(ENEMIES_MAP[y][x] == '0' && started == 4){
		if(possible_movs[0] == true) posy -= 15;
		else if(possible_movs[1] == true) posx += 15;
		else if(possible_movs[2] == true) posy += 15;
		else if(possible_movs[3] == true) posx -= 15;
	}

	else{
		unsigned char randChoice;
		possible_movs[0] = false;
		possible_movs[1] = false;
		possible_movs[2] = false;
		possible_movs[3] = false;

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
		}while(possible_movs[(int)randChoice] == false);

		switch(randChoice){
			case 0:
				posy -= 15;
				possible_movs[0] = true;
				possible_movs[1] = false;
				possible_movs[2] = false;
				possible_movs[3] = false;				
				break;
			case 1:
				posx += 15;
				possible_movs[0] = false;
				possible_movs[1] = true;
				possible_movs[2] = false;
				possible_movs[3] = false;
				break;
			case 2:
				posy += 15;
				possible_movs[0] = false;
				possible_movs[1] = false;
				possible_movs[2] = true;
				possible_movs[3] = false;
				break;
			case 3:
				posx -= 15;
				possible_movs[0] = false;
				possible_movs[1] = false;
				possible_movs[2] = false;
				possible_movs[3] = true;
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

int inicializa() {

    if(!al_init()){
        cout << "Falha ao carregar Allegro" << endl;
        return 0;
    }

    if(!al_install_keyboard()){
        cout << "Falha ao inicializar o teclado" << endl;
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer){
        cout << "Falha ao inicializar o temporizador" << endl;
        return 0;
    }

    if(!al_init_image_addon()) {
        cout <<"Falha ao iniciar al_init_image_addon!" << endl;
        return 0;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display){
        cout << "Falha ao inicializar a tela" << endl;
        al_destroy_timer(timer);
        return 0;
    }

    map_bmp = al_load_bitmap("map.bmp");
    if(!map_bmp) {
        cout << "Falha ao carregar o mapa!" << endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(map_bmp,0,0,0);

    ghost1 = al_load_bitmap("brocolis2.tga");
    ghost2 = al_load_bitmap("brocolis2.tga");
    ghost3 = al_load_bitmap("brocolis2.tga");
    ghost4 = al_load_bitmap("brocolis2.tga");
    if(!ghost1 || !ghost2 || !ghost3 || !ghost4){
        cout << "Falha ao carregar o fantasma!" << endl;
        al_destroy_display(display);
        return 0;
    }
	al_draw_bitmap(ghost1, posx_1, posy_1,0);
	al_draw_bitmap(ghost2, posx_2, posy_2,0);
	al_draw_bitmap(ghost3, posx_3, posy_3,0);
	al_draw_bitmap(ghost4, posx_4, posy_4,0);

    event_queue = al_create_event_queue();
    if(!event_queue){
        cout << "Falha ao criar a fila de eventos" << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return 0;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

    return 1;
}

