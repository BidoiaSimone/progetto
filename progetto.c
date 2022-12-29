// 891868 895662

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "vectors.h"


#ifdef __APPLE__

#define DEFAULT 	"\033[0m"
#define BLACK		"\033[0;30m"
#define RED 		"\033[0;31m"		
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define PURPLE		"\033[0;35m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"

#endif


#ifdef __WIN32	

		char test[27] = "Wow, you are using Windows";
		void matrix_printer(char **M, int *row, int *col){      //implementare bella stampa a colori da usare
		for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){
					if(M[i][j] == '.')
						M[i][j] = ' ';
				}
			}
			for(int i = 0; i < tail->size; i++){
				M[tail->row[i]][tail->col[i]] = '.';
			}
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //funziona di merda per il merda di refresh rate del cmd
			for(int i = 0; i < *row; i++){                   //stampa matrice iniziale
				for(int j = 0; j < *col; j++){      
						printf("%c", M[i][j]);	
				}
					printf("\n");
			}   
				printf("\n");
		}
	}

#endif

#ifdef __APPLE__

		void matrix_printer(char **M, int *row, int *col, vector_t *tail){
			for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){
					if(M[i][j] == '.')
						M[i][j] = ' ';
				}
			}
			for(int i = 0; i < tail->size; i++){
				M[tail->row[i]][tail->col[i]] = '.';
			}
			for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){      
					if(M[i][j] == '#'){
						printf("█");
					}else{
						if(M[i][j] == 'o'){
							printf(BLUE);
							printf("◉");
							printf(DEFAULT);
						}else{
							if(M[i][j] == '.'){
								printf(BLUE);
								printf("•");
								printf(DEFAULT);
							}else{
								if(M[i][j] == '<' || M[i][j] == '>' || M[i][j] == 'v' || M[i][j] == '^')
									printf(PURPLE);
								if(M[i][j] == '$')
									printf(YELLOW);
								if(M[i][j] == '!')
									printf(RED);
								if(M[i][j] == 'T')
									printf(CYAN);
								
								printf("%c", M[i][j]);
								printf(DEFAULT);
							}
						}
					}
				}
					printf("\n");
			}   
			
				printf("\n");
		}
#endif


bool vertical_pattern(string_t *moves, char **M, int *row, int *col);
bool orizzontal_pattern(string_t *moves, char **M, int *row, int *col);

int vertical_global = 1;	// vertical_global==-1 movimento in basso, vertical_global==1 movimento verso l'alto
int orizzontal_global = 1;	// orizzontal_global==1 movimento dx, orizzontal_global==-1 movimento sx
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


