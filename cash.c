#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        printf("Change owed: ");
        scanf("%f", &dollars);
    }
    while (dollars < 0);

    int cents = (int) round(dollars * 100);

    int coins = 0;
    int values[] = {25, 10, 5, 1};
    for (int i = 0; i < 4; i++)
    {
        coins += cents / values[i];
        cents %= values[i];
    }

    printf("%i\n", coins);
}
