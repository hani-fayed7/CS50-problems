#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // alphabets array
    char alphabets[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // initializing the sum to 0
    int sum = 0;

    //check each character in the word
    for (int i = 0; i < strlen(word); i++)
    {
        //if that character is lower case then make it upper case
        if (islower(word[i]))
        {
            word[i] = toupper(word[i]);
        }

        //for loop that loops 25 times (we have 25 elements int the array alphabets and the array POINTS)
        for (int j = 0; j < 26; j++)
        {
            //check which alphabet is the character and the give it its value.
            if (word[i] == alphabets[j])
            {
                word[i] = POINTS[j];

                //add the value of the character to the sum
                sum += word[i];
            }
        }
    }

    return sum;
}