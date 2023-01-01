#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int validate_key(string key);
bool only_digits(string text);
char rotate(char input, string rotation);

int main(int argc, string argv[])
{
    // check input that really is on 1 argument
    if (argc == 0 || argc > 2 || argv[1] == NULL)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check that input is built only by alpha characters
    bool are_only_alpha = validate_key(argv[1]);
    if (!are_only_alpha)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1]; // string argv[1] becomes an int
    string p_text = get_string("plaintext: ");

    // convert all to uppercase
    for (int i = 0; i < strlen(key); i++)
    {
        // check if lower case
        if (islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }

    // print some text for a nicer input ask
    printf("ciphertext: ");

    // variable initialization
    int i = 0;
    int l_text = strlen(p_text);
    char c_letter;
    char temp;

    // loop through letters to rotate
    do
    {
        c_letter = p_text[i];
        temp = rotate(c_letter, key);
        printf("%c", temp);
        i++;
    }
    while (i < l_text);

    // a nice return space
    printf("\n");

    return 0;
}

// this method validates the key, returns -1 if wrong
int validate_key(string text)
{
    // check key length
    int l_text = strlen(text);
    if (l_text != 26)
    {
        return false;
    }

    // check for a non-alphabetical character
    int x = 0;
    char arr[26];
    do
    {
        char c_char = text[x];
        arr[x] = c_char;
        // all have to be alhpa characters
        if (!isalpha(c_char))
        {
            return false;
        }
        x++;
    }
    while (x < l_text);

    // check for duplicated characters
    for (int i = 0; i < 26 - 1; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            // cannot be duplicated characters
            if (arr[i] == arr[j])
            {
                return false;
            }
        }
    }
    return true;
}

// rotates the input #rotation times
char rotate(char input, string rotation)
{
    // is alpha input?
    if (isalpha(input))
    {
        // is uppercase?
        if (isupper(input))
        {
            // correction
            int letter = input - 65;
            input = rotation[letter];
        }
        else
        {
            // correction
            int letter = input - 97;
            input = rotation[letter] + 32;
        }
    }
    return input;
}