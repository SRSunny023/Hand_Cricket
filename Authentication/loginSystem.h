#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <string>
#include <vector>
using namespace std;

struct User {
    string email,username,password,confirmPassword;
};

void account_menu();

int getIntInput(const string &prompt);

void clearScreen();

void pressToContinue();

#endif
