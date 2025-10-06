#include "menu.h"
#include "loginSystem.h"
#include "matchEngine.h"
#include "printMenu.h"
#include "utility.h"
#include "pitchReport.h"
#include "../Tournament/Asia_Cup_2025/asiaCup2025.h"
#include "../Tournament/Champions_Trophy/championsTrophy.h"
#include "../Tournament/Odi_World_Cup/wc.h"
#include "tournamentEngine.h"









#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
using namespace std;












/****************************************************************************************************/
/* Function Name: tournamentMenu                                                                    */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for tournamentMenu Where Player Can Play Tournament                 */
/****************************************************************************************************/

void tournamentMenu(){

    int teamChoice;

    string asiaCupTeam[] = {
                "Afghanistan",
                "Bangladesh",
                "HongKong",
                "India",
                "Oman",
                "Pakistan",
                "SriLanka",
                "UAE",
    };

    string championsTrophyTeam[] = {
                "Afghanistan",
                "Australia",
                "Bangladesh",
                "England",
                "India",
                "NewZealand",
                "Pakistan",
                "SouthAfrica",
    };

    string worldCupTeam[] = {
                "Afghanistan",
                "Australia",
                "Bangladesh",
                "England",
                "India",
                "Ireland",
                "NewZealand",
                "Netherlands",
                "Pakistan",
                "SouthAfrica",
                "SriLanka",
                "Scotland",
                "WestIndies",
                "Zimbabwe",
    };

    string userTeam = "";
    
    while(true){

        printTournamentMenu();

        int choice = getIntInput("Enter Your Choice: ");

        if(choice == 1){
            
            int asiaCupOver;

            clearScreen();

            if(userTeam == ""){

                do{

                    printAsiaCupTeamSelection();

                    teamChoice = getIntInput("Enter Your Choice: ");

                    if(teamChoice < 1 || teamChoice > 8){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 8)!\n";

                        pressToContinue();

                    }

                }   while(teamChoice < 1 || teamChoice > 8);

                userTeam = asiaCupTeam[teamChoice - 1];

            }

            int choiceOver = getIntInput("Choose Over For The Asia Cup! (5,10,20,50): ");

            if(choiceOver == 5) asiaCupOver = 5;
            else if(choiceOver == 10) asiaCupOver = 10;
            else if(choiceOver == 20) asiaCupOver = 20;
            else if(choiceOver == 50) asiaCupOver = 50;
            else cout << "Invalid Input! Choose (5, 10, 20, 50)!\n";

            int asiaCupBall = asiaCupOver*6;

            asiaCupMenu(userTeam,asiaCupBall);

        }

        else if(choice == 2){

            int championsTrophyOver;

            clearScreen();

            if(userTeam == ""){

                do{

                    printChampionsTrophyTeamSelection();

                    teamChoice = getIntInput("Enter Your Choice: ");

                    if(teamChoice < 1 || teamChoice > 8){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 8)!\n";

                        pressToContinue();

                    }

                }   while(teamChoice < 1 || teamChoice > 8);

                userTeam = championsTrophyTeam[teamChoice - 1];

            }

            int choiceOver = getIntInput("Choose Over For The Asia Cup! (5,10,20,50): ");

            if(choiceOver == 5) championsTrophyOver = 5;
            else if(choiceOver == 10) championsTrophyOver = 10;
            else if(choiceOver == 20) championsTrophyOver = 20;
            else if(choiceOver == 50) championsTrophyOver = 50;

            else cout << "Invalid Input! Choose (5, 10, 20, 50)!\n";

            int championsTrophyBall = championsTrophyOver*6;

            championsTrophyMenu(userTeam,championsTrophyBall);

        }

        else if(choice == 3){

            int worldCupOver;

            clearScreen();

            if(userTeam == ""){

                do{

                    printWorldCupTeamSelection();

                    teamChoice = getIntInput("Enter Your Choice: ");

                    if(teamChoice < 1 || teamChoice > 14){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 14)!\n";

                        pressToContinue();

                    }

                }   while(teamChoice < 1 || teamChoice > 14);

                userTeam = worldCupTeam[teamChoice - 1];

            }

            int choiceOver = getIntInput("Choose Over For The Asia Cup! (5,10,20,50): ");

            if(choiceOver == 5) worldCupOver = 5;
            else if(choiceOver == 10) worldCupOver = 10;
            else if(choiceOver == 20) worldCupOver = 20;
            else if(choiceOver == 50) worldCupOver = 50;

            else cout << "Invalid Input! Choose (5, 10, 20, 50)!\n";

            int worldCupBall = worldCupOver*6;

            worldCupMenu(userTeam,worldCupBall);

        }

        else if(choice == 4){

            clearScreen();

            cout << "T20 World Cup 2024 Under Development!\n";

            pressToContinue();

        }

        else if(choice == 5){

            userTeam = "";

            cout << "Team Resetted!\n";

            pressToContinue();

        }

        else if(choice == 6){

            return;

        }

        else if(choice == 7){

            clearScreen();

            cout << "Program Exitted!\n";

            exit(0);

        }

        else{

            clearScreen();
            
            cout << "Wrong Input! Choose Between (1 - 7)!\n";

            pressToContinue();

        }

    }

}

















