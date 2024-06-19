#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== STRUCTS EMBAIXO ===== */

typedef struct
{
    int movie_id;
    struct node *next;
} node;

struct node *create_node(int id)
{
    node *new_node = (node*) malloc (sizeof(node));
    new_node->movie_id = id;
    new_node->next = NULL;
}



typedef struct
{
    int id;
    char *name;
    struct node *movies;
} actor;

actor construtor_actor(int id, char *name, char *movies)
{
    actor new_actor;
    new_actor.id = id;
    new_actor.name = name;
    new_actor.movies = movies;
    return new_actor;
}



typedef struct
{
    int id;
    char *title;
    node *neighbors;
} movie;

movie construtor_movie(int id, char *title, node *next)
{
    movie new_movie;
    new_movie.id = id;
    new_movie.title = title;
    new_movie.neighbors = next;
    return new_movie;
}




/* ===== STRUCTS EM CIMA ===== */





int main()
{

    return 0;
}
