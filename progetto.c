// 891868 895662

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int vertical_global;	// vertical_global==1 movimento in basso, vertical_global==0 movimento verso l'alto
int orizzontal_global;	// orizzontal_global==1 movimento dx, orizzontal_global==0 movimento sx

void matrix_reader(char **M, int *row, int *col){       //legge una matrice da stdin riga per riga
        int i = 0;

        while(i < *row){
            scanf("%[^\n]%*c", &M[i][0]);
            i++;
        }



}



void matrix_printer(char **M, int *row, int *col){      //implementare bella stampa a colori da usare
    for(int i = 0; i < *row; i++){                   //stampa matrice iniziale
        for(int j = 0; j < *col; j++){      
            if(M[i][j] == 'o'){
               // printf("\033[0;36m");
                printf("%c", M[i][j]);
               // printf("\033[0m");
            }else{
                if(M[i][j] == '^' || M[i][j] == '<' || M[i][j] == '>' || M[i][j] == 'v'){
                   // printf("\033[0;35m");
                    printf("%c", M[i][j]);
                   // printf("\033[0m");   
                }else{
                    printf("%c", M[i][j]);
                }
            }
        }
            printf("\n");
    }   
        printf("\n");
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
    int points = 112;
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

        c = getchar();
        int cnt = 0;
        if(c == 'w' && M[g_row-1][g_col] != '#' && g_row-1 >= 0){//fine istruzione if muove pedina in su
            
            if(M[g_row-1][g_col] == '$')
                points+=3;
            if(M[g_row-1][g_col] == '!')
                points /= 2;

            if(M[g_row-1][g_col] == '^'){ //portale in alto
                M[g_row][g_col] = ' ';
                while(M[g_row-1][g_col] == '^'){
                    g_row--;
                }
                
                M[g_row][g_col] = '^';
                M[g_row-1][g_col] = 'o';
                g_row--;

            }else{
                if(M[g_row-1][g_col] == '!' || M[g_row-1][g_col] == '$' || 
                M[g_row-1][g_col] == ' ' || M[g_row-1][g_col] == '_'){//fine if
                    M[g_row-1][g_col] = 'o';
                    M[g_row][g_col] = ' ';
                    g_row--;
                    points--;
                }
            }
		
            
        }

        if(c == 's' && M[g_row+1][g_col] != '#' && g_row+1 >= 0){//fine istruzione if muove pedina in giù
            
            if(M[g_row+1][g_col] == '$')
                points+=3;
            if(M[g_row+1][g_col] == '!')
                points /= 2;

            if(M[g_row+1][g_col] == 'v'){ //portale in basso
                M[g_row][g_col] = ' ';
                while(M[g_row+1][g_col] == 'v'){
                    g_row++;
                }
                
                M[g_row][g_col] = 'v';
                M[g_row+1][g_col] = 'o';
                g_row++;

            }else{
                if(M[g_row+1][g_col] == '!' || M[g_row+1][g_col] == '$' || 
                M[g_row+1][g_col] == ' ' || M[g_row+1][g_col] == '_'){//fine if
                    M[g_row+1][g_col] = 'o';
                    M[g_row][g_col] = ' ';
                    g_row++;
                    points--;
                }
            }
        }

        if(c == 'a' && M[g_row][g_col-1] != '#' && g_col-1 >= 0){//fine istruzione if muove pedina a sinistra
            
            if(M[g_row][g_col-1] == '$')
                points+=3;
            if(M[g_row][g_col-1] == '!')
                points /= 2;

            if(M[g_row][g_col-1] == '<'){ 		//portale verso sinistra
                M[g_row][g_col] = ' ';
                while(M[g_row][g_col-1] == '<'){
                    g_col--;
                }
                
                M[g_row][g_col] = '<';
                M[g_row][g_col-1] = 'o';
                g_col--;

            }else{
                if(M[g_row][g_col-1] == '!' || M[g_row][g_col-1] == '$' || 
                M[g_row][g_col-1] == ' ' || M[g_row][g_col-1] == '_'){//fine if
                    M[g_row][g_col-1] = 'o';
                    M[g_row][g_col] = ' ';
                    g_col--;
                    points--;
                }
            }
        }

        if(c == 'd' && M[g_row][g_col+1] != '#' && g_col+1 >= 0){//fine istruzione if muove pedina a destra
            
            if(M[g_row][g_col+1] == '$')
                points+=3;
            if(M[g_row][g_col+1] == '!')
                points /= 2;

            if(M[g_row][g_col+1] == '>'){		//portale verso destra
                M[g_row][g_col] = ' ';
                while(M[g_row][g_col+1] == '>'){
                    g_col++;
                }
                
                M[g_row][g_col] = '>';
                M[g_row][g_col+1] = 'o';
                g_col++;

            }else{
                if(M[g_row][g_col+1] == '!' || M[g_row][g_col+1] == '$' || 
                M[g_row][g_col+1] == ' ' || M[g_row][g_col+1] == '_'){//fine if
                    M[g_row][g_col+1] = 'o';
                    M[g_row][g_col] = ' ';
                    g_col++;
                    points--;
                }
            }
        }

        
        
        if(c != '\n'){              

            matrix_printer(M, row, col);


            if(points < 0)
                points = 0;


            if(points > 100)
                printf("Score: 100\n");
            else
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
	int counter_trivella=0;
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
		if (M[g_row][g_col+1] == '#'  &&  counter_trivella==0){
			right_move = 0;
		}else{
			right_move=1;
		}
		if (M[g_row][g_col-1] == '#'  &&  counter_trivella==0){
			left_move = 0;
		}else{
			left_move=1;
		}
		if (M[g_row+1][g_col] == '#'  &&  counter_trivella==0){
			down_move = 0;
		}else{
			down_move = 1;
		}
		if (M[g_row-1][g_col] == '#'  &&  counter_trivella==0){
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
	}
	else{if (orizzontal_global == 1 && vertical_global == 0  && right_move == 0  &&  up_move == 0){//bisogna completare le istruzioni
			orizzontal_global = 0;
		}else{ if (orizzontal_global == 0  &&  vertical_global == 1){ //bisogna completare le istruzioni
					orizzontal_global = 1;
				}else{ if (orizzontal_global == 0 && vertical_global == 0){//bisogna completare le istruzioni
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
					case 0:		if(orizzontal_global == 1){
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
						
                    case 0: 	if(vertical_global == 1){
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

    int row, col;
    scanf("%d\n%d\n", &col, &row);
    
    char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
    for(int i = 0; i < col; i++){
        M[i] = (char*)malloc(col * sizeof(char));
    }


    if(argc == 2 && strcmp(argv[1], "--challenge") == 0){           //--challenge branch (IA)

        matrix_reader(M, &row, &col);                 //legge un labirinto da input terminale
        labyrint_analysis(M, &row, &col);             //IA

        return 0;

    }else{

        matrix_reader(M, &row, &col);                 //legge un labirinto da input terminale
        labyrinth_player(M, &row, &col);              //modifica la matrice facendo muovere il giocatore
        return 0;
    }

	return 0;
	
}
