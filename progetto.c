// 891868 895662

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#ifdef __APPLE__

#define RED "\033[0;31m"		//fare per tutti i colori <3


#endif

#ifdef __WIN32	
		char* test = "Wow, you are using Windows";
		void matrix_printer(char **M, int *row, int *col){      //implementare bella stampa a colori da usare
			for(int i = 0; i < *row; i++){                   //stampa matrice iniziale
				for(int j = 0; j < *col; j++){      
					if(M[i][j] == '#'){
						printf("█");
					}else{
						printf("%c", M[i][j]);	
				}
					printf("\n");
			}   
				printf("\n");
		}

#endif

#ifdef __APPLE__

		void matrix_printer(char **M, int *row, int *col){
			for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){      
					if(M[i][j] == '#'){
						printf("█");
					}else{
						if(M[i][j] == '<' || M[i][j] == '>' || M[i][j] == 'v' || M[i][j] == '^')
							printf("\033[0;35m");
						if(M[i][j] == '$')
							printf("\033[0;33m");
						if(M[i][j] == '!')
							printf(RED);
						if(M[i][j] == 'T')
							printf("\033[0;36m");
						if(M[i][j] == 'o')
							printf("\033[0;34m");

						printf("%c", M[i][j]);
						printf("\033[0m");
					}
				}
					printf("\n");
			}   
				printf("\n");
		}
#endif

int vertical_global;	// vertical_global==1 movimento in basso, vertical_global==0 movimento verso l'alto
int orizzontal_global;	// orizzontal_global==1 movimento dx, orizzontal_global==0 movimento sx
int counter_trivella = 0;


void matrix_reader(char **M, int *row, int *col){       //legge una matrice da stdin riga per riga
        int i = 0;

        while(i < *row){
            scanf("%[^\n]%*c", &M[i][0]);
            i++;
        }



}


void labyrinth_initializer(char **M){
//inizializzava la matrice come il primo labirinto proposto dai prof, ora obsoleta

    int row = 10;
    int col = 19; 

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){       //inizializza tutti gli elementi a ' ' (spazio)
            M[i][j] = ' ';
        }
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){           //assegna '#' ai muri esterni del labirinto
            if(i == 0 || i == row - 1){         //sopra-sotto
                M[i][j] = '#';
            }
            if(j == 0 || j == col - 1){         //sinistra-destra
                M[i][j] = '#';
            }
        }
    }

    for(int i = 1; i <= row - 4; i++){          //crea primo separatore
        M[i][5] = '#';
    }


    for(int i = row - 1; i >= row - 7; i--){    //crea secondo separatore
        M[i][12] = '#';
    }


    M[5][18] = '_'; //arrivo
    M[1][0] = 'o';  //giocatore

    for(int i = 5; i < 9; i++){     //primo gruppo monete
        M[8][i] = '$';
    }

    for(int i = 1; i < 5; i++){     //secondo gruppo monete
        M[i][16] = '$';
    }

    M[3][9] = '!';                  //imprevisto

}



