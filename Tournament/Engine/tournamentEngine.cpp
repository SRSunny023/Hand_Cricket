#include "tournamentEngine.h"
#include "../../Match/matchEngine.h"
#include "../../Authentication/loginSystem.h"
#include "../../Utility/utility.h"
#include "../Asia_Cup_2025/asiaCup2025.h"





#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;








// ANSI Color Codes
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define WHITE   "\033[1;37m"









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

    for (auto &t : T.qualifierA) if (t.name == name) return &t;
    
    for (auto &t : T.qualifierB) if (t.name == name) return &t;
    
    for (auto &t : T.platesemifinalists) if (t.name == name) return &t;
    
    for (auto &t : T.platethirdplace) if (t.name == name) return &t;

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

    if (T.name == "Asia Cup"){

        if (T.stage == "QualifierA") {
            
            sort(T.qualifierA.begin(), T.qualifierA.end(), cmpTeam);

            Team A1 = T.qualifierA[0], A2 = T.qualifierA[1];

            T.platesemifinalists = {A1, A2};

            T.fixtures.clear();

            for (size_t i = 0; i < T.qualifierB.size(); i++)
                for (size_t j = i + 1; j < T.qualifierB.size(); j++)
                    T.fixtures.push_back({T.qualifierB[i].name, T.qualifierB[j].name});
        
            T.currentMatch = 0;
        
            T.stage = "QualifierB";

            cout << ">>> Proceeding to Qualifier Group Stage B!\n";
    
        }

        else if (T.stage == "QualifierB") {
            
            sort(T.qualifierB.begin(), T.qualifierB.end(), cmpTeam);

            Team A1 = T.platesemifinalists[0];
            Team A2 = T.platesemifinalists[1];
        
            Team B1 = T.qualifierB[0], B2 = T.qualifierB[1];

        
            T.platesemifinalists = {A1, A2, B1, B2};
            
            T.fixtures = {
                
                {A1.name, B2.name},
                
                {B1.name, A2.name}
            
            };
        
            T.currentMatch = 0;

            T.qualifierA.clear();

            T.qualifierB.clear();

            for (auto &t : T.platesemifinalists) {
                t.played = 0;
                t.won = 0;
                t.lost = 0;
                t.points = 0;
            }
        
            T.stage = "PlateSemi";

            cout << ">>> Proceeding to Plate Semi Finals!\n";
    
        }

        else if (T.stage == "PlateSemi") {
        
        
            vector<Team> winners, losers;
        
            for (auto &t : T.platesemifinalists) {
            
                if (t.won > 0) winners.push_back(t);
            
                else losers.push_back(t);
        
            }

        
            if (winners.size() < 2 || losers.size() < 2) {
                cout << ">>> Waiting for all Plate Semi matches to finish...\n";
                return;
            }

        
            for (auto &w : winners)
        
                T.groupA.push_back(w);

            
            T.platethirdplace = {losers[0], losers[1]};
            
            T.fixtures.clear();
        
            T.fixtures.push_back({losers[0].name, losers[1].name});
        
            T.currentMatch = 0;
        
            T.stage = "PlateThirdPlace";
        
            cout << ">>> Proceeding to Plate Third Place!\n";
    
        }

    
        else if (T.stage == "PlateThirdPlace") {
        
            for (auto &t : T.platethirdplace)
            
                if (t.won > 0)
                    T.groupB.push_back(t);

        
            T.groupA.push_back({"India"});
        
            T.groupA.push_back({"Pakistan"});

        
            T.groupB.push_back({"Sri Lanka"});
        
            T.groupB.push_back({"Afghanistan"});
        
            T.groupB.push_back({"Bangladesh"});

        
            for (auto &t : T.groupA) {
                t.played = t.won = t.lost = t.points = 0;
            }
            for (auto &t : T.groupB) {
                t.played = t.won = t.lost = t.points = 0;
            }

        
            T.fixtures.clear();

            for (size_t i = 0; i < T.groupA.size(); i++)
                for (size_t j = i + 1; j < T.groupA.size(); j++)
                    T.fixtures.push_back({T.groupA[i].name, T.groupA[j].name});

            for (size_t i = 0; i < T.groupB.size(); i++)
                for (size_t j = i + 1; j < T.groupB.size(); j++)
                    T.fixtures.push_back({T.groupB[i].name, T.groupB[j].name});

            T.stage = "Group";
        
            T.currentMatch = 0;

            cout << ">>> Proceeding to Main Round (Group Stage)!\n";
    
        }

    
        else if (T.stage == "Group") {
            
            sort(T.groupA.begin(), T.groupA.end(), cmpTeam);
        
            sort(T.groupB.begin(), T.groupB.end(), cmpTeam);

        
            vector<Team> top4 = {T.groupA[0], T.groupA[1], T.groupB[0], T.groupB[1]};
        
            for (auto &t : top4)
                t.played = t.points = t.won = t.lost = 0;

            T.groupA.clear();
        
            T.groupB.clear();
        
            T.super4 = top4;

            T.fixtures.clear();
            
            for (size_t i = 0; i < T.super4.size(); i++)
                for (size_t j = i + 1; j < T.super4.size(); j++)
                    T.fixtures.push_back({T.super4[i].name, T.super4[j].name});

            T.stage = "Super4";
        
            T.currentMatch = 0;
        
            cout << ">>> Proceeding to Super 4!\n";
    
        }

    
        else if (T.stage == "Super4") {
            
            sort(T.super4.begin(), T.super4.end(), cmpTeam);
        
            T.finalists = {T.super4[0], T.super4[1]};
        
            T.fixtures = { {T.finalists[0].name, T.finalists[1].name} };
        
            T.stage = "Final";
        
            T.currentMatch = 0;
        
            cout << ">>> Proceeding to Final!\n";
    
        }

    
        else if (T.stage == "Final") {
        
            cout << ">>> Tournament Winner: "
                << (T.finalists[0].points > T.finalists[1].points
                        ? T.finalists[0].name
                        : T.finalists[1].name)
                << "\n";
        
            T.finished = true;
    
        }

    }

    else if (T.name == "Champions Trophy"){

        if (T.stage == "Group"){

            sort(T.groupA.begin(), T.groupA.end(), cmpTeam);
        
            sort(T.groupB.begin(), T.groupB.end(), cmpTeam);
            
            Team A1=T.groupA[0], A2=T.groupA[1];
            
            Team B1=T.groupB[0], B2=T.groupB[1];
            
            T.semifinalists = {A1,A2,B1,B2};
            
            T.fixtures.clear();
            
            T.fixtures.push_back({A1.name, B2.name});
            
            T.fixtures.push_back({B1.name, A2.name});
            
            T.stage = "SemiFinal";
            
            T.currentMatch = 0;
            
            cout << ">>> Proceeding to Semi Finals!\n";

        }

        else if (T.stage == "SemiFinal"){
        
            vector<Team> winners;
            for (auto &t : T.semifinalists) {
                if (t.won > 0) winners.push_back(t);
            }

            if (winners.size() < 2) {
                cout << ">>> Waiting for all Semi Final matches to finish...\n";
                return;
            }

            T.finalists = {winners[0], winners[1]};
            for (auto &f : T.finalists) {
                f.played = 0;
                f.won = 0;
                f.lost = 0;
                f.points = 0;
            }

            T.fixtures = {{T.finalists[0].name, T.finalists[1].name}};
            T.stage = "Final";
            T.currentMatch = 0;

            cout << ">>> Proceeding to Final!\n";

        }

        else if (T.stage == "Final"){

            cout << ">>> Tournament Winner: "
                << (T.finalists[0].points > T.finalists[1].points
                        ? T.finalists[0].name
                        : T.finalists[1].name)
                << "\n";
        
            T.finished = true;

        }

    }

    else if (T.name == "World Cup"){

        if (T.stage == "QualifierA") {
            
            sort(T.qualifierA.begin(), T.qualifierA.end(), cmpTeam);

            Team A1 = T.qualifierA[0], A2 = T.qualifierA[1], A3 = T.qualifierA[2];

            T.fixtures.clear();

            for (size_t i = 0; i < T.qualifierB.size(); i++)
                for (size_t j = i + 1; j < T.qualifierB.size(); j++)
                    T.fixtures.push_back({T.qualifierB[i].name, T.qualifierB[j].name});
        
            T.currentMatch = 0;
        
            T.stage = "QualifierB";

            cout << ">>> Proceeding to Qualifier Group Stage B!\n";
    
        }

        else if (T.stage == "QualifierB") {
            
            sort(T.qualifierB.begin(), T.qualifierB.end(), cmpTeam);

            Team A1 = T.qualifierA[0], A2 = T.qualifierA[1], A3 = T.qualifierA[2];
        
            Team B1 = T.qualifierB[0], B2 = T.qualifierB[1], B3 = T.qualifierB[2];

        
            vector<Team> top6 = {T.qualifierA[0], T.qualifierA[1], T.qualifierA[2], T.qualifierB[0], T.qualifierB[1], T.qualifierB[2]};
        
            T.qualifierA.clear();

            T.qualifierB.clear();
            
            T.super6 = top6;

            T.fixtures.clear();

            for (size_t i = 0; i < T.super6.size(); i++)
                for (size_t j = i + 1; j < T.super6.size(); j++)
                    T.fixtures.push_back({T.super6[i].name, T.super6[j].name});
        
            T.currentMatch = 0;

            for (auto &t : T.super6) {
                t.played = 0;
                t.won = 0;
                t.lost = 0;
                t.points = 0;
            }
        
            T.stage = "Super6";

            cout << ">>> Proceeding to World Cup Super 6!\n";
    
        }
    
        else if (T.stage == "Super6") {
            
            sort(T.super6.begin(), T.super6.end(), cmpTeam);
        
            T.semifinalists = {T.super6[0], T.super6[1],T.super6[2], T.super6[3]};
        
            T.fixtures = {
            
                {T.semifinalists[0].name, T.semifinalists[3].name},
                {T.semifinalists[1].name, T.semifinalists[2].name},
            
            };
        
            T.stage = "SemiFinal";

            for (auto &f : T.semifinalists) {
                f.played = 0;
                f.won = 0;
                f.lost = 0;
                f.points = 0;
            }
        
            T.currentMatch = 0;
        
            cout << ">>> Proceeding to Semi Final!\n";
    
        }

        else if (T.stage == "SemiFinal"){
        
            vector<Team> winners;
            
            for (auto &t : T.semifinalists) {
                if (t.won > 0) winners.push_back(t);
            }

            if (winners.size() < 2) {
                cout << ">>> Waiting for all Semi Final matches to finish...\n";
                return;
            }

            T.finalists = {winners[0], winners[1]};
            
            for (auto &f : T.finalists) {
                f.played = 0;
                f.won = 0;
                f.lost = 0;
                f.points = 0;
            }

            T.fixtures = {{T.finalists[0].name, T.finalists[1].name}};
            T.stage = "Final";
            T.currentMatch = 0;

            cout << ">>> Proceeding to Final!\n";

        }

        else if (T.stage == "Final") {
        
            cout << ">>> Tournament Winner: "
                << (T.finalists[0].points > T.finalists[1].points
                        ? T.finalists[0].name
                        : T.finalists[1].name)
                << "\n";
        
            T.finished = true;
    
        }

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

void playNextFixture(Tournament &T, string userTeam, int ball) {
    
    if (T.currentMatch >= T.fixtures.size()) {
        
        proceedNextStage(T);
        
        return;
    
    }

    auto match = T.fixtures[T.currentMatch];
    
    cout << "\nMatch " << (T.currentMatch + 1) << ": "
         << match.first << " vs " << match.second << "\n";

    
    int userMatchResult;

    string winner;

    if (match.first == userTeam){

        userMatchResult = tournamentMatchStart(match.first, match.second, ball);

        if(userMatchResult == 1){

            winner = match.first;

        }

        else if(userMatchResult == 2 || userMatchResult == 4){

            int num = rand()%2 + 1;
            if(num==1)  winner = match.first;
            else    winner = match.second;

        }

        else if(userMatchResult == 3){

            winner = match.second;

        }

    }

    else if (match.second == userTeam){

        userMatchResult = tournamentMatchStart(match.second, match.first, ball);

        if(userMatchResult == 1){

            winner = match.second;

        }

        else if(userMatchResult == 2 || userMatchResult == 4){

            int num = rand()%2 + 1;
            if(num==1)  winner = match.second;
            else    winner = match.first;

        }

        else if(userMatchResult == 3){

            winner = match.first;

        }

    }

    else{

        int s1 = rand() % 100;
    
        int s2 = rand() % 100;
    
        cout << match.first << " scored: " << s1 << "\n";
    
        cout << match.second << " scored: " << s2 << "\n";

        if (s1 > s2) winner = match.first;
    
        else if (s2 > s1) winner = match.second;
    
        else{
        
            int win = rand()%2;
            if(win == 0){

                winner = match.first;

            }
            else{

                winner = match.second;

            }

        }

        cout << "Winner: " << (winner.empty() ? "TIE" : winner)
            << " (" << s1 << " vs " << s2 << ")\n";

    }

    
    // Update inside correct stage vector
    
    auto updateStats = [&](vector<Team>& vec) {
        
        for (auto &t : vec) {
            
            if (t.name == match.first) {
                
                t.played++;
                
                if (winner == match.first) { t.won++; t.points += 2; }
                
                else if (winner.empty()) { t.points++; }
                
                else t.lost++;
            
            }
            
            else if (t.name == match.second) {
                
                t.played++;
                
                if (winner == match.second) { t.won++; t.points += 2; }
                
                else if (winner.empty()) { t.points++; }
                
                else t.lost++;
            
            }
        
        }
    
    };


    // Update correct container depending on stage

    if (T.name == "Asia Cup"){

        if (T.stage == "QualifierA") updateStats(T.qualifierA);

        else if (T.stage == "QualifierB") updateStats(T.qualifierB);
    
        else if (T.stage == "PlateSemi") updateStats(T.platesemifinalists);
    
        else if (T.stage == "PlateThirdPlace") updateStats(T.platethirdplace);
    
        else if (T.stage == "Group") {
        
            updateStats(T.groupA);
        
            updateStats(T.groupB);
    
        }
    
        else if (T.stage == "Super4") updateStats(T.super4);
    
        else if (T.stage == "Final") updateStats(T.finalists);

        T.currentMatch++;

        if (T.currentMatch >= T.fixtures.size()) {
        
            proceedNextStage(T);
    
        }

    }

    else if (T.name == "Champions Trophy"){
    
        if (T.stage == "Group") {
        
            updateStats(T.groupA);
        
            updateStats(T.groupB);
    
        }
    
        else if (T.stage == "SemiFinal") updateStats(T.semifinalists);
    
        else if (T.stage == "Final") updateStats(T.finalists);

        T.currentMatch++;

        if (T.currentMatch >= T.fixtures.size()) {
        
            proceedNextStage(T);
    
        }

    }

    else if (T.name == "World Cup"){
    
        if (T.stage == "QualifierA") updateStats(T.qualifierA);

        else if (T.stage == "QualifierB") updateStats(T.qualifierB);

        else if (T.stage == "Super6") updateStats(T.super6);
    
        else if (T.stage == "SemiFinal") updateStats(T.semifinalists);
    
        else if (T.stage == "Final") updateStats(T.finalists);

        T.currentMatch++;

        if (T.currentMatch >= T.fixtures.size()) {
        
            proceedNextStage(T);
    
        }

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
    cout << YELLOW << "╔══════════════════════════════╗\n";
    cout << "║ " << GREEN << setw(29) << left << "FIXTURE" << "║\n";
    cout << YELLOW << "╠══════════════════════════════╣\n";

    string title = T.name + " " + T.stage;
    cout << "║ " << setw(29) << left << title << "║\n";
    cout << "╠══════════════════════════════╣\n";

    for (size_t i = 0; i < T.fixtures.size(); i++) {
        string match = to_string(i + 1) + ". " + 
                       T.fixtures[i].first + " vs " + 
                       T.fixtures[i].second;

        cout << "║ " << setw(29) << left << match << "║";
        if (i < T.currentMatch)
            cout << RED << " [Played]";
        cout << "\n";
    }

    cout << "╚══════════════════════════════╝\n" << RESET;
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
    
    if (T.name == "Asia Cup"){

        if (T.stage == "QualifierA") {
        
            vector<Team> qualifierAcopy = T.qualifierA;

            sort(qualifierAcopy.begin(), qualifierAcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";

            
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << " Group - A:" << YELLOW << "║\n";
            cout << "╠═══════════════════════════════╣\n";

    
            cout << WHITE << left << setw(20) << "Team"
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : qualifierAcopy) {
        
                cout << GREEN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }

        if (T.stage == "QualifierB") {
        
            vector<Team> qualifierBcopy = T.qualifierB;

            sort(qualifierBcopy.begin(), qualifierBcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << " Group - B:" << YELLOW << "║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : qualifierBcopy) {
        
                cout << BLUE << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }

        if (T.stage == "PlateSemi") {

            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "   ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.platesemifinalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

        if (T.stage == "PlateThirdPlace") {

            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "MATCH!" << YELLOW << "║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.platesemifinalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }
        
        
        if (T.stage == "Group") {
        
            vector<Team> groupAcopy = T.groupA;
            vector<Team> groupBcopy = T.groupB;

            sort(groupAcopy.begin(), groupAcopy.end(), cmpTeam);
            sort(groupBcopy.begin(), groupBcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";

            
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << " Group - A:" << YELLOW << "     ║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE <<  left << setw(20) << "Team"
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : groupAcopy) {
        
                cout << GREEN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n";
    
            }

            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << " Group - B:" << YELLOW << "     ║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : groupBcopy) {
        
                cout << BLUE << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }
        
        
        
        
        if (T.stage == "Super4") {
        
            vector<Team> super4copy = T.super4;
        
            sort(super4copy.begin(), super4copy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << YELLOW << "               ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
        
            for (auto &t : super4copy) {
            
                cout << CYAN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
        
            }
        
            return;
    
        }

        if (T.stage == "Final") {
        
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "       ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.finalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

    }

    else if (T.name == "Champions Trophy"){
        
        if (T.stage == "Group") {
        
            vector<Team> groupAcopy = T.groupA;
            vector<Team> groupBcopy = T.groupB;

            sort(groupAcopy.begin(), groupAcopy.end(), cmpTeam);
            sort(groupBcopy.begin(), groupBcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";

            
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << " Group - A:" << YELLOW << "     ║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE <<  left << setw(20) << "Team"
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : groupAcopy) {
        
                cout << GREEN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n";
    
            }

            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << " Group - B:" << YELLOW << "     ║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : groupBcopy) {
        
                cout << BLUE << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }
        
        if (T.stage == "SemiFinal") {

            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "   ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.semifinalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

        if (T.stage == "Final") {
        
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "       ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.finalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

    }

    if (T.name == "World Cup"){

        if (T.stage == "QualifierA") {
        
            vector<Team> qualifierAcopy = T.qualifierA;

            sort(qualifierAcopy.begin(), qualifierAcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";

            
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << " Group - A:" << YELLOW << "║\n";
            cout << "╠═══════════════════════════════╣\n";

    
            cout << WHITE << left << setw(20) << "Team"
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : qualifierAcopy) {
        
                cout << GREEN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }

        if (T.stage == "QualifierB") {
        
            vector<Team> qualifierBcopy = T.qualifierB;

            sort(qualifierBcopy.begin(), qualifierBcopy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << " Group - B:" << YELLOW << "║\n";
            cout << "╠═══════════════════════════════╣\n";
    
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
    
            for (auto &t : qualifierBcopy) {
        
                cout << BLUE << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
    
            }
        
            return;
    
        }
        
        if (T.stage == "Super6") {
        
            vector<Team> super6copy = T.super6;
        
            sort(super6copy.begin(), super6copy.end(), cmpTeam);
        
            cout << YELLOW << "╔═══════════════════════════════╗\n";
            cout << "║ " << YELLOW << setw(30) << left << "Points Table" << "║\n";
            cout << "╠═══════════════════════════════╣\n";


            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << BLUE << T.stage << YELLOW << "               ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            cout << WHITE << left << setw(20) << "Team" 
                << setw(8) << "Played" 
                << setw(8) << "Won" 
                << setw(8) << "Lost" 
                << setw(8) << "Points" << "\n";
        
            for (auto &t : super6copy) {
            
                cout << CYAN << left << setw(20) << t.name
                    << setw(8) << t.played
                    << setw(8) << t.won
                    << setw(8) << t.lost
                    << setw(8) << t.points << "\n" << RESET;
        
            }
        
            return;
    
        }

        if (T.stage == "SemiFinal") {

            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "   ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.semifinalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

        if (T.stage == "Final") {
        
            cout << YELLOW << "╠═══════════════════════════════╣\n";
            cout << "║ " << RED << T.name << " " << GREEN << T.stage << "Finalist!" << YELLOW << "       ║\n";
            cout << "╠═══════════════════════════════╣\n";
        
            for (auto &t : T.finalists) {
            
                cout << RED << t.name << GREEN << " (Points: " << t.points << ", Won: " << t.won << ")\n" << RESET;
        
            }
        
            return;
    
        }

    }

}











void saveTournament(const Tournament &T) {
    
    string fileName;

    if (T.name == "Asia Cup")
        fileName = "Database/asia_cup_save.txt";
    else if (T.name == "Champions Trophy")
        fileName = "Database/champions_trophy_save.txt";
    else if (T.name == "World Cup")
        fileName = "Database/world_cup_save.txt";
    else
        fileName = "Database/tournament_save.txt";
    
    
    
    stringstream buffer;

    buffer << T.name << "\n";
    buffer << T.stage << "\n";
    buffer << T.currentMatch << "\n";
    buffer << T.finished << "\n";

    auto saveTeams = [&](const vector<Team>& teams) {
        buffer << teams.size() << "\n";
        for (auto &t : teams) {
            buffer << t.name << " " << t.played << " " << t.won << " "
                   << t.lost << " " << t.points << "\n";
        }
    };

    if (T.name == "Asia Cup"){

        saveTeams(T.qualifierA);
        saveTeams(T.qualifierB);
        saveTeams(T.platesemifinalists);
        saveTeams(T.platethirdplace);
        saveTeams(T.groupA);
        saveTeams(T.groupB);
        saveTeams(T.super4);
        saveTeams(T.finalists);

    }

    else if (T.name == "Champions Trophy"){

        saveTeams(T.groupA);
        saveTeams(T.groupB);
        saveTeams(T.semifinalists);
        saveTeams(T.finalists);

    }

    else if (T.name == "World Cup"){

        saveTeams(T.qualifierA);
        saveTeams(T.qualifierB);
        saveTeams(T.super6);
        saveTeams(T.semifinalists);
        saveTeams(T.finalists);

    }

    

    buffer << T.fixtures.size() << "\n";
    for (auto &f : T.fixtures) {
        buffer << f.first << "," << f.second << "\n";
    }


    string encoded = encode(buffer.str());

    ofstream file(fileName, ios::binary);
    
    file << encoded;
    
    file.close();

    cout << "Tournament saved!\n";

}


Tournament loadTournament(const string &tournamentName) {
    
    string fileName;

    if (tournamentName == "Asia Cup")
        fileName = "Database/asia_cup_save.txt";
    else if (tournamentName == "Champions Trophy")
        fileName = "Database/champions_trophy_save.txt";
    else if (tournamentName == "World Cup")
        fileName = "Database/world_cup_save.txt";
    else
        fileName = "Database/tournament_save.txt";

    ifstream file(fileName, ios::binary);
    
    string encoded;
    
    char c;
    
    while (file.get(c)) {
        
        encoded += c;
    
    }
    
    file.close();


    string decoded = decode(encoded);
    
    stringstream buffer(decoded);

    Tournament T;

    getline(buffer, T.name);
    
    getline(buffer, T.stage);
    
    buffer >> T.currentMatch;
    
    buffer >> T.finished;

    auto loadTeams = [&](vector<Team>& teams) {
        size_t n;
        buffer >> n;
        teams.clear();
        for (size_t i = 0; i < n; i++) {
            Team temp;
            buffer >> temp.name >> temp.played >> temp.won >> temp.lost >> temp.points;
            teams.push_back(temp);
        }
    };

    if (tournamentName == "Asia Cup"){

        loadTeams(T.qualifierA);
        loadTeams(T.qualifierB);
        loadTeams(T.platesemifinalists);
        loadTeams(T.platethirdplace);
        loadTeams(T.groupA);
        loadTeams(T.groupB);
        loadTeams(T.super4);
        loadTeams(T.finalists);

    }

    else if (tournamentName == "Champions Trophy"){

        loadTeams(T.groupA);
        loadTeams(T.groupB);
        loadTeams(T.semifinalists);
        loadTeams(T.finalists);

    }

    else if (tournamentName == "World Cup"){

        loadTeams(T.qualifierA);
        loadTeams(T.qualifierB);
        loadTeams(T.super6);
        loadTeams(T.semifinalists);
        loadTeams(T.finalists);

    }

    

    size_t fixtureCount;
    
    buffer >> fixtureCount;
    
    buffer.ignore();

    T.fixtures.clear();
    for (size_t i = 0; i < fixtureCount; i++) {
        string line;
        getline(buffer, line);
        size_t comma = line.find(',');
        T.fixtures.push_back({line.substr(0, comma), line.substr(comma + 1)});
    }

    cout << "Tournament loaded!\n";
    
    return T;

}
