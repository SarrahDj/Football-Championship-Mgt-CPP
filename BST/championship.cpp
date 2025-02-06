
#include <iostream>
#include "championship.h"

using namespace std;

championship::championship(int s, string c) : category(c)
{
    season = s > 0 ? s : 0000;
    first = nullptr;
}

int championship::getSeason() const
{
    return season;
}
string championship::getCat() const
{
    return category;
}

// Function to add a new round to the binary search tree
void championship::addRound(Round round)
{
    if (first == nullptr)
    {
        first = new round_node(round);
    }
    else
    {
        addRoundToTree(first, round);
    }
}

// Utility function
void championship::addRoundToTree(round_node *node, Round round)
{
    if (round.getRoundNum() < node->key.getRoundNum())
    {
        if (node->left == nullptr)
        {
            node->left = new round_node(round);
        }
        else
        {
            addRoundToTree(node->left, round);
        }
    }
    else if (round.getRoundNum() > node->key.getRoundNum())
    {
        if (node->right == nullptr)
        {
            node->right = new round_node(round);
        }
        else
        {
            addRoundToTree(node->right, round);
        }
    }
    // Optionally, you can handle the case where roundNum is equal to node->key.getRoundNum()
    // and decide how to handle duplicates.
}

round_node *championship::findRound(int roundNum)
{
    return findRoundInTree(first, roundNum);
}

// utility function to search a node in a bst
round_node *championship::findRoundInTree(round_node *node, int roundNum)
{
    if (node == nullptr || node->key.getRoundNum() == roundNum)
    {
        return node;
    }

    if (roundNum < node->key.getRoundNum())
    {
        return findRoundInTree(node->left, roundNum);
    }

    return findRoundInTree(node->right, roundNum);
}

game *championship::findRoundGame(string awayTeam, string homeTeam)
{
    game *gamee = findGameInChampionship(first, awayTeam, homeTeam);
    if (gamee != nullptr)
    {
        return gamee;
    }
    else
        cout << "not found";
    return nullptr;
}

// utility function to search for a game in the entire championship
game *championship::findGameInChampionship(round_node *node, string awayTeam, string homeTeam)
{
    game *result = nullptr;

    if (node != nullptr)
    {
        result = findGameInRound(&(node->key), awayTeam, homeTeam);

        if (result == nullptr)
        {
            // If the game is not found
            result = findGameInChampionship(node->left, awayTeam, homeTeam);

            if (result == nullptr)
            {
                result = findGameInChampionship(node->right, awayTeam, homeTeam);
            }
        }
    }
    return result;
}

// Helper function to search for a game in a round
game *championship::findGameInRound(Round *roundPtr, string awayTeam, string homeTeam)
{
    return roundPtr->findGame(awayTeam, homeTeam);
}

// Function to display details of a given game by knowing only the name of the two teams
void championship::displayRoundGame(string awayTeam, string homeTeam)
{
    game *result = findGameInChampionship(first, awayTeam, homeTeam);

    if (result != nullptr)
    {
        result->displayGame();
    }
    else
    {
        cout << "Game not found." << endl;
    }
}

// Function to display results of all games in a given round
void championship::displayAllGamesInRound(int roundNum)

{
    round_node *roundPtr = findRound(roundNum);

    if (roundPtr != nullptr)
    {
        roundPtr->key.displayGames();
    }
    else
    {
        cout << "Round not found." << endl;
    }
}

// Function to display results of all games in the championship
void championship::displayAllGames()
{
    displayAllGamesInChampionship(first);
}

// utility function to display results of all games in a round
void championship::displayAllGamesInChampionship(round_node *node)
{

    if (node != nullptr)
    {
        node->key.displayGames();
        displayAllGamesInChampionship(node->left);
        displayAllGamesInChampionship(node->right);
    }
}

// utility function to display results of a game in a round
void championship::displayRoundGameInChampionship(round_node *node, string awayTeam, string homeTeam)
{
    game *result = findGameInRound(&(node->key), awayTeam, homeTeam);

    if (result != nullptr)
    {
        result->displayGame();
    }
    else
    {
        cout << "Game not found in Round " << node->key.getRoundNum() << "." << endl;
    }
}

