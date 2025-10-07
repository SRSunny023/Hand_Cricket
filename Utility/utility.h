#ifndef UTILITY_H
#define UTILITY_H


#include <string>
#include <vector>
using namespace std;

int clearScreen();
void pressToContinue();
int getIntInput(const string &prompt);
string getEmailInput(const string &prompt);


#endif