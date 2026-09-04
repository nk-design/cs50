#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);

    for (int row = 1; row <= height; row++)
    {
        for (int col = 0; col < height - row; col++)
        {
            printf(" ");
        }
        for (int col = 0; col < row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}
