#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void decimalToBinary(int decimal); //function prototype

int main(void)
{
    int decimal;

    //prompt the user to enter a message
    string message = get_string("Message: ");

    //go in each character in the message
    for (int i = 0; i < strlen(message); i++)
    {
        //assign the ASCII value of the character to decimal
        decimal = message[i];

        //call the function
        decimalToBinary(decimal);

        //go to new line
        printf("\n");
    }
}

void decimalToBinary(int decimal)
{
    //array that stores first binary 8 bits values in decimal
    int array[BITS_IN_BYTE];

    //initializing the first element to 1
    array[0] = 1;

    //initializing the array
    for (int i = 0; i < BITS_IN_BYTE - 1; i++)
    {
        array[i + 1] = array[i] * 2;
    }

    //go in each element of the array but backwards to start from the most significant bit
    for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
    {
        //the bit is 1
        if (decimal >= array[j])
        {
            print_bulb(1);
            //substract the element of the array from the decimal value  of the character
            decimal -= array[j];
        }
        //the bit is 0
        else if (decimal < array[j])
        {
            print_bulb(0);
        }
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}