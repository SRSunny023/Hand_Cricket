#ifndef MATCHENGINE_H
#define MATCHENGINE_H





#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;







extern int userScore;
extern int aiScore;
extern int userWicket;
extern int aiWicket;
extern int target;
extern int bowlSpeed;
extern bool targetFlag;



extern string bowlVariation[9];

extern string batVariation[4];





void startMatch(string, string, int, int);

void bat(string, string, int);
void bowl(string, string, int);

int batTournament(string, string, int);
int bowlTournament(string, string, int);

void resetProgressTournamentMatch();

#endif