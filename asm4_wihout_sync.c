#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int total_amount = 2500;
void *add_money(void *x) {
    int cash = 700;
    total_amount += cash;
    printf("Writer %d credited Rs- %d. New balance: Rs- %d\n", *((int *)x), cash, total_amount);
}

void *deduct_money(void *x) {
    int cash = 400;
    total_amount -= cash;
    printf("Writer %d debited Rs- %d. New balance: Rs- %d\n", *((int *)x), cash, total_amount);
}

void *show_balance(void *x) {
    printf("Reader %d checked balance: Rs- %d\n", *((int *)x), total_amount);
}

int main() {
    pthread_t readers[6], writers[3];
    char actions[] = {'D', 'C', 'D'};
    int ids[6] = {1, 2, 3, 4, 5, 6};
    for(int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, show_balance, &ids[i]);
    }
    for(int i = 0; i < 3; i++) {
        if(actions[i] == 'C')
            pthread_create(&writers[i], NULL, add_money, &ids[i]);
        else
            pthread_create(&writers[i], NULL, deduct_money, &ids[i]);
    }
    for(int i = 3; i < 6; i++) {
        pthread_create(&readers[i], NULL, show_balance, &ids[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }
    for(int i = 3; i < 6; i++) {
        pthread_join(readers[i], NULL);
    }
    return 0;
}
