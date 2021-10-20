void ghosts_move(unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, 
	unsigned char &, unsigned char &, bool [], bool [], bool [], bool []);
void ghosts_redraw(unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, 
	unsigned char &, unsigned char &, bool [], bool [], bool [], bool [], ALLEGRO_BITMAP *, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *);
bool possible(bool [], bool [], unsigned char);
void move(unsigned char &, unsigned char , bool [], short int &);
void looking(bool [], char []);
bool killed(unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, unsigned char &, 
	unsigned char &, unsigned char &, int, int);