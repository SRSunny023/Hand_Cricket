#include "score.h"
#include "matchEngine.h"
#include "commentary.h"


#include <iostream>
#include <string>
using namespace std;



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



void scoreCard(int score, int wicket, int ball, int target, string team, int over){
    
    int width = 77;
    
    auto printLine = [&](const string &label, const string &value){
        
        int len = label.size() + value.size();
        
        int space = width - len;
        
        cout << "| " << label << value << string(space, ' ') << "|\n";
        
        cout << "|";
        
        cout << string(width, ' ') << "|\n";
    
    };
    
    cout << string(width+2, '-') << "\n";
    
    printLine("Team: ", team);
    
    printLine("Score: ", to_string(score));
    
    printLine("Wicket: ", to_string(wicket));
    
    printLine("Ball: ", to_string(ball));

    if(targetFlag){

        printLine("Target: ", to_string(target));

        int runsNeeded = target - score;
    
        int ballsLeft  = over - ball;
    
        string needLine = "" + team + " Need " + to_string(runsNeeded) + 
                      " Runs From " + to_string(ballsLeft) + " Balls To Win The Match";
    
        printLine("", needLine);
    }
    
    cout << string(width+2, '-') << "\n";

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

