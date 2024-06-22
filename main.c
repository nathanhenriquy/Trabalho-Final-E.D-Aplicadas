#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 100

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
} ArrayDina;


typedef struct {
    Movie *data;
    int size;
    int capacity;
} ListAdja;

void initArray(ArrayDina *a) {
    a->data = malloc(CAPACIDADE_INICIAL * sizeof(Actor));
    a->size = 0;
    a->capacity = CAPACIDADE_INICIAL;
}

void insertArray(ArrayDina *a, Actor actor) {
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, a->capacity * sizeof(Actor));
    }
    a->data[a->size++] = actor;
}

void initListAdja(ListAdja *la) {
    la->data = malloc(CAPACIDADE_INICIAL * sizeof(Movie));
    la->size = 0;
    la->capacity = CAPACIDADE_INICIAL;
}

void insertListAdja(ListAdja *la, Movie movie) {
    if (la->size == la->capacity) {
        la->capacity *= 2;
        la->data = realloc(la->data, la->capacity * sizeof(Movie));
    }
    la->data[la->size++] = movie;
}



// ===== ESTRUTURA DE STRUCS E INICIALIZAÇÕES A CIMA =====



void lerActorsFile(ArrayDina *actors, const char *filename) {

    FILE *file = fopen(filename, "r");
        
    char line[1024];
    fgets(line, sizeof(line), file);

    int counter = 0;

    while (fgets(line, sizeof(line), file) && counter < 50) { // CASO QUEIRA TESTAR COM MENORES DADOS, MUDAR NUMERO DO COUNTER
        char nconst[10];
        char primaryName[100];
        char knownForTitles[100];

        sscanf(line, "%[^\t]\t%[^\t]\t%[^\n]", nconst, primaryName, knownForTitles);

        Actor actor;
        actor.id = atoi(nconst + 2); 

        actor.name = malloc(strlen(primaryName) + 1);
        if (actor.name != NULL) {
            strcpy(actor.name, primaryName);
        }
        
        actor.movies = NULL;
       
        
        char *token = strtok(knownForTitles, ",");        
        while (token != NULL) {
            Node *movie = malloc(sizeof(Node));
            movie->id = atoi(token + 2); 
            movie->next = actor.movies;
            actor.movies = movie;
            token = strtok(NULL, ",");
        }

        insertArray(actors, actor);
        counter++;
    }
    
    fclose(file);
}

        

void lerMoviesFile(ListAdja *movies, const char *filename) {

    FILE *file = fopen(filename, "r");
   
    char line[1024];

    fgets(line, sizeof(line), file); 
    
    while (fgets(line, sizeof(line), file)) {
        char tconst[10];
        char type[10];
        char primaryTitle[100];
        char restoDaLinha[100]; // CRIEI POIS ESTAVA INDO JUNTO NA HORA DE ESCREVER NO DOT

        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]", tconst, type, primaryTitle, restoDaLinha);

        if (strcmp(type, "movie") == 0) {
            Movie movie;
            movie.id = atoi(tconst + 2);

            movie.title = malloc(strlen(primaryTitle) + 1);
            if (movie.title != NULL) {
                strcpy(movie.title, primaryTitle);
            }
            
            movie.neighbors = NULL;
            insertListAdja(movies, movie);
        }
    }
    
    fclose(file);
}



void addAresta(Movie *movies, int size, int id1, int id2) {

    Movie *movie1 = NULL, *movie2 = NULL;

    for (int i = 0; i < size; i++) {
        if (movies[i].id == id1) {
            movie1 = &movies[i];
        }
        if (movies[i].id == id2) {
            movie2 = &movies[i];
        }
    }
    if (movie1 && movie2) {
        Node *newNeighbor1 = malloc(sizeof(Node));
        newNeighbor1->id = id2;
        newNeighbor1->next = movie1->neighbors;
        movie1->neighbors = newNeighbor1;

        Node *newNeighbor2 = malloc(sizeof(Node));
        newNeighbor2->id = id1;
        newNeighbor2->next = movie2->neighbors;
        movie2->neighbors = newNeighbor2;
    }
}

void formarGrafo(ArrayDina *actors, ListAdja *movies) {

    for (int i = 0; i < actors->size; i++) {
        Node *movie1 = actors->data[i].movies;

        while (movie1 != NULL) {
            Node *movie2 = movie1->next;
            while (movie2 != NULL) {
                addAresta(movies->data, movies->size, movie1->id, movie2->id);
                movie2 = movie2->next;
            }
            movie1 = movie1->next;
        }
    }
}


const char* getMovieTitle(Movie *movies, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (movies[i].id == id) {
            return movies[i].title;
        }
    }
    return NULL;
}



void desenharDot(ListAdja *movies, const char *filename) {

    FILE *file = fopen(filename, "w");
       
    fprintf(file, "graph {\n");
    fprintf(file, "  concentrate=true;\n");

    for (int i = 0; i < movies->size; i++) {
        Node *neighbor = movies->data[i].neighbors;
        
        while (neighbor != NULL) {
            if (movies->data[i].id < neighbor->id) { 
                const char *title1 = getMovieTitle(movies->data, movies->size, movies->data[i].id);
                const char *title2 = getMovieTitle(movies->data, movies->size, neighbor->id);
                if (title1 && title2) {
                   
                    fprintf(file, "  \"%s\" -- \"%s\";\n", title1, title2);
                }
            }
            neighbor = neighbor->next;
        }
    }

    fprintf(file, "}\n");
    fclose(file);
}



// ===== LIBERAÇÕES ABAIXO =====



void freeList(Node *node) {
    while (node != NULL) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
}

void freeArray(ArrayDina *actors) {
    for (int i = 0; i < actors->size; i++) {
        free(actors->data[i].name);
        freeList(actors->data[i].movies);
    }
    free(actors->data);
}

void freeListAdja(ListAdja *movies) {
    for (int i = 0; i < movies->size; i++) {
        free(movies->data[i].title);
        freeList(movies->data[i].neighbors);
    }
    free(movies->data);
}


// ===== LIBERAÇÕES A CIMA =====



int main() {

    ArrayDina actors;
    ListAdja movies;

    initArray(&actors);
    initListAdja(&movies);

    lerActorsFile(&actors, "name.basics.tsv");
    lerMoviesFile(&movies, "title.basics.tsv");

    formarGrafo(&actors, &movies);

    desenharDot(&movies, "input.dot");

    printf("== CONCLUIDO ==");

    freeArray(&actors);
    freeListAdja(&movies);

    return 0;
}
