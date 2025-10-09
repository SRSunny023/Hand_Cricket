#include "championsTrophy.h"
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
/* Function Name: setupChampionsTrophy                                          */
/*                                                                              */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Initializes the Champions Trophy structure and fixtures       */
/********************************************************************************/

Tournament setupChampionsTrophy() {

    Tournament T("Champions Trophy", "Group");

    // -------------------- Teams --------------------
    T.groupA = {
        Team("India"), Team("Pakistan"), Team("Bangladesh"), Team("NewZealand")
    };

    T.groupB = {
        Team("Australia"), Team("England"), Team("SouthAfrica"), Team("Afghanistan")
    };

    // -------------------- Fixtures Group A --------------------
    T.fixtures = {
        {"India", "Pakistan"},
        {"India", "Bangladesh"},
        {"India", "NewZealand"},
        {"Pakistan", "Bangladesh"},
        {"Pakistan", "NewZealand"},
        {"Bangladesh", "NewZealand"},

        // -------------------- Fixtures Group B --------------------
        {"Australia", "England"},
        {"Australia", "SouthAfrica"},
        {"Australia", "Afghanistan"},
        {"England", "SouthAfrica"},
        {"England", "Afghanistan"},
        {"SouthAfrica", "Afghanistan"}
    };

    return T;
}



/********************************************************************************/
/* Function Name: resetTournamentChampionsTrophy                                */
/*                                                                              */
/* Inputs       : string name                                                   */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Resets and returns a new instance of the Champions Trophy     */
/********************************************************************************/

Tournament resetTournamentChampionsTrophy(const string &name) {
    return setupChampionsTrophy();
}



/********************************************************************************/
/* Function Name: printChampionsTrophyMenu                                      */
/*                                                                              */
/* Inputs       : Tournament &T, string userTeam, int ball                      */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Displays the Champions Trophy menu with styled formatting     */
/********************************************************************************/

void printChampionsTrophyMenu(const Tournament &T, const string &userTeam, int ball) {

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
/* Function Name: championsTrophyMenu                                           */
/*                                                                              */
/* Inputs       : string userTeam, int ball                                     */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Main control flow for Champions Trophy tournament             */
/********************************************************************************/

void championsTrophyMenu(string userTeam, int ball) {

    int choice;
    static Tournament championsTrophy;

    // -------------------- Load Tournament if Exists --------------------
    ifstream fin("Database/champions_trophy_save.txt");
    string tournamentName;

    if (fin >> tournamentName && !tournamentName.empty()) {
        fin.close();
        championsTrophy = loadTournament("Champions Trophy");
        clearScreen();
        cout << "Loaded Previous Tournament!\n";
        speak("Previous tournament loaded!");
        pressToContinue(0);
    } else {
        championsTrophy = setupChampionsTrophy();
    }

    bool running = true;

    // -------------------- Main Menu Loop --------------------
    while (running) {

        printChampionsTrophyMenu(championsTrophy, userTeam, ball);

        choice = getIntInput("Enter Your Choice: ");

        switch (choice) {

            case 1: { // Play Next Match
                clearScreen();
                playNextFixture(championsTrophy, userTeam, ball);
                saveTournament(championsTrophy);
                pressToContinue(0);
                break;
            }

            case 2: { // View Fixtures
                clearScreen();
                showFixtures(championsTrophy);
                pressToContinue(0);
                break;
            }

            case 3: { // View Points Table
                clearScreen();
                showPointsTable(championsTrophy);
                pressToContinue(0);
                break;
            }

            case 4: { // Reset Tournament
                clearScreen();
                championsTrophy = resetTournamentChampionsTrophy(championsTrophy.name);
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

            case -1:
                running = false;
                break;

            default:
                feedback("Invalid Input! Choose Between 1 - 5!");
                break;
        }
    }
}
