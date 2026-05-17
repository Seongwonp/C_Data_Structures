#ifndef SEARCH_H
#define SEARCH_H

// 선형 탐색: O(n)
int linear_search(int arr[], int n, int target);

// 이진 탐색 (반복): O(log n) - 정렬된 배열 전제
int binary_search(int arr[], int n, int target);

// 이진 탐색 (재귀)
int binary_search_rec(int arr[], int low, int high, int target);

// 보간 탐색: O(log log n) 평균 - 균등 분포 데이터에 효율적
int interpolation_search(int arr[], int n, int target);

void search_main();

#endif //SEARCH_H