void labyrinth_player(char **M, int *row, int *col){
    char c = '\0';
    int g_col;
    int g_row;
    int victory_row;
    int victory_col;
    int points = 6500;
	int trapano = 0;
	int cnt;
    for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col; j++){          //controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == 'o'){
                g_col = j;
                g_row = i;
            }
            if(M[i][j] == '_'){
                victory_row = i;
                victory_col = j;
            }
        }
    }



    matrix_printer(M, row, col);
    


    while((c != 'q')){          //muove pedina

		#ifdef __APPLE__
		system("stty raw");
		#endif

        c = getchar();
        if(c == 'w' && g_row-1 >= 0){//muove pedina in su
            
            if(M[g_row-1][g_col] == '$')
                points+=3;
            if(M[g_row-1][g_col] == '!')
                points /= 2;
			if(M[g_row-1][g_col] == 'T')
				trapano += 3;

            if(M[g_row-1][g_col] == '^'){		//portale verso giù multiplo
				cnt = g_row;
                while(M[cnt-1][g_col] == '^'){
                    cnt--;
                }

				if(M[cnt-1][g_col] != '#' || (M[cnt-1][g_col] == '#' && trapano > 0)){

					if(M[cnt-1][g_col] == '#')
						trapano--;
					if(M[cnt-1][g_col] == '$')
						points+=3;
					if(M[cnt-1][g_col] == '!')
						points /= 2;
					if(M[cnt-1][g_col] == 'T')
						trapano += 3;

					M[g_row][g_col] = ' ';
					g_row = cnt;
					M[g_row-1][g_col] = 'o';
					g_row--;
				}


				if(M[g_row-1][g_col] == '$')
					points += 3;
				if(M[g_row-1][g_col] == '!')
					points /= 2;
				if(M[g_row-1][g_col] == 'T')
					trapano += 3;

            }else{

				if(M[g_row-1][g_col] == '#' && g_row-1 > 0 && trapano >= 1){ //trapano
					M[g_row-1][g_col] = 'o';
                    M[g_row][g_col] = ' ';
                    g_row--;
                    points--;
					trapano--;

				}else{
						//spazio o punti
					if(M[g_row-1][g_col] == '!' || M[g_row-1][g_col] == '$' || 
                		M[g_row-1][g_col] == ' ' || M[g_row-1][g_col] == '_' || M[g_row-1][g_col] == 'T'){

                    	M[g_row-1][g_col] = 'o';
                    	M[g_row][g_col] = ' ';
                    	g_row--;
                    	points--;
                }

				}
            } 
        }

        if(c == 's' && g_row+1 >= 0){//muove pedina in giù
            
            if(M[g_row+1][g_col] == '$')
                points+=3;
            if(M[g_row+1][g_col] == '!')
                points /= 2;
			if(M[g_row+1][g_col] == 'T')
				trapano += 3;

            if(M[g_row+1][g_col] == 'v'){		//portale verso giù multiplo
				cnt = g_row;
                while(M[cnt+1][g_col] == 'v'){
                    cnt++;
                }

				if(M[cnt+1][g_col] != '#' || (M[cnt+1][g_col] == '#' && trapano > 0)){

					if(M[cnt+1][g_col] == '#')
						trapano--;
					if(M[cnt+1][g_col] == '$')
						points+=3;
					if(M[cnt+1][g_col] == '!')
						points /= 2;
					if(M[cnt+1][g_col] == 'T')
						trapano += 3;

					M[g_row][g_col] = ' ';
					g_row = cnt;
					M[g_row+1][g_col] = 'o';
					g_row++;
				}


				if(M[g_row+1][g_col] == '$')
					points += 3;
				if(M[g_row+1][g_col] == '!')
					points /= 2;
				if(M[g_row+1][g_col] == 'T')
					trapano += 3;

            }else{

				if(M[g_row+1][g_col] == '#' && g_row+1 < *row-1 && trapano > 0){ //trapano
					M[g_row+1][g_col] = 'o';
                    M[g_row][g_col] = ' ';
                    g_row++;
                    points--;
					trapano--;
				
				}else{
							//spazio o punti
					if(M[g_row+1][g_col] == '!' || M[g_row+1][g_col] == '$' || 
                		M[g_row+1][g_col] == ' ' || M[g_row+1][g_col] == '_' || M[g_row+1][g_col] == 'T'){		//fine if

                    	M[g_row+1][g_col] = 'o';
                    	M[g_row][g_col] = ' ';
                    	g_row++;
                    	points--;
                	}
				}
            }
        }

        if(c == 'a' && g_col-1 >= 0){//muove pedina a sinistra
            
            if(M[g_row][g_col-1] == '$')
                points+=3;
            if(M[g_row][g_col-1] == '!')
                points /= 2;
			if(M[g_row][g_col-1] == 'T')
				trapano += 3;

            if(M[g_row][g_col-1] == '<'){		//portale verso sinistra multiplo
				cnt = g_col;
                while(M[g_row][cnt-1] == '<'){
                    cnt--;
                }

				if(M[g_row][cnt-1] != '#' || (M[g_row][cnt-1] == '#' && trapano > 0)){

					if(M[g_row][cnt-1] == '#')
						trapano--;
					if(M[g_row][cnt-1] == '$')
						points+=3;
					if(M[g_row][cnt-1] == '!')
						points /= 2;
					if(M[g_row][cnt-1] == 'T')
						trapano += 3;

					M[g_row][g_col] = ' ';
					g_col = cnt;
					M[g_row][g_col-1] = 'o';
					g_col--;
				}


				if(M[g_row][g_col-1] == '$')
					points += 3;
				if(M[g_row][g_col-1] == '!')
					points /= 2;
				if(M[g_row][g_col-1] == 'T')
					trapano += 3;

            }else{

				if(M[g_row][g_col-1] == '#' && g_col-1 > 0 && trapano >= 1){ //trapano

						M[g_row][g_col-1] = 'o';
						M[g_row][g_col] = ' ';
						g_col--;
						points--;
						trapano--;

				}else{
								//spazio o punti
					if(M[g_row][g_col-1] == '!' || M[g_row][g_col-1] == '$' || 
						M[g_row][g_col-1] == ' ' || M[g_row][g_col-1] == '_' || M[g_row][g_col-1] == 'T'){		//fine if

						M[g_row][g_col-1] = 'o';
						M[g_row][g_col] = ' ';
						g_col--;
						points--;
					}

				}

                
            }
        }

        if(c == 'd' && g_col+1 >= 0){//muove pedina a destra
            
            if(M[g_row][g_col+1] == '$')
                points+=3;
            if(M[g_row][g_col+1] == '!')
                points /= 2;
			if(M[g_row][g_col+1] == 'T')
				trapano += 3;

            if(M[g_row][g_col+1] == '>'){		//portale verso destra multiplo
				cnt = g_col;
                while(M[g_row][cnt+1] == '>'){
                    cnt++;
                }

				if(M[g_row][cnt+1] != '#' || (M[g_row][cnt+1] == '#' && trapano > 0)){

					if(M[g_row][cnt+1] == '#')
						trapano--;
					if(M[g_row][cnt+1] == '$')
						points+=3;
					if(M[g_row][cnt+1] == '!')
						points /= 2;
					if(M[g_row][cnt+1] == 'T')
						trapano += 3;

					M[g_row][g_col] = ' ';
					g_col = cnt;
					M[g_row][g_col+1] = 'o';
					g_col++;
				}


				if(M[g_row][g_col+1] == '$')
					points += 3;
				if(M[g_row][g_col+1] == '!')
					points /= 2;
				if(M[g_row][g_col+1] == 'T')
					trapano += 3;
	
                
            }else{

				if(M[g_row][g_col+1] == '#' && g_col+1 < *col-1 && trapano > 0){ //trapano

						M[g_row][g_col+1] = 'o';
						M[g_row][g_col] = ' ';
						g_col++;
						points--;
						trapano--;

				}else{
									//spazio o punti
					if(M[g_row][g_col+1] == '!' || M[g_row][g_col+1] == '$' || 
						M[g_row][g_col+1] == ' ' || M[g_row][g_col+1] == '_' || M[g_row][g_col+1] == 'T'){		//fine if

						M[g_row][g_col+1] = 'o';
						M[g_row][g_col] = ' ';
						g_col++;
						points--;
					}

				}
				
            }
        }
		#ifdef __APPLE__
        system("stty cooked");
		system("clear");
		#endif

        if(c != '\n'){              
			for(int i = 0; i < 30; i++){
				printf("\n");
			}
            matrix_printer(M, row, col);

            if(points < 0)
            	points = 0;

        	printf("Score: %d\n", points);

        	if(points < 0)
           		points = 0;

        	if(M[victory_row][victory_col] == 'o'){
            	printf("Vittoria!!!\n");
            
            break;
        	}
    	}	
    }
}

