#include "matchEngine.h"
#include "battingEngine.h"
#include "pitchReport.h"
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




void startMatch(string userTeam,string aiTeam,int ball,int toss,int temparature,int rain,string pitch){

    int matchResult;
    
    clearScreen();

    if(rain >= 90 && rain <= 100){

        cout << "Match Abandoned Without A Ball Being Bowled Due To Heavy Rain & Storm!\n";

        pressToContinue(0);

        return;

    }

    if(toss == 1){

        matchResult = bat(userTeam, aiTeam, ball, temparature, rain, pitch);

    }

    else if(toss == 2){

        matchResult = bowl(userTeam, aiTeam, ball, temparature, rain, pitch);

    }

    else{

        return;

    }

    clearScreen();

    if(matchResult == 1){

        cout << userWinComments[rand() % userWinComments.size()] << "\n\n";

    }

    else if(matchResult == 2){

        cout << tieComments[rand() % tieComments.size()] << "\n\n";

    }

    else if(matchResult == 3){

        cout << userLoseComments[rand() % userLoseComments.size()] << "\n\n";

    }

    else if(matchResult == 4){

        cout << "Match Abandoned Due To Rain\n";

    }

    pressToContinue(0);

}









int tournamentMatchToss(string userTeam, string aiTeam){

    int tossChoose;

    do{

        clearScreen();

        tossChoose = getIntInput("TOSS TIME\n\n1. Head\n2. Tail\n\nEnter Your Choice: ");

        if(tossChoose < 1 || tossChoose > 2){

            cout << "Wrong Input! Choose Between (1 - 2)!\n";

        }

    }   while(tossChoose < 1 || tossChoose > 2);

    int aiTossChoose = rand()%(2-1+1)+1;

    if(tossChoose == aiTossChoose){

        clearScreen();

        cout << "Congratulations! " << userTeam << " Won The Toss!\n";

        pressToContinue(0);

        int tossDecision;

        do{

            clearScreen();
            
            tossDecision = getIntInput("What You Want To Do First!\n\n1. Bat\n2. Ball\n\nEnter Choice: ");

            if(tossDecision < 1 || tossDecision > 2){

                cout << "Invalid Input! Choose Between (1 - 2)!\n";

            }

        }   while(tossDecision < 1 || tossDecision > 2);

        if(tossDecision == 1)   return 1; // 1 Indicates User Bat First
        else    return 2; // 2 Indicates User Ball First

    }

    else{

        int aiTossDecision = rand()%(2-1+1)+1;

        if(aiTossDecision == 1) return 3; // 3 Indicates AI Won Toss And Choose Ball First
        else    return 4;   // 4 Indicates AI Won Toss And Choose Bat First

    }

    return 1;

}




int tournamentMatchStart(string userTeam,string aiTeam,int ball){

    clearScreen();
    
    string pitches[4] = {

        "Green",

        "Dusty",

        "Hard",

        "Soft",

    };
    
    cout << "Welcome To " << userTeam << " vs " << aiTeam << " Clash!\n\n";

    
    
    int pitchChoice = rand()%4;

    int temparature = rand()%(50-10+1)+10;

    int rainProbability = rand()%91;

    string choosenPitch = pitches[pitchChoice];
    
    pitchReport(choosenPitch, temparature, rainProbability);

    pressToContinue(0);

    int toss = tournamentMatchToss(userTeam, aiTeam);

    clearScreen();

    if(toss == 1){

        cout << userTeam << " Won The Toss And Elected To Bat First!\n\n";

        pressToContinue(0);

        return bat(userTeam, aiTeam, ball, temparature, rainProbability, choosenPitch);

    }

    else if(toss == 2){

        cout << userTeam << " Won The Toss And Elected To Ball First!\n\n";

        return bowl(userTeam, aiTeam, ball, temparature, rainProbability, choosenPitch);

    }

    else if(toss == 3){

        cout << aiTeam << " Won The Toss And Elected To Ball First!\n\n";

        return bat(userTeam, aiTeam, ball, temparature, rainProbability, choosenPitch);

    }
    else{

        cout << aiTeam << " Won The Toss And Elected To Bat First!\n\n";

        return bowl(userTeam, aiTeam, ball, temparature, rainProbability, choosenPitch);

    }



}