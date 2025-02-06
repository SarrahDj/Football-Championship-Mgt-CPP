#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include "date.h"
#include "player.h"

#include "team.h"
#include "game.cpp"

#ifndef ROUND_H
#define ROUND_H

using namespace std;

class Round
{
private:
   list<game> games;
   list<Team> teams;
   list<Player> scorers;
   int roundNum;

   //utility functions
   bool compareGoalScorers(const Player &a, const Player &b);
   auto partition(list<Player> &scorers, typename list<Player>::iterator low, typename list<Player>::iterator high) -> typename list<Player>::iterator;
   // sorting the scorers
   void SortScorers(typename list<Player>::iterator low, typename list<Player>::iterator high);
   // function to update team order in championship
   void sortRoundTeams();

public:
   // Constructor
   Round(int num);

   // inserting a game
   void addGame(game newGame);

   // finding a game in a round
   game *findGame(string);         // by one teeam
   game *findGame(string, string); // by two teams , home and away

   // finding a team in a certain game in a round:
   Team *findTeam(string team);

   // 5 display functions:
   // 1- display a game in a round:
   void displayRoundGame(string team);

   // 2- display teams order:
   void displayTeamsStanding();

   // 3- display scorers order:
   void displayScorersStanding();

   // 4- display all round games:
   void displayGames();

   // 5- display players details in a certain team:
   void displayTeamPlayersStanding(string team);

   // getter functions that returns list of scorers
   list<Player> getScorers() const;
   list<Team> getTeamsList() const;
   int getRoundNum() const;

};

#endif
