//
// Created by 김서연 on 26. 1. 3.
//

#include "cart.h"
#include "../product/product.h"
#include "../vector/vector.h"
#include <string.h>  // <string.h> 추가

// 장바구니에 상품을 추가하는 함수
void add_to_cart(FILE *fp, VECTOR *cart) {
    char name[SIZE];
    int quantity;
    PRODUCT data;
    int found = 0;
    fseek(fp, 0, SEEK_SET);

    printf("장바구니에 추가할 상품 이름: ");
    fgets(name, SIZE, stdin);
    name[strcspn(name, "\n")] = '\0';  // \n 제거

    while (fread(&data, sizeof(data), 1, fp)) {
        if (strcmp(data.name, name) == 0) {
            found = 1;
            printf("수량 입력: ");
            scanf("%d", &quantity);
            getchar();

            CART_ITEM item;
            strcpy(item.name, data.name);
            item.quantity = quantity;
            item.total_price = data.price * quantity;

            vector_add(cart, &item);
            printf("장바구니에 추가되었습니다.\n");
            return;
        }
    }

    if (!found) {
        printf("상품을 찾을 수 없습니다.\n");
    }
}

// 장바구니 내용 보기
void view_cart(VECTOR *cart) {
    if (cart->size == 0) {
        printf("장바구니가 비어 있습니다.\n");
        return;
    }

    printf("장바구니 내용:\n");
    for (size_t i = 0; i < cart->size; i++) {
        CART_ITEM *item = (CART_ITEM*)((char*)cart->data + i * cart->element_size);
        printf("상품명: %s, 수량: %d, 총 가격: %.2f\n",
               item->name, item->quantity, item->total_price);
    }
}

// 장바구니에서 상품 삭제
void remove_from_cart(VECTOR *cart) {
    char name[SIZE];
    int found = 0;

    if (cart->size == 0) {
        printf("장바구니가 비어 있습니다.\n");
        return;
    }

    printf("장바구니에서 삭제할 상품 이름: ");
    fgets(name, SIZE, stdin);
    name[strcspn(name, "\n")] = '\0'; // \n 제거

    for (size_t i = 0; i < cart->size; i++) {
        CART_ITEM *item = (CART_ITEM*)((char*)cart->data + i * cart->element_size);
        if (strcmp(item->name, name) == 0) {
            vector_remove(cart, i);
            found = 1;
            printf("장바구니에서 삭제되었습니다.\n");
            break;
        }
    }

    if (!found) {
        printf("장바구니에 해당 상품이 없습니다.\n");
    }
}

// 결제 처리
void checkout(VECTOR *cart) {
    if (cart->size == 0) {
        printf("장바구니가 비어 있습니다.\n");
        return;
    }

    float total = 0;
    printf("결제 내역:\n");
    for (size_t i = 0; i < cart->size; i++) {
        CART_ITEM *item = (CART_ITEM*)((char*)cart->data + i * cart->element_size);
        printf("상품명: %s, 수량: %d, 총 가격: %.2f\n",
               item->name, item->quantity, item->total_price);
        total += item->total_price;
    }

    printf("총 결제 금액: %.2f\n", total);
    printf("결제가 완료되었습니다.\n");

    // 장바구니 초기화
    cart->size = 0;
}
