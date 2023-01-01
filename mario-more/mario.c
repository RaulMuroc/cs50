#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // main while to loop everything
    while (true)
    {
        // retrieve the input of the user
        int input = get_int("Input: ");
        // check that input range is correct
        if (input >= 1 && input <= 8)
        {
            for (int i = 1; i <= input; i++)
            {
                // draw the dots
                for (int Ldots = input - i; Ldots > 0; Ldots--)
                {
                    printf(" ");
                }
                // draw the squares
                for (int j = 1; j <= i; j++)
                {
                    printf("#");
                }
                // draw the dots
                printf("  ");
                for (int Ldots = 1; Ldots <= i; Ldots++)
                {
                    printf("#");
                }
                printf("\n");
            }
            break;
        }
        else
        {
            // return error
            printf("Wrong input! try again.");
            continue;
        }
    }
}