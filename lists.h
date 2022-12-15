/*libreria con le funzioni delle liste vite con Lucchese*/


typedef struct list     list_t;

struct list{                    //list o node
    int data;
    struct list *next;
};

list_t * l_create(int x){                       //crea lista con un solo elemento x
    list_t *l = (list_t*)malloc(sizeof(list_t));
    if(l==NULL) exit(EXIT_FAILURE);
    l->data = x;
    l->next = NULL;
    return l;
}

void l_append(list_t **l_orig, int v){            //aggiunge in coda
    if(*l_orig==NULL){
        *l_orig = l_create(v);
       
    }else{
        list_t *l = *l_orig;
        while(l->next != NULL){
            l = l->next;
        }
        l->next = l_create(v);
    }  
}

list_t *array_to_list(int *v, size_t v_size){       //converts an array to a list
    list_t * new_list = NULL;
    for(size_t i = 0; i < v_size; i++){
        l_append(&new_list, v[i]);
    }
    return new_list;
}

void l_print(list_t * l){
    printf("{ ");
    while(l != NULL){
        printf("%d ", l->data);
        l = l->next;
    }
    printf(" }\n");
}

void l_free(list_t *l){
    while(l!=NULL){
        list_t * succ = l->next;
        free(l);
        l = l->next;
    }
}

bool l_is_in(list_t * l, int x){
    while(l!=NULL){
        if(l->data == x)
            return true;
        l = l->next;
    }
    return false;
}