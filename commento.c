//per comodità scriviamo una nuova funzione copiando i pezzi che possiamo riutilizzare 


/*void labyrint_analysis( char **M, int *row, int *col, string_t *moves){

	int g_row;	//giocatore row
	int g_col;	//giocatore col
	int w_row;	//win row
	int w_col;	//win col

	
							vector_t *tail = v_create();
	bool global_direction_priority; //se = 1 propiorità verticale, se = 0 priorità orizzontale
	bool up_move;
	bool down_move;
	bool right_move;
	bool left_move;
	bool finish_check;
	
	

	for(int i = 0; i < *row; i++){
		for(int j = 0; j < *col; j++){
			if(M[i][j] == 'o'){
				g_row = i;
				g_col = j;
				break;
			}
		}
	}

	for(int i = 0; i < *row; i++){
		for(int j = 0; j < *col; j++){
			if(M[i][j] == '_'){
				w_row = i;
				w_col = j;
				break;
			}
		}
	}

	for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col && finish_check == 0; j++){//controlla dove è la posizione di partenza del giocaotore
            if(M[i][j] == '_'){
                w_row = i;
                w_col = j;			
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

	


	if(moves->size >= 2){
		vertical_pattern(moves);
		orizzontal_pattern(moves);
	}
	

	
	
	

	if (g_col==0){   // uscita del giocatore dal bordo
		if( M[g_row][g_col+1] == '$' || M[g_row][g_col+1] == 'T'){ 
			if (M[g_row][g_col+1] == 'T'){
				counter_trivella += 3;
			}
		}
        printf("%c\n",'E');
		s_push_back(moves, 'E', vertical_global, orizzontal_global);
        M[g_row][g_col+1] = 'o';
		M[g_row][g_col] = ' ';
		matrix_printer(M, row, col, tail);
		labyrint_analysis( M, row, col, moves);
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
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
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
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis( M, row, col, moves);
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
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis( M, row, col, moves);
					return;
				}
			}
		}
	}

	// lo sburooooooooooooooooooooooooo controlla se nelle vicinanze c'è l'arrivo
	if( M[g_row][g_col+1] == '_'){ //controllo se nelle coordinate col+-1 e row+-1 c'è '_'
	printf("_%c\n", 'E');
	s_push_back(moves, 'E', vertical_global, orizzontal_global);
	M[g_row][g_col+1] = 'o';
	M[g_row][g_col] = ' ';
	matrix_printer(M, row, col, tail);
	labyrint_analysis(M, row, col, moves);
	return;
	}else{
		if(M[g_row][g_col-1] == '_'){
			printf("_%c\n", 'O');
			s_push_back(moves, 'O', vertical_global, orizzontal_global);
			M[g_row][g_col-1] = 'o';
			M[g_row][g_col] = ' ';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		}else{
			if(M[g_row+1][g_col] == '_'){
				printf("_%c\n", 'S');
				s_push_back(moves, 'S', vertical_global, orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}else{
				if(M[g_row-1][g_col] == '_'){
					printf("_%c\n", 'N');
					s_push_back(moves, 'N', vertical_global, orizzontal_global);
					M[g_row-1][g_col] = 'o';
					M[g_row][g_col] = ' ';
					matrix_printer(M, row, col, tail);
					labyrint_analysis(M, row, col, moves);
					return;
				}
			}
		}
	}



	if (M[g_row][g_col+1] == '#'  &&  counter_trivella  == 0){
			right_move = 0;
		}else{
			right_move = 1;
		}
		if(M[g_row][g_col-1] == '#'  &&  counter_trivella == 0){
			left_move = 0;
		}else{
			left_move = 1;
		}
		if(M[g_row+1][g_col] == '#'  &&  counter_trivella == 0){
			down_move = 0;
		}else{
			down_move = 1;
		}
		if(M[g_row-1][g_col] == '#'  &&  counter_trivella == 0){
			up_move = 0;
		}else{
			up_move = 1;
		}

	if(up_move == 0 && right_move == 0 && down_move == 0){		//check vicolo ceco
		printf("%c\n", 'O');
		s_pop_back(moves);
		M[g_row][g_col-1] = 'o';
		M[g_row][g_col] = '#';
		matrix_printer(M, row, col, tail);
		labyrint_analysis(M, row, col, moves);
		return;
	}else{
		if(left_move == 0 && right_move == 0 && down_move == 0){
			printf("%c\n", 'N');
			s_pop_back(moves);
			M[g_row-1][g_col] = 'o';
			M[g_row][g_col] = '#';
			matrix_printer(M, row, col, tail);
			labyrint_analysis(M, row, col, moves);
			return;
		}else{
			if(left_move == 0 && up_move == 0 && down_move == 0){
				printf("%c\n", 'E');
				s_pop_back(moves);
				M[g_row][g_col+1] = 'o';
				M[g_row][g_col] = '#';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}else{
				if(left_move == 0 && up_move == 0 && right_move == 0){
					printf("%c\n", 'S');
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




	
	if(abs(g_row - w_row) >= abs(g_col - w_col)){
		global_direction_priority = 1;				//priorità vertical_global
	}else{
		global_direction_priority = 0;				//priorità orizzontal_global
	}

	if(global_direction_priority == 1){		//verticale

		if(vertical_global == 1){	//su
			if(up_move == 1){
				printf("%c\n",'N');
				s_push_back(moves, 'N', vertical_global, orizzontal_global);
				M[g_row-1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis( M, row, col, moves);
				return;
			}else{
				if(orizzontal_global == 1){	//dx
					if(right_move == 1){
						printf("%c\n",'E');
						s_push_back(moves, 'E', vertical_global, orizzontal_global);
						M[g_row][g_col+1] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'E'){
							printf("%c\n",'S');
							s_push_back(moves, 'S', vertical_global, orizzontal_global);
							M[g_row+1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'N'){
							printf("%c\n",'O');
							s_push_back(moves, 'O', vertical_global, orizzontal_global);
							M[g_row][g_col-1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis(M, row, col, moves);
							return;
						}
					}
				}
				if(orizzontal_global == -1){	//sx
					if(left_move == 1){
						printf("%c\n",'O');
						s_push_back(moves, 'O', vertical_global, orizzontal_global);
						M[g_row][g_col-1] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis(M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'O'){
							printf("%c\n",'S');
							s_push_back(moves, 'S', vertical_global, orizzontal_global);
							M[g_row+1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'N'){
							printf("%c\n",'E');
							s_push_back(moves, 'E', vertical_global, orizzontal_global);
							M[g_row][g_col+1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
					}
				}
			}
		}else{	//if(vertical_global == -1)
			if(down_move == 1){
				printf("%c\n",'S');
				s_push_back(moves, 'S', vertical_global, orizzontal_global);
				M[g_row+1][g_col] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis( M, row, col, moves);
				return;
			}else{
				if(orizzontal_global == 1){	//dx
					if(right_move == 1){
						printf("%c\n",'E');
						s_push_back(moves, 'E', vertical_global, orizzontal_global);
						M[g_row][g_col+1] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'S'){
							printf("%c\n",'O');
							s_push_back(moves, 'O', vertical_global, orizzontal_global);
							M[g_row][g_col-1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis(M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'E'){
							printf("%c\n",'N');
							s_push_back(moves, 'N', vertical_global, orizzontal_global);
							M[g_row-1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
					}
				}
				if(orizzontal_global == -1){
					if(left_move == 1){
						printf("%c\n",'O');
						s_push_back(moves, 'O', vertical_global, orizzontal_global);
						M[g_row][g_col-1] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis(M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'S'){
							printf("%c\n",'E');
							s_push_back(moves, 'E', vertical_global, orizzontal_global);
							M[g_row][g_col+1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'O'){
							printf("%c\n",'N');
							s_push_back(moves, 'N', vertical_global, orizzontal_global);
							M[g_row-1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
					}
				}
			}
		}
	}		
		
	

	
	if(global_direction_priority == 0){ //orizzonatale

		if(orizzontal_global == 1){	//dx
			if(right_move == 1){
				printf("%c\n",'E');
				s_push_back(moves, 'E', vertical_global, orizzontal_global);
				M[g_row][g_col+1] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis( M, row, col, moves);
				return;
			}else{
				if(vertical_global == 1){
					if(up_move == 1){
						printf("%c\n",'N');
						s_push_back(moves, 'N', vertical_global, orizzontal_global);
						M[g_row-1][g_col] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'E'){
							printf("%c\n",'S');
							s_push_back(moves, 'S', vertical_global, orizzontal_global);
							M[g_row+1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'N'){
							printf("%c\n",'O');
							s_push_back(moves, 'O', vertical_global, orizzontal_global);
							M[g_row][g_col-1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis(M, row, col, moves);
							return;
						}
					}
				}
				if(vertical_global == -1){
					if(down_move == 1){
						printf("%c\n",'S');
						s_push_back(moves, 'S', vertical_global, orizzontal_global);
						M[g_row+1][g_col] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'E'){
							printf("%c\n",'N');
							s_push_back(moves, 'N', vertical_global, orizzontal_global);
							M[g_row-1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'S'){
							printf("%c\n",'O');
							s_push_back(moves, 'O', vertical_global, orizzontal_global);
							M[g_row][g_col-1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis(M, row, col, moves);
							return;
						}
					}
				}
			}
		}else{	//if(orizzontal_global == -1)
			if(left_move == 1){
				printf("%c\n",'O');
				s_push_back(moves, 'O', vertical_global, orizzontal_global);
				M[g_row][g_col-1] = 'o';
				M[g_row][g_col] = ' ';
				matrix_printer(M, row, col, tail);
				labyrint_analysis(M, row, col, moves);
				return;
			}else{
				if(vertical_global == 1){
					if(up_move == 1){
						printf("%c\n",'N');
						s_push_back(moves, 'N', vertical_global, orizzontal_global);
						M[g_row-1][g_col] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'O'){
							printf("%c\n",'S');
							s_push_back(moves, 'S', vertical_global, orizzontal_global);
							M[g_row+1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'N'){
							printf("%c\n",'E');
							s_push_back(moves, 'E', vertical_global, orizzontal_global);
							M[g_row][g_col+1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
					}
				}
				if(vertical_global == -1){
					if(down_move == 1){
						printf("%c\n",'S');
						s_push_back(moves, 'S', vertical_global, orizzontal_global);
						M[g_row+1][g_col] = 'o';
						M[g_row][g_col] = ' ';
						matrix_printer(M, row, col, tail);
						labyrint_analysis( M, row, col, moves);
						return;
					}else{
						if(moves->string[moves->size-1] == 'O'){
							printf("%c\n",'N');
							s_push_back(moves, 'N', vertical_global, orizzontal_global);
							M[g_row-1][g_col] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
						if(moves->string[moves->size-1] == 'S'){
							printf("%c\n",'E');
							s_push_back(moves, 'E', vertical_global, orizzontal_global);
							M[g_row][g_col+1] = 'o';
							M[g_row][g_col] = ' ';
							matrix_printer(M, row, col, tail);
							labyrint_analysis( M, row, col, moves);
							return;
						}
					}
				}
			}
		}	
	}
}





void vertical_pattern(string_t *moves, vector_t *check_global){
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
		check_global.vertical_global[0] = vertical_global;
		vertical_global *= -1;
		check_global.vertical_global[1] = vertical_global;
		s_cut(moves, moves->size-2);
	}
	printf("\n----------------------- v_g %d   %d -----------------------\n",vertical_global, ptt);
	s_print(moves);
	return;
}

void orizzontal_pattern(string_t *moves){
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
		check_global.orizzontal_global[0] = orizzontal_global;
		orizzontal_global *= -1;
		check_global.orizzontal_global[1] = orizzontal_global;
		s_cut(moves, moves->size-2);
	}
	printf("\n----------------------- o_g %d   %d -----------------------\n",orizzontal_global, ptt);
	s_print(moves);
	return;
}
*/