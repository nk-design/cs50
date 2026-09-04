#include <stdio.h>

int main(void)
{
    long number;
    printf("Number: ");
    scanf("%ld", &number);

    long digits[16];
    int n = 0;
    for (long tmp = number; tmp > 0; tmp /= 10)
    {
        digits[n++] = tmp % 10;
    }

    if (n < 13 || n > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    int sum_others = 0;
    int sum_doubled = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            sum_others += digits[i];
        }
        else
        {
            int doubled = digits[i] * 2;
            sum_doubled += doubled / 10 + doubled % 10;
        }
    }

    if ((sum_others + sum_doubled) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    long first_two = digits[n - 1] * 10 + digits[n - 2];
    long first_one = digits[n - 1];

    if (n == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (n == 16 && first_two >= 51 && first_two <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((n == 13 || n == 16) && first_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
