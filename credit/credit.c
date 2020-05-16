// Checks Validity of a user-inputted credit card

#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    //User inputted # greater than 1
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);

    //Counts # of digits, m local variable
    int digit = 0;
    long m = n;
    do
    {
        digit ++;
        m = m / 10;
    }
    while (m != 0);

    //Displays # of digits
    printf("# of digits: %i\n", digit);
    printf("\n");
    
    //Creates an array from inputtted number
    int d[digit];
    for (int i = 0; i < digit; i++)
    {
        d[i] = n % 10;
        n = n / 10;
        printf("%i\n", d[i]);
    }
    
    //Creates a new array with every other digit multiplied by 2 
    //& sums those digits
    printf("\n");
    int e[digit];
    int sum_odd = 0;
    for (int j = 1; j <= digit; j = j + 2)
    {
        e[j] = d[j] * 2 ;
        printf("%i\n", e[j]);

        if (e[j] < 10)
        {
            sum_odd = sum_odd + e[j];
        }

        else if (e[j] >= 10)
        {   
            int dummy = e[j] / 10 + e[j] % 10;
            sum_odd = sum_odd + dummy;
        }
    }
    //Sum of every other digit
    printf("\n");
    printf("Sum of odds: %i\n", sum_odd);

    //Sum of the remaining digits
    int sum_even = 0;
    for (int k = 0; k < digit; k = k + 2)
    {
        d[k] = d[k];
        printf("%i\n", d[k]);
        sum_even = sum_even + d[k];
    }
    printf("\n");
    printf("Sum of even: %i\n", sum_even);

    //Sums & displays the two values above
    int sum_total = sum_odd + sum_even;
    printf("Sum of total: %i\n", sum_total);

    //Luhn's Algorithm Check for Validity
    if (sum_total % 10 != 0)
    {
        printf("INVALID\n");
    }

    //Checks if American Express
    else if 
    (digit == 15 && d[digit - 1] == 3)

        if (d[digit - 2] == 7 || d[digit - 2] == 4)
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }

    //Checks if Mastercard
    else if (digit == 16 && d[digit - 1] == 5)
    {
        if (d[digit - 2] == 1) 
        {
            
            printf("MASTERCARD\n");
        }

        else if (d[digit - 2] == 2) 
        {
            
            printf("MASTERCARD\n");
        }

        else if (d[digit - 2] == 3) 
        {
            
            printf("MASTERCARD\n");
        }

        else if (d[digit - 2] == 4) 
        {
            
            printf("MASTERCARD\n");
        }

        else if (d[digit - 2] == 5) 
        {
            
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    //Checks if VISA
    else if (digit == 16 && d[digit - 1] == 4)
    {

        printf("VISA\n");
    }

    else if (digit == 13 && d[digit - 1] == 4)
    {
        printf("VISA\n");

    }

    else
    {
        printf("INVALID\n");
    }
}


 
