#include <iostream>
#include <set>
#include "round.h"

// constructor
Round::Round(int num) : roundNum(num)
{
}

void Round::addGame(game newGame)
{
    games.push_back(newGame);

    teams.push_back(*newGame.getAway());
    teams.push_back(*newGame.getHome());
    sortLeagueTeams();
    sortRoundTeams();

    auto it = LeagueScorers.begin();
    for (int i = 0; i < LeagueScorers.size(); i++)
    {
        Player &currentScorer = *(*it);

        // Check if the scorer is already in scorers
        bool isDuplicate = false;
        for (auto &scorer : scorers)
        {
            if (scorer.getPlayerName() == currentScorer.getPlayerName())
            {
                isDuplicate = true;
                break;
            }
        }

        // If not a duplicate, add to scorers
        if (!isDuplicate)
        {
            scorers.push_back(currentScorer);
        }

        it++;
    }

    SortScorers(scorers.begin(), scorers.end());
}

// sorting the scorers
// Quicksort function for a list
void Round::SortScorers(typename list<Player>::iterator low, typename list<Player>::iterator high)
{
    if (distance(low, high) > 1)
    {
        auto pivot = partition(scorers, low, high);

        SortScorers(low, pivot);
        SortScorers(next(pivot), high);
    }
}

bool Round::compareGoalScorers(const Player &a, const Player &b)
{
    return a.getGoals() > b.getGoals();
}

auto Round::partition(list<Player> &scorers, typename list<Player>::iterator low, typename list<Player>::iterator high) -> typename list<Player>::iterator
{
    auto pivot = prev(high);
    auto i = prev(low);

    for (auto j = low; j != prev(high); ++j)
    {
        if (compareGoalScorers(*j, *pivot))
        {
            i = (i == scorers.end()) ? low : next(i);
            swap(*i, *j);
        }
    }
    i = (i == scorers.end()) ? low : next(i);
    swap(*i, *pivot);
    return i;
}

// finding a team in a certain game in a round:
Team *Round::findTeam(string team)
{
    auto it = teams.begin();
    for (; it != teams.end(); it++)
    {
        if ((it)->getTeamName() == team)
            return &(*it);
    }
    return nullptr;
}

// function to update team order in championship
void Round::sortRoundTeams()
{
    teams.sort([](const Team &a, const Team &b)
               { return a.getPoints() > b.getPoints(); });
}

// finding a game in a round
game *Round::findGame(string team)
{
    auto it = games.begin();
    for (int i = 0; i < games.size(); i++)
    {
        if (team == (*it).getHname() || team == (*it).getAname())
        {
            return &(*it);
        }
        else
            it++;
    }

    // If the team is not found in any game
    return nullptr;
}
game *Round::findGame(string away, string home)
{
    auto it = games.begin();
    for (int i = 0; i < games.size(); i++)
    {
        if (home == (*it).getHname() && away == (*it).getAname())
        {
            return &(*it);
        }
        else
            it++;
    }

    // If the team is not found in any game
    return nullptr;
}

// 5 display functions:
// 1- display a game in a round:
void Round::displayRoundGame(string team)
{
    game *GAME = (findGame(team));
    GAME->displayGame();
}

// 2- display teams order:
void Round::displayTeamsStanding()
{
    auto it = teams.begin();
    int order = 1;

    // Adjusted setw values for better alignment
    cout << setw(10) << left << "Order" << setw(29) << left << "Team Name" << setw(14) << left << "Points"
         << setw(19) << left << "Goals Scored" << setw(19) << left << "Goals Received"
         << setw(24) << left << "Goals Difference" << setw(19) << "Yellow Cards"
         << setw(19) << left << "Red Cards" << setw(19) << left << "Games Played" << endl;
    cout << endl;

    for (int i = 0; i < teams.size(); i++)
    {
        // Adjusted setw values for better alignment
        cout << setw(10) << left << order << setw(29) << left << (*it).getTeamName() << setw(14) << left << (*it).getPoints()
             << setw(19) << left << (*it).getGoalsScored() << setw(19) << left << (*it).getGoalsRecieved()
             << setw(24) << left << (*it).getGoalsDiff() << setw(19) << left << (*it).getYellowCards()
             << setw(19) << left << (*it).getRedCards() << setw(19) << left << (*it).getGamesNum() << endl;

        order++;
        it++;
    }
}

// 3- display scorers order:
void Round::displayScorersStanding()
{
    auto it = scorers.begin();
    int order = 1;
    cout << setw(20) << left << "Order" << setw(20) << left << "Player Name" << setw(20) << left << "Goals Scored"
         << setw(20) << left << "Team Name" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < scorers.size(); i++)
    {
        cout << setw(20) << left << order << setw(20) << left << (*it).getPlayerName() << setw(20) << left << (*it).getGoals()
             << setw(20) << left << (*it).getPlayerTeamName() << endl;

        order++;
        it++;
    }
}
 
// 4- display all round games:
void Round::displayGames()
{
    auto it = games.begin();
    int order = 1;
    for (int i = 0; i < games.size(); i++)
    {
        cout << endl;
        (*it).displayGame();
        cout << endl<<"===============================================================================" << endl;
        it++;
        order++;
    }
    cout << endl;
}

// 5- display players details in a certain team:
void Round::displayTeamPlayersStanding(string team)
{
    Team *teamObj = findTeam(team);
    teamObj->displayTeamPlayers();
}

// Getter functions 
list<Player> Round::getScorers() const
{
    return scorers;
}

list<Team> Round::getTeamsList() const
{
    return teams;
}

int Round::getRoundNum() const
{
    return roundNum;
}


