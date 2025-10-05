#include "battingEngine.h"
#include "utility.h"
#include "bowlingEngine.h"
#include "score.h"
#include "matchEngine.h"



#include <iostream>
#include <string>
#include <vector>
using namespace std;









int aiBattingDecision(
    int &stamina, 
    int runsNeeded, 
    int ballsLeft, 
    int wicketsLeft,
    string ballType, 
    string pitchType,
    string lastShot,
    float winProb
) {
    
    // ---------- BASE METRICS ----------
    
    float rrr = (ballsLeft > 0) ? (runsNeeded * 6.0 / ballsLeft) : 0;  // required run rate
    
    int totalBalls = 120; // assume 20-over match (you can adjust)
    
    float progress = 1.0f - (float)ballsLeft / totalBalls;

    
    
    
    // ---------- CONFIDENCE SYSTEM ----------
    
    static float aiConfidence = 50.0f; // persistent across overs

    
    
    
    // adjust confidence based on last shot outcome
    
    if (lastShot == "Boundary") aiConfidence += 10;
    
    else if (lastShot == "Six") aiConfidence += 15;
    
    else if (lastShot == "Dot") aiConfidence -= 5;
    
    else if (lastShot == "Out") aiConfidence -= 20;
    
    else if (lastShot == "Rotate") aiConfidence += 2;

    
    
    
    // decay & clamp
    
    aiConfidence = max(10.0f, min(100.0f, aiConfidence));

    
    
    
    // ---------- WEIGHTS ----------
    
    int loftWeight = 10, strikeWeight = 30, rotateWeight = 40, defendWeight = 20;

    
    
    
    
    // ---------- STAMINA EFFECT ----------
    
    if (stamina < 20) { 
        
        loftWeight -= 8; strikeWeight -= 15; rotateWeight -= 20; defendWeight += 25;
    
    }

    else if (stamina < 40) {
        
        loftWeight -= 6; strikeWeight -= 10; rotateWeight -= 10; defendWeight += 20;
    
    } 
    
    else if (stamina > 90) { 
        
        loftWeight += 40; strikeWeight += 15;
    
    }

    else if (stamina > 70) { 
        
        loftWeight += 10; strikeWeight += 5;
    
    }

    
    
    
    // ---------- CONFIDENCE MODIFIER ----------
    
    if (aiConfidence > 70) {
        
        loftWeight += 10; strikeWeight += 10;
    
    }
    
    else if (aiConfidence < 40) {
        
        defendWeight += 10; rotateWeight += 5;
    
    }

    
    
    
    // ---------- WIN PROBABILITY ADJUSTMENT ----------
    
    if (winProb < 30) { // losing badly — must attack
        
        loftWeight += 15; strikeWeight += 10; defendWeight -= 10;
    
    }
    
    else if (winProb > 70) { // comfortably winning — play safe
        
        rotateWeight += 10; defendWeight += 10; loftWeight -= 10;
    
    }

    
    
    
    // ---------- REQUIRED RATE LOGIC ----------
    
    if (rrr >= 12) { 
        
        loftWeight += 25; strikeWeight += 15; defendWeight -= 15;
    
    }
    
    else if (rrr >= 10) { 
        
        loftWeight += 15; strikeWeight += 10; defendWeight -= 10;
    
    }
    
    else if (rrr >= 7) { 
        
        strikeWeight += 10; rotateWeight += 5;
    
    }
    
    else { 
        
        rotateWeight += 10; defendWeight += 5;
    
    }

    
    
    
    // ---------- PITCH & BALL EFFECT ----------
    
    if (pitchType == "Dusty" && (ballType == "Off_Spin" || ballType == "Leg_Spin" || ballType == "Slower")) {
        
        loftWeight -= 5; rotateWeight += 5; defendWeight += 5;
    
    }
    
    else if (pitchType == "Green" && (ballType == "In_Swing" || ballType == "Out_Swing")) {
        
        strikeWeight -= 5; defendWeight += 5;
    
    }
    
    else if (pitchType == "Hard" && (ballType == "Pace" || ballType == "Bouncer")) {
        
        strikeWeight -= 5; defendWeight += 5;
    
    }
    
    else if (pitchType == "Soft") {
        
        loftWeight += 10; strikeWeight += 10; rotateWeight -= 10; defendWeight -= 5;
    
    }

    
    
    
    // ---------- BALLS LEFT + WICKETS ----------
    
    if (wicketsLeft <= 2) { // last wickets — play safe
        
        loftWeight -= 15; defendWeight += 10;
    
    }
    
    else if (ballsLeft <= 6) { // death overs
        
        loftWeight += 25; strikeWeight += 15; defendWeight -= 10;
    
    }
    
    else if (ballsLeft <= 12) {
        
        loftWeight += 10; strikeWeight += 5;
    
    }

    
    
    
    // ---------- CLAMP ----------
    
    int minAggression = 5;
    
    loftWeight   = max(loftWeight, minAggression);
    
    strikeWeight = max(strikeWeight, minAggression);
    
    rotateWeight = max(rotateWeight, minAggression);
    
    defendWeight = max(defendWeight, minAggression);

    
    
    
    // ---------- CHOOSE SHOT ----------
    
    int total = loftWeight + strikeWeight + rotateWeight + defendWeight;
    
    int roll = rand() % total;

    int shot;
    
    if (roll < loftWeight) shot = 0;         // LoftShot
    
    else if (roll < loftWeight + strikeWeight) shot = 1; // StrikeShot
    
    else if (roll < loftWeight + strikeWeight + rotateWeight) shot = 2; // Rotate
    
    else shot = 3;                           // Defend

    
    
    
    // ---------- STAMINA MANAGEMENT ----------
    
    if (shot == 3) stamina = min(100, stamina + 3);     // Defend recovers energy
    
    else if (shot == 2) stamina = min(100, stamina + 3); // Rotate slightly recovers

    return shot;
}













