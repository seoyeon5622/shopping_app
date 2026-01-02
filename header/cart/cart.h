//
// Created by 김서연 on 26. 1. 3.
//
#ifndef DKU_PROJECT_CART_H
#define DKU_PROJECT_CART_H


#include <stdio.h>
#include "../vector/vector.h" // 벡터 자료구조를 사용

// 장바구니 아이템 구조체 정의
typedef struct cart_item {
    char name[100];      // 상품명
    int quantity;        // 수량
    float total_price;   // 총 가격
} CART_ITEM;

// 장바구니 관련 함수 선언
void add_to_cart(FILE *fp, VECTOR *cart);       // 장바구니에 상품 추가
void view_cart(VECTOR *cart);                    // 장바구니 내용 보기
void remove_from_cart(VECTOR *cart);             // 장바구니에서 상품 삭제
void checkout(VECTOR *cart);                     // 결제 처리


#endif //DKU_PROJECT_CART_H
