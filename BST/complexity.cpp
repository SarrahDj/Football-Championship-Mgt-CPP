#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <vector>
#include <chrono>
#include "championship.cpp"

using namespace std;
// Global List of championships:
vector<championship> competition;

bool isString(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    for (char c : input)
    {
        if (!isalpha(static_cast<unsigned char>(c)) && !isspace(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

void menu(championship champ)
{
    int choice;

    do
    {
        cout << "choose one of the following:" << endl;
        cout << "1)TEAM STANDINGS\n"
             << endl;
        cout << "2)GOAL SCORERS\n"
             << endl;
        cout << "3)PLAYERS STATS IN A GIVEN GAME\n"
             << endl;
        cout << "4)BEST SCORERS\n"
             << endl;
        cout << "5)GAMES DETAILS\n"
             << endl;
        cout << "6)PLAYERS STATS IN A GAME\n"
             << endl;
        cout << "7)PLAYER HISTORY\n"
             << endl;
        cout << "8)DISPLAY WINNER TEAM\n"
             << endl;
        cout << "9)EXIT\n"
             << endl;
        try
        {
            cin.exceptions(cin.failbit);
            cin >> choice;
            if (choice < 1 || choice > 9)
                throw "invalid input.please enter a valid choice";
            if (choice == 9)
                menu(champ);
        }
        catch (const char *e)
        {
            cerr << e << endl;
        }
        cout << endl;
        cout << "================================================" << endl;
        switch (choice)
        {
        case 1:
        {
            cout << endl<<"TEAMS STANDING:" << endl;
            int choice1;
            do
            {
                cout << "choose one of the following:" << endl;
                cout << "1)teams standings in a given week" << endl;
                cout << "2)teams standing in all the championship" << endl;
                cout << "3)EXIT" << endl;

                try
                {
                    cin.exceptions(cin.failbit);
                    cout<<endl<<"Your choice: ";
                    cin >> choice1;
                    if (choice1 < 1 || choice1 > 3)
                        throw "invalid input.please enter a valid choice";
                    if (choice1 == 3)
                        menu(champ);
                }
                catch (const char *e)
                {
                    cerr << e << endl;
                }
                cout << endl;
                cout << "================================================" << endl;
                switch (choice1)
                {
                case 1:
                {
                    int week;
                    do
                    {
                        cout << "choose a week:";
                        cin >> week;
                        cout << "teams standings after week:" << week << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.displayTeamsInRound(week);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;

                    } while (week < 0);
                    cout << "================================================" << endl;
                    break;
                }
                case 2:
                {
                    cout << "teams standing in all championship:";
                    auto start = std::chrono::high_resolution_clock::now();
                    champ.displayTeamsStandings();
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    cout << "================================================" << endl;
                    break;
                }
                }
            } while (choice1 > 2 || choice1 < 1);
            break;
        }
        case 2:
        {
            cout << "GOAL SCORERS STANDING" << endl;

            int choice2;
            do
            {
                cout << "choose one of the following:" << endl;
                cout << "1)best scorers in certain week" << endl;
                cout << "2)best scorers in championship" << endl;
                cout << "3)goals of a player in a given round" << endl;
                cout << "4)goals of a player in the championship" << endl;
                cout << "5)EXIT" << endl;

                try
                {
                    cin.exceptions(cin.failbit);
                    cin >> choice2;
                    if (choice2 < 1 || choice2 > 5)
                        throw "invalid input.please enter a valid choice";
                    if (choice2 == 5)
                        menu(champ);
                }
                catch (const char *e)
                {
                    cerr << e << endl;
                }

                cout << endl;
                cout << "================================================" << endl;

                switch (choice2)
                {
                case 1:
                {
                    int week;
                    do
                    {
                        cout << "choose the week";
                        cin >> week;
                        cout << "goal scorers in week:" << week << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.displayRoundScorers(week);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;

                    } while (week < 0);
                    cout << "================================================" << endl;
                    break;
                }
                case 2:
                {
                    cout << "list of best scorers in the championship:" << endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    champ.displayBestScorersStandings();
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;

                    cout << "================================================" << endl;
                    break;
                }
                case 3:
                {
                    cout << "1)BY NAME:" << endl;
                    cout << "2)BY NUMBER" << endl;
                    int by;

                    cin >> by;
                    switch (by)
                    {
                    case 1:
                    {
                        string team;
                        int week;
                        string name;

                        cout << "choose team name: ";
                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> team;
                            if (!isString(team))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }
                        cout << "choose player name: ";
                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> name;
                            if (!isString(name))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }
                        cout << "choose a week: ";
                        cin >> week;
                        cout << "goals of a player " << name << "in week: " << week << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.getPlayerGoalInRound(week, team, name);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                        break;
                    }

                    case 2:
                    {
                        string team;
                        int week;
                        string nbr;

                        cout << "choose team name: ";
                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> team;
                            if (!isString(team))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }
                        cout << "choose player number: ";
                        cin >> nbr;
                        cout << "choose a week: ";
                        cin >> week;
                        cout << "goals of player number " << nbr << "in week: " << week << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.getPlayerGoalInRound(week, team, nbr);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                        break;
                    }
                    }
                    cout << "================================================" << endl;
                    break;
                }

                case 4:
                {
                    string name;
                    do
                    {
                        cout << "choose player name";
                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> name;
                            if (!isString(name))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }
                        string team;
                        cout << "enter player team:";
                        cin >> team;
                        cout << "goals of a player:" << name;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.getPlayerGoalsInChamp(name, team);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;

                    } while (name == "");
                    cout << "================================================" << endl;
                    break;
                }

                break;
                }
            } while (choice2 < 1 || choice2 > 4);
            break;
        }
        case 3:
        {
            cout << "PLAYERS STATS IN A GIVEN GAME : " << endl;

            int choice3;
            do
            {
                cout << "choose one of the following:" << endl;
                cout << "1)players stats in a given week" << endl;
                cout << "2)players stats in championship" << endl;
                cout << "3)EXIT" << endl;
                try
                {
                    cin.exceptions(cin.failbit);
                    cin >> choice3;
                    if (choice3 < 0 || choice3 > 3)
                        throw "invalid input.please enter a valid choice";
                    if (choice3 == 3)
                        menu(champ);
                }
                catch (const char *e)
                {
                    cerr << e << endl;
                }
                cout << endl;
                cout << "================================================" << endl;
                switch (choice3)
                {
                case 1:
                {
                    string team;
                    int week;
                    do
                    {
                        cout << "enter team name: ";
                        cin >> team;
                        cout << "enter week number: ";
                        cin >> week;

                        cout << "stats of player: " << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.displayPlayersStandingInTeams(week, team);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    } while (week < 0);

                    cout << "================================================" << endl;
                    break;
                }
                case 2:
                {
                    int week;
                    string team;
                    do
                    {
                        cout << "enter team name";

                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> team;
                            if (!isString(team))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }

                        cout << "players standing in the championship: " << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.displayPlayerStanding(team);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    } while (week < 0);
                    cout << "================================================" << endl;
                    break;
                }
                }
            } while (choice3 < 1 || choice3 > 2);
            break;
        }
        case 4:
        {
            int week;
            cout << "BEST SCORERS:" << endl;
            int choice4;
            do
            {
                cout << "choose one of the following" << endl;
                cout << "1)best scorers in a team" << endl;
                cout << "2)best scorers in all the championship" << endl;
                cout << "3)EXIT" << endl;
                try
                {
                    cin.exceptions(cin.failbit);
                    cin >> choice4;
                    if (choice4 < 1 || choice4 > 3)
                        throw "invalid input.please enter a valid choice";
                    if (choice4 == 3)
                        menu(champ);
                }
                catch (const char *e)
                {
                    cerr << e << endl;
                }
                cout << endl;
                cout << "================================================" << endl;
                switch (choice4)
                {
                case 1:
                {
                    string team;
                    do
                    {
                        
                        cout << "choose team:";

                        try
                        {
                            cin.exceptions(cin.failbit);
                            cin >> team;
                            if (!isString(team))
                                throw "invalid input.please enter a valid choice";
                        }
                        catch (const char *e)
                        {
                            cerr << e << endl;
                        }
                        cout << "best scorers in team:" << team << endl;
                        auto start = std::chrono::high_resolution_clock::now();
                        champ.displayBestScorerInTeam(team);
                        auto end = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    } while (week < 0);
                    cout << "================================================" << endl;
                    break;
                }
                case 2:
                {
                    cout << "best scorers in all championship:";
                    auto start = std::chrono::high_resolution_clock::now();
                    champ.displayBestScorer();
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;

                    cout << "================================================" << endl;
                    break;
                }
                }

            } while (choice4 > 2 || choice4 < 1);
            break;
        }
        case 5:
        {
            cout << "GAME DETAILS:" << endl;
            cout << "choose one of the following:" << endl;
            int choice5;

            do
            {
                cout << "1)in a given round" << endl;
                cout << "2)all games in round" << endl;
                cout << "3)EXIT" << endl;
                cin >> choice5;

                switch (choice5)
                {
                case 1:
                {
                    string home, away;
                    cout << "enter home team ";
                    cin >> home;
                    cout << "enter away team ";
                    cin >> away;
                    auto start = std::chrono::high_resolution_clock::now();
                    champ.displayRoundGame(away, home);
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    break;
                }
                case 2:
                {
                    int week;
                    cout << "enter week: ";
                    cin >> week;
                    auto start = std::chrono::high_resolution_clock::now();
                    champ.displayAllGamesInRound(week);
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
                    break;
                }
                case 3:
                    menu(champ);
                    break;
                }
            } while (choice5 <1|| choice5>3);
            break;
        }
        case 6:
        {
            string home, away;
            cout << "PLAYERS STAT IN A GAME: " << endl;
            cout << "enter home team:" << endl;
            cin >> home;
            cout << "enter away team:" << endl;
            cin >> away;
            auto start = std::chrono::high_resolution_clock::now();
            champ.displayTeamPlayersInGame(away, home);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
            break;
        }
        case 7:
        {
            string pname, pteam;
            cout << "PLAYER HISTORY:" << endl;
            cout << "enter player name: ";
            cin >> pname;
            cout << "enter the team of the player: ";
            cin >> pteam;
            auto start = std::chrono::high_resolution_clock::now();
            displayPlayerHistory(pteam, pname);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
            break;
        }
        case 8:
        {
            cout << "DISPLAY THE WINNER TEAM:" << endl;
            auto start = std::chrono::high_resolution_clock::now();
            champ.displayWinner();
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Running time: " << duration.count() << " microseconds" << std::endl;
            break;
        }
        }
    } while (choice != 9);
}

