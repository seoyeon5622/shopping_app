#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header/product/product.h"
#include "header/cart/cart.h"
#include "header/vector/vector.h"
#include "header/weather/weather.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(void) {
    FILE *fp;
    VECTOR *cart = vector_init(sizeof(CART_ITEM));
    int choice, sub_choice;

    if ((fp = fopen("products.txt", "ab+")) == NULL) {
        fprintf(stderr, "파일 오류\n");
        return 1;
    }

    while (true) {
        clear_screen();
        printf("현재 날씨: %.0f도\n", get_current_temp_by_api());
        printf("=== 쇼핑 프로그램 ===\n");
        printf("1. 관리자 모드 (상품 관리)\n");
        printf("2. 구매자 모드 (쇼핑 하기)\n");
        printf("3. 종료\n");
        printf("====================\n");
        printf("선택: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();

        if (choice == 1) { // 관리자 모드
            if (check_password()) {
                bool admin_loop = true;
                while (admin_loop) {
                    printf("\n[관리자 메뉴] 1.상품추가 2.상품삭제 3.이전으로: ");
                    scanf("%d", &sub_choice);
                    getchar();
                    switch(sub_choice) {
                        case 1:
                            add_product_direct(fp);
                        break;
                        case 2:
                            delete_product(&fp); // fp의 주소 전달
                        break;
                        case 3:
                            admin_loop = false;
                        break;
                        default:
                            printf("잘못된 입력입니다.\n");
                    }
                }
            }
        }
        else if (choice == 2) { // 구매자 모드
            bool user_loop = true;
            while (user_loop) {
                printf("\n[구매자 메뉴] 1.목록 2.검색 3.담기 4.보기 5.삭제 6.결제 7.이전: ");
                scanf("%d", &sub_choice);
                getchar();
                switch (sub_choice) {
                    case 1: view_products(fp); break;
                    case 2: search_product(fp); break;
                    case 3: add_to_cart(fp, cart); break;
                    case 4: view_cart(cart); break;
                    case 5: remove_from_cart(cart); break;
                    case 6: checkout(cart); break;
                    case 7: user_loop = false; break;
                }
            }
        }
        else if (choice == 3) break;
    }

    fclose(fp);
    vector_free(cart);
    return 0;
}