// Function to display players standings in a given team until a given round
void championship::displayPlayersStandingInTeams(int roundNum, string teamName)
{
    
    round_node *roundPtr = findRound(roundNum);

    if (roundPtr != nullptr)
    {
        Team teamPtr = findTeamInRoundTree(&(roundPtr->key), teamName);

        if (teamPtr.getTeamName() != " ")
        {

            // Display player standings in the team
            cout << "Player Standings in Team " << teamName << " for Round " << roundNum << ":" << endl;
            teamPtr.displayTeamPlayers();
        }
        else
        {
            cout << "Team not found in Round " << roundNum << "." << endl;
        }
    }
    else
    {
        cout << "Round not found." << endl;
    }
}

// utility function to search for a team in a round
Team championship::findTeamInRoundTree(Round *roundPtr, string teamName)
{
    Team *ptr = roundPtr->findTeam(teamName);

    if (ptr != nullptr)
        return *ptr;
    else
        return *ptr;
}

// Function to display players data in the championship for a given team (final)
void championship::displayPlayerStanding(string teamName)
{
    cout << "Final standings in Championship for Team " << teamName << " Players:" << endl;

    round_node *temp = first;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }

    if (temp != nullptr)
    {
        auto teamPtr = temp->key.getTeamsList().begin();

        for (; teamPtr != temp->key.getTeamsList().end(); teamPtr++)
        {
            if ((teamPtr)->getTeamName() == teamName)
            {
                (teamPtr)->displayTeamPlayers();
                return; // Team found, exit the function
            }
        }

        cout << "Team not found in round " << endl;
    }
    else
    {
        cout << "Championship is empty." << endl;
    }
}
// Function to display best Scorers standings in the championship
void championship::displayBestScorersStandings()
{
    cout << "Best Scorers in the championship: " << endl;

    Round *lastRound = findLastRound();

    if (lastRound != nullptr)
    {
        lastRound->displayScorersStanding();
    }
    else
    {
        cout << "Championship is empty or no rounds found." << endl;
    }
}

// Function to display data of players of a team in a given game (game details)
void championship::displayTeamPlayersInGame(string awayTeam, string homeTeam)
{
    game *result = findGameInChampionship(first, awayTeam, homeTeam);

    if (result != nullptr)
    {
        cout << "Game Details for " << awayTeam << " vs " << homeTeam << ":" << endl;
        result->displayGame();

        Team *awayTeamPtr = (result->getAway());
        Team *homeTeamPtr = (result->getHome());

        cout << "Players of " << awayTeam << ":" << endl;
        awayTeamPtr->displayTeamPlayersGameDetails();

        cout << "Players of " << homeTeam << ":" << endl;
        homeTeamPtr->displayTeamPlayersGameDetails();
    }
    else
    {
        cout << "Game not found." << endl;
    }
}

// Function to display teams standings in a given round
void championship::displayTeamsInRound(int roundNum)
{
    round_node *roundPtr = findRound(roundNum);

    if (roundPtr != nullptr)
    {
        cout << "Teams Standings in Round " << roundNum << ":" << endl;
        roundPtr->key.displayTeamsStanding();
    }

    else
    {
        cout << "Round not found." << endl;
    }
}

// Function to display results of standings in the whole championship
void championship::displayTeamsStandings()
{
    Round *lastRound = findLastRound();

    if (lastRound == nullptr)
    {
        cout << "Championship is empty or no rounds found." << endl;
        return;
    }

    // Display teams standings in the last round
    displayTeamsInRound(lastRound->getRoundNum());
}

// Function to find the winner team in the championship
Team *championship::findWinnerTeam()
{
    Round *lastRound = findLastRound();

    if (lastRound != nullptr && !lastRound->getTeamsList().empty())
    {
        return &lastRound->getTeamsList().front();
    }
    else
    {
        cout << "Error: No winner team found." << endl;
        return nullptr;
    }
}

