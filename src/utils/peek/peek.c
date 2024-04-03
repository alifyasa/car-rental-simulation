#include "peek.h"

double* peek_transfer;
struct master *peek_row = NULL;

void init_peek(){
    peek_transfer = (double *) calloc (maxatr + 1, sizeof (double));
}

void peek_first(int list){
    peek_row = head[list];
    free ((char *) peek_transfer);
    peek_transfer = (*peek_row).value;
    free ((char *) peek_row);
}
