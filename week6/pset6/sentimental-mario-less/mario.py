# Repeat forever
while True:
    # Try taking from the user an integer
    try:
        height = int(input("Height: "))
    # If the user did not type an integer
    except ValueError:
        print("!!! Height must be an integer !!!")
    # If he did typed an integer
    else:
        # If height is between 0 and 9
        if height >= 1 and height <= 8:
            # Exit the while loop
            break
        else:
            print("!!! Height must be between 0 and 9 !!!")

space = height - 1
# Loop form 0 to height
for i in range(height):
    # Loop to print spaces
    for s in range(space):
        print(" ", end="")

    # Print starting from 1
    print("#" * (i + 1))
    space -= 1