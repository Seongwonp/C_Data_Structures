#include "dijkstra.h"
#include <stdio.h>

// 다익스트라 알고리즘: 단일 출발지 최단 경로
// 음수 가중치 없는 가중 그래프에서 O(V^2) (인접 행렬 기준)
// 매 단계: 아직 확정되지 않은 노드 중 dist 최솟값 노드를 선택 → 인접 노드 거리 갱신

static int min_distance(int dist[], int visited[], int n) {
    int min = INF, min_idx = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_idx = v;
        }
    }
    return min_idx;
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int start) {
    int dist[MAX_VERTICES];    // 출발지에서 각 노드까지 최단 거리
    int visited[MAX_VERTICES]; // 최단 거리가 확정된 노드
    int prev[MAX_VERTICES];    // 경로 추적용: 직전 노드 저장

    for (int i = 0; i < n; i++) {
        dist[i]    = INF;
        visited[i] = 0;
        prev[i]    = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        // 미확정 노드 중 dist 최솟값 선택 → 확정
        int u = min_distance(dist, visited, n);
        if (u == -1) break;
        visited[u] = 1;

        // 선택된 노드 u를 경유하는 경로가 더 짧으면 거리 갱신
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF
                    && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // 결과 출력
    printf("출발지 %d에서 각 노드까지 최단 거리:\n", start);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("  %d → %d : 도달 불가\n", start, i);
        } else {
            // 경로 역추적
            printf("  %d → %d : %d  (경로: ", start, i, dist[i]);
            int path[MAX_VERTICES], len = 0, cur = i;
            while (cur != -1) { path[len++] = cur; cur = prev[cur]; }
            for (int j = len - 1; j >= 0; j--)
                printf("%d%s", path[j], j ? " → " : "");
            printf(")\n");
        }
    }
}

void dijkstra_main() {
    printf("===== 다익스트라 최단 경로 =====\n");
    // 0: INF (연결 없음), 양수: 가중치
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0,11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9,14, 0, 0, 0},
        {0, 0, 0, 9, 0,10, 0, 0, 0},
        {0, 0, 4,14,10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8,11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    dijkstra(graph, 9, 0);
}
