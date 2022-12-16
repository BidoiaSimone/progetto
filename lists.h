/*libreria con le funzioni delle liste vite con Lucchese*/


typedef struct list     list_t;

struct list{                    //list o node
    int row;
    int col;
    struct list *next;
};

list_t * l_create(int x, int y){                       //crea lista con un solo elemento x
    list_t *l = (list_t*)malloc(sizeof(list_t));
    if(l==NULL) exit(EXIT_FAILURE);
    l->row = x;
    l->col = y;
    l->next = NULL;
    return l;
}

void l_append(list_t **l_orig, int x, int y){            //aggiunge in coda
    if(*l_orig==NULL){
        *l_orig = l_create(x, y);
       
    }else{
        list_t *l = *l_orig;
        while(l->next != NULL){
            l = l->next;
        }
        l->next = l_create(x, y);
    }  
}

list_t *array_to_list(int *v, size_t v_size){       //converts an array to a list
    list_t * new_list = NULL;
    for(size_t i = 0; i < v_size; i++){
        l_append(&new_list, v[i], 0);
    }
    return new_list;
}

void l_print(list_t * l){
    printf("{ ");
    int i = 1;
    while(l != NULL){
        if(i % 13 == 0)
            printf("\n");
        printf("(%d, %d) ", l->row, l->col);
        l = l->next;
        i++;
    }
    printf("}\n");
}

void l_free(list_t *l){
    while(l!=NULL){
        list_t * succ = l->next;
        free(l);
        l = succ;
    }
}

bool l_is_in(list_t * l, int x){
    while(l!=NULL){
        if(l->row == x)
            return true;
        else
            if(l->col == x)
                return true;
        l = l->next;
    }
    return false;
}
