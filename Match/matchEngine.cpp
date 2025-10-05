#include "matchEngine.h"
#include "battingEngine.h"
#include "pitchReport.h"
#include "loginSystem.h"
#include "commentary.h"
#include "score.h"
#include "utility.h"
#include "bowlingEngine.h"



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
    "Leg_Spin",
    "Off_Spin",
    "Pace",
    "Slower",
    "Arm_Ball",

};

string batVariation[] = {

    "LoftShot",
    "StrikeShot",
    "StrikeRotate",
    "Defend",

};





void showWinProbabilityBar(float prob, string team) {
    
    int barWidth = 30;
    
    int filled = (int)((prob / 100.0f) * barWidth);

    string color;
    
    if (prob >= 70) color = "\033[1;32m"; // Green (winning)
    
    else if (prob >= 40) color = "\033[1;33m"; // Yellow (balanced)
    
    else color = "\033[1;31m"; // Red (losing)

    cout << "🏆 Win Probability ( " << team << " ) : [";

    for (int i = 0; i < barWidth; i++) {
        if (i < filled) cout << color << "█" << "\033[0m";
        else cout << "░";
    }

    cout << "] " << fixed << setprecision(1) << prob << "%";

    
    // Add emotion/comment flavor
    
    if (prob >= 80) cout << " 🔥 Dominating!";
    
    else if (prob >= 55) cout << " 💪 In Control";
    
    else if (prob >= 35) cout << " ⚖️ Balanced Battle";
    
    else if (prob >= 15) cout << " 😬 Under Pressure";
    
    else cout << " 💀 Collapsing!";

    cout << "\n\n";

}





float calculateWinProbability(int score, int wicket, int ballCount, int target, int totalBalls) {
    
    if (target <= 0) return -1.0;       // First innings, probability undefined
    
    if (score >= target) return 100.0;  // Already won
    
    if (wicket >= 10) return 0.0;       // All out

    int remainingRuns = target - score;
    
    int remainingBalls = totalBalls - ballCount + 1;
    
    int remainingWickets = 10 - wicket;

    float currentRR = (float)score / (ballCount / 6.0f);
    
    float requiredRR = (remainingBalls > 0) ? (float)remainingRuns / (remainingBalls / 6.0f) : 999.0;

    
    // Base probability: more wickets and balls → higher chance
    
    float prob = (remainingWickets * 8.0) + (remainingBalls / (float)totalBalls) * 50.0;

    
    // Adjust based on required run rate vs current run rate
    
    float rrFactor = (currentRR >= requiredRR) ? 20.0 : -20.0;
    
    prob += rrFactor;

    
    // Adjust based on remaining runs
    
    prob -= remainingRuns * 2.0;

    
    // Clamp to 0-100
    
    prob = max(0.0f, min(100.0f, prob));

    return prob;

}























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


















int batTournament(string userTeam, string aiTeam, int ball, int temparature, int rain, string pitch){

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

            scoreLogic(stamina,batChoice-1,1,temparature,bowlVariation[aiBowl],pitch);

            pressToContinue();

            temporaryBall++;

        }

        clearScreen();
        
        target = userScore + 1;

        targetFlag = true;

        cout << userTeam << " Batting End! " << aiTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        return bowlTournament(userTeam, aiTeam, ball, temparature, rain, pitch);

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

            scoreLogic(stamina,batChoice-1,1,temparature,bowlVariation[aiBowl],pitch);

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











int bowlTournament(string userTeam, string aiTeam, int ball, int temparature, int rain, string pitch){

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

            scoreLogic(stamina,tempScore,0,temparature,bowlVariation[bowlChoice-1],pitch);

            pressToContinue();

            temporaryBall++;
        
        }

        clearScreen();
        
        target = aiScore + 1;

        targetFlag = true;

        cout << aiTeam << " Batting End! " << userTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        return batTournament(userTeam, aiTeam, ball, temparature, rain, pitch);

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

            scoreLogic(stamina,tempScore,0,temparature,bowlVariation[bowlChoice-1],pitch);

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
















void startMatch(string userTeam,string aiTeam,int ball,int toss,int temparature,int rain,string pitch){

    clearScreen();

    if(rain >= 90 && rain <= 100){

        cout << "Match Abandoned Without A Ball Being Bowled Due To Heavy Rain & Storm!\n";

        pressToContinue();

        return;

    }

    if(toss == 1){

        bat(userTeam, aiTeam, ball, temparature, rain, pitch);

    }

    else if(toss == 2){

        bowl(userTeam, aiTeam, ball, temparature, rain, pitch);

    }

    else{

        return;

    }

}