#include "tournamentEngine.h"
#include "../../Match/matchEngine.h"
#include "../../Authentication/loginSystem.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;









/****************************************************************************************************/
/* Function Name: findTeam                                                                          */
/*                                                                                                  */
/* Inputs       : struct, const string                                                              */
/*                                                                                                  */
/* Returns      : struct*                                                                           */
/*                                                                                                  */
/* Note         : findTeam ensures we always update the right stage’s team object.                  */
/*              : The order avoids updating outdated team copies.                                   */
/*              : Returning a pointer lets us modify the real stats directly.                       */
/****************************************************************************************************/

Team* findTeam(Tournament &T, const string &name) {
    
    for (auto &t : T.super4) if (t.name == name) return &t;
    
    for (auto &t : T.groupA) if (t.name == name) return &t;
    
    for (auto &t : T.groupB) if (t.name == name) return &t;
    
    for (auto &t : T.semifinalists) if (t.name == name) return &t;
    
    for (auto &t : T.finalists) if (t.name == name) return &t;
    
    return nullptr;
}















/****************************************************************************************************/
/* Function Name: cmpTeam                                                                           */
/*                                                                                                  */
/* Inputs       : const struct, const struct                                                        */
/*                                                                                                  */
/* Returns      : bool                                                                              */
/*                                                                                                  */
/* Note         : cmpTeam is the ranking rule → More points = higher rank                           */
/*              : If same points → more wins = higher rank.                                         */
/****************************************************************************************************/

bool cmpTeam(const Team &a, const Team &b) {
    
    if (a.points != b.points) return a.points > b.points;
    
    return a.won > b.won;

}
















/****************************************************************************************************/
/* Function Name: proceedNextStage                                                                  */
/*                                                                                                  */
/* Inputs       : struct                                                                            */
/*                                                                                                  */
/* Returns      : none                                                                              */
/*                                                                                                  */
/* Note         : This proceedNextStage() function is the engine that moves your tournament         */
/****************************************************************************************************/

void proceedNextStage(Tournament &T) {
    
    if (T.stage == "Group") {
        
        sort(T.groupA.begin(), T.groupA.end(), cmpTeam);
        sort(T.groupB.begin(), T.groupB.end(), cmpTeam);

        if (T.name == "Asia Cup") {

            vector<Team> top4 = {T.groupA[0], T.groupA[1], T.groupB[0], T.groupB[1]};


            for (auto &t : top4) {
                t.played = t.points = t.won = t.lost = 0;
            }


            T.groupA.clear();
            T.groupB.clear();
            T.super4 = top4;


            T.fixtures.clear();
            
            for (size_t i=0; i<T.super4.size();i++) {
                
                for (size_t j=i+1;j<T.super4.size();j++) {
                    
                    T.fixtures.push_back({T.super4[i].name, T.super4[j].name});
                
                }
            
            }

            T.stage = "Super4";

            T.currentMatch = 0;

            cout << ">>> Proceeding to Super 4!\n";
        
        }
        
        else if (T.name == "Champions Trophy") {
            
            Team A1=T.groupA[0], A2=T.groupA[1];
            
            Team B1=T.groupB[0], B2=T.groupB[1];
            
            T.semifinalists = {A1,A2,B1,B2};
            
            T.fixtures.clear();
            
            T.fixtures.push_back({A1.name, B2.name});
            
            T.fixtures.push_back({B1.name, A2.name});
            
            T.stage = "Semi";
            
            T.currentMatch = 0;
            
            cout << ">>> Proceeding to Semi Finals!\n";
        
        }
    
    }

    else if (T.stage == "Super4") {
        
        sort(T.super4.begin(), T.super4.end(), cmpTeam);
        
        T.finalists = {T.super4[0], T.super4[1]};
        
        T.fixtures.clear();
        
        T.fixtures.push_back({T.finalists[0].name, T.finalists[1].name});
        
        T.stage = "Final";
        
        T.currentMatch = 0;
        
        cout << ">>> Proceeding to Final!\n";
    
    }
    
    else if (T.stage == "Semi") {
        
        T.finalists.clear();
        
        for (auto &t : T.semifinalists) if (t.won > 0) T.finalists.push_back(t);
        
        if (T.finalists.size() == 2) {
            
            T.fixtures.clear();
            
            T.fixtures.push_back({T.finalists[0].name, T.finalists[1].name});
            
            T.stage = "Final";
            
            T.currentMatch = 0;
            
            cout << ">>> Proceeding to Final!\n";
        
        }
    
    }
    
    else if (T.stage == "Final") {
        
        cout << ">>> Tournament Winner: " 
             << (T.finalists[0].points > T.finalists[1].points ? 
                 T.finalists[0].name : T.finalists[1].name) << "\n";
        
                 T.finished = true;
    }

}













