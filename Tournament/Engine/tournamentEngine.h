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
    
    vector<Team> groupA, groupB, super4, semifinalists, finalists;
    
    vector<pair<string,string>> fixtures;
    
    size_t currentMatch = 0;
    
    bool finished = false;
    
    string stage = "Group";   // Group / Super4 / Semi / Final
    
    Tournament(string n="") : name(n) {}

};


Team* findTeam(Tournament &T, const string &name);

bool cmpTeam(const Team &a, const Team &b);

void proceedNextStage(Tournament &T);

void playNextFixture(Tournament &T, string userTeam);

void showFixtures(Tournament &T);

void showPointsTable(Tournament &T);

#endif