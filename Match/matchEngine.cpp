#include <iostream>
#include "matchEngine.h"
#include "loginSystem.h"
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

string commentaryForSix[] = {

    "Six!!!!!!! Massive Shot.",

    "Unbeleivable Hit!",

    "Hit And Goes To The Over Boundary",

    "And Its Goes For Maximum",

    "Superb! Hit Fans Cheering Him For This Hit",

    "What A Shot! This Shot Will Be Written In The History",

    "Maximum Out Of The Boundary!",

    "Goes For Six, Fielder Cant Catch It",

    "Should Be Taken Oh Its Gone For Boundary",

};

string commentaryForFour[] = {

    "Hits And Goes To The Boundary",

    "Wonderful Shot Miss The Overboundary For A Little But Goes For Four",

    "Super Classical Timing",

    "Wonderful Bat And Bowl Connection",

    "The Unbelievable Power Of Shot",

    "These Shots Makes Him Great",

    "Super Shot Gone For Four",

    "Should Be Taken Oh Its Dropped And Goes For The Boundary",

    "Good Gap Finding Goes For Four",

};

string commentaryForDot[] = {

    "Dot Ball",

    "Again Dot",

    "Nice Defending",

    "Tried To Take Single But Cant",

    "Good Defending",

    "Tying To Rotate Strike",

    "Increasing Energy Nice",

    "Dot Ball Looks Like A Class For Him",

    "How More Dot Balls?",

};

string commentaryForWicket[] = {

    "Bowled!!!!!!!!!!",

    "Super Bowled Middle Stump Goes To The Air",

    "Should Be Taken Oh Its Taken, Super Fielding",

    "Oh Taken! Fielding Like Eagle",

    "Missed Oh No Taken Wow",

    "Nice Catch",

    "Oh Catched But Almost Dropped",

    "Super Dive And Taken The Catch",

    "Less Effort Great Outcome, Super Catch",

};

string commentaryForOneTwo[] = {

    "Good Strike Rotate",

    "Nice Gap Finding",

    "There is a Player On The Boundary But Some Runs Come",

    "Slow Batting",

    "Good Hit",

    "Try To Find Gap For Four But Missed",

    "Nice Running Between The Wicket",

    "Good Brain",

    "Nice Shot",

};





void scoreCard(int score, int wicket, int ball, int target, string team){
    int width = 77; // inner width between |...|
    
    auto printLine = [&](const string &label, const string &value){
        int len = label.size() + value.size();
        int space = width - len;
        cout << "| " << label << value << string(space, ' ') << "|\n";
        cout << "|";
        cout << string(width, ' ') << "|\n";
    };
    
    cout << string(width+2, '-') << "\n"; // top border
    printLine("Team: ", team);
    printLine("Score: ", to_string(score));
    printLine("Wicket: ", to_string(wicket));
    printLine("Ball: ", to_string(ball));
    if(targetFlag) printLine("Target: ", to_string(target));
    cout << string(width+2, '-') << "\n"; // bottom border
}