/****************************************************************************************************/
/* Function Name: exhibitionMenu                                                                    */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for ExhibitionMenu Where Player Can Play Exhibition Match           */
/****************************************************************************************************/

void exhibitionMenu(){

    string team[] = {
                "Afghanistan",
                "Australia",
                "Bangladesh",
                "England",
                "India",
                "Ireland",
                "NewZealand",
                "Pakistan",
                "SouthAfrica",
                "SriLanka",
                "WestIndies",
                "Zimbabwe",
    };

    string pitch[4] = {

        "Green", // Seam Bowling Pitch

        "Dusty", // Spinning Pitch

        "Hard",  // Pace & Bounce Pitch

        "Soft",  // Pure Batting Pitch

    };

    string userTeam = "";

    string aiTeam = "";

    int ball = 0;

    int tossResult = 0;

    bool userTeamFlag = false;

    bool aiTeamFlag = false;

    bool ballFlag = false;

    bool tossResultFlag = false;

    int temparature = -1;

    int rainProbability = -1;

    int pitchChoice = -1;

    bool pitchReportFlag = false;

    string choosenPitch = "";
    
    while(true){

        printExhibitionMenu();

        int choice = getIntInput("Enter Choice: ");

        if(choice == 1){

            if(ballFlag == false){

                int over;
            
                do{
                
                    clearScreen();
                
                    over = getIntInput("Enter The Over (5 - 50): ");

                    if(over == -1)  break;

                    if(over<5 || over>10){

                        clearScreen();

                        cout << "Invalid Input! Choose Between (5 - 50)!\n";

                        pressToContinue();

                    }

                }   while(over<5 || over>10);

                if(over == -1){}
                else{

                    clearScreen();

                    ball = over*6;

                    cout << "Over Selection Done. Now You Will Play Match In " << over << " Overs\n";

                    cout << "Loading...\n";

                    pressToContinue();

                    ballFlag = true;

                }

            }

            else{

                clearScreen();

                cout << "You Already Done Choosing Over!\n";

                pressToContinue();

            }

        }

        else if(choice == 2){

            if(userTeamFlag == false){

                int teamChoice;
            
                do{

                    printUserTeamSelectionMenu();

                    teamChoice = getIntInput("Enter Your Choice: ");

                    if(teamChoice == -1)    break;

                    if(teamChoice < 1 || teamChoice > 12){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 12)!\n";

                        pressToContinue();

                    }

                    if(team[teamChoice-1] == aiTeam){

                        clearScreen();

                        cout << team[teamChoice-1] << " Already Selected For AI Team So Can't Choose!\n";

                        teamChoice = 0;

                        pressToContinue();

                    }


                } while(teamChoice < 1 || teamChoice > 12);

                if(teamChoice == -1){}

                else{

                    clearScreen();

                    userTeam = team[teamChoice-1];

                    cout << "Team Selection Done!\n\nYour Team: " << userTeam << " \n\n";

                    pressToContinue();

                    userTeamFlag = true;

                }

            }

            else{

                clearScreen();

                cout << "You Already Selected Your Team!\n";

                pressToContinue();

            }

        }

        else if(choice == 3){

            if(aiTeamFlag == false){

                int teamChoice;
            
                do{

                    printAiTeamSelectionMenu();

                    teamChoice = getIntInput("Enter Your Choice: ");

                    if(teamChoice == -1)    break;

                    if(teamChoice < 1 || teamChoice > 12){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 12)!\n";

                        pressToContinue();

                    }

                    if(team[teamChoice-1] == userTeam){

                        clearScreen();

                        cout << team[teamChoice-1] << " Already Selected For User Team So Can't Choose!\n";

                        teamChoice = 0;

                        pressToContinue();

                    }


                } while(teamChoice < 1 || teamChoice > 12);

                if(teamChoice == -1){}

                else{

                    clearScreen();

                    aiTeam = team[teamChoice-1];

                    cout << "Team Selection Done!\n\nAI Team: " << aiTeam << " \n\n";

                    pressToContinue();

                    aiTeamFlag = true;

                }

            }

            else{

                clearScreen();

                cout << "You Already Selected AI Team!\n";

                pressToContinue();

            }

        }

        else if(choice == 4){

            if(tossResultFlag == false){

                int toss;

                do{

                    printTossSelectionMenu();

                    toss = getIntInput("Enter Your Choice: ");

                    if(toss == -1)  break;

                    if(toss < 1 || toss > 2){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 2)!\n";

                        pressToContinue();

                    }

                }   while(toss < 1 || toss > 2);

                if(toss == -1){}

                else{

                    clearScreen();

                    tossResultFlag = true;

                    int aiToss = rand()%2 + 1;

                    if(toss==aiToss){

                        int userTossChoose;

                        do{

                            clearScreen();
                    
                            cout << "Congrats! You Won The Toss! Choose Which One First You Want To Do\n\n";

                            cout << "1. Bat\n\n2. Bowl\n\n";

                            userTossChoose = getIntInput("Enter Your Choice (1 - 2): ");

                            if(userTossChoose<1 || userTossChoose>2){

                                clearScreen();

                                cout << "Wrong Input! Choose Between (1 - 2)!\n";

                                pressToContinue();

                            }

                        }   while(userTossChoose<1 || userTossChoose>2);

                        tossResult = userTossChoose;

                        clearScreen();

                        if(tossResult==1){

                            cout << "You Won The Toss And Elected To Bat First!\n";

                        }

                        else{

                            cout << "You Won The Toss And Elected To Bowl First!\n";

                        }

                        pressToContinue();

                    }

                    else{

                        int aiTossChoose = rand()%2 + 1;

                        tossResult = aiTossChoose;

                        clearScreen();

                        if(tossResult==1){

                            cout << "You Lost The Toss! You Have To Bat First!\n";

                        }

                        else{

                            cout << "You Lost The Toss! You Have To Bowl First!\n";

                        }

                        pressToContinue();

                    }

                }

            }

            else{

                clearScreen();

                cout << "You Already Done Toss!\n";

                pressToContinue();

            }

        }

        else if(choice == 5){
            
            if(pitchReportFlag == false){

                pitchChoice = rand()%4;

                temparature = rand()%(50-10+1)+10;

                rainProbability = rand()%101;

                choosenPitch = pitch[pitchChoice];
            
                pitchReport(choosenPitch, temparature, rainProbability);

                pitchReportFlag = true;

                pressToContinue();

            }

            else{

                clearScreen();

                cout << "Sorry For A Match Pitch Report Can Be Seen One Time Only!\n";

                cout << "You Can Again See Pitch Report For Next Match\n";

                pressToContinue();

            }

        }

        else if(choice == 6){

            if(userTeam == "" || aiTeam == "" || ball == 0 || tossResult == 0 || choosenPitch == ""){

                cout << "First Complete 1 - 5 step\n";

                pressToContinue();

            }

            else{

                startMatch(userTeam,aiTeam,ball,tossResult,temparature,rainProbability,choosenPitch);

                userTeamFlag = false;

                aiTeamFlag = false;

                ballFlag = false;

                tossResultFlag = false;

                userTeam = "";

                aiTeam = "";

                ball = 0;

                tossResult = 0;

                temparature = -1;

                rainProbability = -1;

                pitchChoice = -1;

                pitchReportFlag = false;

                choosenPitch = "";

            }

        }

        else if(choice == 7){

            clearScreen();

            userTeamFlag = false;

            aiTeamFlag = false;

            ballFlag = false;

            tossResultFlag = false;

            userTeam = "";

            aiTeam = "";

            ball = 0;

            tossResult = 0;

            temparature = -1;

            rainProbability = -1;

            pitchChoice = -1;

            pitchReportFlag = false;

            choosenPitch = "";

            cout << "1 - 5 (Section) Resetted Successfully!\n";

            pressToContinue();

        }

        else if(choice == 8 || choice == -1){

            return;

        }

        else if(choice == 9){

            clearScreen();

            cout << "Program Exitted!\n";

            exit(0);

        }

        else{

            clearScreen();

            cout << "Invalid Input! Choose Between (1 - 8)!\n";

            pressToContinue();

        }

    }

}




















