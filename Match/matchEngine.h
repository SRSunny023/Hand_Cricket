#ifndef MATCHENGINE_H
#define MATCHENGINE_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void startMatch(string, string, int, int);

void scoreLogic(int);

void bat(string, string, int);
void bowl(string, string, int);

int batTournament(string, string, int);
int bowlTournament(string, string, int);

void resetProgressTournamentMatch();

#endif