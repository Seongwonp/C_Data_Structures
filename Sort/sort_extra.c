#include "sort_extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

/* ============================================================
   힙 정렬 (Heap Sort) - O(n log n), 제자리 정렬
   최대 힙을 구성한 뒤 루트(최댓값)를 맨 뒤로 보내길 반복
   ============================================================ */
static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest); // 교환된 위치에서 다시 힙 성질 복구
    }
}

void heap_sort(int arr[], int size) {
    // 1단계: 배열 전체를 최대 힙으로 구성 (뒤에서부터 heapify)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // 2단계: 루트(최댓값)를 맨 뒤로 보내고, 힙 크기를 줄이며 반복
    for (int i = size - 1; i > 0; i--) {
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

/* ============================================================
   계수 정렬 (Counting Sort) - O(n + k), 비교 없는 정렬
   값의 범위(k)가 작을 때 매우 효율적 (정수 전용)
   ============================================================ */
void counting_sort(int arr[], int size) {
    if (size <= 0) return;

    // 최댓값 탐색
    int max = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] > max) max = arr[i];

    // 각 값의 등장 횟수 카운트
    int* count = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < size; i++) count[arr[i]]++;

    // 누적합으로 변환 (출력 배열에서의 위치 계산)
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];

    // 출력 배열에 안정적으로 배치 (뒤에서부터 순회)
    int* output = (int*)malloc(size * sizeof(int));
    for (int i = size - 1; i >= 0; i--)
        output[--count[arr[i]]] = arr[i];

    memcpy(arr, output, size * sizeof(int));
    free(count);
    free(output);
}

/* ============================================================
   기수 정렬 (Radix Sort) - O(d * (n + k)), 자릿수 기반 정렬
   각 자릿수(1의 자리 → 10의 자리 → ...)를 기준으로 계수 정렬 반복
   ============================================================ */
static void counting_sort_by_digit(int arr[], int size, int exp) {
    int* output = (int*)malloc(size * sizeof(int));
    int count[10] = {0};

    // exp 자릿수 기준으로 카운트
    for (int i = 0; i < size; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)   count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--)
        output[--count[(arr[i] / exp) % 10]] = arr[i];

    memcpy(arr, output, size * sizeof(int));
    free(output);
}

void radix_sort(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] > max) max = arr[i];

    // 각 자릿수(1, 10, 100, ...)에 대해 계수 정렬 수행
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort_by_digit(arr, size, exp);
}

void sort_extra_main() {
    int a[] = {64, 34, 25, 12, 22, 11, 90};
    int b[] = {64, 34, 25, 12, 22, 11, 90};
    int c[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = 7;

    printf("===== 추가 정렬 알고리즘 =====\n");

    printf("원본:       ");  print_arr(a, n);

    heap_sort(a, n);
    printf("힙 정렬:    "); print_arr(a, n);

    counting_sort(b, n);
    printf("계수 정렬:  "); print_arr(b, n);

    radix_sort(c, 8);
    printf("기수 정렬:  "); print_arr(c, 8);
}
