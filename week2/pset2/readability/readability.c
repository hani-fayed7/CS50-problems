#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //prompt the user to enter some text
    string text = get_string("Text:");

    float index;
    int letters = 0;
    int words = 1;
    int sentences = 0;


    //to calculate the number of letters: count the nb of uppercase and lowercase letters in a text
    for (int l = 0; l < strlen(text); l++)
    {
        if (islower(text[l]) || isupper(text[l]))
        {
            letters++;

        }
    }

    //to calculate the number of words: count nb of words in a sentence, a word is any sequence of characters separated by a space (count spaces and add 1)
    for (int w = 0; w < strlen(text); w++)
    {
        if (text[w] == ' ')
        {
            words++;

        }
    }

    //to calculate the number of sentences: for this problem any period, exclamation pt, or question mark indicates a sentence
    for (int s = 0; s < strlen(text); s++)
    {
        if (text[s] == '.' || text[s] == '?' || text[s] == '!')
        {
            sentences++;
        }
    }

    //L is average number of letters per  100 words
    //S is average number of sentences per 100 words
    float L, S;

    L = (float)letters / words * 100;
    S = (float)sentences / words * 100;

    index = 0.0588 * L - 0.296 * S - 15.8;

    //round index to the nearest integer
    int x = (int)round(index);

    //printing grades
    if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (x >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", x);
    }

}