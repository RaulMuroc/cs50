#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string text);
char rotate(char input, int rotation);

int main(int argc, string argv[])
{
    // check input that really is on 1 argument
    if (argc == 0 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (argv[1] == NULL)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // check that input is built only by digits
    bool are_only_digits = only_digits(argv[1]);
    if (!are_only_digits)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int converted_argv = atoi(argv[1]); // string argv[1] becomes an int
    string p_text = get_string("plaintext:  ");
    int i = 0;
    int l_text = strlen(p_text);
    char c_letter;
    char temp;

    printf("ciphertext: ");

    // cyphers letter-by-letter and prints them
    do
    {
        c_letter = p_text[i];
        temp = rotate(c_letter, converted_argv);
        printf("%c", temp);
        i++;
    }
    while (i < l_text);

    printf("\n");

    return 0;
}

// returns true when only digits present
bool only_digits(string text)
{
    int i = 0;
    int l_text = strlen(text);

    do
    {
        char c_char = text[i];
        if (!isdigit(c_char))
        {
            return false;
        }
        i++;
    }
    while (i < l_text);
    return true;
}

// rotates the input #rotation times
char rotate(char input, int rotation)
{
    // a 97 ..... z 122
    // A 65...Z 90
    // "barfoo" => "yxocll" with key 65
    // ci = (pi + k) % 26
    //char alpha_index[] = {'A','B', 'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //char alpha_m_index[] = {a','b','c','d','e','f','g','h','i','j'};
    if (isalpha(input))
    {
        if (isupper(input))
        {
            input = (input - 65 + rotation) % 26 + 65;
        }
        else
        {
            input = (input - 97 + rotation) % 26 + 97;
        }
    }
    return input;
}