# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file

    # Open the file that is given as argument
    with open(sys.argv[1], "r") as file:
        # Read the file
        reader = csv.DictReader(file)
        # For each line in the file
        for line in reader:
            # Convert the rating of the team to an integer
            line["rating"] = int(line["rating"])
            # Append the line to the list teams as dictionary
            teams.append(line)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts

    for i in range(N):
        # Store the winning team by caling the function that returns the name of the winner
        winningTeam = simulate_tournament(teams)
        # if the winning team has won tournaments in the past so increment the number of winning by 1
        if winningTeam in counts:
            counts[winningTeam] += 1
        # else just count that the team has won just one tournament
        else:
            counts[winningTeam] = 1

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

    # Simulate tournament
    while len(teams) > 1:
        teams = simulate_round(teams)
    # return the name of the winner team
    return teams[0]["team"]


if __name__ == "__main__":
    main()
