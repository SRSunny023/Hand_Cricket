#include "loginSystem.h"
#include "menu.h"
#include "printMenu.h"
#include "utility.h"









#include <iostream>
#include <fstream>
#include <limits>
using namespace std;









const string fileName = "Database/userManual.txt";   // Account Details Holding File
const string sessionFile = "Database/session.txt";   // Session Login or Logged Out Detection File





/****************************************************************************************************/
/* Function Name: encode                                                                            */
/*                                                                                                  */
/* Inputs       : const string,char                                                                 */
/*                                                                                                  */
/* Returns      : string                                                                            */
/*                                                                                                  */
/* Note         : This Function encode data                                                         */
/****************************************************************************************************/

string encode(const string &data, char key) {
    
    string encoded = data;
    
    for (char &c : encoded) {
        
        c ^= key;  // XOR each character
    
    }
    
    return encoded;

}



/****************************************************************************************************/
/* Function Name: decode                                                                            */
/*                                                                                                  */
/* Inputs       : const string,char                                                                 */
/*                                                                                                  */
/* Returns      : string                                                                            */
/*                                                                                                  */
/* Note         : This Function decode data                                                         */
/****************************************************************************************************/

string decode(const string &data, char key) {
    
    return encode(data, key); // XOR twice = original

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
    
    string encoded = encode(username);
    
    ofstream fout(sessionFile, ios::binary);
    
    if (fout){

        fout << encoded;

        fout.close();

    }

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
    
    ifstream fin(sessionFile, ios::binary);

    string encoded;
    
    char c;
    
    while (fin.get(c)) {
        
        encoded += c;
    
    }
    
    fin.close();
    
    string username = decode(encoded);
    
    if (!username.empty() && username.back() == '\n')
        username.pop_back();
    
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

    newUser.email = getEmailInput("Enter Email: ");

    if(newUser.email == "/")    return;
    
    auto users = loadUsers();
    
    for (auto &u : users) {
        
        if (u.email == newUser.email) {
            
            cout << "Email already exists!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }

    cout << "Enter Username: ";
    cin >> newUser.username;

    if(newUser.username == "*"){

        clearScreen();

        cout << "Program Successfully Exitted!\n";

        exit(0);

    }

    if(newUser.username == "/"){

        return;

    }

    for (auto &u : users) {
        
        if (u.username == newUser.username) {
            
            cout << "Username already exists!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }

    cout << "Enter Password: ";
    cin >> newUser.password;

    if(newUser.password == "*"){

        clearScreen();

        cout << "Program Successfully Exitted!\n";

        exit(0);

    }

    if(newUser.password == "/"){

        return;

    }

    cout << "Confirm Password: ";
    cin >> newUser.confirmPassword;

    if(newUser.confirmPassword == "*"){

        clearScreen();

        cout << "Program Successfully Exitted!\n";

        exit(0);

    }

    if(newUser.confirmPassword == "/"){

        return;

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
        
        printUserMenu();
        
        int choice = getIntInput("Enter choice: ");

        if (choice == 1) {

            clearScreen();

            playMenu();

        }

        else if (choice == 2) {
            
            clearScreen();
            
            cout << "----------------------------------------------------------------------------\n";
            cout << "|                               Profile                                    |\n";
            cout << "----------------------------------------------------------------------------\n";
            
            cout << "Email: " << loggedInUser.email << "\n\n";
            
            cout << "Username: " << loggedInUser.username << "\n\n";
            
            pressToContinue();
        
        }
        
        else if (choice == 4) {
            
            cout << "Logging out...\n";

            clearSession();
            
            pressToContinue();

            account_menu();
        
        }

        else if(choice == 5) {

            clearScreen();

            cout << "Program Exitted!\n";

            exit(0);

        }

        else if(choice == -1){

            cout << "Going Back Not Allowed Here!\n";

            pressToContinue();

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

    int incorrectPass = 0;
    int incorrectEmail = 0;

    while(true){
        
        clearScreen();
        
        string email, pass;
    
        cout << "----------------------------------------------------------------------------\n";
        cout << "|                               Login                                      |\n";
        cout << "----------------------------------------------------------------------------\n";
        cout << "Enter Email: ";
        cin >> email;
        if(email == "*"){

            clearScreen();

            cout << "Program Successfully Exitted!\n";

            exit(0);

        }
        if(email == "/"){

            return;

        }
        cout << "Enter Password: ";
        cin >> pass;

        if(pass == "*"){

            clearScreen();

            cout << "Program Successfully Exitted!\n";

            exit(0);

        }
        if(pass == "/"){

            return;

        }

    
        auto users = loadUsers();
    
        bool emailFound = false;

        for (auto &u : users) {
        
            if (u.email == email) {
            
                emailFound = true;
            
                if (u.password == pass) {
                
                    cout << "Login Successful! Welcome " << u.username << "\n";
                
                    saveSession(u.username);
                
                    pressToContinue();
                
                    userMenu(u, users);
                
                    return;
            
                } 
            
                else {
                
                    cout << "Incorrect password for user: " << u.username << "\n";

                    incorrectPass++;
                
                    pressToContinue();
            
                }
        
            }
    
        }

        if (!emailFound) {
        
            clearScreen();
            
            cout << "Email not found!\n";

            incorrectEmail++;
        
            pressToContinue();
    
        }

        if(incorrectPass > 2){

            clearScreen();
            
            cout << "Too Much Wrong Password Do You Want To Reset Password?\nIf Yes Click 1\n";
            cout << "If You Want To Create A New Account\nClick 2\n";

            int choice;

            choice = getIntInput("Enter Your Choice: ");

            if(choice == 1){

                resetPassword();

                return;

            }

            else if(choice == 2){

                registerUser();

                return;

            }

            else if(choice == -1){

                return;

            }

            else{

                int incorrectPass = 0;

            }

        }
        if(incorrectEmail > 2){

            clearScreen();
            
            cout << "Too Much Wrong Email Do You Want To Create A New Accout?\nIf Yes Click 1\n";

            int choice;

            choice = getIntInput("Enter Your Choice: ");

            if(choice == 1){

                registerUser();

                return;

            }

            else if(choice == -1){

                return;

            }

            else{

                int incorrectEmail = 0;

            }

        }

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

    string email, newPass, confirmNewPass;
    
    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Reset Password                             |\n";
    cout << "----------------------------------------------------------------------------\n";
    cout << "Enter Email: ";
    cin >> email;

    if(email == "*"){

        clearScreen();

        cout << "Program Successfully Exitted!\n";

        exit(0);

    }

    if(email == "/"){

        return;

    }

    auto users = loadUsers();
    
    for (auto &u : users) {
        
        if (u.email == email) {
            
            cout << "Enter New Password: ";
            cin >> newPass;

            if(newPass == "*"){

                clearScreen();

                cout << "Program Successfully Exitted!\n";

                exit(0);

            }

            if(newPass == "/")  return;

            cout << "Confirm New Password: ";
            cin >> confirmNewPass;

            if(confirmNewPass == "*"){

                clearScreen();

                cout << "Program Successfully Exitted!\n";

                exit(0);

            }

            if(confirmNewPass == "/")  return;

            if(newPass == confirmNewPass){

                u.password = newPass;
            
                saveUsers(users);
            
                cout << "Password Updated!\n";
            
                pressToContinue();
            
                return;

            }

            else{

                cout << "Password Didn't Matched!\n";

                pressToContinue();

                return;

            }
        
        }
    
    }
    cout << "Email Not Found\n";
    
    pressToContinue();

}




void resetUsername() {
    
    clearScreen();

    string email, newUserName;
    
    cout << "----------------------------------------------------------------------------\n";
    cout << "|                               Reset Username                             |\n";
    cout << "----------------------------------------------------------------------------\n";
    cout << "Enter Email: ";
    cin >> email;

    if(email == "*"){

        clearScreen();

        cout << "Program Successfully Exitted!\n";

        exit(0);

    }

    if(email == "/"){

        return;

    }

    auto users = loadUsers();
    
    for (auto &u : users) {
        
        if (u.email == email) {
            
            cout << "Enter New Username: ";
            cin >> newUserName;
            
            if(newUserName == "*"){

                clearScreen();

                cout << "Program Successfully Exitted!\n";

                exit(0);

            }

            if(newUserName == "/")  return;
            
            u.username = newUserName;
            
            saveUsers(users);
            
            cout << "Username Updated!\n";
            
            pressToContinue();
            
            return;
        
        }
    
    }
    
    cout << "Email Not Found\n";
    
    pressToContinue();

}