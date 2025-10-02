#include <iostream>
#include <limits>
#include <string>

#include "menu.h"
#include "loginSystem.h"
#include "matchEngine.h"

using namespace std;







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

    string userTeam = "";

    string aiTeam = "";

    int ball = 0;

    int tossResult = 0;

    bool userTeamFlag = false;

    bool aiTeamFlag = false;

    bool ballFlag = false;

    bool tossResultFlag = false;
    
    while(true){

        clearScreen();

        cout << "----------------------------------------------------------------------------\n";
        cout << "|                             Exhibition Menu                              |\n";
        cout << "|                                                                          |\n";
        cout << "| 1. Choose Over                                                           |\n";
        cout << "|                                                                          |\n";
        cout << "| 2. Choose Your Team                                                      |\n";
        cout << "|                                                                          |\n";
        cout << "| 3. Choose Your Opponent Team                                             |\n";
        cout << "|                                                                          |\n";
        cout << "| 4. Do Toss                                                               |\n";
        cout << "|                                                                          |\n";
        cout << "| 5. Start The Match                                                       |\n";
        cout << "|                                                                          |\n";
        cout << "| 6. Reset (1 - 4)                                                         |\n";
        cout << "|                                                                          |\n";
        cout << "| 7. Back                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "| 8. Exit                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "----------------------------------------------------------------------------\n";

        int choice = getIntInput("Enter Choice: ");

        if(choice == 1){

            if(ballFlag == false){

                int over;
            
                do{
                
                    clearScreen();
                
                    over = getIntInput("Enter The Over (5 - 10): ");

                    if(over<5 || over>10){

                        clearScreen();

                        cout << "Invalid Input! Choose Between (1 - 5)!\n";

                        pressToContinue();

                    }

                }   while(over<5 || over>10);

                clearScreen();

                ball = over*6;

                cout << "Over Selection Done. Now You Will Play Match In " << over << " Overs\n";

                cout << "Loading...\n";

                pressToContinue();

                ballFlag = true;

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

                    clearScreen();

                    cout << "----------------------------------------------------------------------------\n";
                    cout << "|                         User Team Selection Menu                         |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 1.  Afghanistan                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 2.  Australia                                                            |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 3.  Bangladesh                                                           |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 4.  England                                                              |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 5.  India                                                                |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 6.  Ireland                                                              |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 7.  New Zealand                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 8.  Pakistan                                                             |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 9.  South Africa                                                         |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 10. Sri Lanka                                                            |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 11. West Indies                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 12. Zimbabwe                                                             |\n";
                    cout << "|                                                                          |\n";
                    cout << "----------------------------------------------------------------------------\n";

                    teamChoice = getIntInput("Enter Your Choice: ");

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

                clearScreen();

                userTeam = team[teamChoice-1];

                cout << "Team Selection Done!\n\nYour Team: " << userTeam << " \n\n";

                pressToContinue();

                userTeamFlag = true;

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

                    clearScreen();

                    cout << "----------------------------------------------------------------------------\n";
                    cout << "|                        AI Team Selection Menu                            |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 1.  Afghanistan                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 2.  Australia                                                            |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 3.  Bangladesh                                                           |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 4.  England                                                              |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 5.  India                                                                |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 6.  Ireland                                                              |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 7.  New Zealand                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 8.  Pakistan                                                             |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 9.  South Africa                                                         |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 10. Sri Lanka                                                            |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 11. West Indies                                                          |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 12. Zimbabwe                                                             |\n";
                    cout << "|                                                                          |\n";
                    cout << "----------------------------------------------------------------------------\n";

                    teamChoice = getIntInput("Enter Your Choice: ");

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

                clearScreen();

                aiTeam = team[teamChoice-1];

                cout << "Team Selection Done!\n\nAI Team: " << aiTeam << " \n\n";

                pressToContinue();

                aiTeamFlag = true;

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

                    clearScreen();

                    cout << "----------------------------------------------------------------------------\n";
                    cout << "|                        Toss Selection Menu                               |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 1. Head                                                                  |\n";
                    cout << "|                                                                          |\n";
                    cout << "| 2. Tail                                                                  |\n";
                    cout << "|                                                                          |\n";
                    cout << "----------------------------------------------------------------------------\n";

                    toss = getIntInput("Enter Your Choice: ");

                    if(toss < 1 || toss > 2){

                        clearScreen();

                        cout << "Wrong Input! Choose Between (1 - 2)!\n";

                        pressToContinue();

                    }

                }   while(toss < 1 || toss > 2);

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

                    tossResult = aiTossChoose - 1;

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

            else{

                clearScreen();

                cout << "You Already Done Toss!\n";

                pressToContinue();

            }

        }

        else if(choice == 5){

            if(userTeam == "" || aiTeam == "" || ball == 0 || tossResult == 0){

                cout << "First Complete 1 - 4 step";

                pressToContinue();

            }

            else{

                startMatch(userTeam,aiTeam,ball,tossResult);

                userTeamFlag = false;

                aiTeamFlag = false;

                ballFlag = false;

                tossResultFlag = false;

                userTeam = "";

                aiTeam = "";

                ball = 0;

                tossResult = 0;

            }

        }

        else if(choice == 6){

            clearScreen();

            userTeamFlag = false;

            aiTeamFlag = false;

            ballFlag = false;

            tossResultFlag = false;

            userTeam = "";

            aiTeam = "";

            ball = 0;

            tossResult = 0;

            cout << "1 - 4 (Section) Resetted Successfully!\n";

            pressToContinue();

        }

        else if(choice == 7){

            return;

        }

        else if(choice == 8){

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






void playMenu(){

    while(true){

        clearScreen();

        cout << "----------------------------------------------------------------------------\n";
        cout << "|                               Play Menu                                  |\n";
        cout << "|                                                                          |\n";
        cout << "| 1. Exhibition Match                                                      |\n";
        cout << "|                                                                          |\n";
        cout << "| 2. Tournament                                                            |\n";
        cout << "|                                                                          |\n";
        cout << "| 3. Series                                                                |\n";
        cout << "|                                                                          |\n";
        cout << "| 4. About                                                                 |\n";
        cout << "|                                                                          |\n";
        cout << "| 5. Back                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "| 6. Exit                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "----------------------------------------------------------------------------\n";

        int choice = getIntInput("Enter Choice: ");

        if(choice == 1){

            clearScreen();

            exhibitionMenu();

        }

        else if(choice == 2){

            clearScreen();

            cout << "Tournament Under Development!\n";

            pressToContinue();

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

        else if(choice == 5){

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