void playShot(int &stamina, int temparature, string bowlType, string pitch){
    
    cout << "Batting Choice:\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

    cout << "5. Exit The Game!\n\n";
    
    int batChoice = getIntInput("Enter Your Choice: ");

    clearScreen();

    if(batChoice == 5){

        cout << "Program Exitted Successfully!\n";

        resetMatch();
                
        exit(1);

    }

    if(batChoice < 1 || batChoice > 5){

        cout << "Invalid Input! That's Why Random Shot Choosen\n";

        batChoice = rand()%(4-1+1)+1;

    }

    scoreLogic(stamina,batChoice-1,1,temparature,bowlType,pitch);

    pressToContinue();

}





void playInnings(int &temporaryBall, int ball, string userTeam, int &stamina, int temparature, string pitch, bool targetFlag, int target){

    
    while(temporaryBall != ball+1){

        clearScreen();

        scoreCard(userScore, userWicket, temporaryBall, target, userTeam, ball);

        if (targetFlag) {
            float winProb = calculateWinProbability(userScore, userWicket, temporaryBall, target, ball);
            if (winProb >= 0)
                showWinProbabilityBar(winProb,userTeam);
            else
                cout << "🏆 Win Probability: Yet to Calculate (First Innings)\n\n";
        }

        if(userWicket == 10){

            cout << "Ops! You Have All Out, Your Batting Comes To End!\n\n";

            pressToContinue();

            break;

        }

        else if(targetFlag == true && userScore >= target){

            cout << "Your Batting Comes To End!\n\n";

            pressToContinue();

            break;

        }


            
        cout << "Stamina: " << stamina << " \n";

        int aiBowl = rand()%9;

        bowlSpeed = rand()%(145-80+1) + 80;

        cout << bowlVariation[aiBowl] << " Delivary Incoming With " << bowlSpeed << " km/h!" << " \n";

        playShot(stamina, temparature, bowlVariation[aiBowl], pitch);

        temporaryBall++;

    }

    clearScreen();

}




int bat(string userTeam, string aiTeam, int ball, int temparature, int rain, string pitch){

    int stamina = 100;
    
    clearScreen();

    int temporaryBall = 1;

    if(targetFlag == false){ //Batting First

        playInnings(temporaryBall, ball, userTeam, stamina, temparature, pitch, targetFlag, 0);
        
        target = userScore + 1;

        targetFlag = true;

        cout << userTeam << " Batting End! " << aiTeam << " Need " << target << " Runs From " << ball;

        cout << " Balls!\n";

        pressToContinue();

        return bowl(userTeam, aiTeam, ball, temparature, rain, pitch);

    }

    else{ // Batting Second
        
        if(rain >= 80 && rain < 90){

            clearScreen();

            cout << "Play Stopped Due To Rain\n";

            pressToContinue();

            cout << "Match Abandoned Due To Rain\n";

            cout << "No One Win\n";

            resetMatch();

            pressToContinue();

            return 4; // 4 Means Match Abandoned

        }

        else if(rain >= 60 && rain < 80){

            clearScreen();

            cout << "Play Stopped Due To Rain\n";

            pressToContinue();

            cout << "Luckily! Rain Stopped And Play Continue...\n";

            int ballReduced = ball - (rand() % 10 + 10);  // reduce 10–19 balls
            
            if (ballReduced < 6) ballReduced = 6;        // keep at least 1 over

            int targetReduced = target * (ballReduced / (float)ball); // scale target proportionally
            
            targetReduced = max(1, targetReduced);

            cout << "Ball Reduced To " << ballReduced << " & Revised Target Is " << targetReduced << " \n";

            pressToContinue();

            playInnings(temporaryBall, ballReduced, userTeam, stamina, temparature, pitch, targetFlag, targetReduced);
        
            if(userScore >= targetReduced){

                cout << userTeam << " Won By " << 10-userWicket << " Wickets!\n\n";

                cout << userWinComments[rand() % userWinComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 1; // 1 Means User Win;

            }

            else if(userScore == targetReduced - 1){

                cout << "Match Tied!\n\n";
                
                cout << tieComments[rand() % tieComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 2; // 2 Means Tied

            }

            else{

                cout << aiTeam << " Won By " << targetReduced-userScore << " Runs\n\n";

                cout << userLoseComments[rand() % userLoseComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 3; // 3 Means Tied

            }
        
        }

        else{

            playInnings(temporaryBall, ball, userTeam, stamina, temparature, pitch, targetFlag, target);
        
            if(userScore >= target){

                cout << userTeam << " Won By " << 10 - userWicket << " Wickets!\n\n";
                
                cout << userWinComments[rand() % userWinComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 1;

            }

            else if(userScore == target - 1){

                cout << "Match Tied!\n\n";
                
                cout << tieComments[rand() % tieComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 2;

            }

            else{

                cout << aiTeam << " Won By " << target-userScore-1 << " Runs\n\n";

                cout << userLoseComments[rand() % userLoseComments.size()] << "\n\n";

                resetMatch();

                pressToContinue();

                return 3;

            }

        }

    }

}