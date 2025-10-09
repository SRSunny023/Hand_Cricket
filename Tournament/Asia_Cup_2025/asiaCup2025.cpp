#include "asiaCup2025.h"
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
/* Function Name: setupAsiaCup                                                  */
/*                                                                              */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Initializes the Asia Cup tournament structure and fixtures    */
/********************************************************************************/

Tournament setupAsiaCup() {

    Tournament T("Asia Cup", "QualifierA");

    T.qualifierA = {
        Team("Nepal"), Team("HongKong"), Team("Qatar"),
        Team("SaudiArabia"), Team("Malaysia")
    };

    T.qualifierB = {
        Team("Oman"), Team("UAE"), Team("Kuwait"),
        Team("Bahrain"), Team("Cambodia")
    };

    T.fixtures = {
        {"Malaysia", "Nepal"},
        {"HongKong", "Qatar"},
        {"Nepal", "Qatar"},
        {"Malaysia", "SaudiArabia"},
        {"SaudiArabia", "HongKong"},
        {"HongKong", "Nepal"},
        {"Malaysia", "Qatar"},
        {"Qatar", "SaudiArabia"},
        {"Malaysia", "HongKong"},
        {"SaudiArabia", "Nepal"}
    };

    return T;
}



/********************************************************************************/
/* Function Name: resetTournamentAsiaCup                                        */
/*                                                                              */
/* Inputs       : string name                                                   */
/* Returns      : Tournament                                                    */
/*                                                                              */
/* Note         : Resets and returns a new instance of the Asia Cup tournament  */
/********************************************************************************/

Tournament resetTournamentAsiaCup(const string &name) {
    
    return setupAsiaCup();

}



/********************************************************************************/
/* Function Name: printAsiaCupMenu                                              */
/*                                                                              */
/* Inputs       : Tournament &T, string userTeam, int ball                      */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the Asia Cup main menu in styled format                */
/********************************************************************************/

void printAsiaCupMenu(const Tournament &T, const string &userTeam, int ball) {

    clearScreen();

    cout << "╔══════════════════════════════" << T.name << "══════════════════════════════╗\n\n";
    
    cout << "Your Team   : " << userTeam << "\n";
    
    cout << "Match Format: " << ball / 6 << " Overs\n\n";
    
    cout << "1. Play Next Match\n";
    
    cout << "2. View Fixtures\n";
    
    cout << "3. View Points Table\n";
    
    cout << "4. Reset Tournament\n";
    
    cout << "5. Back\n";
    
    cout << "\n╚══════════════════════════════" << T.name << "══════════════════════════════╝\n\n";

}



/********************************************************************************/
/* Function Name: asiaCupMenu                                                   */
/*                                                                              */
/* Inputs       : string userTeam, int ball                                     */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Controls the Asia Cup 2025 tournament flow                    */
/********************************************************************************/

void asiaCupMenu(string userTeam, int ball) {

    int choice;
    
    static Tournament asia;

    ifstream fin("Database/asia_cup_save.txt");
    
    string tournamentName;

    if (fin >> tournamentName && !tournamentName.empty()) {
        
        fin.close();
        
        asia = loadTournament("Asia Cup");
        
        clearScreen();

        loadingScreen("Loading Previous Tournament Please Wait");
        
        cout << "Previous Tournament Loaded!\n";
        
        speak("Previous tournament loaded!");
        
        if(!VOICE_ENABLED){

            #ifdef _WIN32
                sleepMS(2000);
                while (_kbhit()) _getch();
            #else
                sleepIgnoreInput(2000);
            #endif

        }
    
    }
    
    else {
        
        asia = setupAsiaCup();
    
    }

    bool running = true;

    while (running) {

        printAsiaCupMenu(asia, userTeam, ball);

        choice = getIntInput("Enter Your Choice: ");

        switch (choice) {

            case 1: {
                
                clearScreen();

                loadingScreen("Playing Next Match Please Wait!");

                clearScreen();
                
                playNextFixture(asia, userTeam, ball);
                
                saveTournament(asia);
                
                if(!VOICE_ENABLED){

                    pressToContinue(0);

                }
                
                break;
            
            }

            case 2: {
                
                clearScreen();
                
                loadingScreen("Loading Fixture Please Wait!");

                cout << "Fixtures Loaded Successfully!\n";

                cout << flush;

                if(!VOICE_ENABLED){

                    #ifdef _WIN32
                        sleepMS(2000);
                        while (_kbhit()) _getch();
                    #else
                        sleepIgnoreInput(2000);
                    #endif

                }
                
                speak("Fixtures Loaded Successfully!");

                clearScreen();
                
                showFixtures(asia);
                
                if(!VOICE_ENABLED){

                    pressToContinue(0);

                }
                
                break;
            
            }

            case 3: {
                
                clearScreen();

                loadingScreen("Loading Points Table Please Wait!");

                cout << "Points Table Loaded Successfully!\n";

                cout << flush;

                if(!VOICE_ENABLED){

                    #ifdef _WIN32
                        sleepMS(2000);
                        while (_kbhit()) _getch();
                    #else
                        sleepIgnoreInput(2000);
                    #endif

                }
                
                speak("Points Table Loaded Successfully!");

                clearScreen();
                
                showPointsTable(asia);
                
                if(!VOICE_ENABLED){

                    pressToContinue(0);

                }
                
                break;
            
            }

            case 4: {
                
                clearScreen();
                
                asia = resetTournamentAsiaCup(asia.name);
                
                cout << "Tournament Reset Successfully!\n";
                
                speak("Tournament reset successful!");
                
                if(!VOICE_ENABLED){

                    #ifdef _WIN32
                        sleepMS(2000);
                        while (_kbhit()) _getch();
                    #else
                        sleepIgnoreInput(2000);
                    #endif

                }
                
                break;
            
            }

            case 5: {
                
                clearScreen();
                
                loadingScreen("Returning To Tournament Menu");
                
                speak("Returning to tournament menu!");
                
                if(!VOICE_ENABLED){

                    #ifdef _WIN32
                        sleepMS(2000);
                        while (_kbhit()) _getch();
                    #else
                        sleepIgnoreInput(2000);
                    #endif

                }
                
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
