#include "wc.h"
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
/* Function Name: setupWorldCup                                                 */
/*                                                                              */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Initializes the ICC World Cup structure and fixtures          */
/********************************************************************************/

Tournament setupWorldCup() {

    Tournament T("World Cup", "QualifierA");

    // -------------------- Teams --------------------
    T.qualifierA = {
        Team("NewZealand"), Team("Australia"), Team("SriLanka"),
        Team("Bangladesh"), Team("England"), Team("Afghanistan"),
        Team("Scotland")
    };

    T.qualifierB = {
        Team("India"), Team("SouthAfrica"), Team("Pakistan"),
        Team("WestIndies"), Team("Ireland"), Team("Zimbabwe"),
        Team("Netherlands")
    };

    // -------------------- Fixtures for Qualifier A --------------------
    for (size_t i = 0; i < T.qualifierA.size(); i++) {
        for (size_t j = i + 1; j < T.qualifierA.size(); j++) {
            T.fixtures.push_back({T.qualifierA[i].name, T.qualifierA[j].name});
        }
    }

    return T;
}



/********************************************************************************/
/* Function Name: resetTournamentWorldCup                                       */
/*                                                                              */
/* Inputs       : string name                                                   */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Resets and returns a new instance of the World Cup            */
/********************************************************************************/

Tournament resetTournamentWorldCup(const string &name) {
    return setupWorldCup();
}



/********************************************************************************/
/* Function Name: printWorldCupMenu                                             */
/*                                                                              */
/* Inputs       : Tournament &T, string userTeam, int ball                      */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Displays the styled World Cup menu                            */
/********************************************************************************/

void printWorldCupMenu(const Tournament &T, const string &userTeam, int ball) {

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
/* Function Name: worldCupMenu                                                  */
/*                                                                              */
/* Inputs       : string userTeam, int ball                                     */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Main control flow for ICC World Cup tournament                */
/********************************************************************************/

void worldCupMenu(string userTeam, int ball) {

    int choice;
    static Tournament worldCup;

    // -------------------- Load Previous Tournament --------------------
    ifstream fin("Database/world_cup_save.txt");
    string tournamentName;

    if (fin >> tournamentName && !tournamentName.empty()) {
        fin.close();
        worldCup = loadTournament("World Cup");
        clearScreen();
        cout << "Loaded Previous Tournament!\n";
        speak("Previous tournament loaded!");
        pressToContinue(0);
    } else {
        worldCup = setupWorldCup();
    }

    bool running = true;

    // -------------------- Main Menu Loop --------------------
    while (running) {

        printWorldCupMenu(worldCup, userTeam, ball);
        choice = getIntInput("Enter Your Choice: ");

        switch (choice) {

            case 1: { // Play Next Match
                clearScreen();
                playNextFixture(worldCup, userTeam, ball);
                saveTournament(worldCup);
                pressToContinue(0);
                break;
            }

            case 2: { // View Fixtures
                clearScreen();
                showFixtures(worldCup);
                pressToContinue(0);
                break;
            }

            case 3: { // View Points Table
                clearScreen();
                showPointsTable(worldCup);
                pressToContinue(0);
                break;
            }

            case 4: { // Reset Tournament
                clearScreen();
                worldCup = resetTournamentWorldCup(worldCup.name);
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
