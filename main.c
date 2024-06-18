#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== STRUCTS EMBAIXO ===== */




struct node {
    int movieId;
    struct node* next;
};

struct actor {
    int id;
    char* name;
    struct node* movies;
};

struct movie {
    int id;
    char* title;
    struct lista* neighbors;
};




/* ===== STRUCTS EM CIMA ===== */

int main()
{
    
    return 0;
}
