#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== STRUCTS EMBAIXO ===== */




typedef struct {
    int movie_id;
    struct node* next;
} node;

typedef struct {
    int id;
    char* name;
    struct node* movies;
} actor;

typedef struct {
    int id;
    char* title;
    struct node* neighbors;
} movie;

struct node* create_node(int id) {
    node* new_node = malloc(sizeof(node));
    new_node->movie_id = id;
    new_node->next = NULL;
}




/* ===== STRUCTS EM CIMA ===== */

int main()
{
    
    return 0;
}
