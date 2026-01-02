//
// Created by 김서연 on 26. 1. 3.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// 벡터 초기화 함수: 초기 용량 2로 설정
VECTOR* vector_init(size_t element_size) {
    VECTOR *vector = (VECTOR*)malloc(sizeof(VECTOR));
    if (!vector) {
        fprintf(stderr, "벡터 메모리 할당 실패\n");
        exit(1);
    }
    // 초기 용량 2로 할당
    vector->data = malloc(element_size * 2);
    if (!vector->data) {
        fprintf(stderr, "벡터 데이터 메모리 할당 실패\n");
        exit(1);
    }
    vector->size = 0;
    vector->capacity = 2;
    vector->element_size = element_size;
    return vector;
}

// 벡터 크기 조정 함수: 용량이 부족하면 두 배로 증가시킴
void vector_resize(VECTOR *vector) {
    vector->capacity *= 2;
    vector->data = realloc(vector->data, vector->capacity * vector->element_size);
    if (!vector->data) {
        fprintf(stderr, "벡터 메모리 재할당 실패\n");
        exit(1);
    }
}

// 벡터에 데이터 추가 함수
void vector_add(VECTOR *vector, void *element) {
    // 용량이 부족하면 크기 조정
    if (vector->size == vector->capacity) {
        vector_resize(vector);
    }
    // 새 데이터를 벡터에 추가
    memcpy((char*)vector->data + vector->size * vector->element_size, element, vector->element_size);
    vector->size++;
}

// 벡터에서 데이터 제거 함수
void vector_remove(VECTOR *vector, size_t index) {
    if (index < vector->size) {
        // 데이터를 삭제하고 뒤의 데이터를 한 칸씩 당긴다
        memmove((char*)vector->data + index * vector->element_size,
                (char*)vector->data + (index + 1) * vector->element_size,
                (vector->size - index - 1) * vector->element_size);
        vector->size--;
    }
}

// 벡터 메모리 해제 함수
void vector_free(VECTOR *vector) {
    free(vector->data);
    free(vector);
}
