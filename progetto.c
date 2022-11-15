
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void matrix_reader(char **M,int *row,int *col){
        int i = 0;
        int j = 0;
        char c = '\0';
        while(i < *row){
            c = getchar();
            if(c != '\n'){
                M[i][j] = c;
                j++;
            }
            if(c == '\n'){
                i++;
                j = 0;
            }
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
        if(c == 's' && M[g_row+1][g_col] != '#' && g_row+1 >= 0){           //uove pedina in giù
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
        
        
        if(c != '\n'){              //stampa labirinto aggiornato di 1 mossa
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



int main(int argc, char * argv[]){
//891868 895662


    int row, col;
    scanf("%d\n%d\n", &col, &row);
    
    char ** M = (char**)malloc(row * sizeof(char*));     //alloca la matrice
    for(int i = 0; i < col; i++){
        M[i] = (char*)malloc(col * sizeof(char));
    }


    if(argc == 2 && strcmp(argv[1], "--challenge") == 0){           //--challenge branch (IA)

        matrix_reader(M, &row, &col);

        for(int i = 0; i < row; i++){                   //print per test, cancellabile
                for(int j = 0; j < col; j++){      
                        printf("%c", M[i][j]);
                }
                printf("\n");
            }   
        printf("\n");





        return 0;
    }else{
        //labyrinth_initializer(M);
        matrix_reader(M, &row, &col);
        labyrinth_player(M, &row, &col);                       //modifica la matrice facendo muovere il giocatore
        return 0;
    }
    return 0;
}


    
