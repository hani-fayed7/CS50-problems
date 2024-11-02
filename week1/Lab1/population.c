#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Prompt for start size
    float startSize;
    do
    {
        startSize = get_float("Start size: ");
    }
    while (startSize < 9);

    //Prompt for end size
    float endSize;
    do
    {
        endSize = get_float("End size: ");
    }
    while (endSize < startSize);

    //Calculate number of years until we reach threshold
    float gain, lose;
    int numberOfYears = 0;

    while (startSize != endSize && startSize < endSize)
    {
        gain = startSize / 3;
        lose = startSize / 4;
        startSize = startSize + gain - lose;
        numberOfYears++;
    }
    numberOfYears--;

    //Print number of years
    printf("Years: %i\n", numberOfYears);
}
