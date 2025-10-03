#include <iostream>
#include "utility.h"
#include <limits>
#include <string>
using namespace std;


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
/* Function Name: getIntInput                                                                       */
/*                                                                                                  */
/* Inputs       : const string                                                                      */
/*                                                                                                  */
/* Returns      : Int                                                                               */
/*                                                                                                  */
/* Note         : This Function Takes Only Integer Input Other Input Is Invalid                     */
/****************************************************************************************************/

int getIntInput(const string &prompt) {
    
    string value;
    
    while (true) {
        
        cout << prompt;
        
        cin >> value;

        if(value == "*"){

            clearScreen();

            cout << "Program Exitted Successfully!\n\n";
            
            exit(0);

        }

        else if(value == "/"){

            return -1;

        }

        else{

            bool isNumber = true;

            for(char c : value){

                if(!isdigit(c)){

                    isNumber = false;
                    break;

                }

            }

            if(isNumber){

                return stoi(value);

            }

            else{

                cout << "Invalid Input! Please Enter A Number, * to Exit, or / to go back!\n";

            }

        }
    
    }

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

string getEmailInput(const string &prompt) {
    
    string value;
    
    while (true) {
        
        clearScreen();

        cout << "----------------------------------------------------------------------------\n";
        cout << "|                               Registration                               |\n";
        cout << "----------------------------------------------------------------------------\n";
        
        int atTheRate = 0;
        int atTheRateIndex = -1;
        bool atTheRateOk = false;
        int dot = 0;
        int dotIndex = 0;
        bool dotFlag = false;
        

        cout << prompt;
        
        cin >> value;

        if(value == "*"){

            clearScreen();

            cout << "Program Exitted Successfully!\n\n";
            
            exit(0);

        }

        else if(value == "/"){

            return value;

        }
        
        char ch;

        for(int i=0; i < value.length(); i++){

            ch = value[i];

            if(ch == '@'){

                atTheRate++;
                atTheRateIndex = i;

            }

            if(ch == '.' && i > atTheRateIndex+1){

                dot++;
                dotIndex = i;

            }

        }

        if(atTheRate == 1 && atTheRateIndex >= 2){

            atTheRateOk = true;

        }

        if(dot == 1 && dotIndex > atTheRateIndex+1){

            int len = value.length();

            if(len > dotIndex+1)
            
                dotFlag = true;

        }

        if(atTheRateOk == true && dotFlag == true){

            return value;

        }

        else{

            clearScreen();
            
            cout << "Wrong Input!\n\n";

            cout << "Correct Form : yy@yyy.yyy\n\n";

            cout << "before @ there must me minimum 2 letters or digits\n\n";

            cout << "Loading...Enter Any Key!... ";

            cin.ignore();

            cin.get();

        }
    
    }

}