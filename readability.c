#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char text[1024];

    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = 0, words = 1, sentences = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        char c = text[i];
        if (isalpha((unsigned char) c))
        {
            letters++;
        }
        else if (c == ' ')
        {
            words++;
        }
        else if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    double L = (letters / (double) words) * 100;
    double S = (sentences / (double) words) * 100;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) (index + 0.5);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
