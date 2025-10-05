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
    
    vector<Team> qualifierA,qualifierB,platesemifinalists,platethirdplace; // Asia Cup Qualifier
    vector<Team> groupA, groupB, super4; // Asia Cup Main Round
    vector<Team> semifinalists, finalists; // Semi Final & Final
    
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

#endif