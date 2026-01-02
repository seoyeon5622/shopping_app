#include "product.h"
#include "../cart/cart.h"
#include <string.h>

#define CORRECT_PASSWORD "1234"

int check_password() {
    char input_password[SIZE];
    printf("관리자 비밀번호를 입력하세요: ");
    fgets(input_password, SIZE, stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    if (strcmp(input_password, CORRECT_PASSWORD) == 0) {
        return 1;
    } else {
        printf("비밀번호가 틀렸습니다.\n");
        return 0;
    }
}

void add_product_direct(FILE *fp) {
    PRODUCT data = get_product();
    fseek(fp, 0, SEEK_END);
    fwrite(&data, sizeof(data), 1, fp);
    printf("상품이 추가되었습니다.\n");
}

void view_products(FILE *fp) {
    PRODUCT data;
    int count = 0; // 상품 개수를 세기 위한 변수

    // 파일의 시작으로 이동
    fseek(fp, 0, SEEK_SET);

    printf("\n--- 상품 목록 ---\n");

    // 데이터를 하나씩 읽어옴
    while (fread(&data, sizeof(data), 1, fp)) {
        print_product(data);
        printf("--------------------\n");
        count++;
    }

    // 만약 읽어온 데이터가 하나도 없다면 메시지 출력
    if (count == 0) {
        printf("등록된 상품이 없습니다. 관리자에게 문의하세요.\n");
        printf("--------------------\n");
    }
}

void add_product(FILE *fp) {
    if (check_password()) {
        add_product_direct(fp);
    }
}

PRODUCT get_product() {
    PRODUCT data;
    printf("상품 이름: ");
    fgets(data.name, SIZE, stdin);
    data.name[strcspn(data.name, "\n")] = '\0';
    printf("상품 가격: ");
    scanf("%f", &data.price);
    getchar();
    return data;
}

void print_product(PRODUCT data) {
    printf("이름: %s | 가격: %.2f\n", data.name, data.price);
}


void search_product(FILE *fp) {
    char keyword[SIZE];
    PRODUCT data;
    int found = 0;
    fseek(fp, 0, SEEK_SET);

    printf("검색할 키워드(상품명 일부): ");
    fgets(keyword, SIZE, stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // 개행 문자 제거

    printf("\n' %s ' 키워드 검색 결과:\n", keyword);
    printf("--------------------\n");

    while (fread(&data, sizeof(data), 1, fp)) {
        // strstr(전체문자열, 찾는단어): 포함되어 있으면 해당 주소 반환, 없으면 NULL
        if (strstr(data.name, keyword) != NULL) {
            print_product(data);
            printf("--------------------\n");
            found++;
        }
    }

    if (found == 0) {
        printf("해당 키워드를 포함하는 상품이 없습니다.\n");
    } else {
        printf("총 %d개의 상품을 찾았습니다.\n", found);
    }
}

void delete_product(FILE **fp) {
    char target_name[SIZE];
    PRODUCT data;
    int found = 0;

    printf("삭제할 상품 이름: ");
    fgets(target_name, SIZE, stdin);
    target_name[strcspn(target_name, "\n")] = '\0';

    // 임시 파일 생성
    FILE *temp_fp = fopen("temp.txt", "wb");
    if (temp_fp == NULL) {
        printf("임시 파일 생성 실패\n");
        return;
    }

    fseek(*fp, 0, SEEK_SET);
    while (fread(&data, sizeof(data), 1, *fp)) {
        if (strcmp(data.name, target_name) == 0) {
            found = 1;
            printf("상품 '%s'을(를) 삭제했습니다.\n", target_name);
            continue; // 삭제할 상품은 임시 파일에 쓰지 않고 건너뜀
        }
        fwrite(&data, sizeof(data), 1, temp_fp);
    }

    fclose(temp_fp);
    fclose(*fp); // 기존 파일 닫기

    if (found) {
        remove("products.txt");       // 원본 삭제
        rename("temp.txt", "products.txt"); // 임시 파일 이름을 원본으로 변경
    } else {
        printf("삭제할 상품을 찾지 못했습니다.\n");
        remove("temp.txt"); // 임시 파일 삭제
    }

    // 파일을 다시 열어서 포인터 갱신
    *fp = fopen("products.txt", "ab+");
}