/* libreria per vector_t */


typedef struct vector vector_t;
typedef struct string string_t;

struct string{
    size_t size;
    char *string;
    int *moves;
};




struct vector{
    size_t size;
    int *row;
    int *col;
};


string_t *s_create(){
    string_t *s = (string_t*)malloc(sizeof(string_t));
    s->size = 0;
    return s;
}

struct vector *v_create(){
    vector_t *v = (vector_t*)malloc(sizeof(vector_t));
    v->size = 0; //inizializzo
    return v;
}





void v_push_back(vector_t *v, int x, int y){      //aggiungi valori row e col alla coda del vettore
    if(v->size == 0){
        v->row = (int *)malloc(1*sizeof(int));
        v->col = (int *)malloc(1*sizeof(int));
    }else{
        v->row = realloc(v->row, (v->size+1)*sizeof(int));
        v->col = realloc(v->col, (v->size+1)*sizeof(int));
    }
    v->row[v->size] = x;
    v->col[v->size] = y;
    v->size++;
}

void s_push_back(string_t *s, char c, int x){
    if(s->size == 0){
        s->string = (char*)malloc(1*sizeof(char));
        s->moves = (int *)malloc(1*sizeof(int));
    }else{
        s->string = realloc(s->string, (s->size+1)*sizeof(char));
        s->moves = realloc(s->moves, (s->size+1)*sizeof(int));
    }
    s->moves[s->size] = x;
    s->string[s->size] = c;
    s->size++;
}


void v_push_front(vector_t * v, int x, int y){      //aggiungi valori alla testa del vettore
    if(v->size == 0){
        v->row = (int *)malloc(1*sizeof(int));
        v->col = (int *)malloc(1*sizeof(int));
        v->row[0] = x;
        v->col[0] = y;
        v->size++;
    }else{
        v->row = realloc(v->row, (v->size+1)*sizeof(int));
        v->col = realloc(v->col, (v->size+1)*sizeof(int));
        for(int i = v->size; i > 0; i--){
            v->row[i] = v->row[i-1];
            v->col[i] = v->col[i-1];
        }
        v->row[0] = x;
        v->col[0] = y;
        v->size++;
    }

}

void s_push_front(string_t *s, char c, int x){
    if(s->size == 0){
        s->string = (char *)malloc(1*sizeof(char));
        s->moves = (int *)malloc(1*sizeof(int));
        s->moves[0] = x;
        s->string[0] = c;
        s->size++;
    }else{
        s->string = realloc(s->string, (s->size+1)*sizeof(char));
        s->moves = realloc(s->moves, (s->size+1)*sizeof(int));
        for(int i = s->size; i > 0; i--){
            s->string[i] = s->string[i-1];
        }
        s->moves[0] = x;
        s->string[0] = c;
        s->size++;
    }
}




void v_free(vector_t *v){                          //libera la memoria allocata di un vector_t
    if(v->size != 0){
        free(v->row);
        free(v->col);
    }
    free(v);
}

void s_free(string_t *s){
    if(s->size != 0){
        free(s->moves);
        free(s->string);
    }
    free(s);
}


void v_pop_back(vector_t *v){
    v->size--;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
}


void s_pop_back(string_t *s){
    s->size--;
    s->string = realloc(s->string, (s->size)*sizeof(char));
    s->moves = realloc(s->moves, (s->size)*sizeof(int));
}



void v_pop_front(vector_t *v){                          //rimuove il primo elemento del vettore
    for(int i = 0; i < v->size-1; i++){
        v->row[i] = v->row[i+1];
        v->col[i] = v->col[i+1];
    }
    v->size--;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
}

void s_pop_front(string_t *s){
    for(int i = 0; i < s->size-1; i++){
        s->string[i] = s->string[i+1];
        s->moves[i] = s->moves[i+1];
    }
    
    s->size--;
    s->string = realloc(s->string, (s->size)*sizeof(char));
    s->moves = realloc(s->moves, (s->size)*sizeof(int));
}





void v_pop_elem(vector_t *v, size_t index){             //rimuove l'elemento in posizione index (0->size-1)
    if(index >= v->size){
        printf("Error: index out of vector bounds\n");
        exit(EXIT_FAILURE);
    }
    for(int i = index; i < v->size; i++){
        v->row[i] = v->row[i+1];
        v->col[i] = v->col[i+1];
    }
    v->size--;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
}


void s_pop_elem(string_t *s, size_t index){
    if(index >= s->size){
        printf("Error: index out of string bounds\n");
        exit(EXIT_FAILURE);
    }
    for(int i = index; i < s->size; i++){
        s->string[i] = s->string[i+1];
        s->moves[i] = s->moves[i+1];
    }
    s->size--;
    s->string = realloc(s->string, (s->size)*sizeof(char));
    s->moves = realloc(s->moves, (s->size)*sizeof(int));
}



void v_cut(vector_t *v, size_t index){                  //rimuove tutti gli elementi da index in poi
    if(index > v->size){
        printf("Error: index out of vector bounds");
        exit(EXIT_FAILURE);
    }
    v->size = index;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
}


void s_cut(string_t *s, size_t index){
    if(index > s->size){
        printf("Error: index out of string bounds");
        exit(EXIT_FAILURE);
    }
    s->size = index;
    s->string = realloc(s->string, (s->size)*sizeof(char));
    s->moves = realloc(s->moves, (s->size)*sizeof(int));
}




void v_cut_front(vector_t *v, size_t index){            //rimuove tutti gli elementi dal primo a index
    if(index >= v->size){
        printf("Error: index out of vector bounds");
        exit(EXIT_FAILURE);
    }
    for(int i = index; i < v->size; i++){
        v->row[i - index] = v->row[i+1];
        v->col[i - index] = v->col[i+1];
    }
    v->size = v->size - index - 1;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
}


void s_cut_front(string_t *s, size_t index){
    if(index > s->size){
        printf("Error: index out of string bounds");
        exit(EXIT_FAILURE);
    }
    for(int i = index; i < s->size; i++){
        s->string[i - index] = s->string[i+1];
        s->moves[i - index] = s->moves[i+1];
    }
    s->size = s->size - index - 1;
    s->string = realloc(s->string, (s->size)*sizeof(char));
    s->moves = realloc(s->moves, (s->size)*sizeof(int));
}




void v_print(vector_t *v){                              //stampa a schermo un vector_t
    printf("{ ");
    for(int i = 0; i < v->size; i++){
        printf("\n(%d, %d)", v->row[i], v->col[i]);
    }
    printf("\n}\n");
}

void s_print(string_t *s){
    printf("{ ");
    for(int i = 0; i < s->size; i++){
        printf("\n(%c, %d)", s->string[i], s->moves[i]);
    }
    printf("\n}\n");
}
