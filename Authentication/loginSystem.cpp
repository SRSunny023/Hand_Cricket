#include "loginSystem.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;






const string fileName = "Database/userManual.txt";   // Account Details Holding File
const string sessionFile = "Database/session.txt";   // Session Login or Logged Out Detection File

void account_menu();







/****************************************************************************************************/
/* Function Name: clearScreen                                                                       */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : Non                                                                               */
/*                                                                                                  */
/* Note         : This Function Clear The Console Screen                                            */
/****************************************************************************************************/

void clearScreen() {
    
    cout << "\033[H\033[J";

}









/****************************************************************************************************/
/* Function Name: pressToContinue                                                                   */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : Non                                                                               */
/*                                                                                                  */
/* Note         : This Function Tells User To Press Any Key To Continue The Program                 */
/****************************************************************************************************/

void pressToContinue() {
    
    cout << "Press Enter to continue...";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    cin.get();

}









/****************************************************************************************************/
/* Function Name: getIntInput                                                                       */
/*                                                                                                  */
/* Inputs       : const string                                                                      */
/*                                                                                                  */
/* Returns      : Int                                                                               */
/*                                                                                                  */
/* Note         : This Function Takes Only Integer Input Other Input Is Invalid                     */
/****************************************************************************************************/

int getIntInput(const string &prompt) {
    
    int value;
    
    while (true) {
        
        cout << prompt;
        
        cin >> value;
        
        if (cin.fail()) {
            
            cin.clear();
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Invalid input! Please enter a number.\n";
        }
        
        else {
            
            return value;
        
        }
    
    }

}








/****************************************************************************************************/
/* Function Name: saveSession                                                                       */
/*                                                                                                  */
/* Inputs       : const string                                                                      */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function Save the User Login So that He Dont need to login again             */
/****************************************************************************************************/

void saveSession(const string &username) {
    
    ofstream fout(sessionFile);
    
    if (fout) fout << username;

}









/****************************************************************************************************/
/* Function Name: loadSession                                                                       */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : string                                                                            */
/*                                                                                                  */
/* Note         : This Function load the saved login details                                        */
/****************************************************************************************************/

string loadSession() {
    
    ifstream fin(sessionFile);
    
    string username;
    
    if (fin) fin >> username;
    
    return username;

}











/****************************************************************************************************/
/* Function Name: clearSession                                                                      */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function clear the saved login details                                       */
/****************************************************************************************************/

void clearSession() {
    
    ofstream fout(sessionFile, ios::trunc); // overwrite with nothing

}









/****************************************************************************************************/
/* Function Name: loadUsers                                                                         */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : vector                                                                            */
/*                                                                                                  */
/* Note         : This Function load all the user login details                                     */
/****************************************************************************************************/


vector<User> loadUsers() {
    
    ifstream fin(fileName);
    
    vector<User> users;
    
    User u;
    
    while (fin >> u.email >> u.username >> u.password) {
        
        users.push_back(u);
    
    }
    
    return users;
}










/****************************************************************************************************/
/* Function Name: saveUsers                                                                         */
/*                                                                                                  */
/* Inputs       : const vector                                                                      */
/*                                                                                                  */
/* Returns      : bool                                                                              */
/*                                                                                                  */
/* Note         : This Function save user login details                                             */
/****************************************************************************************************/


bool saveUsers(const vector<User> &users) {
    
    ofstream fout(fileName);
    
    if (!fout) return false;
    
    for (auto &u : users)
        
        fout << u.email << " " << u.username << " " << u.password << "\n";
    
    return true;
}











/****************************************************************************************************/
/* Function Name: registerUser                                                                      */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function take user details for registration and save in a file               */
/****************************************************************************************************/