Player *championship::findBestScorer()
{
    Round *lastRound = findLastRound();

    if (lastRound != nullptr && !lastRound->getScorers().empty())
    {
        return &lastRound->getScorers().front();
    }
    else
    {
        cout << "Error: No best scorer found." << endl;
        return nullptr;
    }
}

round_node *championship::getRound(int n)
{
    return findRoundInTree(first, n);
}

// / / / / / / / /   function to show the winner and the best scorers / / / / / / / / /
void championship::displayWinner()
{
    Team *winner = findWinnerTeam();
    cout << "The winner of The profesional algerian league championship " << season << " season is: " << winner->getTeamName() << endl;
}
void championship::displayBestScorer()
{
    Player *scorer = findBestScorer();
    cout << "The Best scorer in The  profesional algerian league championship " << season << " season is: " << scorer->getPlayerName() << endl;
}

// / / / / / / / / / / / /  functions to get number of goals scored by a player  / / / / / /  / //  / //
// in a given round
// 1. by player name
int championship::getPlayerGoalInRound(int num, string team, string pname)
{
    if (num != 1)
    {
        round_node *roundNode = findRound(num);
        round_node *roundNodeprev = findRound(num - 1);

        if (roundNode == nullptr)
        {
            // Round not found
            cout << "Round  not found." << endl;
            return -1;
        }

        Round r = roundNode->key;
        Round rprev = roundNodeprev->key;

        Team *teamPtr = r.findTeam(team);
        Team *teamPtrprev = rprev.findTeam(team);

        if (teamPtr == nullptr || teamPtrprev == nullptr)
        {
            // Team not found in the round
            cout << "Team " << team << " not found in round " << num << "." << endl;
            return -1;
        }

        Player *playerPtr = teamPtr->findPlayer(pname);
        Player *playerPtrprev = teamPtrprev->findPlayer(pname);

        if (playerPtr == nullptr || playerPtrprev == nullptr)
        {
            // Player not found in the team
            cout << "Player " << pname << " not found in team " << team << "." << endl;
            return -1;
        }

        return (playerPtr->getGoals() - playerPtrprev->getGoals());
    }
    else
    {
        round_node *roundNode = findRound(num);

        if (roundNode == nullptr)
        {
            // Round not found
            cout << "Round  not found." << endl;
            return -1;
        }

        Round r = roundNode->key;

        Team *teamPtr = r.findTeam(team);

        if (teamPtr == nullptr)
        {
            // Team not found in the round
            cout << "Team " << team << " not found in round " << num << "." << endl;
            return -1;
        }

        Player *playerPtr = teamPtr->findPlayer(pname);

        if (playerPtr == nullptr)
        {
            // Player not found in the team
            cout << "Player " << pname << " not found in team " << team << "." << endl;
            return -1;
        }

        return playerPtr->getGoals();
    }
}

// 2. by player number
int championship::getPlayerGoalInRound(int num, string team, int pnum)
{
    if (num != 1)
    {
        round_node *roundNode = findRound(num);
        round_node *roundNodeprev = findRound(num - 1);

        if (roundNode == nullptr)
        {
            // Round not found
            cout << "Round  not found." << endl;
            return -1;
        }

        Round r = roundNode->key;
        Round rprev = roundNodeprev->key;

        Team *teamPtr = r.findTeam(team);
        Team *teamPtrprev = rprev.findTeam(team);

        if (teamPtr == nullptr && teamPtrprev == nullptr)
        {
            // Team not found in the round
            cout << "Team " << team << " not found in round " << num << "." << endl;
            return -1;
        }

        Player *playerPtr = teamPtr->findPlayer(pnum);
        Player *playerPtrprev = teamPtrprev->findPlayer(pnum);

        if (playerPtr == nullptr || playerPtrprev == nullptr)
        {
            // Player not found in the team
            cout << "Player number " << pnum << " not found in team " << team << "." << endl;
            return -1;
        }

        return (playerPtr->getGoals() - playerPtrprev->getGoals());
    }
    else
    {
        round_node *roundNode = findRound(num);

        if (roundNode == nullptr)
        {
            // Round not found
            cout << "Round  not found." << endl;
            return -1;
        }

        Round r = roundNode->key;

        Team *teamPtr = r.findTeam(team);

        if (teamPtr == nullptr)
        {
            // Team not found in the round
            cout << "Team " << team << " not found in round " << num << "." << endl;
            return -1;
        }

        Player *playerPtr = teamPtr->findPlayer(pnum);

        if (playerPtr == nullptr)
        {
            // Player not found in the team
            cout << "Player number " << pnum << " not found in team " << team << "." << endl;
            return -1;
        }

        return (playerPtr->getGoals());
    }
}

