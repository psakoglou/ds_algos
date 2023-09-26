// calculate the surface of a triangle

#include <stdio.h>

int main()
{
    float height, base;

    printf("please enter a height");
    scanf("%f", &height);

    printf("please enter a base");
    scanf("%f", &base);

    float area = (height / 2) * base;
    printf("The area of your triangle is %f", area);

    return 0;
}