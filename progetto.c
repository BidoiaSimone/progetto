// 891868 895662

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "vectors.h"
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#endif

#define DEFAULT 	"\033[0m"
#define BLACK		"\033[0;30m"
#define RED 		"\033[0;31m"		
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define PURPLE		"\033[0;35m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"


bool vertical_pattern(string_t *moves, vector_global *check_global, char **M, int *row, int *col, string_t *pattern_history);
bool orizzontal_pattern(string_t *moves, vector_global *check_global, char **M, int *row, int *col, string_t *pattern_history);


int vertical_global = 1;	// vertical_global==-1 movimento in basso, vertical_global==1 movimento verso l'alto
int orizzontal_global = 1;	// orizzontal_global==1 movimento dx, orizzontal_global==-1 movimento sx
int counter_trivella = 0;
int v_ptt = 0;
int o_ptt = 0;
int MS;





#ifdef __APPLE__

	int milliseconds_calculator(){
		int start = time(NULL);
		double clock_start = clock();
		while(time(NULL) <= start+1){}
		double clock_finish = clock();
		double clocks_in_one_sec = clock_finish - clock_start;
		double clocks_in_one_millisec = clocks_in_one_sec / 1000;
		return clocks_in_one_millisec;
	}

	void delay_milliseconds(int milliseconds){
		double start_time = clock();
		while(clock() <= start_time + (milliseconds * MS)){}
	}

	void matrix_printer(char **M, int *row, int *col, vector_t *tail){
		for(int i = 0; i < *row; i++){                   
			for(int j = 0; j < *col; j++){
				if(M[i][j] == '0')
					M[i][j] = ' ';
			}
		}
		for(int i = 0; i < tail->size; i++){
			M[tail->row[i]][tail->col[i]] = '0';
		}
		system("clear");
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
						if(M[i][j] == '0'){
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
							if(M[i][j] == 'a'){
								printf(" ");
							}else{
								printf("%c", M[i][j]);
							}
							
							printf(DEFAULT);
						}
					}
				}
			}
				printf("\n");
		}   
		
			printf("\n");
			delay_milliseconds(40);
	}
#elif _WIN32

	void matrix_printer(char **M, int *row, int *col, vector_t *tail){
		for(int i = 0; i < *row; i++){                   
			for(int j = 0; j < *col; j++){
				if(M[i][j] == '0')
					M[i][j] = ' ';
			}
		}
		for(int i = 0; i < tail->size; i++){
			M[tail->row[i]][tail->col[i]] = '0';
		}
		system("cls");
		for(int i = 0; i < *row; i++){                   
			for(int j = 0; j < *col; j++){      
				if(M[i][j] == '#'){
					printf("%c", M[i][j]);
				}else{
					if(M[i][j] == 'o'){
						printf(BLUE);
						printf("o");
						printf(WHITE);
					}else{
						if(M[i][j] == '0'){
							printf(BLUE);
							printf("0");
							printf(WHITE);
						}else{
							if(M[i][j] == '<' || M[i][j] == '>' || M[i][j] == 'v' || M[i][j] == '^')
								printf(PURPLE);
							if(M[i][j] == '$')
								printf(YELLOW);
							if(M[i][j] == '!')
								printf(RED);
							if(M[i][j] == 'T')
								printf(CYAN);
							if(M[i][j] == 'a'){
								printf(" ");
							}else{
								printf("%c", M[i][j]);
							}
							printf(WHITE);
						}
					}
				}
			}
				printf("\n");
		}   
		
			printf("\n");
			system("ping /n 1 /w 20 localhost >nul");
	}
#elif __unix__


		void matrix_printer(char **M, int *row, int *col, vector_t *tail){
			for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){
					if(M[i][j] == '0')
						M[i][j] = ' ';
				}
			}
			for(int i = 0; i < tail->size; i++){
				M[tail->row[i]][tail->col[i]] = '0';
			}
			system("clear");
			for(int i = 0; i < *row; i++){                   
				for(int j = 0; j < *col; j++){      
					if(M[i][j] == '#'){
						printf("█");
					}else{
						if(M[i][j] == 'o'){
							printf(BLUE);
							printf("o");
							printf(DEFAULT);
						}else{
							if(M[i][j] == '0'){
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
								if(M[i][j] == 'a'){
									printf(" ");
								}else{
									printf("%c", M[i][j]);
								}
								
								printf(DEFAULT);
							}
						}
					}
				}
					printf("\n");
			}   
			
				printf("\n");
				system("sleep 0.3s");
		}