void matrix_player(char **M, int *row, int *col){
    char c = '\0';
    int g_col;
    int g_row;
    int victory_row;
    int victory_col;
    int points = 1000;
	int trapano = 0;
	vector_t *tail = v_create();
	


    for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col; j++){          //controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == 'o'){
                g_col = j;
                g_row = i;
				tail->row = &i;
				tail->col = &j;
            }
            if(M[i][j] == '_'){
                victory_row = i;
                victory_col = j;
            }
        }
    }



    matrix_printer(M, row, col, tail);
    


    while((c != 'q')){          //muove pedina

		#ifdef __APPLE__
		system("stty raw");
		#endif

        c = getchar();
        if(c == 'w' && g_row-1 >= 0){//muove pedina in su
            
            if(M[g_row-1][g_col] == '$'){
				points+=10;
				v_push_back(tail, g_row, g_col);
			}
				
			    
            if(M[g_row-1][g_col] == '!'){
				points /= 2;
				if(tail->size > 0)
					v_cut(tail, tail->size/2);
			}  
			if(M[g_row-1][g_col] == 'T')
				trapano += 3;

			

			if(M[g_row-1][g_col] == '#' && trapano > 0){ //trapano
				M[g_row-1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				if(tail->size >= 0){
					for(int i = tail->size-1; i > 0; i--){
						tail->row[i] = tail->row[i-1];
						tail->col[i] = tail->col[i-1];
					}
					tail->row[0] = g_row;
					tail->col[0] = g_col;
				}
				g_row--;
				points--;
				trapano--;
				

			}else{
				//spazio o punti
			
				if(M[g_row-1][g_col] == '!' || M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == '.' ||
				M[g_row-1][g_col] == ' ' || M[g_row-1][g_col] == '_' || M[g_row-1][g_col] == 'T' || M[g_row-1][g_col] == '^'){

					if(M[g_row-1][g_col] == '.'){
						for(int i = 0; i < tail->size; i++){
							if(M[tail->row[i]+1][tail->col[i]] == 'o')
								v_cut(tail, i+1);
						}
					}
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					
					if(tail->size >= 0){
						for(int i = tail->size-1; i > 0; i--){
							tail->row[i] = tail->row[i-1];
							tail->col[i] = tail->col[i-1];
						}
						tail->row[0] = g_row;
						tail->col[0] = g_col;
					}
					g_row--;
					points--;
				
				}	
			}
		}
	

        if(c == 's' && g_row+1 < *row){//muove pedina in giù
            
            if(M[g_row+1][g_col] == '$'){
				points+=10;
				v_push_back(tail, g_row, g_col);
			}
				
			    
            if(M[g_row+1][g_col] == '!'){
				points /= 2;
				if(tail->size > 0)
					v_cut(tail, tail->size/2);
			}  
			if(M[g_row+1][g_col] == 'T')
				trapano += 3;

			

			if(M[g_row+1][g_col] == '#' && trapano > 0){ //trapano
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				if(tail->size >= 0){
					for(int i = tail->size-1; i > 0; i--){
						tail->row[i] = tail->row[i-1];
						tail->col[i] = tail->col[i-1];
					}
					tail->row[0] = g_row;
					tail->col[0] = g_col;
				}
				
				g_row++;
				points--;
				trapano--;

			}else{
				//spazio o punti
			
				if(M[g_row+1][g_col] == '!' || M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == '.' ||
				M[g_row+1][g_col] == ' ' || M[g_row+1][g_col] == '_' || M[g_row+1][g_col] == 'T' || M[g_row+1][g_col] == 'v'){

					if(M[g_row+1][g_col] == '.'){
						for(int i = 0; i < tail->size; i++){
							if(M[tail->row[i]-1][tail->col[i]] == 'o')
								v_cut(tail, i+1);
						}
					}
					M[g_row+1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					if(tail->size >= 0){
						for(int i = tail->size-1; i > 0; i--){
							tail->row[i] = tail->row[i-1];
							tail->col[i] = tail->col[i-1];
						}
						tail->row[0] = g_row;
						tail->col[0] = g_col;
					}
					g_row++;
					points--;
				
				}	
			}
		}

        if(c == 'a' && g_col-1 >= 0){//muove pedina a sinistra
            
            if(M[g_row][g_col-1] == '$'){
				points+=10;
				v_push_back(tail, g_row, g_col);
			}
				
			    
            if(M[g_row][g_col-1] == '!'){
				points /= 2;
				if(tail->size > 0)
					v_cut(tail, tail->size/2);
			}  
			if(M[g_row][g_col-1] == 'T')
				trapano += 3;

			

			if(M[g_row][g_col-1] == '#' && trapano > 0){ //trapano
				M[g_row][g_col-1] = 'o';
				M[g_row][g_col] = ' ';
				if(tail->size >= 0){
					for(int i = tail->size-1; i > 0; i--){
						tail->row[i] = tail->row[i-1];
						tail->col[i] = tail->col[i-1];
					}
					tail->row[0] = g_row;
					tail->col[0] = g_col;
				}
				g_col--;
				points--;
				trapano--;

			}else{
				//spazio o punti
			
				if(M[g_row][g_col-1] == '!' || M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == '.' ||
				M[g_row][g_col-1] == ' ' || M[g_row][g_col-1] == '_' || M[g_row][g_col-1] == 'T' || M[g_row][g_col-1] == '<'){

					if(M[g_row][g_col-1] == '.'){
						for(int i = 0; i < tail->size; i++){
							if(M[tail->row[i]][tail->col[i]+1] == 'o')
								v_cut(tail, i+1);
						}
					}

					M[g_row][g_col-1] = 'o';
					M[g_row][g_col] = ' ';
					if(tail->size >= 0){
						for(int i = tail->size-1; i > 0; i--){
							tail->row[i] = tail->row[i-1];
							tail->col[i] = tail->col[i-1];
						}
						tail->row[0] = g_row;
						tail->col[0] = g_col;
					}
					
					g_col--;
					points--;
				
				}	
			}
		}

        if(c == 'd' && g_col+1 < *col){//muove pedina a sinistra
            
            if(M[g_row][g_col+1] == '$'){
				points+=10;
				v_push_back(tail, g_row, g_col);
			}
				
		    
            if(M[g_row][g_col+1] == '!'){
				points /= 2;
				if(tail->size > 0)
					v_cut(tail, tail->size/2);
			}  
			if(M[g_row][g_col+1] == 'T')
				trapano += 3;

			

			if(M[g_row][g_col+1] == '#' && trapano > 0){ //trapano
				M[g_row][g_col+1] = 'o';
				M[g_row][g_col] = ' ';
				if(tail->size >= 0){
					for(int i = tail->size-1; i > 0; i--){
						tail->row[i] = tail->row[i-1];
						tail->col[i] = tail->col[i-1];
					}
					tail->row[0] = g_row;
					tail->col[0] = g_col;
				}
				g_col++;
				points--;
				trapano--;

			}else{
				//spazio o punti
			
				if(M[g_row][g_col+1] == '!' || M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == '.' ||
				M[g_row][g_col+1] == ' ' || M[g_row][g_col+1] == '_' || M[g_row][g_col+1] == 'T' || M[g_row][g_col+1] == '>'){

					if(M[g_row][g_col+1] == '.'){
						for(int i = 0; i < tail->size; i++){
							if(M[tail->row[i]][tail->col[i]-1] == 'o')
								v_cut(tail, i+1);
						}
					}

					M[g_row][g_col+1] = 'o';
					M[g_row][g_col] = ' ';
					if(tail->size >= 0){
						for(int i = tail->size-1; i > 0; i--){
							tail->row[i] = tail->row[i-1];
							tail->col[i] = tail->col[i-1];
						}
						tail->row[0] = g_row;
						tail->col[0] = g_col;
					}
					g_col++;
					points--;
				
				}	
			}
		}
		#ifdef __APPLE__
        system("stty cooked");
		system("clear");
		#endif

        if(c != '\n'){              
			
            matrix_printer(M, row, col, tail);
			


        	printf("%-10s%lu\n","Score: ", points+tail->size);
			printf("%-10s%d\n", "T: ", trapano);


        	if(M[victory_row][victory_col] == 'o'){
            	printf("Vittoria!!!\n");
				free(tail);
				break;
            
        	}
    	}	
    }
}

void labyrint_global_direction(char  **M, int *row,int *col) { // serve per inizializzare le direzioni principali (dx/sx) (up/down)

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
		vertical_global = -1; // down movimento preferito
	}else{
		vertical_global = 1; // up movimento preferito
	}
	if(g_col <= victory_col){
		orizzontal_global = 1; // movimento preferito a dx
	}else{
		orizzontal_global = -1; //movimento preferito a sx
	}
	
}

