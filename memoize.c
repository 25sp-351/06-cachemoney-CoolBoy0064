#include <stdio.h>
#include <string.h>

#define CACHE_SIZE 1501
const char EMPTY[] = "-1";
int (*memoized_function)(int, char[]);

char memo[1501][150];

void initalize_memo(){
    for(int i = 0; i < CACHE_SIZE; i++){
        strcpy(memo[i], EMPTY);
    }

}

int check_memo(int key, char result[]){
    if(key >= CACHE_SIZE || key < 0){
        return 0;
    }
    if(strcmp(memo[key], EMPTY) != 0){
        strcpy(result, memo[key]);
        return 1;
    }
    return 0;
}

void add_to_memo(char value[], int key){
    if(key >= CACHE_SIZE || key < 0){
        return;
    }
    strcpy(memo[key], value);
}

int memoized_currency(int currency, char result[]){
    int check = check_memo(currency, result);
    if(check == 1){
        printf("Cache hit\n");
        return 1;
    }
    (*memoized_function)(currency, result);
    add_to_memo(result, currency);
    return 0;

    
}