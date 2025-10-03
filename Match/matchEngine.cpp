#include "matchEngine.h"
#include "loginSystem.h"
#include "commentary.h"
#include "score.h"
#include "utility.h"



#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;





int userScore = 0;
int aiScore = 0;
int userWicket = 0;
int aiWicket = 0;
int target = 0;
int bowlSpeed = 0;
bool targetFlag = false;



string bowlVariation[] = {

    "Bouncer",
    "Yorker",
    "In_Swing",
    "Out_Swing",
    "Off_Cutter",
    "Leg_Cutter",
    "Pace",
    "Slower",
    "Knuckle",

};

string batVariation[] = {

    "LoftShot",
    "StrikeShot",
    "StrikeRotate",
    "Defend",

};









int batTournament(string, string, int);
int bowlTournament(string, string, int);
void bat(string, string, int);
void bowl(string, string, int);












void resetProgressTournamentMatch(){

    // Match End All Reset To 0

    userScore = 0;
        
    aiScore = 0;

    userWicket = 0;

    aiWicket = 0;

    target = 0;

    bowlSpeed = 0;

    targetFlag = false;

}




int batTournament(string userTeam, string aiTeam, int ball){

    int batChoice;

    int stamina = 100;

    int temporaryBall = 1;

    if(targetFlag == false){ //Batting First

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam, ball);

            if(userWicket == 10){

                cout << "Ops! You Have All Out, Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }
            
            cout << "Stamina: " << stamina << " \n";

            cout << "\n\n";

            int aiBowl = rand()%9;

            bowlSpeed = rand()%(145-80+1) + 80;

            cout << bowlVariation[aiBowl] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            cout << "Batting Choice:\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n";

            batChoice = getIntInput("Enter Your Choice: ");

            if(batChoice == 5){

                cout << "Program Exitted Successfully!\n";
                
                exit(1);

            }

            if(batChoice < 1 || batChoice > 5){

                cout << "Invalid Input! That's Why Random Shot Choosen\n";

                batChoice = rand()%(4-1+1)+1;

            }

            clearScreen();

            scoreLogic(stamina,batChoice-1,1);

            pressToContinue();

            temporaryBall++;

        }

        clearScreen();
        
        target = userScore + 1;

        targetFlag = true;

        cout << userTeam << " Batting End! " << aiTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        return bowlTournament(userTeam, aiTeam, ball);

    }

    else{

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam, ball);

            if(userWicket == 10){

                cout << "Ops! You Have All Out, Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            if(userScore >= target){

                cout << "Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }
            
            cout << "Stamina: " << stamina << " \n";

            cout << "\n\n";

            int aiBowl = rand()%9;

            bowlSpeed = rand()%(145-80+1) + 80;

            cout << bowlVariation[aiBowl] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            cout << "Batting Choice:\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n";

            batChoice = getIntInput("Enter Your Choice: ");

            if(batChoice == 5){

                cout << "Program Exitted Successfully!\n";
                
                exit(1);

            }

            if(batChoice < 1 || batChoice > 5){

                cout << "Invalid Input! That's Why Random Shot Choosen\n";

                batChoice = rand()%(4-1+1)+1;

            }

            clearScreen();

            scoreLogic(stamina,batChoice-1,1);

            pressToContinue();

            temporaryBall++;

        }

        clearScreen();
        
        if(userScore >= target){

            cout << userTeam << " Won By " << 10-userWicket << " Wickets!\n\n";

            cout << "Congratulations! For This Big Win!\n\n";

            pressToContinue();

            return 1; // 1 Means USER Win

        }

        else if(userScore == target){

            cout << "Match Tied!\n\n";

            pressToContinue();

            return 2; // 2 Means TIE

        }

        else{

            cout << aiTeam << " Won By " << target-userScore << " Runs\n\n";

            pressToContinue();

            return 3; // 3 Means AI Win

        }

    }

}











