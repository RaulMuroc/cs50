#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int find_index(const int a[],int size,int value);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // 1) it determines the winner of a short scrabble-like game
    // 2) 2 players, each enters its word
    // info: POINT[0] == 'a' or 'A' and so on...
    // GOAL: this function has to compute, using the POINTS array, and return the score for the string argument.
    //       Characters that are not letters should be given zero points, and uppercase and lowercase letters should be given the same point values.

    // pseudo-code
    // 1) OK get the lenght of the word
    // 2) OK loop throw the charaacters until reached length
    // 3) check each character if it is a character compresesd in the ASCCI table
    // 3.1) yes? retrieve the points from POINTS table and add to the sum
    // 3.2) no? then sum 0.
    // int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int minuscules[] = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    int majuscules[] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};

    int length = strlen(word);
    int i = 0;
    int sum = 0;
    do
    {
        char letter = word[i];
        int points = 0;
        int index = find_index( minuscules, 26, letter );
        if (index != -1)
        {
            sum += POINTS[index];
        }
        else
        {
            index = find_index( majuscules, 26, letter );
            if (index != -1)
            {
                sum += POINTS[index];
            }
        }
        i++;
    } while( i < length );

    return sum;
}

int find_index ( const int a[], int size, int value )
{
    int index = 0;

    while ( index < size && a[index] != value ) ++index;

    return ( index == size ? -1 : index );
}