bool search(int Season, string Category)
{
    for (const auto &c : competition)
    {
        if (Season == c.getSeason() && Category == c.getCat())
        {
            return true;
        }
    }
    return false;
}

struct PlayerData
{
    string playerName;
    string position;
    int playerNumber;
};

struct TeamData
{
    string teamName;
    string coach;
    string president;
    vector<PlayerData> players;
};

struct HistoryData
{
    string team;
    int year;
    int month;
    int day;
};

struct roundeGame
{
    string awayTeam;
    string homeTeam;
    Team *AwayT;
    Team *HomeT;
    int year;
    int month;
    int day;
    int awayScore;
    int homeScore;
    int startTime;
    float duration;
    int a[14];
    int h[14];
};

struct gamePlayer
{
    int playerNum;
    double distance;
    int p_mins;
    int p_sec;
    int r_mins;
    int r_sec;
    int goals;
    int y_cards;
    int r_cards;
};

void readGameData(const std::string &filename, Round &r)
{
    std::ifstream file(filename);

    std::vector<game> rgames;

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    while (!file.eof())
    {

        std::vector<gamePlayer> awayPlayers;
        std::vector<gamePlayer> homePlayers;

        string str;
        getline(file, str);
        istringstream objiss(str);

        roundeGame mygame;

        // Read round details
        objiss >> mygame.awayTeam >> mygame.homeTeam >> mygame.year >> mygame.month >> mygame.day >> mygame.awayScore >> mygame.homeScore >> mygame.startTime >> mygame.duration;
        getline(file, str);

        mygame.AwayT = findLeagueTeam(mygame.awayTeam);
        mygame.HomeT = findLeagueTeam(mygame.homeTeam);

        // Read away players
        for (int i = 0; i < 14; ++i)
        {
            string str;
            getline(file, str);
            istringstream playiss(str);

            gamePlayer player;
            playiss >> player.playerNum >> player.distance >> player.p_mins >> player.p_sec >> player.r_mins >> player.r_sec >> player.goals >> player.y_cards >> player.r_cards;

            Player *pObj = mygame.AwayT->findPlayer(player.playerNum);
            if (pObj != nullptr)
            {
                pObj->updateGameDetails(player.distance, player.p_mins, player.p_sec, player.r_mins, player.r_sec);

                awayPlayers.push_back(player);
                mygame.a[i] = player.playerNum;
            }
            else
                continue;
        }
        getline(file, str);

        // Read home players
        for (int i = 0; i < 14; ++i)
        {
            string str;
            getline(file, str);
            istringstream playiss(str);
            gamePlayer player;
            playiss >> player.playerNum >> player.distance >> player.p_mins >> player.p_sec >> player.r_mins >> player.r_sec >> player.goals >> player.y_cards >> player.r_cards;

            Player *pObjh = mygame.HomeT->findPlayer(player.playerNum);
            if (pObjh != nullptr)
            {
                pObjh->updateGameDetails(player.distance, player.p_mins, player.p_sec, player.r_mins, player.r_sec);
                homePlayers.push_back(player);
                mygame.h[i] = player.playerNum;
            }
            else
                continue;
        }

        getline(file, str);

        game newGame(mygame.AwayT, mygame.HomeT, mygame.year,
                     mygame.month, mygame.day, mygame.awayScore, mygame.homeScore, mygame.startTime,
                     mygame.duration, mygame.a, mygame.h);

        // add goal scorers
        for (int i = 0; i < awayPlayers.size(); i++)
        {
            if (awayPlayers.at(i).goals > 0)
            {
                Player *ptr = mygame.AwayT->findPlayer(awayPlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addgoalscorerA(ptr->getPlayerName(), awayPlayers.at(i).goals);
            }
        }

        for (int i = 0; i < homePlayers.size(); i++)
        {
            if (homePlayers.at(i).goals > 0)
            {
                Player *ptr = mygame.HomeT->findPlayer(homePlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addgoalscorerH(ptr->getPlayerName(), homePlayers.at(i).goals);
            }
        }

        // add yellow cards
        for (int i = 0; i < homePlayers.size(); i++)
        {
            if (homePlayers.at(i).y_cards > 0)
            {

                Player *ptr = mygame.HomeT->findPlayer(homePlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addyelcard(homePlayers.at(i).playerNum, *mygame.HomeT, homePlayers.at(i).y_cards);
            }
        }

        for (int i = 0; i < awayPlayers.size(); i++)
        {
            if (awayPlayers.at(i).y_cards > 0)
            {
                Player *ptr = mygame.AwayT->findPlayer(awayPlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addyelcard(awayPlayers.at(i).playerNum, *mygame.AwayT, awayPlayers.at(i).y_cards);
            }
        }

        // add red cards
        for (int i = 0; i < homePlayers.size(); i++)
        {
            if (homePlayers.at(i).r_cards > 0)
            {
                Player *ptr = mygame.HomeT->findPlayer(homePlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addredcard(homePlayers.at(i).playerNum, *mygame.HomeT);
            }
        }

        for (int i = 0; i < awayPlayers.size(); i++)
        {
            if (awayPlayers.at(i).r_cards > 0)
            {
                Player *ptr = mygame.HomeT->findPlayer(awayPlayers.at(i).playerNum);
                if (ptr != nullptr)
                    newGame.addredcard(awayPlayers.at(i).playerNum, *mygame.AwayT);
            }
        }

        r.addGame(newGame);
    }
    file.close();
}

int main()
{
    ifstream inputFile("C:\\Users\\DELL\\Desktop\\FTMS\\FILES\\PlayersU.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening Players.txt file." << endl;
        return 1;
    }

    ifstream File("C:\\Users\\DELL\\Desktop\\FTMS\\FILES\\Players History.txt");
    if (!File.is_open())
    {
        cerr << "Error opening Players History.txt file." << endl;
        return 1;
    }

    string line;
    list<Team> teams;
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            // Skip empty lines
            continue;
        }

        TeamData team;
        istringstream iss(line);
        iss >> team.teamName >> team.coach >> team.president;
        Team newTeam(team.teamName, team.coach, team.president);
        for (int i = 0; i < 23; ++i)
        {
            getline(inputFile, line);
            istringstream playerIss(line);
            PlayerData player;
            playerIss >> player.playerName >> player.position >> player.playerNumber;
            Player newPlayer(player.playerName, player.position, player.playerNumber);

            // Read history data for the current player until an empty line is encountered
            while (getline(File, line) && !line.empty())
            {
                istringstream historyIss(line);
                HistoryData history;

                if (!(historyIss >> history.team >> history.year >> history.month >> history.day))
                {
                    cerr << "Error reading player history data from file." << endl;
                    // Handle the error, possibly by skipping the current line or returning an error code.
                }
                else
                {
                    newPlayer.newTeam(history.team, history.year, history.month, history.day);
                }
            }
            newTeam.addPlayer(newPlayer);
        }
        teams.push_back(newTeam);
    }

    File.close();
    inputFile.close();

    auto it = teams.begin();

    for (int i = 0; i < 20; i++)
    {
        addLeagueTeam(&(*it));
        it++;
    }

    Round r1(1);
    readGameData("C:\\Users\\DELL\\Desktop\\FTMS\\FILES\\ROUND1.txt", r1);
    Round r2(2);
    readGameData("C:\\Users\\DELL\\Desktop\\FTMS\\FILES\\ROUND2.txt", r2);
    Round r3(3);
    readGameData("C:\\Users\\DELL\\Desktop\\FTMS\\FILES\\ROUND3.txt", r3);

    championship champion(2023, "Male");
    champion.addRound(r1);
    champion.addRound(r2);
    champion.addRound(r3);

    competition.push_back(champion);

    cin.exceptions(cin.failbit);
    cout << "================================================" << endl;
    cout << "Welcome to the Football Tournament System Menu\n";
    cout << "================================================" << endl;

    do
    {
        string cat;
        int Season;
        cout << "Please choose the category: ";
        try
        {
            cin.exceptions(cin.failbit);
            cin >> cat;
            if (!isString(cat))
                throw "Invalid input. Please enter a valid choice";
        }
        catch (const char *e)
        {
            cerr << e << endl;
        }

        cout << "Please choose the season: ";
        try
        {
            cin.exceptions(cin.failbit);
            cin >> Season;
            if (Season < 0 )
                throw "Invalid input. Please enter a valid choice";
        }
        catch (const char *e)
        {
            cerr << e << endl;
            continue;
        }

        if (search(Season, cat))
        {
            menu(champion);
        }
        else
        {
            cout << "CHAMPIONSHIP NOT FOUND!!!" << endl;
        }

        cout << "================================================" << endl;
        cout << "===========================================================" << endl
             << endl
             << endl;

    } while (champion.getSeason() != 0);

    return 0;
}
