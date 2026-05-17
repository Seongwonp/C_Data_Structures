#include "mst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 최소 신장 트리 (MST): 모든 노드를 연결하는 최소 비용 트리

/* ============================================================
   크루스칼 알고리즘 (Kruskal) - O(E log E)
   간선을 가중치 오름차순 정렬 → Union-Find로 사이클 체크하며 선택
   ============================================================ */
static int parent[MST_MAX_V];

static int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]); // 경로 압축
    return parent[x];
}

static void unite(int x, int y) {
    parent[find(x)] = find(y);
}

static int cmp_edge(const void* a, const void* b) {
    return ((EDGE*)a)->weight - ((EDGE*)b)->weight;
}

void kruskal(EDGE edges[], int e, int v) {
    printf("--- 크루스칼 MST ---\n");
    for (int i = 0; i < v; i++) parent[i] = i;

    qsort(edges, e, sizeof(EDGE), cmp_edge); // 간선 가중치 오름차순 정렬

    int total = 0, count = 0;
    for (int i = 0; i < e && count < v - 1; i++) {
        int u = edges[i].u, vv = edges[i].v, w = edges[i].weight;
        // 사이클이 생기지 않는 경우에만 선택 (두 노드가 다른 집합이면 OK)
        if (find(u) != find(vv)) {
            unite(u, vv);
            printf("  간선 (%d - %d) 가중치 %d 선택\n", u, vv, w);
            total += w;
            count++;
        }
    }
    printf("  MST 총 가중치: %d\n", total);
}

/* ============================================================
   프림 알고리즘 (Prim) - O(V^2) (인접 행렬)
   임의 노드에서 시작 → 매 단계 MST에 연결된 최소 가중치 간선 선택
   ============================================================ */
void prim(int graph[MST_MAX_V][MST_MAX_V], int n) {
    printf("--- 프림 MST ---\n");
    int in_mst[MST_MAX_V] = {0};  // MST에 포함됐는지 여부
    int key[MST_MAX_V];           // MST와 연결되는 최소 가중치
    int parent_node[MST_MAX_V];   // 각 노드의 MST 부모

    for (int i = 0; i < n; i++) { key[i] = 99999; parent_node[i] = -1; }
    key[0] = 0;

    int total = 0;
    for (int count = 0; count < n; count++) {
        // 아직 MST에 없는 노드 중 key 최솟값 선택
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!in_mst[v] && (u == -1 || key[v] < key[u])) u = v;

        in_mst[u] = 1;
        total += key[u];
        if (parent_node[u] != -1)
            printf("  간선 (%d - %d) 가중치 %d 선택\n", parent_node[u], u, key[u]);

        // u를 통해 연결 가능한 인접 노드의 key 값 갱신
        for (int v = 0; v < n; v++)
            if (graph[u][v] && !in_mst[v] && graph[u][v] < key[v]) {
                key[v]         = graph[u][v];
                parent_node[v] = u;
            }
    }
    printf("  MST 총 가중치: %d\n", total);
}

void mst_main() {
    printf("===== 최소 신장 트리 (MST) =====\n");

    EDGE edges[] = {
        {0,1,4},{0,2,3},{1,2,1},{1,3,2},{2,3,4},{2,4,3},{3,4,2},{3,5,1},{4,5,5},{4,6,3},{5,6,2}
    };
    kruskal(edges, 11, 7);

    printf("\n");

    int graph[MST_MAX_V][MST_MAX_V] = {
        {0,4,3,0,0,0,0},
        {4,0,1,2,0,0,0},
        {3,1,0,4,3,0,0},
        {0,2,4,0,2,1,0},
        {0,0,3,2,0,5,3},
        {0,0,0,1,5,0,2},
        {0,0,0,0,3,2,0}
    };
    prim(graph, 7);
}