/****************************************************************************************************/
/* Function Name: playNextFixture                                                                   */
/*                                                                                                  */
/* Inputs       : struct                                                                            */
/*                                                                                                  */
/* Returns      : none                                                                              */
/*                                                                                                  */
/* Note         : This function playNextFixture() is the match engine                               */
/*              : Picks next match → plays it → updates stats → prints results.                     */
/*              : If stage ends, moves to next stage (Super4, Semi, Final).                         */
/*              : Declares winner at the end.                                                       */
/****************************************************************************************************/

void playNextFixture(Tournament &T, string userTeam) {
    
    int result = 0;
    
    if (T.currentMatch >= T.fixtures.size()) {
        
        proceedNextStage(T);
        
        return;
    
    }

    auto match = T.fixtures[T.currentMatch];
    
    Team* t1 = findTeam(T, match.first);
    
    Team* t2 = findTeam(T, match.second);

    if(t1->name == userTeam || t2->name == userTeam){

        resetProgressTournamentMatch();
        
        int toss;

        int tossChoice;
        
        cout << "\nMatch " << (T.currentMatch+1) << ": " 
             << t1->name << " vs " << t2->name << "\n";

        pressToContinue();
        
        clearScreen();
        
        do{

            clearScreen();

            cout << "-----------------TOSS TIME-----------------\n\n1. Head\n\n2. Tail\n\n";

            toss = getIntInput("Enter Your Choice: ");

            if(toss < 1 || toss > 2){

                clearScreen();

                cout << "Invalid Input! Choose Between (1 - 2)!\n";

                pressToContinue();

            }

        }   while(toss < 1 || toss > 2);

        clearScreen();

        int aiToss = rand()%2;

        if((toss-1) == aiToss){

            do{

                clearScreen();
                
                cout << "You Won The Toss!\n\n1. Bat\n\n2. Bowl\n\n";

                tossChoice = getIntInput("Enter Your Choice: ");

                if(tossChoice < 1 || tossChoice > 2){

                    clearScreen();
                    
                    cout << "Wrong Input! Choose Between (1 - 2)!\n";

                    pressToContinue();

                }

            }   while(tossChoice < 1 || tossChoice > 2);

            clearScreen();

            if(tossChoice == 1){

                cout << "You Won The Toss And Elected To Bat First!\n";

                pressToContinue();
                
                if(t1->name == userTeam){

                    result = batTournament(t1->name, t2->name, 30);

                }

                else if(t2->name == userTeam){

                    result = batTournament(t2->name, t1->name, 30);

                }

            }

            else{

                cout << "You Won The Toss And Elected To Bowl First!\n";

                pressToContinue();
                
                if(t1->name == userTeam){

                    result = bowlTournament(t1->name, t2->name, 30);

                }

                else if(t2->name == userTeam){

                    result = bowlTournament(t2->name, t1->name, 30);

                }

            }

        }

        else{
            
            int aiToss = rand()%2;

            if(aiToss == 0){

                cout << "You Lost The Toss And You Have To Bowl First Now!\n";

                pressToContinue();
                
                if(t1->name == userTeam){

                    result = bowlTournament(t1->name, t2->name, 30);

                }

                else if(t2->name == userTeam){

                    result = bowlTournament(t2->name, t1->name, 30);

                }

            }

            else{

                cout << "You Lost The Toss And You Have To Bat First Now!\n";

                pressToContinue();
                
                if(t1->name == userTeam){

                    result = batTournament(t1->name, t2->name, 30);

                }

                else if(t2->name == userTeam){

                    result = batTournament(t2->name, t1->name, 30);

                }

            }

        }

        clearScreen();

        cout << "\nMatch " << (T.currentMatch+1) << ": " 
             << t1->name << " vs " << t2->name << "\n";

        if(result == 1){

            if(t1->name == userTeam){

                cout << "Winner: " << t1->name << " \n";

                t1->points += 2; t1->won++;
        
                t2->lost++;
        
                if (T.stage == "Semi") T.finalists.push_back(*t1);

            }

            else if(t2->name == userTeam){

                cout << "Winner: " << t2->name << " \n";

                t2->points += 2; t2->won++;
        
                t1->lost++;
        
                if (T.stage == "Semi") T.finalists.push_back(*t2);

            }

        }

        else if(result == 2){

            if(t1->name == userTeam){

                cout << "TIED: \n";

                t1->points += 1;
        
                t2->points += 1;
        
                if (T.stage == "Semi") T.finalists.push_back(*t1);

            }

            else if(t2->name == userTeam){

                cout << "TIED: \n";

                t2->points += 1;
        
                t1->points += 1;
        
                if (T.stage == "Semi") T.finalists.push_back(*t2);

            }

        }

        else if(result == 3){

            if(t1->name == userTeam){

                cout << "Winner: " << t2->name << " \n";
        
                t2->points += 2; t2->won++;
        
                t1->lost++;
        
                if (T.stage == "Semi") T.finalists.push_back(*t2);

            }

            else if(t2->name == userTeam){

                cout << "Winner: " << t1->name << " \n";
        
                t1->points += 2; t1->won++;
        
                t2->lost++;
        
                if (T.stage == "Semi") T.finalists.push_back(*t1);

            }

        }

    }

    else{

        int s1 = rand() % 200;
        int s2 = rand() % 200;

        cout << "\nMatch " << (T.currentMatch+1) << ": " 
             << t1->name << " vs " << t2->name << "\n";

        if (s1 > s2) {
        
            cout << "Winner: " << t1->name << " (" << s1 << " vs " << s2 << ")\n";
        
            t1->points += 2; t1->won++;
        
            t2->lost++;
        
            if (T.stage == "Semi") T.finalists.push_back(*t1);
    
        }
    
        else {
        
            cout << "Winner: " << t2->name << " (" << s2 << " vs " << s1 << ")\n";
        
            t2->points += 2; t2->won++;
        
            t1->lost++;
        
            if (T.stage == "Semi") T.finalists.push_back(*t2);
    
        }

    }


    t1->played++; t2->played++;
    
    T.currentMatch++;

    if (T.stage == "Semi" && T.currentMatch >= T.fixtures.size()) {
        
        if (T.finalists.size() == 2) {
            
            T.fixtures.clear();
            
            T.fixtures.push_back({T.finalists[0].name, T.finalists[1].name});
            
            T.stage = "Final";
            
            T.currentMatch = 0;
            
            cout << ">>> Proceeding to Final!\n";
        
        }
    
    }

    if (T.stage == "Final" && T.currentMatch >= T.fixtures.size()) {
        
        cout << ">>> Tournament Winner: " 
             << (T.finalists[0].points > T.finalists[1].points ? 
                 T.finalists[0].name : T.finalists[1].name) << "\n";
        
        T.finished = true;
    
    }

}















