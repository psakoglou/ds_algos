#include <stdio.h>

int main()
{

    int married = 0; // false
    married ? printf(" married") : printf("not married");

    // single printf
    printf(married ? "married" : "not married");

    return 0;
}