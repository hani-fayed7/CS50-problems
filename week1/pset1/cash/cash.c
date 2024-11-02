#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);
int conditionsFordnp(int cents, int h, int f);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int numberOfCents;
    do
    {
        numberOfCents = get_int("Change owed: ");
    }
    while (numberOfCents < 0);

    return numberOfCents;
}

int calculate_quarters(int cents) //25
{
    return conditionsFordnp(cents, 25, 24);
}

int calculate_dimes(int cents) //10
{
    return conditionsFordnp(cents, 10, 9);
}

int calculate_nickels(int cents) //5
{
    return conditionsFordnp(cents, 5, 4);
}

int calculate_pennies(int cents) //1
{
    for (int n = 1; n <= cents; n++)
    {
        if (cents == n)
        {
            return n;
        }
    }
    return 0;
}

int conditionsFordnp(int cents, int h, int f)
{
    for (int n = 1; n <= cents; n++)
    {
        if (cents >= (n * h) && cents <= ((n * h) + f))
        {
            return n;
        }
    }
    return 0;
}