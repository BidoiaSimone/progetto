// 891868 895662

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



void matrix_reader(char **M, int *row, int *col){
        int i = 0;

        while(i < *row){
            scanf("%[^\n]%*c", &M[i][0]);
            i++;
        }
}



void labyrinth_initializer(char **M){

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


    system("clear");
    for(int i = 0; i < *row; i++){                   //stampa matrice iniziale
        for(int j = 0; j < *col; j++){      
            printf("%c", M[i][j]);
        }
            printf("\n");
    }   
        printf("\n");
    


    while((c != 'q')){          //muove pedina
        system("stty raw");
        c = getchar();
        if(c == 'w' && M[g_row-1][g_col] != '#' && g_row-1 >= 0){           //muove pedina in su
            if(M[g_row-1][g_col] == '$')
                points+=3;
            if(M[g_row-1][g_col] == '!')
                points /= 2;
            M[g_row-1][g_col] = 'o';
            M[g_row][g_col] = ' ';
            g_row--;
            points--;
        }
        if(c == 's' && M[g_row+1][g_col] != '#' && g_row+1 >= 0){           //muove pedina in giù
            if(M[g_row+1][g_col] == '$')
                points+=3;
            if(M[g_row+1][g_col] == '!')
                points /= 2;
            M[g_row+1][g_col] = 'o';
            M[g_row][g_col] = ' ';
            g_row++;
            points--;
        }
        if(c == 'a' && M[g_row][g_col-1] != '#' && g_col-1 >= 0){           //muove pedina a sinistra
            if(M[g_row][g_col-1] == '$')
                points+=3;
            if(M[g_row][g_col-1] == '!')
                points /= 2;
            M[g_row][g_col-1] = 'o';
            M[g_row][g_col] = ' ';
            g_col--;
            points--;
        }
        if(c == 'd' && M[g_row][g_col+1] != '#' && g_col+1 >= 0){           //muove pedina a destra
            if(M[g_row][g_col+1] == '$')
                points+=3;
            if(M[g_row][g_col+1] == '!')
                points /= 2;
            M[g_row][g_col+1] = 'o';
            M[g_row][g_col] = ' ';
            g_col++;
            points--;
        }
        system("stty cooked");
        
        
        if(c != '\n'){              
            system("clear");
            for(int i = 0; i < *row; i++){                   //stampa matrice aggiornata di 1 mossa
                for(int j = 0; j < *col; j++){      
                        printf("%c", M[i][j]);
                }
                printf("\n");
            }   
        printf("\n");
        }
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



void labyrint_analysis( char **M, int *row, int *col){ 
//iniziallizzo le variabili che mi serviranno per tenere tracia delle 
//coordinate dell'inizio e della fine del labirinto
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
        if (g_col==0){
        	printf("%c",'E');
        	g_col++;
		}
		if (g_col== *col-1){
			printf("%c",'O');
			g_col--;
		}
		if (g_row==0){
			printf("%c",'S');
			g_row++;
		}
		if(g_row== *row-1){
			printf("%c",'N');
			g_row--;
		}
    }

    if(victory_col == 0 || victory_col == (*col-1)){     //se '_' sta in parete verticale, fa prima direzione di altezza
        if(g_row < victory_row){
		    for(int i=0;  i < abs(g_row - victory_row); i++){
    		    printf("%c", 'S');
            }
	    }else{
            for(int i=0;  i < abs(g_row - victory_row); i++){
    		    printf("%c", 'N');
	        }
        }
        if(g_col < victory_col){
    	    for(int i=0;  i < abs(g_col - victory_col); i++){
    		    printf("%c", 'E');
		    }
	    }else{
		    for(int i=0;  i < abs(g_col - victory_col); i++){
    		    printf("%c", 'O');
	        }
        }
    }


    if(victory_row == 0 || victory_row == (*row-1)){    //se '_' sta in parete orizzontale, fa prima direzione di larghezza
        if(g_col < victory_col){
    	    for(int i=0;  i < abs(g_col - victory_col); i++){
    		    printf("%c", 'E');
		    }
	    }else{
		    for(int i=0;  i < abs(g_col - victory_col); i++){
    		    printf("%c", 'O');
	        }
        }
        if(g_row < victory_row){
		    for(int i=0;  i < abs(g_row - victory_row); i++){
    		    printf("%c", 'S');
            }
	    }else{
            for(int i=0;  i < abs(g_row - victory_row); i++){
    		    printf("%c", 'N');
	        }
        }
    }
    printf("%c", '\n');    
}
    
    							//identifico i 4 principali tipi di labirinto 
/*char labyrint_type;
	if (g_col <= victory_col  &&  g_row <= victory_row){
		labyrint_type= 'a';
	}
	if(g_col > victory_col  &&  g_row > victory_row){
		labyrint_type= 'b';
	
	}
	if
	*/

/* mi dipiace per te ma ho paura che i tipi di labirinto se vogliamo farli randomici saranno 16
        arrivo:     giocatore:
        su          su
        su          giu
        su          sx
        su          dx

        giu         su
        giu         giu
        giu         sx
        giu         dx

        sx          su
        sx          giu
        sx          sx
        sx          dx

        dx          su
        dx          giu
        dx          sx
        dx          dx   */



int main(int argc, char * argv[]){



    int row, col;
    scanf("%d\n%d\n", &col, &row);
    
    char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
    for(int i = 0; i < col; i++){
        M[i] = (char*)malloc(col * sizeof(char));
    }


    if(argc == 2 && strcmp(argv[1], "--challenge") == 0){           //--challenge branch (IA)

        matrix_reader(M, &row, &col);
        labyrint_analysis(M, &row, &col);

        return 0;

    }else{
        //labyrinth_initializer(M);
        matrix_reader(M, &row, &col);
        labyrinth_player(M, &row, &col);                //modifica la matrice facendo muovere il giocatore
        return 0;
    }

	return 0;
	
}
