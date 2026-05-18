#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int id;
    struct Nod *urm;
} NOD;

typedef struct Graf {
    int nr_noduri;
    int *vizitat;
    NOD **liste;
} GRAF;

NOD *creeaza_nod(int id) {
    NOD *nou = malloc(sizeof(NOD));
    nou->id = id;
    nou->urm = NULL;
    return nou;
}

GRAF *creeaza_graf(int nr_noduri) {
    GRAF *g = malloc(sizeof(GRAF));
    g->nr_noduri = nr_noduri; // aici am corectat,
    g->liste = malloc(nr_noduri * sizeof(NOD *)); 
    g->vizitat = malloc(nr_noduri * sizeof(int));

    for (int i = 0; i < nr_noduri; i++) {
        g->liste[i] = NULL;
        g->vizitat[i] = 0;
    }
    return g;
}

void adauga_muchie(GRAF *g, int src, int dest) {
    NOD *nou = creeaza_nod(dest);
    nou->urm = g->liste[src];
    g->liste[src] = nou;

    nou = creeaza_nod(src);
    nou->urm = g->liste[dest];
    g->liste[dest] = nou;
}

void citeste_muchii(GRAF *g, int nr_muchii) {
    int src, dest;
    printf("Adauga %d muchii (0 - %d):\n", nr_muchii, g->nr_noduri - 1);
    for (int i = 0; i < nr_muchii; i++) {
        scanf("%d %d", &src, &dest);
        if (src >= 0 && src < g->nr_noduri && dest >= 0 && dest < g->nr_noduri) {
            adauga_muchie(g, src, dest);
        } else {
            printf("Invalide! Reintrodu muchia %d.\n", i + 1);
            i--; // Reincercam citirea pentru aceeasi muchie, aici am corectat
        }
    }
}

void reseteaza_vizitat(GRAF *g) {
    for (int i = 0; i < g->nr_noduri; i++) {
        g->vizitat[i] = 0;
    }
}

int DFS(GRAF *g, int curent, int dest) {
    if (curent == dest) return 1;
    g->vizitat[curent] = 1;

    NOD *temp = g->liste[curent];
    while (temp != NULL) {
        if (g->vizitat[temp->id] == 0) {
            if (DFS(g, temp->id, dest)) return 1;
        }
        temp = temp->urm;
    }
    return 0;
}

int main() {
    int nr_noduri, nr_muchii, start, destinatie;

    printf("Cate restaurante? ");
    scanf("%d", &nr_noduri);
    printf("Cate muchii? ");
    scanf("%d", &nr_muchii);

    GRAF *g = creeaza_graf(nr_noduri);
    citeste_muchii(g, nr_muchii);

    printf("\nVerificare drum (0 - %d):\nStart: ", nr_noduri - 1);
    scanf("%d", &start);
    printf("Destinatie: ");
    scanf("%d", &destinatie);

    reseteaza_vizitat(g); // curatam vectorul de vizitati

    if (DFS(g, start, destinatie)) {
        printf("Exista drum intre %d si %d.\n", start, destinatie);
    } else {
        printf("NU exista drum intre %d si %d.\n", start, destinatie);
    }

    return 0;
}