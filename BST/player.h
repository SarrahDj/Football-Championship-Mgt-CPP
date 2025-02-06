#include <iostream>
#include <string>
#include <stack>
#include "date.h"
#include "time.h" // including time class header

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

struct Details
{
    double distance;
    Time playingtime;
    Time replacementTime;
    Details(double d = 0, int ptime_min = 0, int ptime_sec = 0, int rep_min = 0, int rep_sec = 0) : distance(d), playingtime(ptime_min, ptime_sec), replacementTime(rep_min, rep_sec) {}
};

struct playerHistory
{
    string team;
    Date startDate;
    playerHistory(const string &teamName, const int &year = 0, const int &month = 0,
                  const int &day = 0) : startDate(day, month, year), team(teamName) {}
};

// Display object of the struct playerHistory
void displayPlayerHistoryObj(playerHistory &player)
{
    if (player.startDate.getYear() == 0)
    {
        cout << "Team: " << player.team << " (current) ";
    }
    else
    {
        cout << "Team: " << player.team << ", Start Date: ";
        player.startDate.displayDate();
    }
}

class Player
{
    friend class game;

private:
    string player_name;
    string team_name;
    string position;
    int playernumber;
    int yellowcards;
    int redcards;
    // distance information
    double avgDistance;
    int games;

    Time timeplaying;
    int goalscored;
    Details playerDetails;
    stack<playerHistory> history;

public:
    friend class game;
    // Constructor
    Player(string name, string pos, int pnum);

    // player setters:
    void setPlayerName(string name);
    void setPlayerNumber(int num);
    void setPlayerTeam(string team);
    void setPosition(string p);
    void newTeam(const string &teamN, const int &y = 0, const int &m = 0, const int &d = 0);
    void updateGameDetails(double d, int pmin = 0, int psec = 0, int rmin = 0, int rsec = 0);
    // functions to display
    void displayGameDetails() const;
    void displayPlayerHistory() const;
    // update functions
    void updateGoals(int x);
    void updateYellowCards(int x);
    void updateRedCards();
    void updateGameNum();

    // getters
    string getPlayerName() const;
    string getPosition() const;
    int getYelCards() const;
    int getRedCards() const;
    double getAvgDistance() const;
    int getGameNum() const;
    int getGoals() const;
    void getPlayingTime() const;
    int getPlayerNumber() const;
    string getPlayerTeamName() const;
    Details getPlayerDetails() const;

    void displayPlayerStanding() const;
    void displayPlayerDetailsinGame() const;
};
#endif