void labyrint_analysis( char **M, int *row, int *col, string_t *moves){ 
//iniziallizzo le variabili che mi serviranno per tenere tracia delle 
//coordinate dell'inizio e della fine del labirinto
	int g_col;
    int g_row;
	int x=0; // variabile che revirà per selezionare il case dello switch;
	int finish_check = 0;		//inserito perchè altrimenti il ciclo di controllo del '_', 
								//se non c'era l'arrivo nella prima cella, faceva return

							vector_t *tail = v_create();//da togliere, solo per chimare funzione printer
	bool v_pattern = false;	
	bool o_pattern = false;
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
        printf("%c\n",'E');
		s_push_back(moves, 'E', orizzontal_global);
        M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis( M, row, col, moves);
		return;
	}else{
		if (g_col== *col-1){
			printf("%c\n",'O');
			s_push_back(moves, 'O', orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		}else{
			if (g_row==0){
				printf("%c\n",'S');
				s_push_back(moves, 'S', orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis( M, row, col, moves);
				return;
			}else{
				if(g_row== *row-1){
					printf("%c\n",'N');
					s_push_back(moves, 'N', orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis( M, row, col, moves);
					return;
				}
			}
		}
        
	}
		
	if( M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == 'T'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '$' o 'T'
		if (M[g_row][g_col+1] == 'T'){
			counter_trivella += 3;
		}
		printf("$%c\n", 'E');
		s_push_back(moves, 'E', orizzontal_global);
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves);
		return;
	}else{
		if(M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == 'T'){
			if (M[g_row][g_col+1] == 'T'){
				counter_trivella += 3;
			}
			printf("$%c\n", 'O');
			s_push_back(moves, 'O', orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		} else{
			if(M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == 'T'){
				if (M[g_row][g_col+1] == 'T'){
					counter_trivella += 3;
				}
				printf("$%c\n", 'S');
				s_push_back(moves, 'S', orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}else{
				if(M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == 'T'){
					if (M[g_row][g_col+1] == 'T'){
						counter_trivella += 3;
					}
					printf("$%c\n", 'N');
					s_push_back(moves, 'N', orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves);
					return;
				}
			}
		}
        
	}
	// controllo quali movimenti sono impossibilitati dalle pareti. 
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
		printf("_%c\n", 'E');
		s_push_back(moves, 'E', orizzontal_global);
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves);
		return;
	}else{
		if(M[g_row][g_col-1] == '_'){
			printf("_%c\n", 'O');
			s_push_back(moves, 'O', orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		} else{
			if(M[g_row+1][g_col] == '_'){
				printf("_%c\n", 'S');
				s_push_back(moves, 'S', orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}else{
				if(M[g_row-1][g_col] == '_'){
					printf("_%c\n", 'N');
					s_push_back(moves, 'N', orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves);
					return;
				}
				}
			}
			
	}
	// se la pedina finisce in un anglo cecocambia direzione preferita	
	/*if (orizzontal_global == 1 && vertical_global == -1  && right_move==0 && down_move==0){
		orizzontal_global = -1;
	}else{	
		if(orizzontal_global == 1 && vertical_global == 1  && right_move == 0  &&  up_move == 0){
			orizzontal_global = -1;
		}else{ 
			if(orizzontal_global == 0  &&  vertical_global == -1  && left_move == 0 && down_move == 0){ 
				orizzontal_global = 1;
			}else{ 
				if (orizzontal_global == 0 && vertical_global == 1 && left_move == 0 && up_move == 0){
					orizzontal_global = 1;
				}
			}
		}
	}*/
	 /*
		vertical_global=-1; // down movimento preferito
	
		vertical_global=1; // up movimento preferito
	
		orizzontal_global=1; // movimento preferito a dx
	
		orizzontal_global=-1; //movimento preferito a sx
	*/
		
	// inizio associazione valore a x in caso di pattern rilevato
	
	o_pattern = orizzontal_pattern(moves, M, &g_row, &g_col);
	v_pattern = vertical_pattern(moves, M, &g_row, &g_col);
		
	if (orizzontal_pattern == true){
		if(vertical_global == 1){
			x = 2;
		}
		else{
			x = 1;
		}
	}
	else{ 	if (vertical_pattern == true){
				if (orizzontal_global == 1){
					x = 3;
				}
				else{
					x=4;
				}
			}
			else{
				if (abs(g_row - victory_row) >= abs(g_col - victory_col)){		// associazione del valore di x per lo switch
						if(g_row < victory_row  ){
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
			}
	}
			

			
		
	 /*
		vertical_global=-1; // down movimento preferito
	
		vertical_global=1; // up movimento preferito
	
		orizzontal_global=1; // movimento preferito a dx
	
		orizzontal_global=-1; //movimento preferito a sx
	*/

    //aggiungere count trivella in tutte le mosse dello switch

	if(up_move == 0 && right_move == 0 && down_move == 0){
		printf("41%c\n", 'O');
		s_pop_back(moves);
		M[g_row][g_col-1] = 'o';
		M[g_row][g_col] = '#';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves);
		return;
	}
	else{
		if(left_move == 0 && right_move == 0 && down_move == 0){
			printf("21%c\n", 'N');
			s_pop_back(moves);
			M[g_row-1][g_col] = 'o';
			M[g_row][g_col] = '#';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		}
		else{
			if(left_move == 0 && up_move == 0 && down_move == 0){
				printf("31%c\n", 'E');
				s_pop_back(moves);
				M[g_row][g_col+1] = 'o';
				M[g_row][g_col] = '#';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}
			else{
				if(left_move == 0 && up_move == 0 && right_move == 0){
					printf("11%c\n", 'S');
					s_pop_back(moves);
					M[g_row+1][g_col] = 'o';
					M[g_row][g_col] = '#';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves);
					return;
				}
			}
		}
	}

	



	switch (x) { //casi labirinto
        
		case  1: switch(down_move){

					case 1: 	if(v_pattern == false){
									printf("11%c\n", 'S');
									s_push_back(moves, 'S', orizzontal_global);
									if(M[g_row+1][g_col] == '#'){
										counter_trivella--;
									}
									M[g_row+1][g_col] = 'o';
									M[g_row][g_col] = ' ';
									matrix_printer(M, row, col, tail);
									labyrint_analysis(M, row, col, moves);
									return;
								}
								
					case 0: 	if(orizzontal_global == 1 && right_move == 1){
									x = 3;
								}else{
									if(left_move == 1){
										x = 4;
									}else{

										x = 1;
									}
									
								}
								switch (x){
											case 3: 	printf("103%c\n", 'E');
														s_push_back(moves, 'E', orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;

											case 4:	 	printf("104%c\n", 'O');
														s_push_back(moves, 'O', orizzontal_global);
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;

											case 1:     printf("101%c\n" , 'N');
														s_push_back(moves, 'N', orizzontal_global);
														M[g_row-1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;                                            
								}
		}                        
					
		case 2: switch(up_move){
					case 1: 	if(v_pattern == false){
									printf("21%c\n", 'N');
									s_push_back(moves, 'N', orizzontal_global);
									if(M[g_row-1][g_col] == '#'){
										counter_trivella--;
									}
									M[g_row-1][g_col] = 'o';
									M[g_row][g_col] = ' ';
									matrix_printer(M, row, col, tail);
									labyrint_analysis(M, row, col, moves);
									return;
								}
								
					case 0:		if(orizzontal_global == 1 && right_move == 1){
									x = 3;
								}else{
									if(left_move == 1){
										x = 4;
									}else{
										x = 2;
									}
									
								}    
                                switch (x) {
											case 3: 	printf("203%c\n", 'E');
														s_push_back(moves, 'E', orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;
						
											case 4:	 	printf("204%c\n", 'O');
														s_push_back(moves, 'O', orizzontal_global);
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;

											case 2:		printf("202%c\n", 'S');
														s_push_back(moves, 'S', orizzontal_global);
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;

                                            
									}					
					}	
		case 3: switch(right_move){

                    case 1: 		if(o_pattern == false){
										printf("31%c\n", 'E');
										s_push_back(moves, 'E', orizzontal_global);
										if(M[g_row][g_col+1] == '#'){
											counter_trivella--;
										}
										M[g_row][g_col+1] = 'o';
										M[g_row][g_col] = ' ';
										matrix_printer(M, row, col, tail);
										labyrint_analysis(M, row, col, moves);
										return;
									}
									
								
									
						
                    case 0: 	if(vertical_global == 1 && up_move == 1){
                                    x=1;
                                }else{ 
										if(down_move == 1){
											x = 2;
										}else{
											x = 4;
										}
                                }
                    
                                switch (x) { 
											case 1: printf("301%c\n", 'N');
													s_push_back(moves, 'N', orizzontal_global);
													M[g_row-1][g_col] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves);
													return;
							
											case 2:	printf("302%c\n", 'S');
													s_push_back(moves, 'S', orizzontal_global);
													M[g_row+1][g_col] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves);
													return;
											
											case 4: printf("304%c\n" , 'O');
													s_push_back(moves, 'O', orizzontal_global);
													M[g_row][g_col-1] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves);
													return;
								}
				}
        case 4: switch(left_move){
                    case 1:  		if(o_pattern == false){
										printf("41%c\n", 'O');
										s_push_back(moves, 'O', orizzontal_global);
										if(M[g_row][g_col-1] == '#'){
											counter_trivella--;
										}
										M[g_row][g_col-1] = 'o';
										M[g_row][g_col] = ' ';
										matrix_printer(M, row, col, tail);
										labyrint_analysis(M, row, col, moves);
										return;
									}
								
                    case 0: if(vertical_global == 1 && up_move == 1){
                                    x=1;          
                                }else{
										if (down_move == 1){
											x=2;
										}else{
											x = 3;
										}
									}
                                
                                switch (x) {


											case  1:	printf("401%c\n", 'N');
														s_push_back(moves, 'N', orizzontal_global);
														M[g_row-1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;
														
							
											case 2:		printf("402%c\n", 'S');
														s_push_back(moves, 'S', orizzontal_global);
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;
														
														
											case 3:		printf("403%c\n" , 'E');
														s_push_back(moves, 'E', orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves);
														return;			                       
								}
					}
    }

	} 



bool vertical_pattern(string_t *moves, char **M, int *g_row, int *g_col){
	bool ptt = 0;
	int s_cnt = 0;
	int n_cnt = 0;
	if(moves->string[moves->size-1] == 'N'){
		for(int i = moves->size-1; moves->string[i] == 'N'; i--){
			n_cnt++;
		}
		for(int i = moves->size-n_cnt-1; moves->string[i] == 'S'; i--){
			s_cnt++;
		}
		if(s_cnt == n_cnt){
			ptt = true;
			vertical_global = -1;
		
			for(int i = 0; i < n_cnt+s_cnt; i++){
				s_pop_back(moves);
			}
			/*for(int i = 0; i < n_cnt; i++){
				s_push_back(moves, 'S', orizzontal_global);
				M[*g_row++][*g_col] = 'o';
				M[*g_row][*g_col] = ' ';
		
			}*/
		}	
	}

	if(moves->string[moves->size-1] == 'S'){
		for(int i = moves->size-1; moves->string[i] == 'S'; i--){
			s_cnt++;
		}
		for(int i = moves->size-s_cnt-1; moves->string[i] == 'N'; i--){
			n_cnt++;
		}
		if(s_cnt == n_cnt){
			ptt = true;
			vertical_global = 1;
		
			for(int i = 0; i < n_cnt+s_cnt; i++){
				s_pop_back(moves);
			}
			/*for(int i = 0; i < n_cnt; i++){
				s_push_back(moves, 'N', orizzontal_global);
				M[*g_row--][*g_col] = 'o';
				M[*g_row][*g_col] = ' ';
				
			}*/
			if(moves->string[moves->size-2] == 'O'){
				orizzontal_global = 1;
			}
			else{
				orizzontal_global = -1;
			}
		}
	}
	printf("\n----------------------- v_g %d   %d -----------------------\n",vertical_global, ptt);
	s_print(moves);
	return ptt;
}


bool orizzontal_pattern(string_t *moves, char **M, int *g_row, int *g_col){
	bool ptt = 0;
	int o_cnt = 0;
	int e_cnt = 0;
	int up_move;
	int right_move;
	int left_move;
	int down_move;
	if(moves->string[moves->size-1] == 'E'){
		for(int i = moves->size-1; moves->string[i] == 'E'; i--){
			e_cnt++;
		}
		for(int i = moves->size-e_cnt-1; moves->string[i] == 'O'; i--){
			o_cnt++;
		}
		if(o_cnt == e_cnt){
			ptt = true;
			orizzontal_global = 1;

			for(int i = 0; i < e_cnt+o_cnt; i++){
				s_pop_back(moves);
			}
			for(int i = 0; i < e_cnt; i++){
				s_push_back(moves, 'O', orizzontal_global);
				M[*g_row][*g_col--] = 'o';
				M[*g_row][*g_col] = ' ';
				
			}
		}
	}
	if(moves->string[moves->size-1] == 'O'){
		for(int i = moves->size-1; moves->string[i] == 'O'; i--){
			o_cnt++;
		}
		for(int i = moves->size-o_cnt-1; moves->string[i] == 'E'; i--){
			e_cnt++;
		}
		if(o_cnt == e_cnt){
			ptt = true;
			orizzontal_global = -1;

			for(int i = 0; i < e_cnt+o_cnt; i++){
				s_pop_back(moves);
			}
			for(int i = 0; i < e_cnt; i++){
				s_push_back(moves, 'E', orizzontal_global);
				M[*g_row][*g_col++] = 'o';
				M[*g_row][*g_col] = ' ';
				
			}
		}
		
	}
		if (ptt){
				if (M[*g_row][*g_col+1] == '#'){
						right_move = 0;
					}else{
						right_move = 1;
					}
					if (M[*g_row][*g_col-1] == '#'){
						left_move = 0;
					}else{
						left_move = 1;
					}
					if (M[*g_row+1][*g_col] == '#'){
						down_move = 0;
					}else{
						down_move = 1;
					}
					if (M[*g_row-1][*g_col] == '#'){
						up_move = 0;
					}else{
						up_move = 1;
					}
					if (down_move == 0 && right_move == 0   ||   down_move == 0 && left_move == 0){
						vertical_global = 1;
					} else{
							if(up_move == 0 && right_move == 0  ||  up_move == 0 && left_move == 0){
								vertical_global = -1;
							}
					}
		}
	
	printf("\n----------------------- o_g %d   %d -----------------------\n",orizzontal_global, ptt);
	s_print(moves);
	return ptt;
}






int main(int argc, char * argv[]){

	int row = 0;
	int col = 0;
	scanf("%d\n%d\n", &col, &row);
	string_t *moves = s_create();

    
    char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
    for(int i = 0; i < row; i++){
        M[i] = (char*)malloc(col * sizeof(char));
    }
	
	matrix_reader(M, &row, &col);


    if(argc == 2 && strcmp(argv[1], "--challenge") == 0){           //--challenge branch (IA)

          
		labyrint_global_direction(M, &row, &col);
        labyrint_analysis(M, &row, &col, moves);             //IA
		s_print(moves);
        return 0;

    }else{

                         //legge un labirinto da input terminale
		#ifdef __APPLE__
			system("clear");
		#endif
        matrix_player(M, &row, &col);              //modifica la matrice facendo muovere il giocatore
        return 0;
    }
	for(int i = 0; i < row; i++){
		free(M[i]);
	}
	free(M);
	return 0;
	
}



/* funzione pattern che legge string_t ed identifica se c'è un pattern lungo N, che ritorna variabile bool
tieni conto tutti i vari tipi di pattern possibili E-O, N-S, in base a tipo di pattern cambiare le variabili
down_move ecc.. unica mossa da mettere true sarà direzione opposta a globale consigliata */
// codice che andrà dentro la funzione Pattern
		 /*
		vertical_global=-1; // down movimento preferito
	
		vertical_global=1; // up movimento preferito
	
		orizzontal_global=1; // movimento preferito a dx
	
		orizzontal_global=-1; //movimento preferito a sx
	*/



