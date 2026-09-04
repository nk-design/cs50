#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2 || strlen(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit((unsigned char) argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]) % 26;

    char plaintext[1024];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char c = plaintext[i];
        if (isupper((unsigned char) c))
        {
            printf("%c", (c - 'A' + key) % 26 + 'A');
        }
        else if (islower((unsigned char) c))
        {
            printf("%c", (c - 'a' + key) % 26 + 'a');
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}
