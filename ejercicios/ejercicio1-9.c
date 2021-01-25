#include <stdio.h>
int main(void)
{
    int a;
    // int b = scanf("%d", &a);
    // printf("numero scanf: %d\n",b);
    printf("enter a number: \n");
    while (scanf("%d", &a) != 1)
    {
        // input was not a number, ask again:
        printf("enter a number: ");
    }
    printf("You entered %d.\n", a);
}