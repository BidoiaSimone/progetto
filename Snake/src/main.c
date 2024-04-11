#include "snake_lab.c"
#include <stdio.h>


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