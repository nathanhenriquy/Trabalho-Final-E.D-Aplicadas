#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 10

// ===== ESTRUTURA DE STRUCS E INICIALIZAÇÕES ABAIXO =====

typedef struct Node {
    int id;
    struct Node *next;
} Node;

typedef struct {
    int id;
    char *name;
    Node *movies;
} Actor;

typedef struct {
    int id;
    char *title;
    Node *neighbors;
} Movie;

typedef struct {
    Actor *data;
    int size;
    int capacity;
} DynamicArray;


typedef struct {
    Movie *data;
    int size;
    int capacity;
} AdjList;

void initArray(DynamicArray *a) {
    a->data = malloc(CAPACIDADE_INICIAL * sizeof(Actor));
    a->size = 0;
    a->capacity = CAPACIDADE_INICIAL;
}

void insertArray(DynamicArray *a, Actor actor) {
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, a->capacity * sizeof(Actor));
    }
    a->data[a->size++] = actor;
}

void initAdjList(AdjList *al) {
    al->data = malloc(CAPACIDADE_INICIAL * sizeof(Movie));
    al->size = 0;
    al->capacity = CAPACIDADE_INICIAL;
}

void insertAdjList(AdjList *al, Movie movie) {
    if (al->size == al->capacity) {
        al->capacity *= 2;
        al->data = realloc(al->data, al->capacity * sizeof(Movie));
    }
    al->data[al->size++] = movie;
}



// ===== ESTRUTURA DE STRUCS E INICIALIZAÇÕES A CIMA =====