int bowlTournament(string userTeam, string aiTeam, int ball){

    int bowlChoice;

    int stamina = 100;
    
    clearScreen();

    int temporaryBall = 1;

    if(targetFlag == false){ // Bowling First

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam, ball);

            if(aiWicket == 10){

                cout << "Ops! AI Have All Out, AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            cout << "Bowling Variation:\n1. Bouncer\n2. Yorker\n3. In_Swing\n4. Out_Swing\n5. Off_Cutter\n";

            cout << "6. Leg_Cutter\n7. Pace\n8. Slower\n9. Knuckle\n10. Exit\n\n\n";

            bowlChoice = getIntInput("Enter Your Choice: ");

            if(bowlChoice == 10){

                clearScreen();

                cout << "Program Exitted!\n";

                exit(0);

            }

            if(bowlChoice < 1 || bowlChoice > 10){

                cout << "Invalid Input! That's Why Random Delivary Choosen\n";

                bowlChoice = rand()%(9-1+1)+1;

                pressToContinue();

            }

            clearScreen();

            if(bowlChoice == 8){

                bowlSpeed = rand()%(110-80+1) + 80;

            }

            else if(bowlChoice == 7){

                bowlSpeed = rand()%(145-139+1) + 139;

            }

            else{

                bowlSpeed = rand()%(145-80+1) + 80;

            }

            cout << bowlVariation[bowlChoice-1] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            pressToContinue();

            int tempScore = rand()%4;

            scoreLogic(stamina,tempScore,0);

            pressToContinue();

            temporaryBall++;
        
        }

        clearScreen();
        
        target = aiScore + 1;

        targetFlag = true;

        cout << aiTeam << " Batting End! " << userTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        return batTournament(userTeam, aiTeam, ball);

    }

    else{

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam, ball);

            if(aiWicket == 10){

                cout << "Ops! AI Have All Out, AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            if(aiScore >= target){

                cout << "AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            cout << "Bowling Variation:\n1. Bouncer\n2. Yorker\n3. In_Swing\n4. Out_Swing\n5. Off_Cutter\n";

            cout << "6. Leg_Cutter\n7. Pace\n8. Slower\n9. Knuckle\n10. Exit\n\n\n";

            bowlChoice = getIntInput("Enter Your Choice: ");

            if(bowlChoice == 10){

                clearScreen();

                cout << "Program Exitted!\n";

                exit(0);

            }

            if(bowlChoice < 1 || bowlChoice > 10){

                cout << "Invalid Input! That's Why Random Delivary Choosen\n";

                bowlChoice = rand()%(9-1+1)+1;

                pressToContinue();

            }

            clearScreen();

            if(bowlChoice == 8){

                bowlSpeed = rand()%(110-80+1) + 80;

            }

            else if(bowlChoice == 7){

                bowlSpeed = rand()%(145-139+1) + 139;

            }

            else{

                bowlSpeed = rand()%(145-80+1) + 80;

            }

            cout << bowlVariation[bowlChoice-1] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            pressToContinue();

            int tempScore = rand()%4;

            scoreLogic(stamina,tempScore,0);

            pressToContinue();

            temporaryBall++;
        
        }

        clearScreen();
        
        if(aiScore >= target){

            cout << aiTeam << " Won By " << 10-aiWicket << " Wickets!\n\n";

            cout << "Hard Luck! Better Try Next Time!\n\n";

            pressToContinue();

            return 3;

        }

        else if(aiScore == target){

            cout << "Match Tied!\n\n";

            pressToContinue();

            return 2;

        }

        else{

            cout << userTeam << " Won By " << target-aiScore << " Runs\n\n";

            pressToContinue();

            return 1;

        }

    }

}














void bat(string userTeam, string aiTeam, int ball){

    int batChoice;

    int stamina = 100;
    
    clearScreen();

    int temporaryBall = 1;

    if(targetFlag == false){ //Batting First

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam, ball);

            if(userWicket == 10){

                cout << "Ops! You Have All Out, Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }
            
            cout << "Stamina: " << stamina << " \n";

            cout << "\n\n";

            int aiBowl = rand()%9;

            bowlSpeed = rand()%(145-80+1) + 80;

            cout << bowlVariation[aiBowl] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            cout << "Batting Choice:\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n";

            batChoice = getIntInput("Enter Your Choice: ");

            clearScreen();

            if(batChoice == 5){

                cout << "Program Exitted Successfully!\n";
                
                exit(1);

            }

            if(batChoice < 1 || batChoice > 5){

                cout << "Invalid Input! That's Why Random Shot Choosen\n";

                batChoice = rand()%(4-1+1)+1;

            }

            scoreLogic(stamina,batChoice-1,1);

            pressToContinue();

            temporaryBall++;

        }

        clearScreen();
        
        target = userScore + 1;

        targetFlag = true;

        cout << userTeam << " Batting End! " << aiTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        bowl(userTeam, aiTeam, ball);

    }

    else{

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam, ball);

            if(userWicket == 10){

                cout << "Ops! You Have All Out, Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            if(userScore >= target){

                cout << "Your Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }
            
            cout << "Stamina: " << stamina << " \n";

            cout << "\n\n";

            int aiBowl = rand()%9;

            bowlSpeed = rand()%(145-80+1) + 80;

            cout << bowlVariation[aiBowl] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            cout << "Batting Choice:\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n";

            batChoice = getIntInput("Enter Your Choice: ");

            clearScreen();

            if(batChoice == 5){

                cout << "Program Exitted Successfully!\n";
                
                exit(1);

            }

            if(batChoice < 1 || batChoice > 5){

                cout << "Invalid Input! That's Why Random Shot Choosen\n";

                batChoice = rand()%(4-1+1)+1;

            }

            scoreLogic(stamina,batChoice-1,1);

            pressToContinue();

            temporaryBall++;

        }

        clearScreen();
        
        if(userScore >= target){

            cout << userTeam << " Won By " << 10-userWicket << " Wickets!\n\n";

            cout << "Congratulations! For This Big Win!\n\n";

        }

        else if(userScore == target){

            cout << "Match Tied!\n\n";

        }

        else{

            cout << aiTeam << " Won By " << target-userScore << " Runs\n\n";

        }

        // Match End All Reset To 0

        userScore = 0;
        
        aiScore = 0;

        userWicket = 0;

        aiWicket = 0;

        target = 0;

        bowlSpeed = 0;

        targetFlag = false;

        pressToContinue();

    }

}