void registerUser() {
    
    clearScreen();

    User newUser;

    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Registration                               |\n";
    cout << "|                                                                          |\n";
    cout << "| 1. Enter Email: ";
    cin >> newUser.email;
    cout << "|                                                                          |\n";
    cout << "| 2. Enter Username: ";
    cin >> newUser.username;
    cout << "|                                                                          |\n";
    cout << "| 3. Enter Password: ";
    cin >> newUser.password;
    cout << "|                                                                          |\n";
    cout << "| 4. Confirm Password: ";
    cin >> newUser.confirmPassword;
    cout << "|                                                                          |\n";
    cout << "----------------------------------------------------------------------------\n";
    
    auto users = loadUsers();

    for (auto &u : users) {
        
        if (u.email == newUser.email) {
            
            cout << "Email already exists!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }
    
    for (auto &u : users) {
        
        if (u.username == newUser.username) {
            
            cout << "Username already exists!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }

    if(newUser.password != newUser.confirmPassword){

        cout << "Password Didn't Match!\n";

        cout << "Registration Failed! Try Again\n";

        pressToContinue();

        return;

    }
    
    users.push_back(newUser);
    
    saveUsers(users);
    
    cout << "Registration Successful!\n";
    
    pressToContinue();

}











/****************************************************************************************************/
/* Function Name: userMenu                                                                          */
/*                                                                                                  */
/* Inputs       : struct, vector                                                                    */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function is the user menu                                                    */
/****************************************************************************************************/


void userMenu(User &loggedInUser, vector<User> &allUsers) {
    
    while (true) {
        
        clearScreen();

        cout << "----------------------------------------------------------------------------\n";
        cout << "|                               User Menu                                  |\n";
        cout << "|                                                                          |\n";
        cout << "| 1. Play                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "| 2. View Profile                                                          |\n";
        cout << "|                                                                          |\n";
        cout << "| 3. Change Password                                                       |\n";
        cout << "|                                                                          |\n";
        cout << "| 4. History                                                               |\n";
        cout << "|                                                                          |\n";
        cout << "| 5. Logout                                                                |\n";
        cout << "|                                                                          |\n";
        cout << "| 6. Exit                                                                  |\n";
        cout << "|                                                                          |\n";
        cout << "----------------------------------------------------------------------------\n";
        
        int choice = getIntInput("Enter choice: ");

        if (choice == 1) {

            clearScreen();

            playMenu();

        }

        else if (choice == 2) {
            
            clearScreen();
            
            cout << "--- Profile ---\n";
            
            cout << "Email: " << loggedInUser.email << "\n";
            
            cout << "Username: " << loggedInUser.username << "\n";
            
            pressToContinue();
        
        }
        
        else if (choice == 3) {
            
            clearScreen();
            
            cout << "--- Change Password ---\n";
            
            string newPass,newConfirmPass;
            
            cout << "Enter New Password: ";
            
            cin >> newPass;

            cout << "Confirm New Password: ";
            
            cin >> newConfirmPass;

            if(newPass != newConfirmPass){

                cout << "Password Didn't Match!\nPassword Reset Failed! Try Again!\n";

                pressToContinue();

                return;

            }
            
            loggedInUser.password = newPass;

            // Update in allUsers and save
            for (auto &u : allUsers) {
                
                if (u.username == loggedInUser.username) {
                    
                    u.password = newPass;
                    
                    break;
                
                }
            
            }
            
            saveUsers(allUsers);
            
            cout << "Password changed successfully!\n";
            
            pressToContinue();
        
        }
        
        else if (choice == 5) {
            
            cout << "Logging out...\n";

            clearSession();
            
            pressToContinue();

            account_menu();
        
        }

        else if(choice == 6) {

            clearScreen();

            cout << "Program Exitted!\n";

            exit(0);

        }
        
        else {
            
            cout << "Invalid Choice!\n";
            
            pressToContinue();
        
        }
    
    }

}










/****************************************************************************************************/
/* Function Name: loginUser                                                                         */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function take user username and password for login                           */
/****************************************************************************************************/

void loginUser() {
    
    clearScreen();

    string user, pass;
    
    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Login                                      |\n";
    cout << "|                                                                          |\n";
    cout << "| 1. Enter Username: ";
    cin >> user;
    cout << "|                                                                          |\n";
    cout << "| 2. Enter Password: ";
    cin >> pass;
    cout << "|                                                                          |\n";
    cout << "----------------------------------------------------------------------------\n";

    
    auto users = loadUsers();
    
    bool usernameFound = false;

    for (auto &u : users) {
        
        if (u.username == user) {
            
            usernameFound = true;
            
            if (u.password == pass) {
                
                cout << "Login Successful! Welcome " << user << "\n";
                
                saveSession(user);
                
                pressToContinue();
                
                userMenu(u, users);
                
                return;
            
            } 
            
            else {
                
                cout << "Incorrect password for user: " << user << "\n";
                
                pressToContinue();
                
                return;
            
            }
        
        }
    
    }

    if (!usernameFound) {
        
        cout << "Username not found!\n";
        
        pressToContinue();
    
    }

}











/****************************************************************************************************/
/* Function Name: resetPassword                                                                     */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for reset password                                                  */
/****************************************************************************************************/

void resetPassword() {
    
    clearScreen();

    string email, newPass;
    
    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Reset Password                             |\n";
    cout << "|                                                                          |\n";
    cout << "| 1. Enter Email: ";
    cin >> email;

    auto users = loadUsers();
    
    for (auto &u : users) {
        
        if (u.email == email) {
            
            cout << "|                                                                          |\n";
            cout << "| 2. Enter New Password: ";
            cin >> newPass;
            cout << "|                                                                          |\n";
            cout << "----------------------------------------------------------------------------\n";
            
            u.password = newPass;
            
            saveUsers(users);
            
            cout << "Password Updated!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }
    
    cout << "|                                                                          |\n";
    cout << "| Email Not Found                                                          |\n";
    cout << "|                                                                          |\n";
    cout << "----------------------------------------------------------------------------\n";
    
    pressToContinue();

}




void resetUsername() {
    
    clearScreen();

    string email, newUserName;
    
    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Reset Username                             |\n";
    cout << "|                                                                          |\n";
    cout << "| 1. Enter Email: ";
    cin >> email;

    auto users = loadUsers();
    
    for (auto &u : users) {
        
        if (u.email == email) {
            
            cout << "|                                                                          |\n";
            cout << "| 2. Enter New Username: ";
            cin >> newUserName;
            cout << "|                                                                          |\n";
            cout << "----------------------------------------------------------------------------\n";
            
            u.username = newUserName;
            
            saveUsers(users);
            
            cout << "Username Updated!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }
    
    cout << "|                                                                          |\n";
    cout << "| Email Not Found                                                          |\n";
    cout << "|                                                                          |\n";
    cout << "----------------------------------------------------------------------------\n";
    
    pressToContinue();

}








/****************************************************************************************************/
/* Function Name: account_menu                                                                      */
/*                                                                                                  */
/* Inputs       : None                                                                              */
/*                                                                                                  */
/* Returns      : None                                                                              */
/*                                                                                                  */
/* Note         : This Function for account menu                                                    */
/****************************************************************************************************/


void account_menu() {
    
    
    string activeUser = loadSession();

    if (!activeUser.empty()) {

        auto users = loadUsers();
        
        for (auto &u : users) {
            
            if (u.username == activeUser) {
                
                userMenu(u, users);
            
            }
        
        }
    
    }

    else{

        while (true) {
        
            clearScreen();
        
            cout << "----------------------------------------------------------------------------\n";
            cout << "|                               Account                                    |\n";
            cout << "|                                                                          |\n";
            cout << "|  1. Register                                                             |\n";
            cout << "|                                                                          |\n";
            cout << "|  2. Login                                                                |\n";
            cout << "|                                                                          |\n";
            cout << "|  3. Reset Password                                                       |\n";
            cout << "|                                                                          |\n";
            cout << "|  4. Reset Username                                                       |\n";
            cout << "|                                                                          |\n";
            cout << "|  5. Exit                                                                 |\n";
            cout << "|                                                                          |\n";
            cout << "----------------------------------------------------------------------------\n";
        
            int choice = getIntInput("Enter choice: ");

            if (choice == 1) registerUser();
        
            else if (choice == 2) loginUser();
        
            else if (choice == 3) resetPassword();

            else if (choice == 4) resetUsername();
        
            else if (choice == 5) {
            
                clearScreen();
            
                cout << "Program Successfully Exitted!\n";

                exit(0);
        
            }
        
            else {
            
                cout << "Invalid Choice! Choose Between (1 - 5)\n";
            
                pressToContinue();
        
            }
    
        }

    }

}