#endif




void matrix_reader(char **M, int *row, int *col){       //legge una matrice da stdin riga per riga
        int i = 0;
        while(i < *row){
            scanf("%[^\n]%*c", &M[i][0]);
            i++;
        }
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
			c = getchar();
		#elif _WIN32
			c = getch();
		#elif __unix__
			system("stty raw");
        	c = getchar();
		#endif
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
			
				if(M[g_row-1][g_col] == '!' || M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == '0' ||
				M[g_row-1][g_col] == ' ' || M[g_row-1][g_col] == '_' || M[g_row-1][g_col] == 'T' || M[g_row-1][g_col] == '^'){

					if(M[g_row-1][g_col] == '0'){
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
			
				if(M[g_row+1][g_col] == '!' || M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == '0' ||
				M[g_row+1][g_col] == ' ' || M[g_row+1][g_col] == '_' || M[g_row+1][g_col] == 'T' || M[g_row+1][g_col] == 'v'){

					if(M[g_row+1][g_col] == '0'){
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
			
				if(M[g_row][g_col-1] == '!' || M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == '0' ||
				M[g_row][g_col-1] == ' ' || M[g_row][g_col-1] == '_' || M[g_row][g_col-1] == 'T' || M[g_row][g_col-1] == '<'){

					if(M[g_row][g_col-1] == '0'){
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
			
				if(M[g_row][g_col+1] == '!' || M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == '0' ||
				M[g_row][g_col+1] == ' ' || M[g_row][g_col+1] == '_' || M[g_row][g_col+1] == 'T' || M[g_row][g_col+1] == '>'){

					if(M[g_row][g_col+1] == '0'){
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
		#elif _WIN32
		system("cls");
		#elif __unix__
		system("stty cooked");
		system("clear");
		#endif

        if(c != '\n'){              
			
            matrix_printer(M, row, col, tail);
			


        	printf("%-10s%lu\n","Score: ", points+tail->size);
			printf("%-10s%d\n", "T: ", trapano);


        	if(M[victory_row][victory_col] == 'o'){
            	printf("Vittoria!!!\n");
				v_free(tail);
				break;
            
        	}
    	}	
    }
}

void labyrint_global_direction(char  **M, int *row,int *col, vector_global *check_global) { // serve per inizializzare le direzioni principali (dx/sx) (up/down)

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

	if(abs(g_row - victory_row) > abs(g_col - victory_col)){
		if(vertical_global == 1){
			check_global->vertical_direction[0] = -1;
			check_global->vertical_direction[1] = 1;
			check_global->orizzontal_direction[0] = orizzontal_global;
			check_global->orizzontal_direction[1] = orizzontal_global;
		}else{
			check_global->vertical_direction[0] = 1;
			check_global->vertical_direction[1] = -1;
			check_global->orizzontal_direction[0] = orizzontal_global;
			check_global->orizzontal_direction[1] = orizzontal_global;
		}
	}else{
		if(orizzontal_global == 1){
			check_global->orizzontal_direction[0] = -1;
			check_global->orizzontal_direction[1] = 1;
			check_global->vertical_direction[0] = vertical_global;
			check_global->vertical_direction[1] = vertical_global;
		}else{
			check_global->orizzontal_direction[0] = 1;
			check_global->orizzontal_direction[1] = -1;
			check_global->vertical_direction[0] = vertical_global;
			check_global->vertical_direction[1] = vertical_global;
		}
	}
}

void labyrint_analysis( char **M, int *row, int *col, string_t *moves, vector_global *check_global, string_t *pattern_history){ 
//iniziallizzo le variabili che mi serviranno per tenere tracia delle 
//coordinate dell'inizio e della fine del labirinto
	int g_col;
    int g_row;
	int x=0; // variabile che revirà per selezionare il case dello switch;
	int finish_check = 0;		//inserito perchè altrimenti il ciclo di controllo del '_', 
								//se non c'era l'arrivo nella prima cella, faceva return

							vector_t *tail = v_create();//da togliere, solo per chimare funzione printer

    int victory_row;
    int victory_col;
	int left_move = 0;
	int up_move = 0;
	int down_move = 0;
	int right_move = 0;

	
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
                victory_col = j;			
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
		if( M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == 'T'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '$' o 'T'
			if (M[g_row][g_col+1] == 'T'){
				counter_trivella += 3;
			}
		}
        printf("%c\n",'E');
		s_push_back(moves, 'E', vertical_global, orizzontal_global);
        M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = 'a';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves, check_global, pattern_history);
		return;
	}else{
		if (g_col== *col-1){
			if(M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == 'T'){
				if (M[g_row][g_col+1] == 'T'){
					counter_trivella += 3;
				}
			}
			printf("%c\n",'O');
			s_push_back(moves, 'O', vertical_global, orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = 'a';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}else{
			if (g_row==0){
				if(M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == 'T'){
					if (M[g_row][g_col+1] == 'T'){
						counter_trivella += 3;
					}
				}
				printf("%c\n",'S');
				s_push_back(moves, 'S', vertical_global, orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = 'a';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves, check_global, pattern_history);
				return;
			}else{
				if(g_row== *row-1){
					if(M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == 'T'){
						if (M[g_row][g_col+1] == 'T'){
							counter_trivella += 3;
						}
					}
					printf("%c\n",'N');
					s_push_back(moves, 'N', vertical_global, orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = 'a';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves, check_global, pattern_history);
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
		s_push_back(moves, 'E', vertical_global, orizzontal_global);
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves, check_global, pattern_history);
		return;
	}else{
		if(M[g_row][g_col-1] == '$' || M[g_row][g_col-1] == 'T'){
			if (M[g_row][g_col+1] == 'T'){
				counter_trivella += 3;
			}
			printf("$%c\n", 'O');
			s_push_back(moves, 'O', vertical_global, orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		} else{
			if(M[g_row+1][g_col] == '$' || M[g_row+1][g_col] == 'T'){
				if (M[g_row][g_col+1] == 'T'){
					counter_trivella += 3;
				}
				printf("$%c\n", 'S');
				s_push_back(moves, 'S', vertical_global, orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves, check_global, pattern_history);
				return;
			}else{
				if(M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == 'T'){
					if (M[g_row][g_col+1] == 'T'){
						counter_trivella += 3;
					}
					printf("$%c\n", 'N');
					s_push_back(moves, 'N', vertical_global, orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves, check_global, pattern_history);
					return;
				}
			}
		}
        
	}
	// controllo quali movimenti sono impossibilitati dalle pareti. 
		if ((M[g_row][g_col+1] == '#' || M[g_row][g_col+1] == 'a') &&  counter_trivella  == 0){
			right_move = 0;
		}else{
			right_move = 1;
		}
		if ((M[g_row][g_col-1] == '#' || M[g_row][g_col-1] == 'a') &&  counter_trivella == 0){
			left_move = 0;
		}else{
			left_move = 1;
		}
		if ((M[g_row+1][g_col] == '#' || M[g_row+1][g_col] == 'a')  &&  counter_trivella == 0){
			down_move = 0;
		}else{
			down_move = 1;
		}
		if ((M[g_row-1][g_col] == '#' || M[g_row-1][g_col] == 'a')  &&  counter_trivella == 0){
			up_move = 0;
		}else{
			up_move = 1;
		}
		// lo sburooooooooooooooooooooooooo controlla se nelle vicinanze c'è l'arrivo
		if( M[g_row][g_col+1] == '_'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '_'
		printf("_%c\n", 'E');
		s_push_back(moves, 'E', vertical_global, orizzontal_global);
		M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves, check_global, pattern_history);
		return;
		}else{
			if(M[g_row][g_col-1] == '_'){
				printf("_%c\n", 'O');
				s_push_back(moves, 'O', vertical_global, orizzontal_global);
				M[g_row][g_col-1] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves, check_global, pattern_history);
				return;
			} else{
				if(M[g_row+1][g_col] == '_'){
					printf("_%c\n", 'S');
					s_push_back(moves, 'S', vertical_global, orizzontal_global);
					M[g_row+1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves, check_global, pattern_history);
					return;
				}else{
					if(M[g_row-1][g_col] == '_'){
						printf("_%c\n", 'N');
						s_push_back(moves, 'N', vertical_global, orizzontal_global);
						M[g_row-1][g_col] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis(M, row, col, moves, check_global, pattern_history);
						return;
					}
					}
				}
				
	}
	
	
		
	// inizio associazione valore a x in caso di pattern rilevato
	
	if(orizzontal_pattern(moves, check_global, M, &g_row, &g_col, pattern_history) == 1){
		if(moves->string[moves->size-1] == 'E'){
			printf("_%c\n", 'E');
			s_push_back(moves, 'E', vertical_global, orizzontal_global);
			M[g_row][g_col+1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}
		if(moves->string[moves->size-1] == 'O'){
			printf("_%c\n", 'O');
			s_push_back(moves, 'O', vertical_global, orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}
	}
	if(vertical_pattern(moves, check_global, M, &g_row, &g_col, pattern_history) == 1){
		if(moves->string[moves->size-1] == 'N'){
			printf("_%c\n", 'N');
			s_push_back(moves, 'N', vertical_global, orizzontal_global);
			M[g_row-1][g_col] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}
		if(moves->string[moves->size-1] == 'S'){
			printf("_%c\n", 'S');
			s_push_back(moves, 'S', vertical_global, orizzontal_global);
			M[g_row+1][g_col] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}
	}
		
		if (check_global->orizzontal_direction[0]  !=  check_global->orizzontal_direction[1]){
			if(check_global->orizzontal_direction[1] == 1){
				x = 3;
			}else{
				x = 4;
			}
			
		}else{
			
			if (check_global->vertical_direction[0]  !=  check_global->vertical_direction[1]){
				if (check_global->vertical_direction[1] == 1){
					x = 2;
				}else{
					x = 1;
				}
			}
		}
			

		
	
  

	if(up_move == 0 && right_move == 0 && down_move == 0){
		printf("41%c\n", 'O');
		s_pop_back(moves);
		M[g_row][g_col-1] = 'o';
		M[g_row][g_col] = 'a';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves, check_global, pattern_history);
		return;
	}else{
		if(left_move == 0 && right_move == 0 && down_move == 0){
			printf("21%c\n", 'N');
			s_pop_back(moves);
			M[g_row-1][g_col] = 'o';
			M[g_row][g_col] = 'a';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves, check_global, pattern_history);
			return;
		}else{
			if(left_move == 0 && up_move == 0 && down_move == 0){
				printf("31%c\n", 'E');
				s_pop_back(moves);
				M[g_row][g_col+1] = 'o';
				M[g_row][g_col] = 'a';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves, check_global, pattern_history);
				return;
			}else{
				if(left_move == 0 && up_move == 0 && right_move == 0){
					printf("11%c\n", 'S');
					s_pop_back(moves);
					M[g_row+1][g_col] = 'o';
					M[g_row][g_col] = 'a';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves, check_global, pattern_history);
					return;
				}
			}
		}
	}




	switch (x) { //casi labirinto
        
		case  1: switch(down_move){

					case 1: 	
									printf("11%c\n", 'S');
									s_push_back(moves, 'S', vertical_global, orizzontal_global);
									if(M[g_row+1][g_col] == '#'){
										counter_trivella--;
									}
									M[g_row+1][g_col] = 'o';
									M[g_row][g_col] = ' ';
									matrix_printer(M, row, col, tail);
									labyrint_analysis(M, row, col, moves, check_global, pattern_history);
									return;
								
								
					case 0: 	if(orizzontal_global == 1){
									if(right_move == 1){
										x = 3;
									}else{
										if(moves->string[moves->size-1] == 'E'){
											x = 2;
										}else{
											if(moves->string[moves->size-1] == 'S'){
												x = 4;
											}
										}
									}
                                }else{
									if(orizzontal_global == -1){
										if(left_move == 1){
											x = 4;
										}else{
											if(moves->string[moves->size-1] == 'S'){
												x = 3;
											}else{
												if(moves->string[moves->size-1] == 'O'){
													x = 2;
												}
											}
										}
									}
								}

								switch (x){
											case 3: 	printf("103%c\n", 'E');
														s_push_back(moves, 'E', vertical_global, orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;

											case 4:	 	printf("104%c\n", 'O');
														s_push_back(moves, 'O', vertical_global, orizzontal_global);
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;

											case 2:     printf("101%c\n" , 'N');
														s_push_back(moves, 'N', vertical_global, orizzontal_global);
														M[g_row-1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;                                            
								}
		}
		                        
					
		case 2: switch(up_move){
					case 1: 	
									printf("21%c\n", 'N');
									s_push_back(moves, 'N', vertical_global, orizzontal_global);
									if(M[g_row-1][g_col] == '#'){
										counter_trivella--;
									}
									M[g_row-1][g_col] = 'o';
									M[g_row][g_col] = ' ';
									matrix_printer(M, row, col, tail);
									labyrint_analysis(M, row, col, moves, check_global, pattern_history);
									return;
								
								
					case 0:		if(orizzontal_global == 1){
									if(right_move == 1){
										x = 3;
									}else{
										if(moves->string[moves->size-1] == 'E'){
											x = 1;
										}else{
											if(moves->string[moves->size-1] == 'N'){
												x = 4;
											}
										}
									}
                                }else{
									if(orizzontal_global == -1){
										if(left_move == 1){
											x = 4;
										}else{
											if(moves->string[moves->size-1] == 'N'){
												x = 3;
											}else{
												if(moves->string[moves->size-1] == 'O'){
													x = 1;
												}
											}
										}
									}
								}   
                                switch (x) {
											case 3: 	printf("203%c\n", 'E');
														s_push_back(moves, 'E', vertical_global, orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;
						
											case 4:	 	printf("204%c\n", 'O');
														s_push_back(moves, 'O', vertical_global, orizzontal_global);
														M[g_row][g_col-1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;

											case 1:		printf("201%c\n", 'S');
														s_push_back(moves, 'S', vertical_global, orizzontal_global);
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;

                                            
									}					
					}	
		
		case 3: switch(right_move){

                    case 1: 		
								printf("31%c\n", 'E');
								s_push_back(moves, 'E', vertical_global, orizzontal_global);
								if(M[g_row][g_col+1] == '#'){
									counter_trivella--;
								}
								M[g_row][g_col+1] = 'o';
								M[g_row][g_col] = ' ';
								matrix_printer(M, row, col, tail);
								labyrint_analysis(M, row, col, moves, check_global, pattern_history);
								return;
									
									
								
									
						
                    case 0: 	if(vertical_global == 1){
									if(up_move == 1){
										x = 2;
									}else{
										if(moves->string[moves->size-1] == 'E'){
											x = 1;
										}else{
											if(moves->string[moves->size-1] == 'N'){
												x = 4;
											}
										}
									}
                                }else{
									if(vertical_global == -1){
										if(down_move == 1){
											x = 1;
										}else{
											if(moves->string[moves->size-1] == 'S'){
												x = 4;
											}else{
												if(moves->string[moves->size-1] == 'E'){
													x = 2;
												}
											}
										}
									}
								}

								
								

		
										
                                
                    
                                switch (x) { 
											case 2: printf("301%c\n", 'N');
													s_push_back(moves, 'N', vertical_global, orizzontal_global);
													M[g_row-1][g_col] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves, check_global, pattern_history);
													return;
							
											case 1:	printf("302%c\n", 'S');
													s_push_back(moves, 'S', vertical_global, orizzontal_global);
													M[g_row+1][g_col] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves, check_global, pattern_history);
													return;
											
											case 4: printf("304%c\n" , 'O');
													s_push_back(moves, 'O', vertical_global, orizzontal_global);
													M[g_row][g_col-1] = 'o';
													M[g_row][g_col] = ' ';
													matrix_printer(M, row, col, tail);
													labyrint_analysis(M, row, col, moves, check_global, pattern_history);
													return;
								}
				}

		
        case 4: switch(left_move){
                    case 1:  		
										printf("41%c\n", 'O');
										s_push_back(moves, 'O', vertical_global, orizzontal_global);
										if(M[g_row][g_col-1] == '#'){
											counter_trivella--;
										}
										M[g_row][g_col-1] = 'o';
										M[g_row][g_col] = ' ';
										matrix_printer(M, row, col, tail);
										labyrint_analysis(M, row, col, moves, check_global, pattern_history);
										return;
									
								
                    case 0: 	if(vertical_global == 1){
									if(up_move == 1){
										x = 2;
									}else{
										if(moves->string[moves->size-1] == 'O'){
											x = 1;
										}else{
											if(moves->string[moves->size-1] == 'N'){
												x = 3;
											}
										}
									}
                                }else{
									if(vertical_global == -1){
										if(down_move == 1){
											x = 1;
										}else{
											if(moves->string[moves->size-1] == 'S'){
												x = 3;
											}else{
												if(moves->string[moves->size-1] == 'O'){
													x = 2;
												}
											}
										}
									}
								}
                                
                                switch (x) {


											case  2:	printf("401%c\n", 'N');
														s_push_back(moves, 'N', vertical_global, orizzontal_global);
														M[g_row-1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;
														
							
											case 1:		printf("402%c\n", 'S');
														s_push_back(moves, 'S', vertical_global, orizzontal_global);
														M[g_row+1][g_col] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;
														
														
											case 3:		printf("403%c\n" , 'E');
														s_push_back(moves, 'E', vertical_global, orizzontal_global);
														M[g_row][g_col+1] = 'o';
														M[g_row][g_col] = ' ';
														matrix_printer(M, row, col, tail);
														labyrint_analysis(M, row, col, moves, check_global, pattern_history);
														return;			                       
								}
		}
	}
}

// string_t void s_push_back( tring_t *s, charc, vertical, orizzontal)

bool vertical_pattern(string_t *moves, vector_global *check_global, char **M, int *g_row, int *g_col, string_t *pattern_history){
	bool ptt = 0;
	if(moves->string[moves->size-1] == 'N'){
		if(moves->string[moves->size-2] == 'S'){
			ptt = true;
		}
	}
	if(moves->string[moves->size-1] == 'S'){
		if(moves->string[moves->size-2] == 'N'){
			ptt = true;
		}
	}
	if(ptt == true){

		check_global->vertical_direction[0] = check_global->vertical_direction[1];
		check_global->orizzontal_direction[0] = check_global->orizzontal_direction[1];
		vertical_global *= -1;
		check_global->vertical_direction[1] = vertical_global;
		
		if(vertical_global == -1){
			
			if(M[*g_row + 2][*g_col] != '#'){
				
					s_push_back(pattern_history , 'S', *g_row + 2, *g_col);
					
					for(int i=0; i<pattern_history->size-1 &&pattern_history->size > 1; i++){
						
						if(pattern_history->vertical[i] == pattern_history->vertical[pattern_history->size - 1]  && pattern_history->orizzontal[i] == pattern_history->orizzontal[pattern_history->size - 1]  && pattern_history->string[i] == pattern_history->string[pattern_history->size - 1]){
							vertical_global *= -1;
							orizzontal_global *= -1;
							check_global->vertical_direction[1] = vertical_global;
							check_global->orizzontal_direction[1] = orizzontal_global;
							s_pop_elem(pattern_history, i);
							s_pop_back(pattern_history);
							s_cut(moves, moves->size-1);
							return ptt;
						}
					}
			}
		}else{
			if(vertical_global == 1){
				if(M[*g_row - 2][*g_col] != '#'){
				
					s_push_back(pattern_history , 'N', *g_row - 2, *g_col);
					
					for(int i=0; i<pattern_history->size-1 &&pattern_history->size > 1; i++){
						
						if(pattern_history->vertical[i] == pattern_history->vertical[pattern_history->size - 1]  && pattern_history->orizzontal[i] == pattern_history->orizzontal[pattern_history->size - 1]  && pattern_history->string[i] == pattern_history->string[pattern_history->size - 1]){
							vertical_global *= -1;
							orizzontal_global *= -1;
							check_global->vertical_direction[1] = vertical_global;
							check_global->orizzontal_direction[1] = orizzontal_global;
							s_pop_elem(pattern_history, i);
							s_pop_back(pattern_history);
							s_cut(moves, moves->size-1);
							return ptt;
						}
					}
				}
			}
				
				
		}
		s_cut(moves, moves->size-2);
	}
	
	printf("\n%d, %d", check_global->vertical_direction[0], check_global->vertical_direction[1]);
	printf("\nv_g %d   %d \n",vertical_global, ptt);
	//s_print(moves);
	return 0;
}

bool orizzontal_pattern(string_t *moves, vector_global *check_global, char **M, int *g_row, int *g_col, string_t *pattern_history){
	bool ptt = 0;
	if(moves->string[moves->size-1] == 'E'){
		if(moves->string[moves->size-2] == 'O'){
			ptt = true;
		}
	}
	if(moves->string[moves->size-1] == 'O'){
		if(moves->string[moves->size-2] == 'E'){
			ptt = true;
		}
	}

	if(ptt == true){
		check_global->orizzontal_direction[0] = check_global->orizzontal_direction[1];
		check_global->vertical_direction[0] = check_global->vertical_direction[1];
		orizzontal_global *= -1;
		check_global->orizzontal_direction[1] = orizzontal_global;
		if(orizzontal_global == 1){
			
			if(M[*g_row][*g_col + 2] != '#'){
				
				s_push_back(pattern_history , 'E', *g_row, *g_col + 2);
				
				for(int i=0; i<pattern_history->size-1 &&pattern_history->size > 1; i++){
					
					if(pattern_history->vertical[i] == pattern_history->vertical[pattern_history->size - 1]  && pattern_history->orizzontal[i] == pattern_history->orizzontal[pattern_history->size - 1]  && pattern_history->string[i] == pattern_history->string[pattern_history->size - 1]){
						vertical_global *= -1;
						orizzontal_global *= -1;
						check_global->vertical_direction[1] = vertical_global;
						check_global->orizzontal_direction[1] = orizzontal_global;
						s_pop_elem(pattern_history, i);
						s_pop_back(pattern_history);
						s_cut(moves, moves->size - 1);
						return ptt;
					}
				}
			}
		}else{
			if(orizzontal_global == -1){
				
				if(M[*g_row][*g_col - 2] != '#'){
					
					s_push_back(pattern_history , 'O', *g_row, *g_col - 2);
					for(int i=0; i<pattern_history->size-1 && pattern_history->size > 1; i++){
						
						if(pattern_history->vertical[i] == pattern_history->vertical[pattern_history->size - 1]  && pattern_history->orizzontal[i] == pattern_history->orizzontal[pattern_history->size - 1]  && pattern_history->string[i] == pattern_history->string[pattern_history->size - 1]){
							
							vertical_global *= -1;
							orizzontal_global *= -1;
							check_global->vertical_direction[1] = vertical_global;
							check_global->orizzontal_direction[1] = orizzontal_global;
							s_pop_elem(pattern_history, i);
							s_pop_back(pattern_history);
							s_cut(moves, moves->size - 1);
							return ptt;
						}
					}
				}	
			}
		}
		s_cut(moves, moves->size - 2);
	}
	printf("\n%d, %d", check_global->orizzontal_direction[0], check_global->orizzontal_direction[1]);
	printf("\no_g %d   %d \n",orizzontal_global, ptt);
	//s_print(moves);
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










int main(){
	int selection=0;
	puts("Press 1 for Single Player or 2 for AI mode, than copy paste the matrix to play with!");
	scanf("%d", &selection);
	
	if(selection == 1){
		int row = 0;
		int col = 0;
		#ifdef __APPLE__
			MS = milliseconds_calculator();
		#endif
		scanf("%d\n%d\n", &col, &row);
		

    
		char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
		for(int i = 0; i < row; i++){
			M[i] = (char*)malloc(col * sizeof(char));
		}
	
		matrix_reader(M, &row, &col);
		#ifdef __APPLE__
			system("clear");
		#elif __unix__
			system("clear");
		#endif

        matrix_player(M, &row, &col);              //modifica la matrice facendo muovere il giocatore
		for(int i = 0; i < row; i++){
			free(M[i]);
		}
		free(M);
		return 0;
	}
    if(selection == 2){           //--challenge branch (IA)
		int row = 0;
		int col = 0;
		#ifdef __APPLE__
			MS = milliseconds_calculator();
		#endif
		scanf("%d\n%d\n", &col, &row);
		

    
		char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
		for(int i = 0; i < row; i++){
			M[i] = (char*)malloc(col * sizeof(char));
		}
	
		matrix_reader(M, &row, &col);
		string_t *pattern_history = s_create();
        string_t *moves = s_create();  
		vector_global *check_global= v_global_create();
		v_global_push_back (check_global, vertical_global, orizzontal_global); 
		v_global_push_back (check_global, vertical_global, orizzontal_global);
		labyrint_global_direction(M, &row, &col, check_global);		
		labyrint_analysis(M, &row, &col, moves, check_global, pattern_history);             //IA
		s_print(moves);
		s_free(moves);
		s_free(pattern_history);
		v_global_free(check_global);
        for(int i = 0; i < row; i++){
			free(M[i]);
		}
		free(M);
		return 0;
    }
	
	
}
