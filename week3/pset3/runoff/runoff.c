#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //check if the name is valid
        if (strcmp(name, candidates[i].name) == 0)
        {
            //initializing prefereces
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //loop through each voter
    for (int i = 0; i < voter_count; i++)
    {
        //loop through each rank
        for(int j = 0; j < candidate_count; j++)
        {
            //update vote counts if the candidate aren't eliminated
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes += 1;
                //break from the loop
                j = candidate_count;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int half_the_vote;
    //check if voter_count is even or odd then calculate half_the_vote
    if (voter_count % 2 == 0)
    {
        half_the_vote = (int)ceil((float)voter_count / 2);
    }
    else
    {
        half_the_vote = (voter_count / 2) + 1;
    }
    //loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //print the winner if the number of votes he has is more than half of the votes
        if (candidates[i].votes > half_the_vote)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //initializing hold to the max number possible of voters
    int hold = voter_count;

    //loop through each candidate
    for (int i = 0; i < candidate_count - 1; i++)
    {
        //if the current candidate and the next candidate aren't eliminated
        if (!candidates[i].eliminated && !candidates[i + 1].eliminated)
        {
            //if the current candidate have greater than or equal number of votes of the next candidate, and his votes is less than hold
            if (candidates[i].votes <= candidates[i + 1].votes && candidates[i].votes < hold)
            {
                //assign the number of votes to hold
                hold = candidates[i].votes;
            }
            //if the next candidate have greater than or equal number of votes of the current candidate, and his votes is less than hold
            else if (candidates[i + 1].votes <= candidates[i].votes && candidates[i + 1].votes < hold)
            {
                //assign the number of votes to hold
                hold = candidates[i + 1].votes;
            }
        }
    }
    return hold;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int array[candidate_count];

    //loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //if the candidate isn't eliminated
        if (!candidates[i].eliminated)
        {
            //add the candidate index to the array
            array[i] = i;
        }
        else
        {
            //add MAX_CANDIDATES to the array
            array[i] = MAX_CANDIDATES;
        }

        //return false if the element of the array isn't equal to MAX_CANDIDATES, and the candidate votes aren't equal to min
        if (array[i] != MAX_CANDIDATES && candidates[array[i]].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //if the candidate isn't eliminated and he has the minimum number of votes
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            //eliminate the candidate
            candidates[i].eliminated = true;
        }
    }
}