#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //prompt the user to write his name
    string name = get_string("What's your name? ");

    printf("Hello, %s\n", name);
}
