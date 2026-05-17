# Trie (트라이)

## 개념

문자열 집합을 **트리 구조**로 저장하는 자료구조.  
각 노드가 한 문자를 나타내며, 루트에서 리프까지의 경로가 하나의 문자열.

```
삽입: "apple", "app", "apt", "bat", "ball"

           root
          /    \
         a      b
         |      |
         p      a
        / \    / \
       p   t  t   l
       |   |  |   |
       l   *  *   l
       |          |
       e          *
       |
       *

* = is_end (단어 끝 표시)

"app"  경로: root → a → p → p(*)
"apple" 경로: root → a → p → p → l → e(*)
"apt"  경로: root → a → p → t(*)
```

---

## 시간 복잡도

| 연산 | 시간 복잡도 |
|------|------------|
| 삽입 | O(L) — L: 문자열 길이 |
| 검색 | O(L) |
| 접두사 탐색 | O(P) — P: 접두사 길이 |
| 공간 | O(총 문자 수 × ALPHA) |

> 해시맵은 완전 일치만, 트라이는 **접두사 기반 검색** 가능

---

## 구현 구조

```c
typedef struct TrieNode {
    struct TrieNode* children[26];  // a~z
    int is_end;                     // 단어 끝 표시
} TrieNode;
```

---

## 완전 일치 vs 접두사 검색

```
삽입된 단어: "app", "apple", "apt", "bat"

trie_search("app")        → 존재  (is_end=1)
trie_search("ap")         → 없음  (is_end=0, 경로는 있음)
trie_starts_with("ap")    → 있음  (경로 존재)
trie_starts_with("ca")    → 없음  (경로 없음)
```

---

## 활용 분야

- **자동완성** (검색창 추천어)
- **사전 검색** (spellchecker)
- **IP 라우팅** (Longest Prefix Match)
- **DNA 서열 분석**

## 파일 목록

| 파일 | 설명 |
|------|------|
| `trie.c/h` | 트라이 삽입/완전일치검색/접두사검색/메모리해제 |
