# Queue (큐)

## 큐 (Queue)

**FIFO** (First In, First Out): 먼저 들어온 것이 먼저 나감.

```
Enqueue →  [ 1 | 2 | 3 | 4 ]  → Dequeue
           front           rear

enqueue(5): [ 1 | 2 | 3 | 4 | 5 ]
dequeue():  [ 2 | 3 | 4 | 5 ]  (1 반환)
```

---

## 원형 큐 (Ring Queue / Circular Queue)

배열 끝에 도달하면 앞으로 되돌아가 공간을 재사용.

```
크기 5의 원형 큐:

초기:  [ _ | _ | _ | _ | _ ]
        ↑
      front=rear=0

enqueue(A,B,C):
       [ A | B | C | _ | _ ]
         ↑           ↑
       front=0     rear=3

dequeue() → A 반환:
       [ _ | B | C | _ | _ ]
               ↑       ↑
            front=1  rear=3

enqueue(D,E):
       [ _ | B | C | D | E ]
               ↑           ↑
            front=1     rear=5%5=0

enqueue(F): (front==rear → 빈칸 1개 유지)
       [ F | B | C | D | E ]
               ↑   ↑
            front rear → 포화 상태

공식:
  empty: front == rear
  full:  (rear + 1) % size == front
```

---

## 덱 (Deque, Double-Ended Queue)

앞/뒤 양쪽에서 삽입/삭제 모두 가능.

```
push_front(1):  [1]
push_back(2):   [1, 2]
push_front(0):  [0, 1, 2]
pop_front():    [1, 2]  (0 반환)
pop_back():     [1]     (2 반환)

원형 배열로 구현 시 양방향 O(1) 연산
```

### 덱 활용
```
- 슬라이딩 윈도우 최대/최솟값
- 팰린드롬 검사
- 브라우저 앞으로/뒤로 가기
- 작업 스케줄링 (양쪽에서 우선순위 처리)
```

---

## 시간 복잡도

| 연산 | 큐 | 원형 큐 | 덱 |
|------|-----|---------|-----|
| enqueue/push | O(1) | O(1) | O(1) |
| dequeue/pop | O(1) | O(1) | O(1) |
| peek | O(1) | O(1) | O(1) |

---

## 파일 목록

| 파일 | 설명 |
|------|------|
| `queue.c/h` | 기본 큐 (배열 기반) |
| `ring_queue.c/h` | 원형 큐 (Circular Queue) |
| `deque.c/h` | 덱 (양방향 큐, 원형 배열) |
