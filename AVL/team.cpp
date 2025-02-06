#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "team.h"

#include "player.cpp"

using namespace std;

// creating list of teams of the league
list<Team *> LeagueTeams;

// constructor
Team::Team(string n, string c, string pres) : points(0), goalsScored(0), goalsReceived(0), gamesNum(0), redCards(0), yellowCards(0)
{
  setName(n);
  setCoach(c);
  setPresident(pres);
}

// setter functions
void Team::setName(const string &newName)
{
  teamName = newName;
}
void Team::setCoach(const string &newCoach)
{
  coach = newCoach;
}

void Team::setPresident(const string &newPresident)
{
  president = newPresident;
}

// getter functions

string Team::getCoach() const
{
  return coach;
}
string Team::getPresident() const
{
  return president;
}
int Team::getGoalsDiff() const { return goalsScored - goalsReceived; }
int Team::getYellowCards() const { return yellowCards; }
int Team::getRedCards() const { return redCards; }
int Team::getPoints() const { return points; }
int Team::getGoalsScored() const { return goalsScored; }
int Team::getGoalsRecieved() const { return goalsReceived; }
int Team::getGamesNum() const { return gamesNum; }
string Team::getTeamName() const { return teamName; }
list<Player> Team::getPlayersList() { return teamPlayers; }

// function that inserts one player in the list of players
void Team::addPlayer(Player player)
{
  teamPlayers.push_back(player);
  teamPlayers.back().setPlayerTeam(teamName);
}

// removing a player
void Team::removePlayer(Player player)
{
  for (auto it = teamPlayers.begin(); it != teamPlayers.end();)
  {
    if ((*it).getPlayerNumber() == player.getPlayerNumber())
    {
      it = teamPlayers.erase(it);
      break;
    }
    else
    {
      ++it;
    }
  }
}

// update
void Team::updateTeamPoints(int x)
{
  points += x;
}

void Team::updateGoalsScored(int x)
{
  goalsScored += x;
}

void Team::updateGoalsReceived(int x)
{
  goalsReceived += x;
}

void Team::updateTeamGames()
{
  gamesNum = gamesNum + 1;
}
void Team::UpdateYellowCards()
{
  yellowCards++;
}

void Team::UpdateRedCards()
{
  redCards++;
}

// function to find a player in a given team by name
Player *Team::findPlayer(string name)
{
  for (auto it = teamPlayers.begin(); it != teamPlayers.end(); it++)
  {
    if ((*it).getPlayerName() == name)
    {
      return &(*it);
    }
  }
  return nullptr; // Return nullptr if the player is not found
}

// function to find a player in a given team by number
Player *Team::findPlayer(int num)
{
  for (auto it = teamPlayers.begin(); it != teamPlayers.end(); it++)
  {
    if ((*it).getPlayerNumber() == num)
    {
      return &(*it);
    }
  }
  return nullptr; // Return nullptr if the player is not found
}

void Team::displayTeamPlayers() const
{

  cout << setw(25) << left << "Player Name";
  cout << setw(15) << left << "Team Name";
  cout << setw(8) << left << "Number";
  cout << setw(25) << left << "Position";
  cout << setw(15) << left << "Game";
  cout << setw(15) << left << "Goals";
  cout << setw(15) << left << "Yellow Cards";
  cout << setw(15) << left << "Red Cards";
  cout << setw(15) << left << "Avg Distance";
  cout << setw(15) << left << "Playing Time";
  cout << endl;

  int i = 1;
  cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  for (auto it : teamPlayers)
  {
    it.displayPlayerStanding();
    i++;
  }
}

void Team::displayTeamPlayersGameDetails() const
{

  cout << setw(20) << left << "Player Name";
  cout << setw(20) << left << "Position";
  cout << setw(10) << left << "Number";
  cout << setw(10) << left << "Distance";
  cout << setw(20) << left << "playing time";
  cout << setw(20) << left << "replacement time";
  cout << endl;

  for (auto it : teamPlayers)
  {

    it.displayPlayerDetailsinGame();
  }
}

void Team::sortPlayersByGoals()
{
  teamPlayers.sort([](const Player &a, const Player &b)
                   { return a.getGoals() > b.getGoals(); });
}

void Team::displayTeamDetails() const
{
  cout << "Team Name: " << teamName << endl;
  cout << "Coach: " << coach << endl;
  cout << "President: " << president << endl;
}

// function to update team order in championship
void sortLeagueTeams()
{
  LeagueTeams.sort([](Team *a, Team *b)
                   { return a->getPoints() > b->getPoints(); });
}

Team *findLeagueTeam(string teamName)
{

  auto it = LeagueTeams.begin();

  for (; it != LeagueTeams.end(); it++)
  {
    if ((*it)->getTeamName() == teamName)
      return (*it);
  }

  return nullptr;
}

void displayLeagueTeams()
{
  cout << "Teams Standings in the championship: " << endl;

  int order = 1;
  cout << setw(5) << "Order" << setw(20) << left << "Team Name" << setw(10) << left << "Points"
       << setw(15) << left << "Goals Scored" << setw(15) << left << "Goals Received"
       << setw(20) << left << "Goals Difference" << setw(15) << "Yellow Cards"
       << setw(10) << left << "Red Cards" << setw(15) << left << "Games Played" << endl;
  cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;

  for (auto it = LeagueTeams.begin(); it != LeagueTeams.end(); ++it)
  {
    cout << setw(5) << order << setw(20) << left << (*it)->getTeamName() << setw(10) << left << (*it)->getPoints()
         << setw(15) << left << (*it)->getGoalsScored() << setw(15) << left << (*it)->getGoalsRecieved()
         << setw(20) << left << (*it)->getGoalsDiff() << setw(15) << left << (*it)->getYellowCards()
         << setw(10) << left << (*it)->getRedCards() << setw(15) << left << (*it)->getGamesNum() << endl;

    order++;
  }
}

// function to initialise teams of the league
void addLeagueTeam(Team *teamObject)
{
  LeagueTeams.push_back(teamObject);
  sortLeagueTeams();
}
