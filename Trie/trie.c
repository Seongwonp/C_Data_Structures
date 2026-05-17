#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 트라이(Trie): 문자열 집합을 트리 구조로 저장
// 삽입/검색 모두 O(L) — L은 문자열 길이
// 자동완성, 사전 검색, IP 라우팅 테이블 등에 활용

TrieNode* trie_new_node() {
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));
    // is_end = 0, children = NULL (calloc으로 초기화됨)
    return node;
}

void trie_insert(TrieNode* root, const char* word) {
    TrieNode* cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';  // 소문자만 처리
        if (!cur->children[idx])
            cur->children[idx] = trie_new_node();
        cur = cur->children[idx];
    }
    cur->is_end = 1;  // 단어 끝 표시
}

// 완전 일치 검색
int trie_search(TrieNode* root, const char* word) {
    TrieNode* cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx]) return 0;  // 경로 없음
        cur = cur->children[idx];
    }
    return cur->is_end;  // 경로는 있어도 단어 끝이어야 일치
}

// 접두사 검색 (자동완성 기반)
int trie_starts_with(TrieNode* root, const char* prefix) {
    TrieNode* cur = root;
    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a';
        if (!cur->children[idx]) return 0;
        cur = cur->children[idx];
    }
    return 1;  // 접두사 경로가 존재함
}

void trie_free(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < TRIE_ALPHA; i++)
        trie_free(root->children[i]);
    free(root);
}

void trie_main() {
    printf("===== 트라이 (Trie) =====\n");
    TrieNode* root = trie_new_node();

    const char* words[] = {"apple", "app", "apt", "bat", "ball", "band"};
    int cnt = sizeof(words) / sizeof(words[0]);

    printf("삽입: ");
    for (int i = 0; i < cnt; i++) {
        trie_insert(root, words[i]);
        printf("\"%s\" ", words[i]);
    }
    printf("\n\n");

    // 완전 일치 검색
    const char* queries[] = {"app", "ap", "apple", "bat", "ba", "band"};
    printf("검색 (완전 일치):\n");
    for (int i = 0; i < 6; i++)
        printf("  \"%s\" → %s\n", queries[i],
               trie_search(root, queries[i]) ? "존재" : "없음");

    // 접두사 검색
    printf("\n접두사 검색:\n");
    const char* prefixes[] = {"ap", "ba", "ca", "ban"};
    for (int i = 0; i < 4; i++)
        printf("  \"%s\"으로 시작하는 단어 → %s\n", prefixes[i],
               trie_starts_with(root, prefixes[i]) ? "있음" : "없음");

    trie_free(root);
}
