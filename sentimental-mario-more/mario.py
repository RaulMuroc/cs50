from cs50 import get_int

while True:
    # prompt the user for a number between 1 and 8 included
    num_levels = get_int("how many levels?\n")
    # check that input range is correct
    if num_levels > 0 and num_levels < 9:
        break

for i in range(0, num_levels, 1):
    for j in range(0, num_levels, 1):
        # draw the dots
        if (i+j < num_levels-1):
            print(".", end="")
        # draw the squares
        else:
            print("#", end="")
    print()