// in the whole championship
// 1. by player name
int championship::getPlayerGoalsInChamp(string team, string pname)
{
    Round *r = findLastRound();

    if (r == nullptr)
    {
        // Round not found
        cout << "championship is empty" << endl;
        return -1;
    }

    Team *t = r->findTeam(team);
    if (t == nullptr)
    {
        // Team not found in the round
        cout << "Team " << team << " not found in championship." << endl;
        return -1;
    }

    Player *p = t->findPlayer(pname);

    if (p == nullptr)
    {
        // Player not found in the team
        cout << "Player " << pname << " not found in team " << t << "." << endl;
        return -1;
    }

    return (p->getGoals());
}

int championship::getPlayerGoalsInChamp(string team, int pnum)
{
    Round *r = findLastRound();

    if (r == nullptr)
    {
        // Round not found
        cout << "championship is empty" << endl;
        return -1;
    }

    Team *t = r->findTeam(team);
    if (t == nullptr)
    {
        // Team not found in the round
        cout << "Team " << team << " not found in championship." << endl;
        return -1;
    }

    Player *p = t->findPlayer(pnum);

    if (p == nullptr)
    {
        // Player not found in the team
        cout << "Player " << pnum << " not found in team " << t << "." << endl;
        return -1;
    }

    return (p->getGoals());
}

Round *championship::findLastRound()
{
    if (first == nullptr)
    {
        return nullptr;
    }

    // Find the last round in the binary search tree
    round_node *lastRound = first;
    while (lastRound->right != nullptr)
    {
        lastRound = lastRound->right;
    }

    return &lastRound->key;
}

void championship::displayRoundScorers(int roundNum)
{
    Round r = findRound(roundNum)->key;
    r.displayScorersStanding();
}

void championship::displayBestScorerInTeam(string team)
{
    Round r = *findLastRound();
    Team t = *r.findTeam(team);
    Player p = t.getPlayersList().front();

    cout << "Best scorer in " << t.getTeamName() << " for " << season << " season is player number "
         << p.getPlayerNumber() << " with a total of " << p.getGoals() << " goals scored" << endl;
}

// function of recruted
void recrutePlayer(string pName, string oldTeam, string NewTeam)
{
    auto Oteam = LeagueTeams.begin();

    for (; Oteam != LeagueTeams.end(); Oteam++)
    {
        if ((*Oteam)->getTeamName() == oldTeam)
            break;
    }

    auto Nteam = LeagueTeams.begin();

    for (; Nteam != LeagueTeams.end(); Nteam++)
    {
        if ((*Nteam)->getTeamName() == NewTeam)
            break;
    }

    Player *recrutedPlayer = (*Oteam)->findPlayer(pName);

    (*Oteam)->removePlayer(*recrutedPlayer);
    (*Nteam)->addPlayer(*recrutedPlayer);
    recrutedPlayer->setPlayerTeam(NewTeam);
}

// functions to display a player historyyyy
void displayPlayerHistory(string pteam, string pname)
{ // by nameee
    Team team = *findLeagueTeam(pteam);
    Player player = *team.findPlayer(pname);
    player.displayPlayerHistory();
}

void displayPlayerHistory(string pteam, int pnumm)
{ // byy number
    Team team = *findLeagueTeam(pteam);
    Player player = *team.findPlayer(pnumm);
    player.displayPlayerHistory();
}