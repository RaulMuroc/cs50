from cs50 import get_int

while True:
    input = get_int("Input: ")
    if input >= 1 and input <= 8:
        for i in range(1, (input+1), 1):
            for Ldots in range((input-i), 0, -1):
                print(" ", end='')
            for j in range(1, (i+1), 1):
                print("#", end='')
            print("\n", end='')
        break
    else:
        print("Wrong input! try again.")