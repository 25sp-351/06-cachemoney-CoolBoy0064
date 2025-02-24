#ifndef MEMOIZE_H
#define MEMOIZE_H

unsigned long long int memoized_fibonacci(int input);
void add_to_memo(unsigned long long int value, int key);
unsigned long long int check_memo(int key);
void initalize_memo();
int (*memoized_function)(int, char[]);

#endif