void bowl(string userTeam, string aiTeam, int ball){

    int bowlChoice;

    int stamina = 100;
    
    clearScreen();

    int temporaryBall = 1;

    if(targetFlag == false){ // Bowling First

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam, ball);

            if(aiWicket == 10){

                cout << "Ops! AI Have All Out, AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            cout << "Bowling Variation:\n1. Bouncer\n2. Yorker\n3. In_Swing\n4. Out_Swing\n5. Off_Cutter\n";

            cout << "6. Leg_Cutter\n7. Pace\n8. Slower\n9. Knuckle\n10. Exit\n\n\n";

            bowlChoice = getIntInput("Enter Your Choice: ");

            if(bowlChoice == 10){

                clearScreen();

                cout << "Program Exitted!\n";

                exit(0);

            }

            if(bowlChoice < 1 || bowlChoice > 10){

                cout << "Invalid Input! That's Why Random Delivary Choosen\n";

                bowlChoice = rand()%(9-1+1)+1;

                pressToContinue();

            }

            clearScreen();

            if(bowlChoice == 8){

                bowlSpeed = rand()%(110-80+1) + 80;

            }

            else if(bowlChoice == 7){

                bowlSpeed = rand()%(145-139+1) + 139;

            }

            else{

                bowlSpeed = rand()%(145-80+1) + 80;

            }

            cout << bowlVariation[bowlChoice-1] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            pressToContinue();

            int tempScore = rand()%4;

            scoreLogic(stamina,tempScore,0);

            pressToContinue();

            temporaryBall++;
        
        }

        clearScreen();
        
        target = aiScore + 1;

        targetFlag = true;

        cout << aiTeam << " Batting End! " << userTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        bat(userTeam, aiTeam, ball);

    }

    else{

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam, ball);

            if(aiWicket == 10){

                cout << "Ops! AI Have All Out, AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            if(aiScore >= target){

                cout << "AI Batting Comes To End!\n\n";

                pressToContinue();

                break;

            }

            cout << "Bowling Variation:\n1. Bouncer\n2. Yorker\n3. In_Swing\n4. Out_Swing\n5. Off_Cutter\n";

            cout << "6. Leg_Cutter\n7. Pace\n8. Slower\n9. Knuckle\n10. Exit\n\n\n";

            bowlChoice = getIntInput("Enter Your Choice: ");

            if(bowlChoice == 10){

                clearScreen();

                cout << "Program Exitted!\n";

                exit(0);

            }

            if(bowlChoice < 1 || bowlChoice > 10){

                cout << "Invalid Input! That's Why Random Delivary Choosen\n";

                bowlChoice = rand()%(9-1+1)+1;

                pressToContinue();

            }

            clearScreen();

            if(bowlChoice == 8){

                bowlSpeed = rand()%(110-80+1) + 80;

            }

            else if(bowlChoice == 7){

                bowlSpeed = rand()%(145-139+1) + 139;

            }

            else{

                bowlSpeed = rand()%(145-80+1) + 80;

            }

            cout << bowlVariation[bowlChoice-1] << " Delivary Incoming With " << bowlSpeed << " Speed" << " \n\n";

            pressToContinue();

            int tempScore = rand()%4;

            scoreLogic(stamina,tempScore,0);

            pressToContinue();

            temporaryBall++;
        
        }

        clearScreen();
        
        if(aiScore >= target){

            cout << aiTeam << " Won By " << 10-aiWicket << " Wickets!\n\n";

            cout << "Hard Luck! Better Try Next Time!\n\n";

        }

        else if(aiScore == target){

            cout << "Match Tied!\n\n";

        }

        else{

            cout << userTeam << " Won By " << target-aiScore << " Runs\n\n";

        }

        // Match End All Reset To 0

        userScore = 0;
        
        aiScore = 0;

        userWicket = 0;

        aiWicket = 0;

        target = 0;

        bowlSpeed = 0;

        targetFlag = false;

        pressToContinue();

    }

}















void startMatch(string userTeam, string aiTeam, int ball, int toss){

    clearScreen();

    if(toss == 1){

        bat(userTeam, aiTeam, ball);

    }

    else if(toss == 2){

        bowl(userTeam, aiTeam, ball);

    }

    else{

        return;

    }

}