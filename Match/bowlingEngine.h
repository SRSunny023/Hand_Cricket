#ifndef BOWLINGENGINE_H
#define BOWLINGENGINE_H


#include <iostream>
#include <string>
using namespace std;

void handleLastShot(int, int, int, string &lastShotChoosed);

void bowlDelivery(int &stamina, int &aiScore, int &aiWicket, int, string,
                  string &lastShotChoosed, int, int, string, int, float);

void playInnings(string, string, int &aiScore, int &aiWicket, int &stamina,
                 int, int, int, string, string &lastShotChoosed, bool);

void resetMatch();

int bowl(string, string, int, int, int, string);

#endif