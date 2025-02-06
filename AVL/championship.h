#include <iostream>
#include <list>

using namespace std;

#include "round.cpp"

struct round_node
{
  round_node() : key(1), left(nullptr), right(nullptr), height(1) {} // Default constructor

  round_node(Round num) : key(Round(num)), left(nullptr), right(nullptr), height(1) {} // Parameterized constructor

  Round key;
  round_node *left;
  round_node *right;
  int height;
};

#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

class championship
{
private:
  int season;
  string category;
  round_node *first;

  round_node *addRoundToTree(round_node *node, Round roundNum);
  round_node *rotateRight(round_node *y);
  round_node *rotateLeft(round_node *x);
  int getHeight(round_node *node);
  int getBalance(round_node *node);

  round_node *findRoundInTree(round_node *node, int roundNum);
  game *findGameInRound(Round *roundPtr, string awayTeam, string homeTeam);
  game *findGameInChampionship(round_node *node, string awayTeam, string homeTeam);
  void displayAllGamesInChampionship(round_node *node);
  void displayRoundGameInChampionship(round_node *node, string awayTeam, string homeTeam);
  Team findTeamInRoundTree(Round *roundPtr, string teamName);
  round_node *findLastRoundNode(round_node *node);

public:
  championship(int, string);
  void addRound(Round);           // function to create a bst of rounds
  round_node *findRound(int num); // function to search for a round in the bst, returns an iterator to the round
  Round *findLastRound();
  game *findRoundGame(string awayTeam, string homeTeam); // function to search for a game in the bst in a particular round, returns an iterator to the game
  void levelOrderTraversal();

  // getters
  int getSeason() const;
  string getCat() const;
  round_node *getRound(int n);

  // display functions
  //  for games
  void displayRoundGame(string awayTeam, string homeTeam); // display details of a given game by knowing only the name of the two teams ;
  void displayAllGamesInRound(int num);                    // display result of all games in a given round
  void displayAllGames();                                  // display result of all games in the championship

  // for players
  void displayPlayersStandingInTeams(int num, string team); // display players standings in a given team for a given round
  // need function also to display number of goals scored by a player untill a given round
  void displayPlayerStanding(string team); // display player data in the championship for a given team (final)
  void displayBestScorersStandings();      // display best Scorers standings in the championship

  // for teams
  void displayTeamPlayersInGame(string, string); // display data of players of a team in a given game(game details)
  void displayTeamsInRound(int num);             // display teams standings in a given round
  void displayTeamsStandings();                  // display results of standings in the whole championship

  void displayRoundScorers(int roundNum);
  void displayBestScorerInTeam(string team);

  // final result getters
  Team *findWinnerTeam();   // find the winner team
  Player *findBestScorer(); // find best scorer

  void displayWinner();
  void displayBestScorer();

  // function to get player's goals num in a round
  int getPlayerGoalInRound(int, string, string);
  int getPlayerGoalInRound(int, string, int);
  // function to get player's goals num in the whole championship
  int getPlayerGoalsInChamp(string, string);
  int getPlayerGoalsInChamp(string, int);
};

#endif