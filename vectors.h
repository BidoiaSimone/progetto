/* libreria per vector_t */


typedef struct vector vector_t;


struct vector{
    size_t size;
    int *row;
    int *col;
};

struct vector *v_create(){
    struct vector *v = (struct vector*)malloc(sizeof(struct vector));
    v->size = 0; //inizializzo
    return v;
}






void v_push_back(struct vector * v, int x, int y){      //aggiungi valori row e col alla coda del vettore
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


void v_push_front(struct vector * v, int x, int y){      //aggiungi valori alla testa del vettore
    if(v->size == 0){
        v->row = (int *)malloc(1*sizeof(int));
        v->col = (int *)malloc(1*sizeof(int));
        v->row[0] = x;
        v->col[0] = y;
        v->size++;
    }else{
        v->row = realloc(v->row, (v->size+1)*sizeof(int));
        v->col = realloc(v->col, (v->size+1)*sizeof(int));
        for(int i = v->size-1; i > 0; i--){
            v->row[i] = v->row[i-1];
            v->col[i] = v->col[i-1];
        }
        v->row[0] = x;
        v->col[0] = y;
        v->size++;
    }

}





void v_free(struct vector *v){                          //libera la memoria allocata di un vector_t
    if(v->size != 0){
        free(v->row);
        free(v->col);
    }
    free(v);
}


void v_pop_back(vector_t *v){
    v->size--;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
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






void v_cut(vector_t *v, size_t index){                  //rimuove tutti gli elementi da index in poi
    if(index >= v->size){
        printf("Error: index out of vector bounds");
        exit(EXIT_FAILURE);
    }
    v->size = index;
    v->row = realloc(v->row, (v->size)*sizeof(int));
    v->col = realloc(v->col, (v->size)*sizeof(int));
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







void v_print(vector_t *v){                              //stampa a schermo un vector_t
    printf("{ ");
    for(int i = 0; i < v->size; i++){
        printf("\n(%d, %d)", v->row[i], v->col[i]);
    }
    printf("\n}\n");
}
