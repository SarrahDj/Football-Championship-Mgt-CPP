
#include <iostream>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;

#include "team.cpp"


struct goalscorer
{
  string playername;
  int goalsnum;
  string teamName;
  goalscorer(string player, int numofgoals, string team) : playername(player), goalsnum(numofgoals), teamName(team) {}
};

struct yellowcards
{
  int playernumber;
  Team team;
  int cardsnum;

  yellowcards(int pn, Team t, int cn)
  {
    playernumber = pn;
    team = t;
    cardsnum = cn;
  }
};

struct redcards
{
  int playernumber;
  Team team;
  redcards(int pn, Team t)
  {
    playernumber = pn;
    team = t;
  }
};

#ifndef GAME_H
#define GAME_H
class game
{

private:
  Team* away;
  Team* home;
  Date dt;
  int starttime;
  int scorea;
  int scoreh;
  float duration;
  list<goalscorer> goalscorersA;
  list<goalscorer> goalscorersH;
  list<yellowcards> ycards;
  list<redcards> rcards;

  int homePlayers[11];
  int awayPlayers[11];

public:
  game(Team* t1, Team* t2, int,int,int, int sa, int sh, int st, float dur, int a[], int h[]);
 

  // function that specifies each team players for the game:
  void setHomePlayers(int a[]);
  void setAwayPlayers(int a[]);

  void addgoalscorerA(string pname, int goals);

  void addgoalscorerH(string pname, int goals);

  void addyelcard(int pnumber, Team t, int cn);
  void addredcard(int pn, Team t);

  void updatePoints();

  void displayGame();

  void replace(string teamName, int p1);
  // getters:
  //returns goal scorers
  list<goalscorer> getGoalScorersH();
   list<goalscorer> getGoalScorersA();

  //returns home name:
  string getHname() ;
  //returns away name:
  string getAname() ;
  //returns home:
  Team* getHome();
  //returns away: 
  Team* getAway();
};
#endif
