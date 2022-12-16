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

void v_free(struct vector *v){
    if(v->size != 0){
        free(v->row);
        free(v->col);
    }
    free(v);
}

vector_t *v_pop_front(vector_t *v){
    vector_t *new_v = v_create();
    new_v->size = v->size-1;
    for(int i = 1; i <= new_v->size; i++){
        new_v->row[i] = v->row[i];
        new_v->col[i] = v->col[i]; 
    }
    free(v);
    return new_v;
}

