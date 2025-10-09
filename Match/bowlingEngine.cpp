#include "bowlingEngine.h"
#include "utility.h"
#include "matchEngine.h"
#include "score.h"
#include "battingEngine.h"



#include <iostream>
#include <string>
#include <vector>
using namespace std;





void handleLastShot(int runs, int beforeWicket, int afterWicket, string &lastShotChoosed) {
    
    if (runs == 6) lastShotChoosed = "Six";
    
    else if (runs == 4) lastShotChoosed = "Boundary";
    
    else if (runs >= 1) lastShotChoosed = "Rotate";
    
    else if (beforeWicket < afterWicket) lastShotChoosed = "Out";
    
    else lastShotChoosed = "Dot";

}







void bowlDelivery(int &stamina, int &aiScore, int &aiWicket, int temperature, string pitch,
                  string &lastShotChoosed, int ballsLeft, int requiredRuns, string aiTeam, int ball, float winProb) {
    
    
    cout << "Bowling Variation:\n\n1. Bouncer     2. Yorker\n3. In_Swing    4. Out_Swing\n5. Leg_Spin   ";
    
    cout << " 6. Off_Spin\n7. Pace        8. Slower\n9. Arm_Ball   10. Exit\n\n";
    
    int bowlChoice = getIntInput("Enter Your Choice: ");

    int bowlSpeed = 0;
    
    if (bowlChoice == 10){

        cout << "Program Exitted Successfully!\n";

        resetMatch();

        exit(0);

    }
    
    else if (bowlChoice < 1 || bowlChoice > 10) bowlChoice = rand() % 9 + 1;

    else if (bowlChoice == 7)  bowlSpeed = rand()%(148-130+1)+130;
    
    else if (bowlChoice == 8)  bowlSpeed = rand()%(125-115+1)+115;

    else if (bowlChoice == 5 || bowlChoice == 6 || bowlChoice == 9) bowlSpeed = rand()%(90-70+1)+70;

    else    bowlSpeed = rand()%(135-125+1)+125;

    
    string ballType = bowlVariation[bowlChoice - 1];

    cout << ballType << " Delivary Incoming With " << bowlSpeed << " km/h!\n";

    pressToContinue(0);
    
    clearScreen();



    int aiBeforeRun = aiScore;

    int aiBeforeWicket = aiWicket;

    
    int aiShotChoice = aiBattingDecision(stamina, requiredRuns, ballsLeft, 10 - aiWicket,
                                         ballType, pitch, lastShotChoosed, winProb);

    
    
    scoreLogic(stamina, aiShotChoice, 0, temperature, ballType, pitch);

    
    
    int aiAfterRun = aiScore - aiBeforeRun;
    
    int aiAfterWicket = aiWicket - aiBeforeWicket;

    
    
    handleLastShot(aiAfterRun, aiBeforeWicket, aiAfterWicket, lastShotChoosed);
    
    
    pressToContinue(0);

}




void playInnings(string userTeam, string aiTeam, int &aiScore, int &aiWicket, int &stamina,
                 int balls, int target, int temperature, string pitch, string &lastShotChoosed, bool chasing) {
    
    
    
    int ballCount = 1;

    float winProb = 0.0;

    while (ballCount <= balls) {
        
        clearScreen();
        
        scoreCard(aiScore, aiWicket, ballCount, target, aiTeam, balls);

        if (chasing) {
            winProb = calculateWinProbability(aiScore, aiWicket, ballCount, target, balls);
            if (winProb >= 0)
                showWinProbabilityBar(winProb,aiTeam);
            else
                cout << "🏆 Win Probability: Yet to Calculate (First Innings)\n\n";
        }
        
        cout << "Stamina: " << stamina << "\n\n";

        if (aiWicket == 10 || (chasing && aiScore >= target)) break;

        
        int requiredRuns = 0;
        
        if (chasing)
            requiredRuns = target - aiScore;
        
        int ballsLeft = balls - ballCount + 1;

        bowlDelivery(stamina, aiScore, aiWicket, temperature, pitch, lastShotChoosed, ballsLeft, requiredRuns, aiTeam, balls, winProb);
        
        ballCount++;
    
    }

}



