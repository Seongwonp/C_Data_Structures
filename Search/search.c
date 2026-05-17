#include "search.h"
#include <stdio.h>

// 탐색 알고리즘 비교
// 선형: O(n)              — 정렬 불필요, 소규모 데이터
// 이진: O(log n)          — 정렬 필수, 대규모 정적 데이터
// 보간: O(log log n) 평균 — 균등 분포일 때 이진보다 빠름

int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++)
        if (arr[i] == target) return i;
    return -1;
}

int binary_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // 오버플로 방지
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binary_search_rec(int arr[], int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binary_search_rec(arr, mid + 1, high, target);
    return binary_search_rec(arr, low, mid - 1, target);
}

// 보간 탐색: 값의 분포를 이용해 탐색 위치를 추정
// mid = low + (target - arr[low]) / (arr[high] - arr[low]) * (high - low)
int interpolation_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (arr[high] == arr[low]) {
            if (arr[low] == target) return low;
            break;
        }
        // 값의 비율로 예상 위치 계산
        int pos = low + (int)((long long)(target - arr[low])
                              * (high - low) / (arr[high] - arr[low]));
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

void search_main() {
    printf("===== 탐색 알고리즘 =====\n");
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("배열: [");
    for (int i = 0; i < n; i++) printf("%d%s", arr[i], i < n-1 ? ", " : "");
    printf("]\n\n");

    int targets[] = {23, 91, 2, 50};
    for (int t = 0; t < 4; t++) {
        int tgt = targets[t];
        printf("target = %d\n", tgt);
        int r;

        r = linear_search(arr, n, tgt);
        printf("  선형 탐색:  %s (idx=%d)\n", r != -1 ? "찾음" : "없음", r);

        r = binary_search(arr, n, tgt);
        printf("  이진 탐색:  %s (idx=%d)\n", r != -1 ? "찾음" : "없음", r);

        r = binary_search_rec(arr, 0, n - 1, tgt);
        printf("  이진(재귀): %s (idx=%d)\n", r != -1 ? "찾음" : "없음", r);

        r = interpolation_search(arr, n, tgt);
        printf("  보간 탐색:  %s (idx=%d)\n\n", r != -1 ? "찾음" : "없음", r);
    }
}
