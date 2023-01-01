#include <cs50.h>
#include <stdio.h>


// range 1-8 inclusive
// prompt for integer until one num between 1 and 8

// ex 4:
//    #
//   ##
//  ###
// ####

// 6
//      #
//     ##
//    ###
//   ####
//  #####
// ######

int main(void)
{
    while (true) {

        int input = get_int("Input: ");
        if ( input >= 1 && input <= 8) {
             //printf("Output: %i\n", input);

            for (int i = 1; i <= input; i++)
            {
                for (int Ldots = input - i; Ldots > 0; Ldots--){
                    printf(".");
                }
                for (int j = 1; j <= i; j++)
                {
                    printf("#");
                }
                printf("\n");
            }


            break;
        }
        else {
            printf("Wrong input! try again.");
            continue;

        }
    }
}