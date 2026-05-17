#ifndef MST_H
#define MST_H

#define MST_MAX_V 7
#define MST_MAX_E 20

typedef struct {
    int u, v, weight;
} EDGE;

void kruskal(EDGE edges[], int e, int v);
void prim(int graph[MST_MAX_V][MST_MAX_V], int n);
void mst_main();

#endif //MST_H
