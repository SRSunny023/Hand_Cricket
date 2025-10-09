#include "main_menu.h"
#include "utility.h"




#include <iostream>
using namespace std;






/********************************************************************************/
/* Function Name: printPlayMenu                                                 */
/*                                                                              */
/* Inputs       : Struct                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function To print play menu                       */
/********************************************************************************/

void printPlayMenu(){

    clearScreen();
    
    cout << "╔═══════════════════════PLAY MENU═══════════════════════╗\n\n";
    
    cout << "1. EXHIBITION MATCH\n\n2. TOURNAMENT\n\n3. SERIES\n\n4. BACK\n\n5. EXIT\n\n";

    cout << "╚═══════════════════════PLAY MENU═══════════════════════╝\n\n";

}



/********************************************************************************/
/* Function Name: mainMenu                                                      */
/*                                                                              */
/* Inputs       : Struct                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function Of Main Menu                             */
/********************************************************************************/

void playMenu(){

    while(1){

        printPlayMenu();

        int choice = getIntInput("Enter Your Choice: ");

        if(choice == 1){

            exhibitionMenu();

        }

        else if(choice == 2){

            tournamentMenu();

        }

        else if(choice == 3){

            cout << "Series Underdevelopment" << endl;

            speak("Series Underdevelopment");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            continue;

        }

        else if(choice == 4 || choice == -1){

            return;

        }

        else if(choice == 5){

            exitWindow();

        }

        else if(choice == 6){

            exitWindow();

        }

        else{

            cout << "Invalid Input! Choose Between (1 - 6)!" << endl;

            speak("Invalid Input! Choose Between (1 - 6)!");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            continue;

        }

    }

}