#include <stdio.h>

int main(void)
{
    char name[40];
    printf("What's your name? ");
    scanf("%39s", name);
    printf("Hello %s!\n", name);
}