void resetMatch() {
    
    userScore = aiScore = userWicket = aiWicket = target = bowlSpeed = 0;
    
    targetFlag = false;

}




int bowl(string userTeam, string aiTeam, int ball, int temperature, int rain, string pitch) {
    
    int stamina = 100;
    
    string lastShotChoosed = "Dot";
    
    clearScreen();

    
    
    // ---------- FIRST INNINGS ----------
    if (!targetFlag) {
        
        playInnings(userTeam, aiTeam, aiScore, aiWicket, stamina, ball, target, temperature, pitch, lastShotChoosed, false);
        
        clearScreen();
        
        target = aiScore + 1;
        
        targetFlag = true;
        
        cout << aiTeam << " Batting End! " << userTeam << " Need " << target << " Runs From " << ball << " Balls!\n";
        
        pressToContinue(0);
        
        return bat(userTeam, aiTeam, ball, temperature, rain, pitch);
    
    }

    
    
    // ---------- SECOND INNINGS ----------
    
    if (rain >= 80 && rain < 90) {
        
        clearScreen();
        
        cout << "Play Stopped Due To Rain\n";
        
        pressToContinue(0);
        
        cout << "Match Abandoned! No Result.\n";
        
        resetMatch();
        
        pressToContinue(0);
        
        return 4; // 4 Means Match Abandoned
    
    }

    
    int ballReduced = ball;
    
    int targetReduced = target;

    
    if (rain >= 60 && rain < 80) {
        
        clearScreen();
        
        cout << "Play Stopped Due To Rain\n";
        
        pressToContinue(0);
        
        cout << "Luckily! Rain Stopped And Play Continues...\n";
        
        ballReduced = max(6, ball - (rand() % 10 + 10));
        
        targetReduced = max(1, int(target * (ballReduced / (float)ball)));
        
        cout << "Balls Reduced To " << ballReduced << " & Revised Target = " << targetReduced << "\n";
        
        pressToContinue(0);

        playInnings(userTeam, aiTeam, aiScore, aiWicket, stamina, ballReduced, targetReduced, temperature, pitch, lastShotChoosed, true);

    
        clearScreen();
    
        if (aiScore >= targetReduced){

            cout << aiTeam << " Won By " << 10 - aiWicket << " Wickets!\n\nHard Luck!\n\n";

            cout << userLoseComments[rand() % userLoseComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 3;

        }

        else if (aiScore == targetReduced - 1){

            cout << "Match Tied!\n\n";

            cout << tieComments[rand() % tieComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 2;

        }

        else{

            cout << userTeam << " Won By " << targetReduced - aiScore << " Runs\n\n";

            cout << userWinComments[rand() % userWinComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 1;

        }
    
    }

    else{

        clearScreen();

        playInnings(userTeam, aiTeam, aiScore, aiWicket, stamina, ball, target, temperature, pitch, lastShotChoosed, true);
    
        clearScreen();
    
        
        if (aiScore >= target) {
            
            cout << aiTeam << " Won By " << 10 - aiWicket << " Wickets!\n\n";
            
            cout << userLoseComments[rand() % userLoseComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 3;
        
        }
        
        else if (aiScore == target - 1) {
            
            cout << "Match Tied!\n\n";
            
            cout << tieComments[rand() % tieComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 2;
        
        }
    
        else {
            
            cout << userTeam << " Won By " << target - aiScore - 1 << " Runs!\n\n";
            
            cout << userWinComments[rand() % userWinComments.size()] << "\n\n";

            resetMatch();
    
            pressToContinue(0);

            return 1;
        
        }

    }

}
