#include "t20wc.h"
#include "../Asia_Cup_2025/asiaCup2025.h"
#include "../Engine/tournamentEngine.h"
#include "../../Utility/utility.h"
#include "../../Menu/main_menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;


/********************************************************************************/
/* Function Name: setupT20WorldCup                                              */
/*                                                                              */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Initializes T20 World Cup groups and fixtures                 */
/********************************************************************************/

Tournament setupT20WorldCup() {

    Tournament T("T20 World Cup", "Group");

    // -------------------- Groups --------------------
    T.groupA = { {"India"}, {"Pakistan"}, {"Ireland"}, {"USA"}, {"Canada"} };
    T.groupB = { {"Australia"}, {"England"}, {"Scotland"}, {"Oman"}, {"Namibia"} };
    T.groupC = { {"NewZealand"}, {"SouthAfrica"}, {"SriLanka"}, {"Bangladesh"}, {"Netherlands"} };
    T.groupD = { {"Afghanistan"}, {"WestIndies"}, {"Zimbabwe"}, {"Nepal"}, {"UAE"} };

    // -------------------- Fixtures --------------------
    T.fixtures.clear();
    auto makeFixtures = [&](vector<Team> &g) {
        for (size_t i = 0; i < g.size(); i++) {
            for (size_t j = i + 1; j < g.size(); j++) {
                T.fixtures.push_back({ g[i].name, g[j].name });
            }
        }
    };

    makeFixtures(T.groupA);
    makeFixtures(T.groupB);
    makeFixtures(T.groupC);
    makeFixtures(T.groupD);

    return T;
}



/********************************************************************************/
/* Function Name: resetTournamentT20WorldCup                                    */
/*                                                                              */
/* Inputs       : string name                                                   */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Resets and returns new T20 World Cup structure                */
/********************************************************************************/

Tournament resetTournamentT20WorldCup(const string &name) {
    return setupT20WorldCup();
}



/********************************************************************************/
/* Function Name: printT20WorldCupMenu                                          */
/*                                                                              */
/* Inputs       : Tournament &T, string userTeam, int ball                      */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Displays T20 World Cup styled menu                            */
/********************************************************************************/

void printT20WorldCupMenu(const Tournament &T, const string &userTeam, int ball) {

    clearScreen();

    cout << "╔═══════════════════════════ " << T.name << " ═══════════════════════════╗\n\n";
    cout << "Your Team   : " << userTeam << "\n";
    cout << "Match Format: " << ball / 6 << " Overs\n\n";
    cout << "1. Play Next Match\n";
    cout << "2. View Fixtures\n";
    cout << "3. View Points Table\n";
    cout << "4. Reset Tournament\n";
    cout << "5. Back\n";
    cout << "\n╚═══════════════════════════ " << T.name << " ═══════════════════════════╝\n\n";
}



/********************************************************************************/
/* Function Name: t20WorldCupMenu                                               */
/*                                                                              */
/* Inputs       : string userTeam, int ball                                     */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Main control flow for T20 World Cup                           */
/********************************************************************************/

void t20WorldCupMenu(string userTeam, int ball) {

    int choice;
    static Tournament t20WorldCup;

    // -------------------- Load Saved Tournament --------------------
    ifstream fin("Database/t20_world_cup_save.txt");
    string tournamentName;

    if (fin >> tournamentName && !tournamentName.empty()) {
        fin.close();
        t20WorldCup = loadTournament("T20 World Cup");
        clearScreen();
        cout << "Loaded Previous Tournament!\n";
        speak("Previous tournament loaded!");
        pressToContinue(0);
    } else {
        t20WorldCup = setupT20WorldCup();
    }

    bool running = true;

    // -------------------- Main Menu Loop --------------------
    while (running) {

        printT20WorldCupMenu(t20WorldCup, userTeam, ball);
        choice = getIntInput("Enter Your Choice: ");

        switch (choice) {

            case 1: { // Play Next Match
                clearScreen();
                playNextFixture(t20WorldCup, userTeam, ball);
                saveTournament(t20WorldCup);
                pressToContinue(0);
                break;
            }

            case 2: { // View Fixtures
                clearScreen();
                showFixtures(t20WorldCup);
                pressToContinue(0);
                break;
            }

            case 3: { // View Points Table
                clearScreen();
                showPointsTable(t20WorldCup);
                pressToContinue(0);
                break;
            }

            case 4: { // Reset Tournament
                clearScreen();
                t20WorldCup = resetTournamentT20WorldCup(t20WorldCup.name);
                ofstream clearFile("Database/t20_world_cup_save.txt", ios::trunc);
                clearFile.close();
                cout << "Tournament Reset Successfully!\n";
                speak("Tournament reset successful!");
                pressToContinue(0);
                break;
            }

            case 5: { // Back
                clearScreen();
                cout << "Returning to Tournament Menu...\n";
                speak("Returning to tournament menu!");
                pressToContinue(0);
                running = false;
                break;
            }

            default:
                feedback("Invalid Input! Choose Between 1 - 5!");
                break;
        }
    }
}
