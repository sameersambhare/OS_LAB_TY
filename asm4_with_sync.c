#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t resource;
pthread_mutex_t lock;
int total_amount = 2500;
int active_readers = 0;
void *add_money(void *x) {
    int cash = 750;
    sem_wait(&resource);
    total_amount += cash;
    printf("Writer %d credited Rs- %d. New balance: Rs- %d\n", *((int *)x), cash, total_amount);
    sem_post(&resource);
}

void *deduct_money(void *x) {
    int cash = 250;
    sem_wait(&resource);
    total_amount -= cash;
    printf("Writer %d debited Rs- %d. New balance: Rs- %d\n", *((int *)x), cash, total_amount);
    sem_post(&resource);
}

void *show_balance(void *x) {
    pthread_mutex_lock(&lock);
    active_readers++;
    if (active_readers == 1) {
        sem_wait(&resource);
    }
    pthread_mutex_unlock(&lock);
    printf("Reader %d checked balance: Rs- %d\n", *((int *)x), total_amount);
    pthread_mutex_lock(&lock);
    active_readers--;
    if (active_readers == 0) {
        sem_post(&resource);
    }
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t readers[6], writers[3];
    char actions[] = {'D', 'C', 'D'};
    pthread_mutex_init(&lock, NULL);
    sem_init(&resource, 0, 1);
    int ids[6] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, show_balance, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        if (actions[i] == 'C')
            pthread_create(&writers[i], NULL, add_money, &ids[i]);
        else
            pthread_create(&writers[i], NULL, deduct_money, &ids[i]);
    }
    for (int i = 3; i < 6; i++) {
        pthread_create(&readers[i], NULL, show_balance, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }
    for (int i = 3; i < 6; i++) {
        pthread_join(readers[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    sem_destroy(&resource);
    return 0;
}
