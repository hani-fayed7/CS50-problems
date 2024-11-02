#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE *red, *green, *blue;
    int average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = &(image[i][j].rgbtRed);
            green = &(image[i][j].rgbtGreen);
            blue = &(image[i][j].rgbtBlue);

            average = (int)round((float)(*red + *green + *blue)/ 3);

            *red = average;
            *green = average;
            *blue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE *red, *green, *blue;


    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = &(image[i][j].rgbtRed);
            green = &(image[i][j].rgbtGreen);
            blue = &(image[i][j].rgbtBlue);

            sepiaRed = (int)round((0.393 * (*red)) + (0.769 * (*green)) + (0.189 * (*blue)));
            sepiaGreen = (int)round((0.349 * (*red)) + (0.686 * (*green)) + (0.168 * (*blue)));
            sepiaBlue = (int)round((0.272 * (*red)) + (0.534 * (*green)) + (0.131 * (*blue)));

            if (sepiaRed >= 0 && sepiaRed <= 255)
            {
                *red = sepiaRed;
            }
            else
            {
                *red = 255;
            }
            if (sepiaGreen >= 0 && sepiaGreen <= 255)
            {
                *green = sepiaGreen;
            }
            else
            {
                *green = 255;
            }
            if (sepiaBlue >= 0 && sepiaBlue <= 255)
            {
                *blue = sepiaBlue;
            }
            else
            {
                *blue = 255;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = (int)round((float)width / 2);

    BYTE *firstRed, *firstGreen, *firstBlue, *lastRed, *lastGreen, *lastBlue;

    int *tempRed = malloc(sizeof(int));
    int *tempGreen = malloc(sizeof(int));
    int *tempBlue = malloc(sizeof(int));

    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j <= middle; j++)
        {
            firstRed = &(image[i][j].rgbtRed);
            firstGreen = &(image[i][j].rgbtGreen);
            firstBlue = &(image[i][j].rgbtBlue);

            while (k >= middle)
            {
                lastRed = &(image[i][k].rgbtRed);
                lastGreen = &(image[i][k].rgbtGreen);
                lastBlue = &(image[i][k].rgbtBlue);

                *tempRed = *firstRed;
                *firstRed = *lastRed;
                *lastRed = *tempRed;

                *tempGreen = *firstGreen;
                *firstGreen = *lastGreen;
                *lastGreen = *tempGreen;

                *tempBlue = *firstBlue;
                *firstBlue = *lastBlue;
                *lastBlue = *tempBlue;

                break;
            }
            k--;
        }
    }
    free(tempRed);
    free(tempGreen);
    free(tempBlue);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE *red, *green, *blue;

    int averageRed, averageGreen, averageBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = &(image[i][j].rgbtRed);
            green = &(image[i][j].rgbtGreen);
            blue = &(image[i][j].rgbtBlue);

            if (i == 0 && j == 0)
            {
                averageRed = (int)round((image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 3.0);
                averageGreen = (int)round((image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 3.0);
                averageBlue = (int)round((image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 3.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i == 0 && j == (width - 1))
            {
                averageRed = (int)round((image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 3.0);
                averageGreen = (int)round((image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 3.0);
                averageBlue = (int)round((image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 3.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i == (height - 1) && j == 0)
            {
                averageRed = (int)round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed+ image[i][j + 1].rgbtRed) / 3.0);
                averageGreen = (int)round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 3.0);
                averageBlue = (int)round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 3.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                averageRed = (int)round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed) / 3.0);
                averageGreen = (int)round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 3.0);
                averageBlue = (int)round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 3.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                averageRed = (int)round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 5.0);
                averageGreen = (int)round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 5.0);
                averageBlue = (int)round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 5.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i != 0 && i != (height - 1) && j == 0)
            {
                averageRed = (int)round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 5.0);
                averageGreen = (int)round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 5.0);
                averageBlue = (int)round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 5.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                averageRed = (int)round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed) / 5.0);
                averageGreen = (int)round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 5.0);
                averageBlue = (int)round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 5.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else if (i != 0 && i != (height - 1) && j == (width - 1))
            {
                averageRed = (int)round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 5.0);
                averageGreen = (int)round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 5.0);
                averageBlue = (int)round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 5.0);

                *red = averageRed ;
                *green = averageGreen;
                *blue = averageBlue;
            }
            else
            {
                averageRed = (int)round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 8.0);
                averageGreen = (int)round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 8.0);
                averageBlue = (int)round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 8.0);

                *red = averageRed;
                *green = averageGreen;
                *blue = averageBlue;
            }
        }
    }
}