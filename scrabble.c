#include <stdio.h>
#include <string.h>
#include <ctype.h>

int score(const char *word);

int main(void)
{
    char word1[32], word2[32];

    printf("Player 1: ");
    scanf("%31s", word1);
    printf("Player 2: ");
    scanf("%31s", word2);

    int score1 = score(word1);
    int score2 = score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(const char *word)
{
    const int values[26] =
    {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    int total = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha((unsigned char) word[i]))
        {
            total += values[toupper((unsigned char) word[i]) - 'A'];
        }
    }
    return total;
}