/****************************************************************************************************/
/* Function Name: playMenu                                                                          */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for Play Menu User Can Choose What To Play                          */
/****************************************************************************************************/

void playMenu(){

    while(true){

        printPlayMenu();

        int choice = getIntInput("Enter Choice: ");

        if(choice == 1){

            clearScreen();

            exhibitionMenu();

        }

        else if(choice == 2){

            clearScreen();

            tournamentMenu();

        }

        else if(choice == 3){

            clearScreen();

            cout << "Series Under Development!\n";

            pressToContinue();

        }

        else if(choice == 4){

            clearScreen();

            cout << "About Under Development!\n";

            pressToContinue();

        }

        else if(choice == 5 || choice == -1){

            return;

        }

        else if(choice == 6){

            clearScreen();

            cout << "Program Exitted!\n";

            exit(0);

        }

        else{

            clearScreen();
            
            cout << "Wrong Input! Choose Between (1 - 6)!\n";

            pressToContinue();

        }

    }

}




















/****************************************************************************************************/
/* Function Name: account_menu                                                                      */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for account menu                                                    */
/****************************************************************************************************/

void account_menu() {
    
    
    string activeUser = loadSession();

    if (!activeUser.empty()) {

        auto users = loadUsers();
        
        for (auto &u : users) {
            
            if (u.username == activeUser) {
                
                userMenu(u, users);
            
            }
        
        }
    
    }

    else{

        while (true) {
        
            printAccountMenu();
        
            int choice = getIntInput("Enter choice: ");

            if (choice == 1) registerUser();
        
            else if (choice == 2) loginUser();
        
            else if (choice == 3) resetPassword();

            else if (choice == 4) resetUsername();
        
            else if (choice == 5) {
            
                clearScreen();
            
                cout << "Program Successfully Exitted!\n";

                exit(0);
        
            }

            else if (choice == -1){

                clearScreen();

                cout << "Sorry! Going Back Is Not Allowed Here!\n";

                pressToContinue();

            }
        
            else {
            
                cout << "Invalid Choice! Choose Between (1 - 5)\n";
            
                pressToContinue();
        
            }
    
        }

    }

}