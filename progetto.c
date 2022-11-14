
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WALL    '#'


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
                M[i][j] = WALL;
            }
            if(j == 0 || j == col - 1){         //sinistra-destra
                M[i][j] = WALL;
            }
        }
    }

    for(int i = 1; i <= row - 4; i++){          //crea primo separatore
        M[i][5] = WALL;
    }


    for(int i = row - 1; i >= row - 7; i--){    //crea secondo separatore
        M[i][12] = WALL;
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




void labyrinth_player(char **M,int *row,int *col){
    char c = '\0';
    int g_row = 1;
    int g_col = 0;
    int points = 112;
    M[g_row][g_col] = 'o';  //giocatore


    system("clear");
    for(int i = 0; i < *row; i++){
        for(int j = 0; j < *col; j++){              //stampa labirinto di partenza
            printf("%c", M[i][j]);
        }
        printf("\n");
    }
    
    while((c != 'q')){          //muove pedina
        system("stty raw");
        c = getchar();
        if(c == 'w' && M[g_row-1][g_col] != WALL && g_row-1 >= 0){           //muove pedina in su
            if(M[g_row-1][g_col] == '$')
                points+=3;
            if(M[g_row-1][g_col] == '!')
                points /= 2;
            M[g_row-1][g_col] = 'o';
            M[g_row][g_col] = ' ';
            g_row--;
            points--;
        }
        if(c == 's' && M[g_row+1][g_col] != WALL && g_row+1 >= 0){           //uove pedina in giù
            if(M[g_row+1][g_col] == '$')
                points+=3;
            if(M[g_row+1][g_col] == '!')
                points /= 2;
            M[g_row+1][g_col] = 'o';
            M[g_row][g_col] = ' ';
            g_row++;
            points--;
        }
        if(c == 'a' && M[g_row][g_col-1] != WALL && g_col-1 >= 0){           //muove pedina a sinistra
            if(M[g_row][g_col-1] == '$')
                points+=3;
            if(M[g_row][g_col-1] == '!')
                points /= 2;
            M[g_row][g_col-1] = 'o';
            M[g_row][g_col] = ' ';
            g_col--;
            points--;
        }
        if(c == 'd' && M[g_row][g_col+1] != WALL && g_col+1 >= 0){           //muove pedina a destra
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
        
        
        if(c != '\n'){              //stampa labirinto aggiornato di 1 mossa
            system("clear");
            for(int i = 0; i < *row; i++){
                for(int j = 0; j < *col; j++){       
                    printf("%c", M[i][j]);
                }
                printf("\n");
            }
            
            if(points < 0)
                points = 0;


            if(points > 100)
                printf("Score: 100\n");
            else
                printf("Score: %d\n", points);

        }
        if(points < 0)
           points = 0;
        if(M[5][18] == 'o'){
            printf("Vittoria!!!\n");
            
            break;
        }
    }
  
}

int main(int argc, char * argv[]){
//891868 895662

if(argc == 2 && strcmp(argv[1], "--challenge") == 0){       //cambia comportamento del main se viene 
    printf("%d\n%s\n", argc, argv[1]);                      //parametro "--challenge" in esecuzione
    return 0;                                               //qui ora al posto della printf(test)
                                                            //basta inserire la funzione che gestisce la IA
}
    int row = 10;
    int col = 19;
    char **M = (char**) malloc(row * sizeof(char*));

    for(int i = 0; i < col; i++){
        M[i] = (char*) malloc(col * sizeof(char));  //alloca matrice
    }



    labyrinth_initializer(M);                //inizializza la matrice labirinto
    labyrinth_player(M, &row, &col);         //modifica la matrice facendo muovere il giocatore
    return 0;
}
