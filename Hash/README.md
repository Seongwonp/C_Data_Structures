# Hash (해시)

## 개념

**해시 함수**로 키(key)를 인덱스로 변환하여 O(1) 평균 탐색.

```
key: "apple"
            ↓ hash("apple") % table_size
index: 3
            ↓
table[3] = "apple"
```

---

## 충돌(Collision) 해결

### 체이닝 (Chaining)

```
같은 인덱스 → 연결 리스트로 연결

table:
[0] → NULL
[1] → "dog" → "log" → NULL
[2] → "cat" → NULL
[3] → "apple" → NULL
[4] → NULL

장점: 테이블 크기 초과 가능
단점: 포인터 오버헤드, 캐시 미스
```

### 개방 주소법 (Open Addressing)

```
충돌 시 다음 빈 슬롯 탐색

선형 조사 (Linear Probing):
  h(k), h(k)+1, h(k)+2, ...

이차 조사 (Quadratic Probing):
  h(k), h(k)+1, h(k)+4, h(k)+9, ...

이중 해싱 (Double Hashing):
  h(k), h(k)+h'(k), h(k)+2h'(k), ...

장점: 추가 메모리 불필요, 캐시 친화적
단점: 테이블이 꽉 차면 성능 급락, 삭제 복잡
```

---

## 시간 복잡도

| 연산 | 평균 | 최악 |
|------|------|------|
| 삽입 | O(1) | O(n) |
| 탐색 | O(1) | O(n) |
| 삭제 | O(1) | O(n) |

> 최악은 모든 키가 같은 버킷으로 충돌할 때  
> 좋은 해시 함수 + 적절한 로드 팩터(0.7 이하)로 방지

---

## 해시 함수 예시

```c
// djb2 (문자열 해시)
unsigned long hash(const char* str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;  // h * 33 + c
    return h;
}
```

---

## 파일 목록

| 파일 | 설명 |
|------|------|
| `chain_hash.c/h` | 체이닝 방식 해시 테이블 |
| `open_address.c/h` | 개방 주소법 (선형 조사) |
