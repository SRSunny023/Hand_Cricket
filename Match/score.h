#ifndef SCORE_H
#define SCORE_H


#include <string>
#include <vector>
using namespace std;


extern vector<string> tieComments;
extern vector<string> userLoseComments;
extern vector<string> userWinComments;


void scoreLogic(int &stamina, int batChoice, int who, int temparature, string, string);
void scoreCard(int score, int wicket, int ball, int target, string team, int over);
void speak(const std::string &text);


#endif