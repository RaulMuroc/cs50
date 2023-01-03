from cs50 import get_float

count = 0
cents = -1

#  Ask how many cents the customer is owed
while cents < 0:
    cents = get_float("How many cents do you have?")

cents = round(cents*100)

#  Calculate the number of quarters to give the customer
while cents >= 25:
    cents = cents - 25
    count += 1

#  Calculate the number of dimes to give the customer
while cents >= 10:
    cents = cents - 10
    count += 1

#  Calculate the number of nickels to give the customer
while cents >= 5:
    cents = cents - 5
    count += 1

#  Calculate the number of pennies to give the customer
while cents > 0:
    cents = cents - 1
    count += 1

#  Print total number of coins to give the customer
print(f"{count} \n", end="")