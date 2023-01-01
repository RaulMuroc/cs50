#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int number = 12457677;
    int modul = number % 10;
    int modul2 = number % 2;
    // do {
    //     modul = modul % 10;
         printf("rest10: %d, rest2: %d", modul, modul2);
    // } while (modul != 0);
    return 0;
}