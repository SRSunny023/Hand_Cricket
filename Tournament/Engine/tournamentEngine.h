#ifndef TOURNAMENTENGINE_H
#define TOURNAMENTENGINE_H

#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Team {
    
    string name;
    
    int played = 0, points = 0, won = 0, lost = 0; 
    
    Team() = default;
    
    Team(const string &n) : name(n) {}

};

struct Tournament {
    
    string name;
    
    vector<Team> qualifierA,qualifierB,platesemifinalists,platethirdplace;
    vector<Team> groupA, groupB, groupC, groupD, super4, super6, super8A, super8B;
    vector<Team> semifinalists, finalists;
    
    vector<pair<string,string>> fixtures;
    
    size_t currentMatch = 0;
    
    bool finished = false;

    string stage;
    
    Tournament(string n = "", string initialStage = "QualifierA") 
        : name(n), stage(initialStage) {}

};


Team* findTeam(Tournament &T, const string &name);

bool cmpTeam(const Team &a, const Team &b);

void proceedNextStage(Tournament &T);

void playNextFixture(Tournament &T, string userTeam, int ball);

void showFixtures(Tournament &T);

void showPointsTable(Tournament &T);

Tournament loadTournament(const string &tournamentName);

void saveTournament(const Tournament &T);

#endif