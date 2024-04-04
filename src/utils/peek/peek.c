#include "peek.h"

double* peek_transfer;
struct master *peek_row = NULL;

void init_peek(){
    peek_transfer = (double *) calloc (maxatr + 1, sizeof (double));
}

void peek_first(int list){
    if(list_size[list] >= 1) {
        peek_row = head[list];
        peek_transfer = (*peek_row).value;
    } else {
        init_peek();
    }
}
