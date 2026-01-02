//
// Created by 김서연 on 26. 1. 3.
//

#ifndef DKU_PROJECT_VECTOR_H
#define DKU_PROJECT_VECTOR_H

#include <stddef.h>

// 벡터 자료구조 정의
typedef struct {
    void *data;          // 데이터 포인터
    size_t size;         // 현재 벡터에 저장된 요소의 수
    size_t capacity;     // 벡터의 용량
    size_t element_size; // 각 요소의 크기
} VECTOR;

// 벡터 초기화
VECTOR* vector_init(size_t element_size);

// 벡터 크기 조정 (용량이 부족할 때)
void vector_resize(VECTOR *vector);

// 벡터에 요소 추가
void vector_add(VECTOR *vector, void *element);

// 벡터에서 요소 삭제
void vector_remove(VECTOR *vector, size_t index);

// 벡터 메모리 해제
void vector_free(VECTOR *vector);

#endif //DKU_PROJECT_VECTOR_H
