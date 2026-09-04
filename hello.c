#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[64];

    printf("What's your name? ");
    if (fgets(name, sizeof(name), stdin) == NULL)
    {
        return 1;
    }
    name[strcspn(name, "\n")] = '\0';

    printf("hello, %s\n", name);
}
