#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

unsigned char** map (){
	unsigned char **map, tipo[4], c;
	char comentario[200];
	short int largura, altura, i, j, valor;								

	ifstream arqentrada;					
	ofstream arqsaida;	
	
	arqentrada.open("map.pnm",ios::in); 
	arqentrada >> tipo;	
	arqentrada.get();	
	
	while((c = arqentrada.get()) == '#')	
		arqentrada.getline(comentario,200);	
	
	arqentrada.putback(c);
	arqentrada >> largura >> altura;
	arqentrada >> valor;
	
	map = (unsigned char**)malloc(altura*sizeof(unsigned char*));

	for(i=0; i < altura; i++)
		map[i] = (unsigned char*)malloc(largura*sizeof(unsigned char));


	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++) {
			arqentrada >> valor;
			map[i][j] = (unsigned char)valor;
		}
	}
	
	arqentrada.close();
	return map;
}