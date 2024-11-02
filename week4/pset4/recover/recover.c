#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//to use BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //making sure to take the image file in the terminal as argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    //open memory card
    FILE *memoryCard = fopen(argv[1], "r");

    //
    BYTE buffer[512];
    int counter = 0;
    //creating a file pointer to use later on
    FILE *restoredImage = NULL;

    //string array of size 8 to store the file name
    char *JPEG_filename = malloc(sizeof(BYTE));
    //making sure to not touching memory i shouldn't touch
    if (JPEG_filename == NULL)
    {
        return 2;
    }

    // repeat until end of card: read 512 bytes into a buffer
    while (fread(buffer, 1, 512, memoryCard) == 512)
    {
        //if start of new JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            //start writing 000.JPEG and start writing your very first file
            sprintf(JPEG_filename, "%03i.jpg", counter);
            restoredImage = fopen(JPEG_filename, "w");
            counter++;
        }

        if (counter != 0)
        {
            //write to the file
            fwrite(buffer, 1, 512, restoredImage);
        }

    }
    //close any remaining files
    fclose(memoryCard);
    fclose(restoredImage);
    //freeing JPEG_filename
    free(JPEG_filename);
}