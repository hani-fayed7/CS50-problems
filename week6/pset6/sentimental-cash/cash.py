from cs50 import get_float


def main():
    while True:
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break

    cents = int(dollars * 100)

    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    print(f"cents {cents}")
    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents -= pennies * 1

    print(f"{quarters} and {dimes} and {nickels} and {pennies}")
    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


def calculate_quarters(cents):  # 25
    return conditionsFordnp(cents, 25, 24)


def calculate_dimes(cents):  # 10
    return conditionsFordnp(cents, 10, 9)


def calculate_nickels(cents):  # 5
    return conditionsFordnp(cents, 5, 4)


def calculate_pennies(cents):  # 1
    for n in range(cents):
        if (cents == n+1):
            return n+1
    return 0


def conditionsFordnp(cents,  h,  f):
    for n in range(cents):
        if (cents >= (n * h) and cents <= ((n * h) + f)):
            return n
    return 0


main()

