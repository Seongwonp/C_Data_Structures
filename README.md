# C 자료구조 & 알고리즘 실습

C 언어로 구현한 자료구조 및 알고리즘 실습 저장소.  
각 폴더에 개념 설명 `README.md`와 주석이 포함된 구현 코드를 담고 있어 학습 자료로 활용 가능합니다.

---

## 폴더 구성

| 폴더 | 내용 | 핵심 개념 |
|------|------|-----------|
| [List](./List/README.md) | 단순/이중/원형 연결 리스트, 희소 배열 | 포인터, 동적 할당 |
| [Stack](./Stack/README.md) | 스택, 후위 표기식, 계산기 | LIFO, 괄호 검사 |
| [Queue](./Queue/README.md) | 큐, 원형 큐, 덱(Deque) | FIFO, 원형 버퍼 |
| [Tree](./Tree/README.md) | 이진 트리, BST, AVL 트리 | 순회, 균형, 회전 |
| [Heap](./Heap/README.md) | 최소/최대 힙, 우선순위 큐 | sift up/down, heapify |
| [Sort](./Sort/README.md) | 버블/선택/삽입/병합/퀵/힙/계수/기수 정렬 | 비교 정렬, 시간복잡도 |
| [Search](./Search/README.md) | 선형/이진/보간 탐색 | O(log n), 분할 정복 |
| [Graph](./Graph/README.md) | BFS/DFS, 다익스트라, 플로이드, MST | 최단 경로, 신장 트리 |
| [Hash](./Hash/README.md) | 체이닝, 개방 주소법 | 해시 함수, 충돌 해결 |
| [Set](./Set/README.md) | Union-Find (서로소 집합) | 경로 압축, 랭크 합치기 |
| [Trie](./Trie/README.md) | 트라이 (문자열 트리) | 접두사 검색, 자동완성 |
| [Recursive](./Recursive/) | 재귀 기반 알고리즘 | 분할 정복, 백트래킹 |
| [Sosu](./Sosu/) | 소수 판별 (에라토스테네스의 체) | 수학적 알고리즘 |
| [CardConverter](./CardConverter/) | 숫자 → 카드 문자열 변환 | 모듈화 연습 |

---

## 알고리즘 복잡도 요약

### 정렬

| 알고리즘 | 평균 | 최악 | 공간 | 안정 |
|----------|------|------|------|------|
| 버블/선택/삽입 | O(n²) | O(n²) | O(1) | 삽입 ✓ |
| 병합 정렬 | O(n log n) | O(n log n) | O(n) | ✓ |
| 퀵 정렬 | O(n log n) | O(n²) | O(log n) | ✗ |
| 힙 정렬 | O(n log n) | O(n log n) | O(1) | ✗ |
| 계수/기수 정렬 | O(n+k) | O(n+k) | O(k) | ✓ |

### 그래프

| 알고리즘 | 복잡도 | 용도 |
|----------|--------|------|
| BFS/DFS | O(V+E) | 탐색, 연결성 |
| 다익스트라 | O(V²) or O(E log V) | 단일 출발 최단 경로 |
| 플로이드-워셜 | O(V³) | 전체 쌍 최단 경로 |
| 크루스칼 | O(E log E) | MST |
| 프림 | O(V²) or O(E log V) | MST |

---

## 실행 방법

```bash
# 개별 파일 컴파일
gcc Sort/sort.c Sort/sort_extra.c -o sort_test

# 또는 CMake 사용 (CLion)
cmake -B cmake-build-debug && cmake --build cmake-build-debug
```

---

## 개발 환경

- **언어**: C11
- **도구**: GCC, CLion, CMake
- **OS**: macOS, Ubuntu Linux

---

## 작성자

**박성원 (Seongwon Park)**  
C 언어 기반 자료구조 & 알고리즘 학습 + 직접 구현 연습
