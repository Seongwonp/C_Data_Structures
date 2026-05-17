#ifndef TRIE_H
#define TRIE_H

#define TRIE_ALPHA 26  // 소문자 영어 알파벳 수

typedef struct TrieNode {
    struct TrieNode* children[TRIE_ALPHA];
    int is_end;  // 단어 끝 표시
} TrieNode;

TrieNode* trie_new_node();
void      trie_insert(TrieNode* root, const char* word);
int       trie_search(TrieNode* root, const char* word);
int       trie_starts_with(TrieNode* root, const char* prefix);
void      trie_free(TrieNode* root);
void      trie_main();

#endif //TRIE_H
