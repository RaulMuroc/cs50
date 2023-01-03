#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // initialitzations
    string text_user = get_string("Text: ");
    int num_l = strlen(text_user);
    int c_l = count_letters(text_user);
    int c_w = count_words(text_user);
    int c_s = count_sentences(text_user);
    float c_l_f = (float)c_l;
    float c_w_f = (float)c_w;
    float c_s_f = (float)c_s;

    float step = 0.0588 * (c_l_f / c_w_f * 100) - 0.296 * (c_s_f / c_w_f * 100) - 15.8;
    int index = round(step);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// returs number of letters
int count_letters(string text)
{
    int n_l = 0;
    int i = 0;
    int length_text = strlen(text);

    do
    {
        int curr_letter = text[i];
        if ((curr_letter >= 65 && curr_letter <= 90) || (curr_letter >= 97 && curr_letter <= 122))
        {
            n_l += 1;
        }
        i++;
    }
    while (i < length_text);

    return n_l;
}

// returs number of words
int count_words(string text)
{
    int n_w = 0;
    int i = 0;
    int length_text = strlen(text);

    do
    {
        int curr_letter = text[i];
        if (isspace(curr_letter))
        {
            n_w += 1;
        }
        i++;
    }
    while (i < length_text);

    n_w += 1; // 54 whitespaces, meaning 55 words
    return n_w;
}

// returs number of sentencess
int count_sentences(string text)
{
    int n_s = 0;
    int i = 0;
    int length_text = strlen(text);

    do
    {
        int curr_letter = text[i];
        if (curr_letter == 46 || curr_letter == 33 || curr_letter == 63)
        {
            n_s += 1;
        }
        i++;
    }
    while (i < length_text);

    return n_s;
}