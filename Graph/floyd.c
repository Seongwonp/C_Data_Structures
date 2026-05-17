#include "floyd.h"
#include <stdio.h>
#include <string.h>

// 플로이드-워셜: 모든 쌍(all-pairs) 최단 경로 - O(V^3)
// 다익스트라와 달리 음수 가중치도 처리 가능 (단, 음수 사이클 없어야 함)
// dp[i][j] = i→j 최단 거리, 중간 경유지 k를 0~n-1까지 늘려가며 갱신

static int dist[FW_MAX][FW_MAX];
static int next_node[FW_MAX][FW_MAX]; // 경로 추적

static void print_path(int u, int v) {
    if (next_node[u][v] == -1) { printf("경로 없음"); return; }
    printf("%d", u);
    while (u != v) { u = next_node[u][v]; printf(" → %d", u); }
}

void floyd_warshall(int n) {
    // next_node 초기화: 직접 연결된 경우 v로, 아닌 경우 -1
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            next_node[i][j] = (dist[i][j] != FW_INF && i != j) ? j : -1;

    // k: 경유 가능한 중간 노드
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != FW_INF && dist[k][j] != FW_INF
                        && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j]    = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k]; // i→k의 첫 경유지 사용
                }
}

void floyd_main() {
    printf("===== 플로이드-워셜 전체 쌍 최단 경로 =====\n");
    int n = 4;
    int init[FW_MAX][FW_MAX] = {
        {    0,    3, FW_INF,    7},
        {    8,    0,    2, FW_INF},
        {    5, FW_INF,    0,    1},
        {    2, FW_INF, FW_INF,    0}
    };
    memcpy(dist, init, sizeof(init));

    floyd_warshall(n);

    printf("최단 거리 행렬:\n     ");
    for (int i = 0; i < n; i++) printf("%6d", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("  %d |", i);
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == FW_INF) printf("   INF");
            else                      printf("%6d", dist[i][j]);
        }
        printf("\n");
    }

    printf("\n경로 예시:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j) {
                printf("  %d→%d (거리:%d): ", i, j, dist[i][j]);
                print_path(i, j);
                printf("\n");
            }
}
