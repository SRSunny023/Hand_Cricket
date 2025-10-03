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