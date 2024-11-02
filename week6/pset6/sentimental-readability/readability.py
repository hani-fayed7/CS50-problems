# Prompt the user to enter some text
text = input("Text:")

# Initializing letters, words and sentences
letters = 0
words = 1
sentences = 0

for check in text:
    # To calculate the number of letters: count the nb of uppercase and lowercase letters in a text
    if check.isalpha() == True:  # The function isalpha() is a built-in function that checks if the character is a letter and returns true if it is, and returns false if it doesn't
        letters += 1

    # To calculate the number of words: count nb of words in a sentence, a word is any sequence of characters separated by a space (count spaces and add 1)
    elif check == " ":
        words += 1

    # To calculate the number of sentences: for this problem any period, exclamation pt, or question mark indicates a sentence
    elif check in [".", "?", "!"]:
        sentences += 1

# L is average number of letters per  100 words
L = letters / words * 100

# S is average number of sentences per 100 words
S = sentences / words * 100

# Coleman-Liau index formula
index = 0.0588 * L - 0.296 * S - 15.8

# Round index to the nearest integer
x = round(index)

# Printing grades
if x < 1:
    print("Before Grade 1")

elif x >= 16:
    print("Grade 16+")

else:
    print(f"Grade {x}")
