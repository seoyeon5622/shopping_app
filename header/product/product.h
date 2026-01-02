#ifndef DKU_PROJECT_PRODUCT_H
#define DKU_PROJECT_PRODUCT_H

#include <stdio.h>

#define SIZE 100

typedef struct product {
    char name[SIZE];
    float price;
} PRODUCT;

// 함수 선언
PRODUCT get_product();
void print_product(PRODUCT data);
void add_product(FILE *fp);       // 기존 유지
void add_product_direct(FILE *fp); // 관리자용 (비번체크 제외)
void delete_product(FILE **fp); // 파일 포인터를 변경해야 하므로 더블 포인터 사용
void view_products(FILE *fp);
void search_product(FILE *fp);
int check_password();             // main에서 호출 가능하게 추가

#endif