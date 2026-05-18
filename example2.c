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
    g->nr_noduri = nr_noduri;
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
        // aici am corectat, am scos "*" de la &dest, fiindca scanf are nevoie de adresa variabilei
        scanf("%d %d", &src, &dest);
        
        if (src >= 0 && src < g->nr_noduri && dest >= 0 && dest < g->nr_noduri) {
            adauga_muchie(g, src, dest);
        } else {
            printf("Invalide! Reintrodu muchia %d.\n", i + 1);
            i--;
        }
    }
}

// --- UTILS COADA ---
int coada_goala(NOD *coada) {
    return coada == NULL;
}
// aici am corectat pointer-ul triplu "***coada" cu "**coada"
void enqueue(NOD **coada, int id) {
    NOD *nou = creeaza_nod(id);
    if (coada_goala(*coada)) {
        *coada = nou;
    } else {
        NOD *temp = *coada;
        while (temp->urm) temp = temp->urm;
        temp->urm = nou;
    }
}

int dequeue(NOD **coada) {
    if (coada_goala(*coada)) return -1;
    NOD *temp = *coada;
    int id = temp->id;
    *coada = (*coada)->urm;
    free(temp);
    return id;
}

void reseteaza_vizitat(GRAF *g) {
    for (int i = 0; i < g->nr_noduri; i++) {
        g->vizitat[i] = 0;
    }
}

// --- PARCURGERI ---
void dfs(GRAF *g, int start) {
    g->vizitat[start] = 1;
    printf("%d ", start);

    NOD *temp = g->liste[start];
    while (temp != NULL) {
        if (g->vizitat[temp->id] == 0) {
            dfs(g, temp->id);
        }
        temp = temp->urm;
    }
}

void bfs(GRAF *g, int start) {
    NOD *coada = NULL;
    g->vizitat[start] = 1;
    enqueue(&coada, start);

    while (!coada_goala(coada)) {
        int curent = dequeue(&coada);
        printf("%d ", curent);

        NOD *temp = g->liste[curent];
        while (temp != NULL) {
            if (g->vizitat[temp->id] == 0) {
                g->vizitat[temp->id] = 1;
                // aici am corectat pointerul, si am pus doar adresa
                enqueue(&coada, temp->id);
            }
            temp = temp->urm;
        }
    }
}

int main() {
    int nr_noduri, nr_muchii, start;

    printf("Cate noduri? ");
    scanf("%d", &nr_noduri);
    // am folosit doar adresa la nr_noduri
    printf("Cate muchii? ");
    scanf("%d", &nr_muchii);
    // am folosit doar &nr_muchii in loc de &(&nr_muchii)

    // in loc de 'nr_of_verticos' care era gresit, am pus nr_noduri
    GRAF *g = creeaza_graf(nr_noduri);
    citeste_muchii(g, nr_muchii);

    printf("\nNod start (0 - %d): ", nr_noduri - 1);
    // am corectat '&(starting_vertex)* steluta de la final era o greseala de sintaxa
    scanf("%d", &start);

    printf("DFS: ");
    // aici era starting_blin care nu a fost declarata nicaieri
    dfs(g, start);
    printf("\n");

    // aici am schimbat numele variabilei "nr_of_vertixes" care era gresita 
    reseteaza_vizitat(g);

    printf("BFS: ");
    bfs(g, start);
    printf("\n");

    return 0;
}