void scoreLogic(int &stamina, int batChoice, int who){

    if(stamina >= 95){

        if(batVariation[batChoice] == "LoftShot"){

            if(who == 1){

                userScore += 6;

            }

            else{

                aiScore += 6;

            }

            cout << "Commentary: " << commentaryForSix[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 6\n";

            stamina -= 10;

        }

        else if(batVariation[batChoice] == "StrikeShot"){

            if(who == 1){

                userScore += 4;

            }

            else{

                aiScore += 4;

            }

            cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 4\n";

            stamina -= 7;

        }

        else if(batVariation[batChoice] == "StrikeRotate"){

            if(who == 1){

                userScore += 3;

            }

            else{

                aiScore += 3;

            }

            cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 3\n";

            stamina -= 6;

        }

        else if(batVariation[batChoice] == "Defend"){

            if(who == 1){

                userScore += 0;

            }

            else{

                aiScore += 0;

            }

            cout << "Commentary: " << commentaryForDot[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 0\n";

            if(stamina < 100){

                stamina += 3;

            }

            else if(stamina > 100){

                stamina = 100;

            }

        }

    }

    else if((stamina >= 80 && stamina < 95) && (bowlSpeed >= 130 && bowlSpeed < 146)){

                
        if(batVariation[batChoice] == "LoftShot"){

            if(who == 1){

                userScore += 6;

            }

            else{

                aiScore += 6;

            }

            cout << "Commentary: " << commentaryForSix[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 6\n";

            stamina -= 10;

        }

        else if(batVariation[batChoice] == "StrikeShot"){

            if(who == 1){

                userScore += 4;

            }

            else{

                aiScore += 4;

            }

            cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 4\n";

            stamina -= 7;

        }

        else if(batVariation[batChoice] == "StrikeRotate"){

            if(who == 1){

                userScore += 3;

            }

            else{

                aiScore += 3;

            }

            cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 3\n";

            stamina -= 6;

        }

        else if(batVariation[batChoice] == "Defend"){

            if(who == 1){

                userScore += 0;

            }

            else{

                aiScore += 0;

            }

            cout << "Commentary: " << commentaryForDot[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 0\n";

            if(stamina < 100){

                stamina += 3;

            }

            else if(stamina > 100){

                stamina = 100;

            }

        }

    }

    else if((stamina >= 80 && stamina < 95) && bowlSpeed < 130){

        if(batVariation[batChoice] == "LoftShot"){

            int tempScore = rand()%(6-4+1)+4;

            int tempWicket = rand()%3;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else if(tempScore == 6){

                if(who == 1){

                    userScore += 6;

                }

                else{

                    aiScore += 6;

                }

                cout << "Commentary: " << commentaryForSix[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 6\n";

                stamina -= 10;

            }

            else if(tempScore == 4 || tempScore == 5){

                if(who == 1){

                    userScore += 4;

                }

                else{

                    aiScore += 4;

                }

                cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 4\n";

                stamina -= 7;

            }

        }

        else if(batVariation[batChoice] == "StrikeShot"){

            int tempWicket = rand()%4;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else{

                if(who == 1){

                    userScore += 4;

                }

                else{

                    aiScore += 4;

                }

                cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 4\n";

                stamina -= 7;

            }

        }

        else if(batVariation[batChoice] == "StrikeRotate"){

            int tempWicket = rand()%5;

            int tempRun = rand()%(3-1+1)+1;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else if(tempRun == 3){

                if(who == 1){

                    userScore += 3;

                }

                else{

                    aiScore += 3;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 3\n";

                stamina -= 6;

            }

            else if(tempRun == 2){

                if(who == 1){

                    userScore += 2;

                }

                else{

                    aiScore += 2;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 2\n";

                stamina -= 5;

            }

            else if(tempRun == 1){

                if(who == 1){

                    userScore += 1;

                }

                else{

                    aiScore += 1;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 1\n";

                stamina -= 4;

            }

        }

        else if(batVariation[batChoice] == "Defend"){

            if(who == 1){

                userScore += 0;

            }

            else{

                aiScore += 0;

            }

            cout << "Commentary: " << commentaryForDot[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 0\n";

            if(stamina < 100){

                stamina += 3;

            }

            else if(stamina > 100){

                stamina = 100;

            }

        }

    }

    else if((stamina >= 50 && stamina < 80)){

        if(batVariation[batChoice] == "LoftShot"){

            int tempScore = rand()%(6-4+1)+4;

            int tempWicket = rand()%2;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else if(tempScore == 6){

                if(who == 1){

                    userScore += 6;

                }

                else{

                    aiScore += 6;

                }

                cout << "Commentary: " << commentaryForSix[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 6\n";

                stamina -= 10;

            }

            else if(tempScore == 4 || tempScore == 5){

                if(who == 1){

                    userScore += 4;

                }

                else{

                    aiScore += 4;

                }

                cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 4\n";

                stamina -= 7;

            }

        }

        else if(batVariation[batChoice] == "StrikeShot"){

            int tempWicket = rand()%3;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else{

                if(who == 1){

                    userScore += 4;

                }

                else{

                    aiScore += 4;

                }

                cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 4\n";

                stamina -= 7;

            }

        }

        else if(batVariation[batChoice] == "StrikeRotate"){

            int tempWicket = rand()%4;

            int tempRun = rand()%(3-1+1)+1;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else if(tempRun == 3){

                if(who == 1){

                    userScore += 3;

                }

                else{

                    aiScore += 3;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 3\n";

                stamina -= 6;

            }

            else if(tempRun == 2){

                if(who == 1){

                    userScore += 2;

                }

                else{

                    aiScore += 2;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 2\n";

                stamina -= 5;

            }

            else if(tempRun == 1){

                if(who == 1){

                    userScore += 1;

                }

                else{

                    aiScore += 1;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 1\n";

                stamina -= 4;

            }

        }

        else if(batVariation[batChoice] == "Defend"){

            if(who == 1){

                userScore += 0;

            }

            else{

                aiScore += 0;

            }

            cout << "Commentary: " << commentaryForDot[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 0\n";

            if(stamina < 100){

                stamina += 3;

            }

            else if(stamina > 100){

                stamina = 100;

            }

        }

    }

    else if(stamina < 50){

        if(batVariation[batChoice] == "LoftShot"){

            cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: Wicket\n";

            if(who == 1){

                userWicket++;

            }

            else{

                aiWicket++;

            }

            stamina -= 5;

        }

        else if(batVariation[batChoice] == "StrikeShot"){

            int tempWicket = rand()%2;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else{

                if(who == 1){

                    userScore += 4;

                }

                else{

                    aiScore += 4;

                }

                cout << "Commentary: " << commentaryForFour[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 4\n";

                stamina -= 7;

            }

        }

        else if(batVariation[batChoice] == "StrikeRotate"){

            int tempWicket = rand()%3;

            int tempRun = rand()%(3-1+1)+1;

            if(tempWicket == 1){

                cout << "Commentary: " << commentaryForWicket[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: Wicket\n";

                if(who == 1){

                    userWicket++;

                }

                else{

                    aiWicket++;

                }

                stamina -= 5;

            }

            else if(tempRun == 3){

                if(who == 1){

                    userScore += 3;

                }

                else{

                    aiScore += 3;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 3\n";

                stamina -= 6;

            }

            else if(tempRun == 2){

                if(who == 1){

                    userScore += 2;

                }

                else{

                    aiScore += 2;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 2\n";

                stamina -= 5;

            }

            else if(tempRun == 1){

                if(who == 1){

                    userScore += 1;

                }

                else{

                    aiScore += 1;

                }

                cout << "Commentary: " << commentaryForOneTwo[rand()%9] << " \n";
                cout << "Shot Played: " << batVariation[batChoice] << " \n";
                cout << "Shot OutCome: 1\n";

                stamina -= 4;

            }

        }

        else if(batVariation[batChoice] == "Defend"){

            if(who == 1){

                userScore += 0;

            }

            else{

                aiScore += 0;

            }

            cout << "Commentary: " << commentaryForDot[rand()%9] << " \n";
            cout << "Shot Played: " << batVariation[batChoice] << " \n";
            cout << "Shot OutCome: 0\n";

            if(stamina < 100){

                stamina += 5;

            }

            else if(stamina > 100){

                stamina = 100;

            }

        }

    }

}







int batTournament(string, string, int);
int bowlTournament(string, string, int);

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

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam);

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

            cout << "Batting Choice:\n\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n\n";

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

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam);

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

            cout << "Batting Choice:\n\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n\n";

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

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam);

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

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam);

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
















void bat(string, string, int);
void bowl(string, string, int);










void bat(string userTeam, string aiTeam, int ball){

    int batChoice;

    int stamina = 100;
    
    clearScreen();

    int temporaryBall = 1;

    if(targetFlag == false){ //Batting First

        while(temporaryBall != ball+1){

            clearScreen();

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam);

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

            cout << "Batting Choice:\n\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n\n";

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

            scoreCard(userScore, userWicket, temporaryBall, target, userTeam);

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

            cout << "Batting Choice:\n\n\n1. LoftShot\n2. StrikeShot\n3. RotateShot\n4. Defend\n";

            cout << "5. Exit The Game!\n\n\n";

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

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam);

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

            scoreCard(aiScore, aiWicket, temporaryBall, target, aiTeam);

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