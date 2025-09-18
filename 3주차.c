#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int product_count;
int sale_product_count;
int stock[101] = {0};
int buy;
int sale;
int menu_select, sub_select;
int stock_id;
int total_buy = 0;
int total_sale = 0;
int sale_figure[101] = {0};
int max_id = 1, min_id = 1;
int max = 0;
int min = 0;
float persent = 0;

void handle_stock_input(void);
void handle_sale_input(void);
void display_status(void);

int main(void){
    while(true) {
        printf("[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n >>>");
        scanf("%d",&menu_select);
        
        switch (menu_select) {
            case 1:
                handle_stock_input();
                break;
        
            case 2:
                handle_sale_input();
                break;
            
            case 3:
                display_status();
                break;
                
            case 4:
                return 0;
        }
    }
}

void handle_stock_input(void) {
    printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택 : ");
    scanf("%d",&sub_select);
    switch (sub_select) {
        case 1:
            scanf("%d",&product_count);
            for (int i = 1; i <= product_count; i++) {
                scanf("%d",&buy);
                stock[i] += buy;
                total_buy += buy;
            }
            break;
        
        case 2:
            printf("상품ID: ");
            scanf("%d",&stock_id);
            printf("입고수량: ");
            scanf("%d",&buy);
            stock[stock_id] += buy;
            total_buy += buy;
            break;
    }
}

void handle_sale_input(void) {
    printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택 : ");
    scanf("%d",&sub_select);
    switch (sub_select) {
        case 1:
            scanf("%d",&sale_product_count);
            for (int i = 1; i <= sale_product_count; i++) {
            scanf("%d",&sale);
            stock[i] = stock[i] - sale;
            total_sale = total_sale + sale;
            sale_figure[i] = sale_figure[i] + sale;
            }
            break;
        
        case 2:
            printf("상품ID: ");
            scanf("%d",&stock_id);
            printf("판매수량: ");
            scanf("%d",&sale);
            stock[stock_id] = stock[stock_id] - sale;
            sale_figure[stock_id] = sale_figure[stock_id] + sale;
            total_sale = total_sale + sale;
            break;
    }
}

void display_status(void) {
    printf("상품재고현황 :");
    for (int i = 1; i <= product_count; i++){
        printf("%d ",stock[i]);
    }
    
    persent = ((float)total_sale / (float)total_buy) * 100;
    
    printf ("총판매량 %d (판매율 : %.2f % ) \n",total_sale, persent);
    
    max = sale_figure[1];
    min = sale_figure[1];
    max_id = 1;
    min_id = 1;
    
    for (int i = 1; i <= product_count; i++){
        if (sale_figure[i] > max){
            max_id = i;
            max = sale_figure[i];
        } 
        if (sale_figure[i] < min){
            min_id = i;
            min = sale_figure[i];
        }
    }
    printf("가장많이 판매된 상품: ID : %d, 판매량 : %d\n", max_id, max);
    printf("가장적게 판매된 상품: ID : %d, 판매량 : %d\n", min_id, min);
    
    for (int i = 1; i <= product_count; i++){
        if (stock[i] <= 2) printf("상품ID %d : 재고부족(%d)\n", i, stock[i]);
    }
}
