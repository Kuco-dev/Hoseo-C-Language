#include <stdio.h>

int main() {
    int product_count;
    int stock[101];
    int sales[101];
    int inventory[101];
    int query_id;
    
    printf("상품의 갯수를 입력하세요: ");
    scanf("%d", &product_count);
    
    printf("재고 수량을 입력하세요: ");
    for (int i = 1; i <= product_count; i++) {
        scanf("%d", &stock[i]);
    }
    
    printf("판매 수량을 입력하세요: ");
    for (int i = 1; i <= product_count; i++) {
        scanf("%d", &sales[i]);
    }
    
    printf("재고 수량을 계산합니다.\n");
    for (int i = 1; i <= product_count; i++) {
        inventory[i] = stock[i] - sales[i];
    }
    
    printf("조회할 상품 번호를 입력하세요: ");
    scanf("%d", &query_id);
    
    printf("%d\n", inventory[query_id]);
    
    for (int i = 1; i <= product_count; i++) {
        printf("%d", inventory[i]);
        if (i < product_count) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}