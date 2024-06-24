#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define CAPACIDADE_INICIAL 100





int main() {

    ArrayDina actors;
    ListAdja movies;

    initArray(&actors);
    initListAdja(&movies);

    printf("== ESPERAR MENSAGEM DE CONCLUIDO ==");

    lerActorsFile(&actors, "name.basics.tsv");
    lerMoviesFile(&movies, "title.basics.tsv");

    formarGrafo(&actors, &movies);

    desenharDot(&movies, "input.dot");

     printf("\n\n== CONCLUIDO ==");

    freeArray(&actors);
    freeListAdja(&movies);

    return 0;
}
