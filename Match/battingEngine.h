#ifndef BATTINGENGINE_H
#define BATTINGENGINE_H

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
using namespace std;

int aiBattingDecision(int &stamina, int, int, int, string, string, string, float);

void playShot(int &stamina, int, string, string);

void playInnings(int &temporaryBall, int, string, int &stamina, int, string, bool, int);

int bat(string, string, int, int, int, string);


extern sf::SoundBuffer hitBuffer;
void playHitSound();
void loadSounds();


#endif