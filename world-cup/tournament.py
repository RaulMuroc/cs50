# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # 1. read the team data from the CSV file into your program’s memory, and add each team to the list teams.
    # 2. The file to use will be provided as a command-line argument. You can access the name of the file, then, with sys.argv[1].
    # 3. Recall that you can open a file with open(filename), where filename is a variable storing the name of the file.
    # 4. Once you have a file f, you can use csv.DictReader(f) to give you a “reader”: an object in Python that you can loop over to read the file one row at a time, treating each row as a dictionary.
    # 5. By default, all values read from the file will be strings. So be sure to first convert the team’s rating to an int (you can use the int function in Python to do this).
    # 6. Ultimately, append each team’s dictionary to teams. The function call teams.append(x) will append x to the list teams.
    # 7. Recall that each team should be a dictionary with a team name and a rating.

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file (team,rating)
    with open(sys.argv[1]) as file:
        csv_reader = csv.reader(file, delimiter=',')
        for row in csv_reader:
            {'team': row[0], 'rating': row[1]}
    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # This function should accept as input a list of teams and should repeatedly simulate rounds until you’re left with one team. The function should the return the name of that team.
    # 1. You can call the simulate_round function, which simulates a single round, accepting a list of teams as input and returning a list of all of the winners.
    # 2. Recall that if x is a list, you can use len(x) to determine the length of the list.
    # 3. You should not assume the number of teams in the tournament, but you may assume it will be a power of 2.



if __name__ == "__main__":
    main()
