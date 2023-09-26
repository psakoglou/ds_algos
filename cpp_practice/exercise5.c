#include <stdio.h>

int main()
{
    int i = 10;
    printf("Current value of i: %d\n", i);    // 10
    printf("value of i with i--: %d\n", i--); // 10
    printf("value of i after i-- %d\n", i);   // 9

    i = 10;
    printf("Current value of i: %d\n", i);    // 10
    printf("value of i with --i: %d\n", --i); // 9
    printf("value of i with --i: %d\n", --i); // 8

    return 0;
}