void labyrint_global_direction(char **M, int *row,int *col) { // serve per inizializzare le direzioni principali (dx/sx) (up/down)
	int g_col;
    int g_row;
	int victory_row;
    int victory_col;
	 for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col; j++){          //controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == 'o'){
                g_col = j;
                g_row = i;
            }
            if(M[i][j] == '_'){
                victory_row = i;
                victory_col = j;
            }
        }
	}
	if(g_row <= victory_row){
		vertical_global=1; // down movimento preferito
	}else{
		vertical_global=0; // up movimento preferito
	}
	if(g_col <= victory_col){
		orizzontal_global=1; // movimento preferito a dx
	}else{
		orizzontal_global=0; //movimento preferito a sx
	}
	
}
void labyrint_analysis( char **M, int *row, int *col){ 
//iniziallizzo le variabili che mi serviranno per tenere tracia delle 
//coordinate dell'inizio e della fine del labirinto
	int g_col;
    int g_row;
	int x=0; // variabile che revirà per selezionare il case dello switch;
	int finish_check = 0;		//inserito perchè altrimenti il ciclo di controllo del '_', 
								//se non c'era l'arrivo nella prima cella, faceva return
    int victory_row;
    int victory_col;
	int up_move;
	int down_move;
	int right_move;
	int left_move;
    for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col; j++){          //controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == 'o'){
                g_col = j;
                g_row = i;
				break;
            }
            
        }
	}
	for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col && finish_check == 0; j++){          //controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == '_'){
                victory_row = i;
                victory_col = j;			/* inserire questo check dopo ogni chiamata di analysis */
				finish_check = 1;
				break;
			}else{
				finish_check = 0;
			}
        }
	}
	if(finish_check == 0){
		return;
	}
    
	
    if (g_col==0){   // uscita del giocatore dal bordo
        printf("%c",'E');
        M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		labyrint_analysis( M, row, col);
		return;
	}else{
		if (g_col== *col-1){
			printf("%c",'O');
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			labyrint_analysis(M, row, col);
			return;
		}else{
			if (g_row==0){
				printf("%c",'S');
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				labyrint_analysis( M, row, col);
				return;
			}else{
				if(g_row== *row-1){
					printf("%c",'N');
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					labyrint_analysis( M, row, col);
					return;
				}
			}
		}
        
	}
		
	if( M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == 'T'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '$' o 'T'
		if (M[g_row][g_col+1] == 'T'){
			counter_trivella = counter_trivella + 3;
		}
		printf("%c", 'E');
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		labyrint_analysis(M, row, col);
		return;
	}else{
		if(M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == 'T'){
			if (M[g_row][g_col+1] == 'T'){
				counter_trivella = counter_trivella + 3;
			}
			printf("%c", 'O');
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			labyrint_analysis(M, row, col);
			return;
		} else{
			if(M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == 'T'){
				if (M[g_row][g_col+1] == 'T'){
					counter_trivella = counter_trivella + 3;
				}
				printf("%c", 'S');
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				labyrint_analysis(M, row, col);
				return;
			}else{
				if(M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == 'T'){
					if (M[g_row][g_col+1] == 'T'){
						counter_trivella = counter_trivella + 3;
					}
					printf("%c", 'N');
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					labyrint_analysis(M, row, col);
					return;
				}
			}
		}
        
	}
	// controllo quali movimenti sono impossibilitati dalle pareti. QUI ANDRA' MESSA LA CONDIZIONE DELLA TRIVELLA
		if (M[g_row][g_col+1] == '#'  &&  counter_trivella  == 0){
			right_move = 0;
		}else{
			right_move = 1;
		}
		if (M[g_row][g_col-1] == '#'  &&  counter_trivella == 0){
			left_move = 0;
		}else{
			left_move = 1;
		}
		if (M[g_row+1][g_col] == '#'  &&  counter_trivella == 0){
			down_move = 0;
		}else{
			down_move = 1;
		}
		if (M[g_row-1][g_col] == '#'  &&  counter_trivella == 0){
			up_move = 0;
		}else{
			up_move = 1;
		}
		// lo sburooooooooooooooooooooooooo controlla se nelle vicinanze c'è l'arrivo
		if( M[g_row][g_col+1] == '_'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '_'
		printf("%c", 'E');
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		labyrint_analysis(M, row, col);
		return;
	}else{
		if(M[g_row][g_col-1] == '_'){
			printf("%c", 'O');
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			labyrint_analysis(M, row, col);
			return;
		} else{
			if(M[g_row+1][g_col] == '_'){
				printf("%c", 'S');
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				labyrint_analysis(M, row, col);
				return;
			}else{
				if(M[g_row-1][g_col] == '_'){
					printf("%c", 'N');
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					labyrint_analysis(M, row, col);
					return;
				}
			}
		}
        
	}
	// se la pedina finisce in un anglo cecocambia direzione preferita	
	if (orizzontal_global == 1 && vertical_global == 1  && right_move==0 && down_move==0){
		orizzontal_global = 0;
	}else{	
		if(orizzontal_global == 1 && vertical_global == 0  && right_move == 0  &&  up_move == 0){
			orizzontal_global = 0;
		}else{ 
			if(orizzontal_global == 0  &&  vertical_global == 1  && left_move == 0 && down_move == 0){ 
				orizzontal_global = 1;
			}else{ 
				if (orizzontal_global == 0 && vertical_global == 0 && left_move == 0 && up_move == 0){
					orizzontal_global = 1;
				}
			}
		}
	}
		
	if ( abs(g_row - victory_row)>= abs(g_col - victory_col)){		// associazione del valore di x per lo switch
		if(g_row < victory_row){
			x=1;
		}
		if(g_row > victory_row){
			x=2;
		}
		if(g_row == victory_row && g_col < victory_col){
			x=3;
		}
		if(g_row == victory_row && g_col > victory_col)
			x=4;
	}else{ 
		if(g_col < victory_col){
			x=3;
		}
		if(g_col > victory_col){
			x=4;
		}
	}
	 /*
		vertical_global=1; // down movimento preferito
	
		vertical_global=0; // up movimento preferito
	
		orizzontal_global=1; // movimento preferito a dx
	
		orizzontal_global=0; //movimento preferito a sx
	*/
    

	switch (x) { //casi labirinto
        
		case  1: switch(down_move){
					case 1: 	printf("%c", 'S');
								if(M[g_row+1][g_col] == '#'){
									counter_trivella--;
								}
								M[g_row+1][g_col] = 'o';
								M[g_row][g_col] = ' ';
								labyrint_analysis(M, row, col);
								return;
					case 0: 	if (orizzontal_global == 1){
									x=3;
								}else{
									x=4;
								}
								switch (x){
											case 3: 	printf("%c", 'E');
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;

											case 4:	 	printf("%c", 'O');
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;                                            
								}
		}                        
					
		case 2: switch(up_move){
					case 1: 	printf("%c", 'N');
								if(M[g_row-1][g_col] == '#'){
									counter_trivella--;
								}
								M[g_row-1][g_col] = 'o';
								M[g_row][g_col] = ' ';
								labyrint_analysis(M, row, col);
								return;
					case 0:		if(orizzontal_global == 1 && right_move == 1){
									x=3;
								}else{ 
									x=4;
								}    
                                switch (x) {
											case 3: 	printf("%c", 'E');
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;
						
											case 4:	 	printf("%c", 'O');
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;

                                            
									}					
					}	
		case 3: switch(right_move){
                    case 1: 	printf("%c", 'E');
								if(M[g_row][g_col+1] == '#'){
									counter_trivella--;
								}
								M[g_row][g_col+1] = 'o';
								M[g_row][g_col] = ' ';
								labyrint_analysis(M, row, col);
								return;
						
                    case 0: 	if(vertical_global == 1 ){
                                    x=1;
                                }else{
                                    x=2;
                                }
                    
                                switch (x) { 
											case  1: 	printf("%c", 'S');
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;
							
											case 2:	printf("%c", 'N');
													M[g_row-1][g_col] = 'o';
													M[g_row][g_col] = ' ';
													labyrint_analysis(M, row, col);
													return;
                                            
								}
				}
        case 4: switch(left_move){
                    case 1:  	printf("%c", 'O');
								if(M[g_row][g_col-1] == '#'){
									counter_trivella--;
								}
								M[g_row][g_col-1] = 'o';
								M[g_row][g_col] = ' ';
								labyrint_analysis(M, row, col);
								return;
								
                    case 0: if(vertical_global == 1){
                                    x=1;         
                                }else{
                                    x=2;
                                }
                                
                                switch (x) {


											case  1:	printf("%c", 'S');
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;
														
							
											case 2:		printf("%c", 'N');
														M[g_row-1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														labyrint_analysis(M, row, col);
														return;
														                       
								}
					}
    }
} 



int main(int argc, char * argv[]){

	int row = 0;
	int col = 0;

	scanf("%d\n%d\n", &col, &row);
    
    char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
    for(int i = 0; i < col; i++){
        M[i] = (char*)malloc(col * sizeof(char));
    }


    if(argc == 2 && strcmp(argv[1], "--challenge") == 0){           //--challenge branch (IA)

        matrix_reader(M, &row, &col);  
		labyrint_global_direction(M, &row, &col);
        labyrint_analysis(M, &row, &col);             //IA
			
        return 0;

    }else{

        matrix_reader(M, &row, &col);                 //legge un labirinto da input terminale
        labyrinth_player(M, &row, &col);              //modifica la matrice facendo muovere il giocatore
        return 0;
    }
	free(M);
	return 0;
	
}
