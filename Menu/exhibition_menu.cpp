#include "utility.h"
#include "pitchReport.h"
#include "matchEngine.h"
#include "main_menu.h"





#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;





/********************************************************************************/
/* Function Name: printUserTeamSelectionMenu                                    */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the User Team Selection Menu in styled format          */
/********************************************************************************/

void printUserTeamSelectionMenu() {
    
    clearScreen();

    cout << "╔═══════════════════════USER TEAM SELECTION════════════════════════╗\n\n";
    cout << "1.  Afghanistan\n";
    cout << "2.  Australia\n";
    cout << "3.  Bangladesh\n";
    cout << "4.  England\n";
    cout << "5.  India\n";
    cout << "6.  Ireland\n";
    cout << "7.  New Zealand\n";
    cout << "8.  Pakistan\n";
    cout << "9.  South Africa\n";
    cout << "10. Sri Lanka\n";
    cout << "11. West Indies\n";
    cout << "12. Zimbabwe\n";
    cout << "╚═══════════════════════USER TEAM SELECTION════════════════════════╝\n\n";

}




void feedback(const string &text) {
    cout << text << endl;
    speak(text);
    if (!VOICE_ENABLED) pressToContinue(0);
}



/********************************************************************************/
/* Function Name: printAiTeamSelectionMenu                                     */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the AI Team Selection Menu in styled format            */
/********************************************************************************/

void printAiTeamSelectionMenu() {
    
    clearScreen();

    cout << "╔════════════════════════AI TEAM SELECTION═════════════════════════╗\n\n";
    cout << "1.  Afghanistan\n";
    cout << "2.  Australia\n";
    cout << "3.  Bangladesh\n";
    cout << "4.  England\n";
    cout << "5.  India\n";
    cout << "6.  Ireland\n";
    cout << "7.  New Zealand\n";
    cout << "8.  Pakistan\n";
    cout << "9.  South Africa\n";
    cout << "10. Sri Lanka\n";
    cout << "11. West Indies\n";
    cout << "12. Zimbabwe\n";
    cout << "╚════════════════════════AI TEAM SELECTION═════════════════════════╝\n\n";
}



/********************************************************************************/
/* Function Name: printTossSelectionMenu                                       */
/*                                                                              */
/* Inputs       : int mode (optional, can be 0)                                 */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the Toss Selection Menu                                */
/********************************************************************************/

void printTossSelectionMenu(int mode = 0) {
    
    clearScreen();

    cout << "╔══════════════════════════════TOSS MENU══════════════════════════════╗\n\n";
    cout << "1. Head\n\n";
    cout << "2. Tail\n\n";
    cout << "╚══════════════════════════════TOSS MENU══════════════════════════════╝\n\n";
}



/********************************************************************************/
/* Function Name: printExhibitionMenu                                           */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Prints the Exhibition Menu in styled format                   */
/********************************************************************************/

void printExhibitionMenu() {
    
    clearScreen();

    cout << "╔═══════════════════════════EXHIBITION MENU═══════════════════════════╗\n\n";
    cout << "1.  Choose Over\n";
    cout << "2.  Choose Your Team\n";
    cout << "3.  Choose Opponent Team\n";
    cout << "4.  Do Toss\n";
    cout << "5.  Pitch Report\n";
    cout << "6.  Start Match\n";
    cout << "7.  Reset (1 - 5)\n";
    cout << "8.  Back\n";
    cout << "9.  Exit\n";
    cout << "╚═══════════════════════════EXHIBITION MENU═══════════════════════════╝\n\n";
}



/********************************************************************************/
/* Function Name: exhibitionMenu                                                */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : Controls Exhibition match setup and flow                      */
/********************************************************************************/

