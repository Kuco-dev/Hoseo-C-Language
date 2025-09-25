#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int stock[101];
    int sales[101];      
    int total_buy;       
    int total_sale;      
    int product_count;
    char stock_name[101][50];
} ShopData;

void handle_stock_input(ShopData *shop);
void handle_sale_input(ShopData *shop);
void display_status(ShopData *shop);
void display_names(ShopData *shop);

int main(void) {
    ShopData shop = {0};
    int menu_select;
    
    while(true) {
        printf("[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황, 4.상품명 입력, 5. 종료)\n >>>");
        scanf("%d", &menu_select);
        
        switch (menu_select) {
            case 1:
                handle_stock_input(&shop);
                break;
            case 2:
                handle_sale_input(&shop);
                break;
            case 3:
                display_status(&shop);
                break;
            case 4:
                display_names(&shop);
                break;
            case 5:
                return 0;
        }
    }
}

void handle_stock_input(ShopData *shop) {
    int sub_select, buy, stock_id;
    
    printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택 : ");
    scanf("%d", &sub_select);
    
    switch (sub_select) {
        case 1:
            printf("상품 개수: ");
            scanf("%d", &shop->product_count);
            printf("각 상품의 입고수량을 입력하세요: ");
            for (int i = 1; i <= shop->product_count; i++) {
                scanf("%d", &buy);
                shop->stock[i] += buy;
                shop->total_buy += buy;
            }
            break;
        case 2:
            printf("상품ID: ");
            scanf("%d", &stock_id);
            printf("입고수량: ");
            scanf("%d", &buy);
            shop->stock[stock_id] += buy;
            shop->total_buy += buy;
            if (stock_id > shop->product_count) {
                shop->product_count = stock_id;
            }
            break;
    }
}

void handle_sale_input(ShopData *shop) {
    int sub_select, sale, stock_id, sale_product_count;
    
    printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택 : ");
    scanf("%d", &sub_select);
    
    switch (sub_select) {
        case 1:
            printf("판매할 상품 개수: ");
            scanf("%d", &sale_product_count);
            printf("각 상품의 판매수량을 입력하세요: ");
            for (int i = 1; i <= sale_product_count; i++) {
                scanf("%d", &sale);
                if (shop->stock[i] >= sale) {
                    shop->stock[i] -= sale;
                    shop->total_sale += sale;
                    shop->sales[i] += sale;
                } else {
                    printf("상품ID %d: 재고 부족! (현재 재고: %d)\n", i, shop->stock[i]);
                }
            }
            break;
        case 2:
            printf("상품ID: ");
            scanf("%d", &stock_id);
            printf("판매수량: ");
            scanf("%d", &sale);
            if (shop->stock[stock_id] >= sale) {
                shop->stock[stock_id] -= sale;
                shop->sales[stock_id] += sale;
                shop->total_sale += sale;
            } else {
                printf("재고 부족! (현재 재고: %d)\n", shop->stock[stock_id]);
            }
            break;
    }
}

void display_status(ShopData *shop) {
    printf("\n상품재고현황: ");
    for (int i = 1; i <= shop->product_count; i++) {
        printf("%d ", shop->stock[i]);
    }
    printf("\n");
    
    float percent = (shop->total_buy > 0) ? 
                   ((float)shop->total_sale / (float)shop->total_buy) * 100 : 0;
    printf("총판매량 %d (판매율: %.2f%%)\n", shop->total_sale, percent);
    
    if (shop->product_count > 0) {
        int max_id = 1, min_id = 1;
        int max_sale = shop->sales[1];
        int min_sale = shop->sales[1];
        
        for (int i = 2; i <= shop->product_count; i++) {
            if (shop->sales[i] > max_sale) {
                max_id = i;
                max_sale = shop->sales[i];
            }
            if (shop->sales[i] < min_sale) {
                min_id = i;
                min_sale = shop->sales[i];
            }
        }
        
        printf("가장 많이 판매된 상품: ID %d, 상품명 : %s, 판매량 %d\n", max_id, shop->stock_name[max_id], max_sale);
        printf("가장 적게 판매된 상품: ID %d, 상품명 : %s, 판매량 %d\n", min_id, shop->stock_name[min_id], min_sale);
    }
    
    printf("\n재고 부족 상품:\n");
    for (int i = 1; i <= shop->product_count; i++) {
        if (shop->stock[i] <= 2) {
            printf("상품ID %d: 재고부족(%d)\n", i, shop->stock[i]);
        }
    }
    printf("\n");
}

void display_names(ShopData *shop) {
    for (int i = 1; i <= shop->product_count; i++) {
        printf("ID : %d 상품명 :",i);
        scanf("%s",shop->stock_name[i]);
    }
}
