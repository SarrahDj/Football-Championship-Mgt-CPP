#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <iomanip>
#include "player.h"

using namespace std;

// creating list of scorers of the league
list<Player *> LeagueScorers;

// player constructor
Player::Player(string name, string pos, int pnum)
{
    setPlayerName(name);
    setPlayerNumber(pnum);
    setPosition(pos);
    avgDistance = 0;
    yellowcards = 0;
    redcards = 0;
    timeplaying = 0;
    goalscored = 0;
    games = 0;
}

// player setters
void Player::setPlayerName(string name)
{
    player_name = name;
}

void Player::setPlayerNumber(int num)
{
    playernumber = num > 0 ? num : 0;
}

void Player::setPosition(string p)
{
    string positions[10] = {"GK", "RF", "LF", "CB", "DM", "RM", "CM", "ST", "AM", "LM"};

    for (char &c : p)
    {
        c = toupper(c);
    }
    for (int i = 0; i < 10; i++)
    {
        if (p == positions[i])
        {
            position = p;
            return;
        }
    }
    position = "undefined";
}

void Player::setPlayerTeam(string team)
{
    team_name = team;
    newTeam(team);
}

// adding information about the player new team in his history
void Player::newTeam(const string &teamN, const int &y, const int &m, const int &d)
{
    playerHistory nTeam(teamN, y, m, d);
    history.push(nTeam);
}

// functions to intialize linked list , add a node at the end ,
void Player::updateGameDetails(double d, int pmin, int psec, int rmin, int rsec)
{
    // updating distance
    playerDetails.distance = d;
    games++;

    // updating playingtime
    playerDetails.playingtime.setMinutes(pmin);
    playerDetails.playingtime.setSeconds(psec);

    // updating replacement time
    playerDetails.replacementTime.setMinutes(rmin);
    playerDetails.replacementTime.setSeconds(rsec);

    // update average distance
    avgDistance = (avgDistance + d) / 2;

    // update playing time
    timeplaying.setMinutes(timeplaying.getMinutes() + pmin);
    timeplaying.setSeconds(timeplaying.getSeconds() + psec);
}

// Function to display the Game details
void Player::displayGameDetails() const
{

    cout << "Distance: " << playerDetails.distance
         << ", Playing Time: ";
    playerDetails.playingtime.displayTime();
    cout << ", Replacement Time: ";
    playerDetails.replacementTime.displayTime();
    cout << endl;
}

// Function to display the contents of the stack
void Player::displayPlayerHistory() const
{
    stack<playerHistory> tempStack = history;

    while (!tempStack.empty())
    {
        displayPlayerHistoryObj(tempStack.top());
        tempStack.pop();
    }
}

// update functions
void Player::updateGoals(int x)
{
    goalscored += x;
}
void Player::updateYellowCards(int x)
{
    yellowcards += x;
}
void Player::updateRedCards()
{
    redcards++;
}
void Player::updateGameNum()
{
    games++;
}

// getter
string Player::getPlayerName() const
{
    return player_name;
}

int Player::getPlayerNumber() const
{
    return playernumber;
}

string Player::getPosition() const
{
    if (position == "GK")
        return "Goal Keeper";
    else if (position == "RF")
        return "Right Fullback";
    else if (position == "LF")
        return "Left Fullback";
    else if (position == "CB")
        return "Center Back";
    else if (position == "DM")
        return "Defensive Midfielder";
    else if (position == "RM")
        return "Right Midfielder";
    else if (position == "CM")
        return "Center Midfielder";
    else if (position == "ST")
        return "Striker";
    else if (position == "AM")
        return "Attacking Midfielder";
    else if (position == "LM")
        return "Left Midfielder";
    else
        return "undefined";
}

int Player::getYelCards() const
{
    return yellowcards;
}

int Player::getRedCards() const
{
    return redcards;
}

double Player::getAvgDistance() const
{
    return avgDistance;
}

int Player::getGameNum() const
{
    return games;
}

int Player::getGoals() const
{
    return goalscored;
}

string Player::getPlayerTeamName() const
{
    return team_name;
}

void Player::getPlayingTime() const
{
    timeplaying.displayTime();
}

Details Player::getPlayerDetails() const
{
    return playerDetails;
}

// Function to display player information for standings AS A ROW
void Player::displayPlayerStanding() const
{
    cout << setw(25) << left << getPlayerName();
    cout << setw(15) << left << getPlayerTeamName();
    cout << setw(8) << left << getPlayerNumber();
    cout << setw(25) << left << getPosition();
    cout << setw(15) << left << getGameNum();
    cout << setw(15) << left << getGoals();
    cout << setw(15) << left << getYelCards();
    cout << setw(15) << left << getRedCards();
    cout << setw(15) << left << getAvgDistance();
    timeplaying.displayTime();
    cout << endl;
}

// Function to display player data in a game  AS A ROW
void Player::displayPlayerDetailsinGame() const
{
    cout << setw(20) << left;
    cout << player_name;
    cout << setw(20) << left;
    cout << getPosition();
    cout << setw(10) << left;
    cout << getPlayerNumber();
    cout << setw(10) << left;
    cout << getPlayerDetails().distance;
    getPlayerDetails().playingtime.displayTime();
    getPlayerDetails().replacementTime.displayTime();
    cout << endl;
}

// GLOBAL list of scorers in the league

// function to add a new scorer to the list
void addLeagueScorer(Player *playerObject)
{
    auto sc = LeagueScorers.begin();
    while (sc != LeagueScorers.end())
    {
        if ((*sc)->getPlayerName() == playerObject->getPlayerName())
            return; // Player already in the list

        sc++;
    }

    // Player not found in the list, add it now
    LeagueScorers.push_back(playerObject);
    LeagueScorers.sort([](Player *a, Player *b)
                       { return a->getGoals() > b->getGoals(); });
}

// function to display the list league scorers
void displayScorers()
{

    cout << setw(25) << left << "Player Name";
    cout << setw(15) << left << "Team Name";
    cout << setw(8) << left << "Number";
    cout << setw(25) << left << "Position";
    cout << setw(15) << left << "Games Number";
    cout << setw(15) << left << "Goals number";
    cout << setw(15) << left << "Yellow cards";
    cout << setw(15) << left << "Red cards";
    cout << setw(15) << left << "Average distance";
    cout << setw(30) << right << "Total playing time";
    cout << endl;

    auto sc = LeagueScorers.begin();
    while (sc != LeagueScorers.end())
    {
        (*sc)->displayPlayerStanding();
        cout << endl;
        sc++;
    }
}
