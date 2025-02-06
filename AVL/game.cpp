#include <iostream>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;

#include "game.h"

game::game(Team *t1, Team *t2, int y, int m, int d, int sa, int sh, int st, float dur, int a[], int h[])
{
    away = t1;
    home = t2;
    starttime = st;
    scorea = sa;
    scoreh = sh;
    duration = dur;
    Date date(d, m, y);
    dt = date;

    setHomePlayers(h);
    setAwayPlayers(a);

    home->gamesNum += 1;
    away->gamesNum += 1;

    // updating away information
    (away->goalsReceived += scoreh);
    (away->goalsScored += scorea);

    // updating home information
    (home->goalsReceived += scorea);
    (home->goalsScored += scoreh);

    // updating points for each team
    updatePoints();
    sortLeagueTeams();
}

// function that specifies each team players for the game:
void game::setHomePlayers(int a[])
{
    for (int i = 0; i < 11; i++)
    {
        homePlayers[i] = a[i];
    }
}

void game::setAwayPlayers(int b[])
{
    for (int i = 0; i < 11; i++)
    {
        awayPlayers[i] = b[i];
    }
}

void game::addgoalscorerA(string pname, int goals)
{
    goalscorer newScorer(pname, goals, away->getTeamName());
    goalscorersA.push_back(newScorer);

    Player *scorer = away->findPlayer(pname);
    if (scorer != nullptr)
    {
        scorer->updateGoals(goals);
        away->sortPlayersByGoals();
        addLeagueScorer(scorer);
    }
    else
    {
        cout << "Player not found: " << pname << endl;
        // Handle the case when the player is not found
    }
}

void game::addgoalscorerH(string pname, int goals)
{
    goalscorer newScorer(pname, goals, home->getTeamName());
    goalscorersH.push_back(newScorer);
    Player *scorer = (home->findPlayer(pname));

    if (scorer != nullptr)
    {
        scorer->updateGoals(goals);
        home->sortPlayersByGoals();
        addLeagueScorer(scorer);
    }
    else
    {
        cout << "Player not found: " << pname << endl;
        // Handle the case when the player is not found
    }
}

void game::addyelcard(int pnumber, Team t, int cn)
{
    ycards.emplace_back(pnumber, t, cn);
    if (t.getTeamName() == away->getTeamName())
    {
        away->UpdateYellowCards();
        away->findPlayer(pnumber)->updateYellowCards(cn);
    }

    else if (t.getTeamName() == home->getTeamName())
    {
        home->UpdateYellowCards();
        home->findPlayer(pnumber)->updateYellowCards(cn);
    }
}

void game::addredcard(int pn, Team t)
{
    redcards rplayer(pn, t);
    rcards.push_back(rplayer);
    // add it in player class

    if (t.getTeamName() == away->getTeamName())
    {
        away->UpdateRedCards();
        away->findPlayer(pn)->updateRedCards();
    }

    else if (t.getTeamName() == home->getTeamName())
    {
        home->UpdateRedCards();
        home->findPlayer(pn)->updateRedCards();
    }
}

void game::updatePoints()
{

    if (scorea > scoreh)
        away->points += 3;
    else if (scoreh > scorea)
        home->points += 3;

    else if (scoreh == scorea)
    {
        away->points += 1;
        home->points += 1;
    }
}

void game::displayGame()
{
    int maxSize = max(goalscorersA.size(), goalscorersH.size());
    int minSize = min(goalscorersA.size(), goalscorersH.size());
    cout << setw(10) << left << home->getTeamName() << setw(10) << left << scoreh << setw(10) << left << scorea << setw(10) << left << away->getTeamName() << endl;
    cout << "--------------------------------------" << endl;
    auto h = goalscorersH.begin();
    auto a = goalscorersA.begin();

    for (int i = 0; i < maxSize; i++)
    {
        if (i < minSize)
        {
            cout << setw(10) << left << h->playername << setw(10) << left << h->goalsnum << setw(10) << left << a->goalsnum << setw(10) << left << a->playername << endl;
        }
        else
        {
            if (minSize == goalscorersH.size())
            {
                cout << setw(10) << left << " " << setw(10) << left << " " << setw(10) << left << a->goalsnum << setw(10) << left << a->playername << endl;
            }
            else if (minSize == goalscorersA.size())
            {
                cout << setw(10) << left << h->playername << setw(10) << left << h->goalsnum << setw(10) << left << " " << setw(10) << left << " " << endl;
            }
        }
        h++;
        a++;
    }
}

void game::replace(string teamName, int p1)
{

    if (teamName == away->getTeamName())
    {
        Time temp = away->findPlayer(p1)->getPlayerDetails().replacementTime;
        if (temp.getMinutes() != 0)
        {
            cout << "The player: " << away->findPlayer(p1)->getPlayerName() << " was replaced at the minute: ";
            temp.displayTime();
            cout << endl;
        }
    }

    else if (teamName == home->getTeamName())
    {
        Time temp = home->findPlayer(p1)->getPlayerDetails().replacementTime;
        if (temp.getMinutes() != 0)
        {
            cout << "The player: " << home->findPlayer(p1)->getPlayerName() << " was replaced at the minute: ";
            temp.displayTime();
            cout << endl;
        }
    }
}

// getters:
//  returns goal scorers
list<goalscorer> game::getGoalScorersH()
{
    return goalscorersH;
}
list<goalscorer> game::getGoalScorersA()
{
    return goalscorersA;
}

// returns home name:
string game::getHname() { return home->getTeamName(); }
// returns away name:
string game::getAname() { return away->getTeamName(); }
// returns home:
Team *game::getHome() { return home; }
// returns away:
Team *game::getAway() { return away; }