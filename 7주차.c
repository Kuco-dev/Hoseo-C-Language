#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTS 5

typedef struct {
    int id;
    char name[50];
    int price;
    int stock;
    int sales;
    int total_sales_amount;
} Product;

typedef struct {
    Product products[MAX_PRODUCTS];
    int product_count;
    int total_buy;
    int total_sale;
} ShopData;

void handle_stock_input(ShopData *shop);
void handle_sale_input(ShopData *shop);
void display_individual_status(ShopData *shop);
void display_status(ShopData *shop);
int find_product(ShopData *shop, int id);

int main(void) {
    ShopData shop = {0};
    int menu_select;
    
    while(true) {
        printf("[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n >>>");
        scanf("%d", &menu_select);
        
        switch (menu_select) {
            case 1: handle_stock_input(&shop); break;
            case 2: handle_sale_input(&shop); break;
            case 3: display_individual_status(&shop); break;
            case 4: display_status(&shop); break;
            case 5: return 0;
        }
    }
}

int find_product(ShopData *shop, int id) {
    for (int i = 0; i < shop->product_count; i++) {
        if (shop->products[i].id == id) return i;
    }
    return -1;
}

void handle_stock_input(ShopData *shop) {
    int stock_id, buy, idx;
    
    printf("상품ID : ");
    scanf("%d", &stock_id);
    
    idx = find_product(shop, stock_id);
    
    if (idx != -1) {
        printf("상품명 : ");
        scanf("%s", shop->products[idx].name);
        printf("입고량 : ");
        scanf("%d", &buy);
        printf("판매가격 : ");
        scanf("%d", &shop->products[idx].price);
        shop->products[idx].stock += buy;
        shop->total_buy += buy;
    } else {
        if (shop->product_count >= MAX_PRODUCTS) {
            printf("상품 갯수 초과!\n");
            return;
        }
        Product *p = &shop->products[shop->product_count];
        p->id = stock_id;
        printf("상품명 : ");
        scanf("%s", p->name);
        printf("입고량 : ");
        scanf("%d", &buy);
        printf("판매가격 : ");
        scanf("%d", &p->price);
        p->stock = buy;
        p->sales = 0;
        p->total_sales_amount = 0;
        shop->product_count++;
        shop->total_buy += buy;
    }
}

void handle_sale_input(ShopData *shop) {
    int stock_id, sale, idx;
    
    printf("상품ID : ");
    scanf("%d", &stock_id);
    
    idx = find_product(shop, stock_id);
    
    if (idx == -1) {
        printf("오류: 해당 상품 ID가 존재하지 않습니다.\n");
        return;
    }
    
    printf("판매량 : ");
    scanf("%d", &sale);
    
    if (shop->products[idx].stock >= sale) {
        shop->products[idx].stock -= sale;
        shop->products[idx].sales += sale;
        shop->products[idx].total_sales_amount += sale * shop->products[idx].price;
        shop->total_sale += sale;
    } else {
        printf("재고 부족! (현재 재고: %d)\n", shop->products[idx].stock);
    }
}

void display_individual_status(ShopData *shop) {
    int stock_id, idx;
    
    printf("상품ID : ");
    scanf("%d", &stock_id);
    
    idx = find_product(shop, stock_id);
    
    if (idx == -1) {
        printf("오류: 해당 상품 ID가 존재하지 않습니다.\n");
        return;
    }
    
    Product *p = &shop->products[idx];
    printf("\n상품ID : %d\n", p->id);
    printf("상품명 : %s\n", p->name);
    printf("가격 : %d\n", p->price);
    printf("재고 : %d\n", p->stock);
    printf("판매량 : %d\n", p->sales);
    printf("총판매금액 : %d\n\n", p->total_sales_amount);
}

void display_status(ShopData *shop) {
    printf("\n상품재고현황: ");
    for (int i = 0; i < shop->product_count; i++) {
        printf("%d ", shop->products[i].stock);
    }
    printf("\n");
    
    float percent = (shop->total_buy > 0) ? 
                   ((float)shop->total_sale / (float)shop->total_buy) * 100 : 0;
    printf("총판매량 %d (판매율: %.2f%%)\n", shop->total_sale, percent);
    
    if (shop->product_count > 0) {
        int max_idx = 0, min_idx = 0;
        
        for (int i = 1; i < shop->product_count; i++) {
            if (shop->products[i].sales > shop->products[max_idx].sales) max_idx = i;
            if (shop->products[i].sales < shop->products[min_idx].sales) min_idx = i;
        }
        
        printf("가장 많이 판매된 상품: ID %d, 상품명 : %s, 판매량 %d\n", 
               shop->products[max_idx].id, shop->products[max_idx].name, shop->products[max_idx].sales);
        printf("가장 적게 판매된 상품: ID %d, 상품명 : %s, 판매량 %d\n", 
               shop->products[min_idx].id, shop->products[min_idx].name, shop->products[min_idx].sales);
    }
    
    printf("\n재고 부족 상품:\n");
    for (int i = 0; i < shop->product_count; i++) {
        if (shop->products[i].stock <= 2) {
            printf("상품ID %d: 재고부족(%d)\n", shop->products[i].id, shop->products[i].stock);
        }
    }
    printf("\n");
}