/****************************************************************************************************/
/* Function Name: showFixtures                                                                      */
/*                                                                                                  */
/* Inputs       : struct                                                                            */
/*                                                                                                  */
/* Returns      : none                                                                              */
/*                                                                                                  */
/* Note         : This function show the fixture                                                    */
/****************************************************************************************************/

void showFixtures(Tournament &T) {
    
    cout << "\nFixtures for " << T.name << ":\n";
    
    for (size_t i=0; i<T.fixtures.size(); i++) {
        
        cout << (i+1) << ". " << T.fixtures[i].first 
             << " vs " << T.fixtures[i].second;
        
        if (i < T.currentMatch) cout << " [Played]";
        
        cout << "\n";
    
    }

}













/****************************************************************************************************/
/* Function Name: showPointsTable                                                                   */
/*                                                                                                  */
/* Inputs       : struct                                                                            */
/*                                                                                                  */
/* Returns      : none                                                                              */
/*                                                                                                  */
/* Note         : This function show the Points Table                                               */
/****************************************************************************************************/

void showPointsTable(Tournament &T) {
    
    if (T.stage == "Super4") {
        
        vector<Team> super4copy = T.super4;
        
        sort(super4copy.begin(), super4copy.end(), cmpTeam);
        
        cout << "\nPoints Table (Super 4):\n";
        
        cout << left << setw(20) << "Team" 
            << setw(8) << "Played" 
            << setw(8) << "Won" 
            << setw(8) << "Lost" 
            << setw(8) << "Points" << "\n";
        
        for (auto &t : super4copy) {
            
            cout << left << setw(20) << t.name
                << setw(8) << t.played
                << setw(8) << t.won
                << setw(8) << t.lost
                << setw(8) << t.points << "\n";
        
        }
        
        return;
    
    }

    if (T.stage == "Final") {
        
        cout << "\nFinalists:\n";
        
        for (auto &t : T.finalists) {
            
            cout << t.name << " (Points: " << t.points << ", Won: " << t.won << ")\n";
        
        }
        
        return;
    
    }

    vector<Team> groupAcopy = T.groupA;
    vector<Team> groupBcopy = T.groupB; 

    sort(groupAcopy.begin(), groupAcopy.end(), cmpTeam);
    sort(groupBcopy.begin(), groupBcopy.end(), cmpTeam);
    
    cout << "\nPoints Table (Group A):\n";
    
    cout << left << setw(20) << "Team" 
         << setw(8) << "Played" 
         << setw(8) << "Won" 
         << setw(8) << "Lost" 
         << setw(8) << "Points" << "\n";
    
    for (auto &t : groupAcopy) {
        
        cout << left << setw(20) << t.name
            << setw(8) << t.played
            << setw(8) << t.won
            << setw(8) << t.lost
            << setw(8) << t.points << "\n";
    
    }

    cout << "\nPoints Table (Group B):\n";
    
    cout << left << setw(20) << "Team" 
         << setw(8) << "Played" 
         << setw(8) << "Won" 
         << setw(8) << "Lost" 
         << setw(8) << "Points" << "\n";
    
    for (auto &t : groupBcopy) {
        
        cout << left << setw(20) << t.name
            << setw(8) << t.played
            << setw(8) << t.won
            << setw(8) << t.lost
            << setw(8) << t.points << "\n";
    
    }

}














/****************************************************************************************************/
/* Function Name: resetTournament                                                                   */
/*                                                                                                  */
/* Inputs       : const string                                                                      */
/*                                                                                                  */
/* Returns      : struct                                                                            */
/*                                                                                                  */
/* Note         : This function reset the tournament progress                                       */
/****************************************************************************************************/
/*
Tournament resetTournament(const string &name) {
    
    if (name == "Asia Cup") return setupAsiaCup();
    
    return setupChampionsTrophy();

}
*/
