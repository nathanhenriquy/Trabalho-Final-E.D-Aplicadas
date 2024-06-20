#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int index_film;
    int id;
    char *name;
    struct node *next;
} node;

node* construtor_node(int index, int id, char *name, node *next) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->index_film = index;
    new_node->name = name;
    new_node->id = id;
    new_node->next = next;
    return new_node;
}


//=== NODE ACIMA


typedef struct{ 
    int id;
    char *title;
    node *neighbors;
} movie;

movie construtor_movie(int id, char *title, node *next) {
    movie new_movie;
    new_movie.id = id;
    new_movie.title = title;
    new_movie.neighbors = next;
    return new_movie;
}


//=== FILMES ACIMA


typedef struct {
    int id;
    char *name;
    node *movies;
} actor;

actor construtor_actor(int id, char *name, char *movies) {
    actor new_actor;
    new_actor.id = id;
    new_actor.name = name;
    new_actor.movies = movies;
    return new_actor;
}


//=== ATORES ACIMA


typedef struct {
    int size;
    int capacity;   
    actor *actors;
} array__actors;

array__actors* construtor_array_actors() {
    array__actors *new_array = (array__actors*)malloc(sizeof(array__actors));
    new_array->capacity = 0;
    new_array->size = 0;
    new_array->actors = NULL;
    return new_array;
}


//===ARRAY DE ATORES ACIMA



typedef struct {
    int size;
    int capacity;
    movie *movies;
} array__movies;

array__movies*construtor_array_movie() {
    array__movies *new_array = malloc(sizeof(array__movies));
    new_array->size = 0;
    new_array->capacity = 0;
    new_array->movies = NULL;
    return new_array;
}


//===ARRAY DE FILMES ACIMA

