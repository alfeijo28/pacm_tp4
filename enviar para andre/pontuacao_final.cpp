// Verifica na posição atual do pacman se há um doce/bonus 
	void comer (char mapa[17][17], int eixox, int eixoy, bool &bonus, int &cont, int &timer){
		if(mapa[eixoy][eixox] == '0'){        // '0' representa uma fruta 
			mapa[eixoy][eixox] = '3';		 // retira doce da posição 
			cont++;							//  contabiliza pontuacao do jogo
		}
		else if(mapa[eixoy][eixox] == '2'){   // Verifica se há um bonus 
			mapa[eixoy][eixox] = '3';		 // retira doce da posição 
			cont++;							//  contabiliza pontuacao do jogo
			bonus = true;					 // atualiza o estado da variavel bonus 
			timer = 0;						// reinicia a contagem de tempo 
		}

	}




