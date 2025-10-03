#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <string>
#include <vector>
using namespace std;

struct User {
    string email,username,password,confirmPassword;
};

void resetUsername();

void resetPassword();

void loginUser();

void registerUser();

string loadSession();

vector<User> loadUsers();

void userMenu(User &loggedInUser, vector<User> &allUsers);

#endif
