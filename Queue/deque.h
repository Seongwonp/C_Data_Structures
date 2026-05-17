#ifndef DEQUE_H
#define DEQUE_H

#define DEQUE_MAX 100

typedef struct {
    int data[DEQUE_MAX];
    int front;
    int rear;
    int size;
} DEQUE;

DEQUE* deque_init();
void   deque_push_front(DEQUE* dq, int data);
void   deque_push_back(DEQUE* dq, int data);
int    deque_pop_front(DEQUE* dq);
int    deque_pop_back(DEQUE* dq);
int    deque_peek_front(DEQUE* dq);
int    deque_peek_back(DEQUE* dq);
int    deque_is_empty(DEQUE* dq);
int    deque_size(DEQUE* dq);
void   deque_main();

#endif //DEQUE_H