void exhibitionMenu() {
    
    string team[] = {
        "Afghanistan", "Australia", "Bangladesh", "England", "India", "Ireland",
        "New Zealand", "Pakistan", "South Africa", "Sri Lanka", "West Indies", "Zimbabwe"
    };

    string pitch[] = {"Green", "Dusty", "Hard", "Soft"};

    string userTeam = "", aiTeam = "", choosenPitch = "";
    
    int ball = 0, tossResult = 0, temperature = -1, rainProbability = -1, pitchChoice = -1;
    
    bool userTeamFlag = false, aiTeamFlag = false, ballFlag = false, tossResultFlag = false, pitchReportFlag = false;

    bool running = true;

    while (running) {
        
        printExhibitionMenu();
        
        int choice = getIntInput("Enter Your Choice: ");

        switch (choice) {
            
            case 1: { // Choose Over
                
                if (!ballFlag) {
                    
                    int over;
                    
                    do {
                        
                        clearScreen();
                        
                        over = getIntInput("Enter The Over (5 - 50): ");
                        
                        if (over == -1) break;
                        
                        if (over < 5 || over > 50) {
                            
                            feedback("Invalid Input! Choose Between (5 - 50)!");
                        
                        }
                    
                    } while (over < 5 || over > 50);

                    if (over != -1) {
                        
                        ball = over * 6;
                        
                        clearScreen();
                        
                        cout << "Over Selection Done! You Will Play " << over << " Overs.\n";
                        
                        speak("Over selection done!");
                        
                        pressToContinue(0);
                        
                        ballFlag = true;
                    
                    }
                
                }
                
                else feedback("You Already Chose Overs!");
                
                break;
            
            }

            case 2: { // Choose User Team
                
                if (!userTeamFlag) {
                    
                    int teamChoice;
                    
                    do {
                        
                        printUserTeamSelectionMenu();
                        
                        teamChoice = getIntInput("Enter Your Choice: ");
                        
                        if (teamChoice == -1) break;
                        
                        if (teamChoice < 1 || teamChoice > 12) feedback("Choose Between 1 and 12!");
                        
                        else if (team[teamChoice - 1] == aiTeam) {
                            
                            feedback("That Team is already selected for AI!");
                            
                            teamChoice = 0;
                        
                        }
                    
                    } while (teamChoice < 1 || teamChoice > 12);

                    if (teamChoice != -1) {
                        
                        userTeam = team[teamChoice - 1];
                        
                        clearScreen();
                        
                        cout << "Your Team: " << userTeam << "\n";
                        
                        speak("Team Selection Done!");
                        
                        pressToContinue(0);
                        
                        userTeamFlag = true;
                    
                    }
                
                }
                
                else feedback("You Already Selected Your Team!");
                
                break;
            
            }

            case 3: { // Choose AI Team
                
                if (!aiTeamFlag) {
                    
                    int teamChoice;
                    
                    do {
                        
                        printAiTeamSelectionMenu();
                        
                        teamChoice = getIntInput("Enter Your Choice: ");
                        
                        if (teamChoice == -1) break;
                        
                        if (teamChoice < 1 || teamChoice > 12) feedback("Choose Between 1 and 12!");
                        
                        else if (team[teamChoice - 1] == userTeam) {
                            
                            feedback("That Team is already selected for User!");
                            
                            teamChoice = 0;
                        
                        }
                    
                    } while (teamChoice < 1 || teamChoice > 12);

                    if (teamChoice != -1) {
                        
                        aiTeam = team[teamChoice - 1];
                        
                        clearScreen();
                        
                        cout << "AI Team: " << aiTeam << "\n";
                        
                        speak("AI Team Selected!");
                        
                        
                        pressToContinue(0);
                        
                        aiTeamFlag = true;
                    
                    }
                
                }
                
                else feedback("You Already Selected AI Team!");
                
                break;
            
            }

            case 4: { // Toss
                
                if (!tossResultFlag) {
                    
                    int toss;
                    
                    do {
                    
                        printTossSelectionMenu(0);
                        
                        toss = getIntInput("Enter Your Choice (1-2): ");
                        
                        if (toss == -1) break;
                        
                        if (toss < 1 || toss > 2) feedback("Choose Between 1 and 2!");
                    
                    } while (toss < 1 || toss > 2);

                    if (toss != -1) {
                        
                        tossResultFlag = true;
                        
                        int aiToss = rand() % 2 + 1;
                        
                        clearScreen();

                        if (toss == aiToss) {
                            
                            int userTossChoice;
                            
                            do {
                                
                                clearScreen();
                                
                                cout << "You Won The Toss!\n1. Bat\n2. Bowl\n";
                                
                                userTossChoice = getIntInput("Enter Choice: ");
                                
                                if (userTossChoice < 1 || userTossChoice > 2)
                                    
                                    feedback("Choose Between 1 and 2!");
                            
                            } while (userTossChoice < 1 || userTossChoice > 2);

                            tossResult = userTossChoice;
                            
                            if (tossResult == 1) cout << "You Elected To Bat First!\n";
                            
                            else cout << "You Elected To Bowl First!\n";
                            
                            speak("You won the toss!");
                        
                        }
                        
                        else {
                            
                            tossResult = rand() % 2 + 1;
                            
                            if (tossResult == 1) cout << "You Lost The Toss! Bat First.\n";
                            
                            else cout << "You Lost The Toss! Bowl First.\n";
                            
                            speak("You lost the toss!");
                        
                        }
                        
                        pressToContinue(0);
                 
                    }
                
                }
                
                else feedback("Toss Already Done!");
                
                break;
            
            }

            case 5: { // Pitch Report
                
                if (!pitchReportFlag) {
                    
                    pitchChoice = rand() % 4;
                    
                    temperature = rand() % 41 + 10;
                    
                    rainProbability = rand() % 101;
                    
                    choosenPitch = pitch[pitchChoice];

                    pitchReport(choosenPitch, temperature, rainProbability);
                    
                    pitchReportFlag = true;
                    
                    pressToContinue(0);
                
                }
                
                else feedback("Pitch Report Can Be Seen Once Per Match!");
                
                break;
            
            }

            case 6: { // Start Match
                
                if (userTeam.empty() || aiTeam.empty() || ball == 0 || tossResult == 0 || choosenPitch.empty()) {
                    
                    feedback("Complete Steps 1 to 5 First!");
                
                }
                
                else {
                    
                    startMatch(userTeam, aiTeam, ball, tossResult, temperature, rainProbability, choosenPitch);
                    
                    // Reset for next match
                    
                    userTeamFlag = aiTeamFlag = ballFlag = tossResultFlag = pitchReportFlag = false;
                    
                    userTeam = aiTeam = choosenPitch = "";
                    
                    ball = tossResult = temperature = rainProbability = pitchChoice = -1;
                
                }
                
                break;
            
            }

            case 7: { // Reset
                
                clearScreen();
                
                userTeamFlag = aiTeamFlag = ballFlag = tossResultFlag = pitchReportFlag = false;
                
                userTeam = aiTeam = choosenPitch = "";
                
                ball = tossResult = temperature = rainProbability = pitchChoice = -1;
                
                cout << "Steps 1 - 5 Reset Successfully!\n";
                
                speak("Reset successful!");
                
                pressToContinue(0);
                
                break;
            
            }

            case 8:  return;
            
            case -1: running = false; break;

            case 9:  // Exit
                
                exitWindow();
            
                break;

            default:
                feedback("Invalid Input! Choose Between 1 - 9!");
                break;
        
        }
    
    }

}