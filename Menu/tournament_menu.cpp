#include "utility.h"
#include "matchEngine.h"
#include "../Asia_Cup_2025/asiaCup2025.h"
#include "../Champions_Trophy/championsTrophy.h"
#include "../Odi_World_Cup/wc.h"
#include "../T20_World_Cup/t20wc.h"
#include "main_menu.h"





#include <iostream>
#include <string>
#include <vector>
using namespace std;




/********************************************************************************/
/* Function Name: printTournamentMenu                                           */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the Tournament Menu in styled format                   */
/********************************************************************************/

void printTournamentMenu() {

    clearScreen();

    cout << "╔═══════════════════════════TOURNAMENT MENU═══════════════════════════╗\n\n";
    cout << "1.  Asia Cup 2025\n";
    cout << "2.  Champions Trophy 2025\n";
    cout << "3.  ODI World Cup 2023\n";
    cout << "4.  T20 World Cup 2024\n";
    cout << "5.  Reset Team\n";
    cout << "6.  Back\n";
    cout << "7.  Exit\n";
    cout << "\n╚═══════════════════════════TOURNAMENT MENU═══════════════════════════╝\n\n";

}



/********************************************************************************/
/* Function Name: selectTeam                                                    */
/*                                                                              */
/* Inputs       : vector<string> teams, string menuName                         */
/*                                                                              */
/* Returns      : string (selected team name)                                   */
/*                                                                              */
/* Note         : Handles team selection for a tournament                       */
/********************************************************************************/

string selectTeam(const vector<string> &teams, const string &menuName) {

    int teamChoice;

    while (true) {
        clearScreen();
        cout << "╔═══════════════════════════" << menuName << "═══════════════════════════╗\n\n";
        for (size_t i = 0; i < teams.size(); ++i)
            cout << i + 1 << ".  " << teams[i] << "\n";
        cout << "\n╚═══════════════════════════" << menuName << "═══════════════════════════╝\n\n";

        teamChoice = getIntInput("Enter Your Choice: ");

        if (teamChoice == -1) return "";

        if (teamChoice >= 1 && teamChoice <= (int)teams.size())
            return teams[teamChoice - 1];

        feedback("Invalid Input! Choose Between 1 and " + to_string(teams.size()) + "!");
    }
}



/********************************************************************************/
/* Function Name: selectOver                                                    */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : int (number of overs)                                         */
/*                                                                              */
/* Note         : Allows user to choose valid over amount                       */
/********************************************************************************/

int selectOver(const string &tournamentName) {

    int over;

    do {
        clearScreen();
        cout << "Choose Over For The " << tournamentName << " (5, 10, 20, 50): ";
        over = getIntInput("");

        if (over == -1) return -1;

        if (over != 5 && over != 10 && over != 20 && over != 50)
            feedback("Invalid Input! Choose (5, 10, 20, 50)!");

    } while (over != 5 && over != 10 && over != 20 && over != 50);

    return over;
}



/********************************************************************************/
/* Function Name: tournamentMenu                                                */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Handles full tournament selection and flow                    */
/********************************************************************************/

void tournamentMenu() {

    vector<string> asiaCupTeam = {
        "Afghanistan", "Bangladesh", "HongKong", "India",
        "Oman", "Pakistan", "SriLanka", "UAE"
    };

    vector<string> championsTrophyTeam = {
        "Afghanistan", "Australia", "Bangladesh", "England",
        "India", "NewZealand", "Pakistan", "SouthAfrica"
    };

    vector<string> worldCupTeam = {
        "Afghanistan", "Australia", "Bangladesh", "England",
        "India", "Ireland", "NewZealand", "Netherlands",
        "Pakistan", "SouthAfrica", "SriLanka", "Scotland",
        "WestIndies", "Zimbabwe"
    };

    vector<string> t20WorldCupTeam = {
        "Afghanistan", "Australia", "Bangladesh", "Canada",
        "England", "India", "Ireland", "Namibia", "Nepal",
        "NewZealand", "Netherlands", "Oman", "Pakistan",
        "SouthAfrica", "SriLanka", "Scotland", "UAE",
        "USA", "WestIndies", "Zimbabwe"
    };

    string userTeam = "";
    
    bool running = true;

    while (running) {

        printTournamentMenu();

        int choice = getIntInput("Enter Your Choice: ");

        switch (choice) {

            case 1: { // Asia Cup
                if (userTeam.empty())
                    userTeam = selectTeam(asiaCupTeam, "ASIA CUP TEAM SELECTION");

                if (userTeam.empty()) break;

                int over = selectOver("Asia Cup");
                if (over == -1) break;

                asiaCupMenu(userTeam, over * 6);
                break;
            }

            case 2: { // Champions Trophy
                if (userTeam.empty())
                    userTeam = selectTeam(championsTrophyTeam, "CHAMPIONS TROPHY TEAM SELECTION");

                if (userTeam.empty()) break;

                int over = selectOver("Champions Trophy");
                if (over == -1) break;

                championsTrophyMenu(userTeam, over * 6);
                break;
            }

            case 3: { // ODI World Cup
                if (userTeam.empty())
                    userTeam = selectTeam(worldCupTeam, "WORLD CUP TEAM SELECTION");

                if (userTeam.empty()) break;

                int over = selectOver("ODI World Cup");
                if (over == -1) break;

                worldCupMenu(userTeam, over * 6);
                break;
            }

            case 4: { // T20 World Cup
                if (userTeam.empty())
                    userTeam = selectTeam(t20WorldCupTeam, "T20 WORLD CUP TEAM SELECTION");

                if (userTeam.empty()) break;

                int over = selectOver("T20 World Cup");
                if (over == -1) break;

                t20WorldCupMenu(userTeam, over * 6);
                break;
            }

            case 5: { // Reset Team
                userTeam.clear();
                clearScreen();
                cout << "Team Reset Successful!\n";
                speak("Team reset successful!");
                pressToContinue(0);
                break;
            }

            case 6:  // Back
                return;

            case 7:  // Exit
                exitWindow();
                break;

            case -1:
                running = false;
                break;

            default:
                feedback("Invalid Input! Choose Between 1 - 7!");
                break;
        }
    }
}