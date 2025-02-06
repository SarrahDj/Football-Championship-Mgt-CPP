#include <iostream>
#include <string>
#include <list>
#include "player.h"

using namespace std;

#ifndef TEAM_H
#define TEAM_H

class Team
{
    friend class game;

private:
    string teamName;
    string coach;
    string president;
    int points;
    int goalsScored;
    int goalsReceived;
    int gamesNum;
    int yellowCards;
    int redCards;
    list<Player> teamPlayers;

    // setters
    void setName(const string &newName);
    void setCoach(const string &newCoach);
    void setPresident(const string &newPresident);

public:
    Team(string n = "", string c = "", string pres = "");

    // getters
    string getCoach() const;
    string getPresident() const;
    string getTeamName() const;
    int getGoalsDiff() const;
    int getYellowCards() const;
    int getRedCards() const;
    int getPoints() const;
    int getGoalsScored() const;
    int getGoalsRecieved() const;
    int getGamesNum() const;
    list<Player> getPlayersList();

    // function that inserts one player in the list of players
    void addPlayer(Player player);
    // function that removes one player in the list of players
    void removePlayer(Player player);

    // update functions
    void updateTeamPoints(int x);
    void updateGoalsScored(int x);
    void updateGoalsReceived(int x);
    void updateTeamGames();
    void UpdateYellowCards();
    void UpdateRedCards();

    // search functions
    Player *findPlayer(string name);
    Player *findPlayer(int num);

    // function to sort team players according to their goal number
    void sortPlayersByGoals();

    // display:
    void displayTeamPlayers() const;
    void displayTeamDetails() const;
    void displayTeamPlayersGameDetails() const;
};

#endif
