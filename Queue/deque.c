#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

// Deque (Double-Ended Queue): 앞뒤 양쪽에서 삽입/삭제가 가능한 큐
// 원형 배열로 구현 → front/rear를 순환시켜 공간 효율 극대화

DEQUE* deque_init() {
    DEQUE* dq = (DEQUE*)malloc(sizeof(DEQUE));
    dq->front = 0;
    dq->rear  = 0;
    dq->size  = 0;
    return dq;
}

int deque_is_empty(DEQUE* dq) { return dq->size == 0; }
int deque_size(DEQUE* dq)     { return dq->size; }

// 앞에 삽입: front를 뒤로 이동 (원형)
void deque_push_front(DEQUE* dq, int data) {
    if (dq->size >= DEQUE_MAX) { printf("Deque is full\n"); return; }
    dq->front = (dq->front - 1 + DEQUE_MAX) % DEQUE_MAX;
    dq->data[dq->front] = data;
    dq->size++;
}

// 뒤에 삽입: rear가 가리키는 위치에 저장 후 rear 이동
void deque_push_back(DEQUE* dq, int data) {
    if (dq->size >= DEQUE_MAX) { printf("Deque is full\n"); return; }
    dq->data[dq->rear] = data;
    dq->rear = (dq->rear + 1) % DEQUE_MAX;
    dq->size++;
}

// 앞에서 꺼내기
int deque_pop_front(DEQUE* dq) {
    if (deque_is_empty(dq)) { printf("Deque is empty\n"); return -1; }
    int val = dq->data[dq->front];
    dq->front = (dq->front + 1) % DEQUE_MAX;
    dq->size--;
    return val;
}

// 뒤에서 꺼내기
int deque_pop_back(DEQUE* dq) {
    if (deque_is_empty(dq)) { printf("Deque is empty\n"); return -1; }
    dq->rear = (dq->rear - 1 + DEQUE_MAX) % DEQUE_MAX;
    int val = dq->data[dq->rear];
    dq->size--;
    return val;
}

int deque_peek_front(DEQUE* dq) {
    if (deque_is_empty(dq)) return -1;
    return dq->data[dq->front];
}

int deque_peek_back(DEQUE* dq) {
    if (deque_is_empty(dq)) return -1;
    return dq->data[(dq->rear - 1 + DEQUE_MAX) % DEQUE_MAX];
}

void deque_main() {
    printf("===== Deque (양방향 큐) =====\n");
    DEQUE* dq = deque_init();

    deque_push_back(dq, 1);
    deque_push_back(dq, 2);
    deque_push_back(dq, 3);
    deque_push_front(dq, 0);
    deque_push_front(dq, -1);
    // 현재 상태: [-1, 0, 1, 2, 3]

    printf("front peek: %d\n", deque_peek_front(dq)); // -1
    printf("back  peek: %d\n", deque_peek_back(dq));  // 3
    printf("size: %d\n", deque_size(dq));              // 5

    printf("pop_front: %d\n", deque_pop_front(dq)); // -1
    printf("pop_back:  %d\n", deque_pop_back(dq));  //  3
    printf("pop_front: %d\n", deque_pop_front(dq)); //  0

    printf("남은 size: %d\n", deque_size(dq)); // 2
    free(dq);
}
