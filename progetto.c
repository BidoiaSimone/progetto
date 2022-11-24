// 891868 895662

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



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


void labyrint_analysis( char **M, int *row, int *col){  //usata per risolvere labirinti consegna 18/11/22
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

        matrix_reader(M, &row, &col);                 //legge un labirinto da input terminale
        labyrint_analysis(M, &row, &col);             //analizza il labirinto dicendo una soluzione (no pareti)

        return 0;

    }else{
        //labyrinth_initializer(M); inizializzava la matrice come il primo labirinto proposto dai prof, ora obsoleta
        matrix_reader(M, &row, &col);                 //legge un labirinto da input terminale
        labyrinth_player(M, &row, &col);              //modifica la matrice facendo muovere il giocatore
        return 0;
    }

	return 0;
	
}


/* ho implementato le one-way-door che volevo, purtroppo il char è troppo piccolo per rappresentare
le freccette ↑, ←, →, ↓, o usiamo una var più grande (int stampato come %c) oppure  per ora ho usato
v, ^, <, >.
*/


/*
if(M[g_row-1][g_col] == '^'){
                M[g_row][g_col] = ' ';
                while(M[g_row-1][g_col] == '^'){
                    g_row--;
                }
                
                M[g_row][g_col] = '^';
                M[g_row-1][g_col] = 'o';
                g_row--;

            }else{
                if(M[g_row-1][g_col] == '!' || M[g_row-1][g_col] == '$' || M[g_row-1][g_col] == ' '){//fine if
                    M[g_row-1][g_col] = 'o';
                    M[g_row][g_col] = ' ';
                    g_row--;
                    points--;
                }
            }
            */

