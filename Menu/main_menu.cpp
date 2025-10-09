#include "main_menu.h"
#include "authentication.h"
#include "utility.h"
#include "settings.h"


#include <iostream>
#include <string>
using namespace std;






/********************************************************************************/
/* Function Name: printMainMenu                                                 */
/*                                                                              */
/* Inputs       : Struct                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function To print user main menu                  */
/********************************************************************************/

void printMainMenu(User person){

    clearScreen();
    
    cout << "╔═══════════════════════MAIN MENU═══════════════════════╗\n\n";

    cout << "WELCOME, " << person.username << " To The SRS Cricket\n\n";

    string speechText = "WELCOME, " + person.username + " To The SRS Cricket!";

    speak(speechText);
    
    cout << "1. PLAY\n\n2. STATS\n\n3. SETTINGS\n\n4. ABOUT\n\n5. LOG OUT\n\n";

    cout << "6. Exit\n\n";

    cout << "╚═══════════════════════MAIN MENU═══════════════════════╝\n\n";

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

void mainMenu(User person){

    while(1){

        printMainMenu(person);

        int choice = getIntInput("Enter Your Choice: ");

        if(choice == 1){

            playMenu();

        }

        else if(choice == 2){

            cout << "Stats Underdevelopment" << endl;

            speak("Stats Underdevelopment");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            continue;

        }

        else if(choice == 3){

            while(true){

                clearScreen();
                
                cout << "1. Voice Settings\n\n2. Back\n\n3. Exit" << endl;

                int settingChoice = getIntInput("Enter Your Choice: ");

                if(settingChoice == -1 || settingChoice == 2){

                    break;

                }

                else if(settingChoice == 1){

                    voiceSettings();

                }

                else if(settingChoice == 3){

                    exitWindow();

                }
                
                else{

                    cout << "Invalid Input Choose 1" << endl;

                    speak("Invalid Input Choose 1");

                    if(!VOICE_ENABLED){

                        pressToContinue(0);

                    }

                    continue;

                }

            }

        }

        else if(choice == 4){

            cout << "About Underdevelopment" << endl;

            speak("About Underdevelopment");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            continue;

        }

        else if(choice == 5){

            loadingScreen("Logging Out In Progress...");

            cout << "Logged Out Successfully!" << endl;

            speak("Logged Out Successfully!");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            clearSession();

            authenticationMenu();

        }

        else if(choice == 6){

            exitWindow();

        }

        else if(choice == -1){

            cout << "Sorry Going Back Isn't Allowed In This Screen!" << endl;

            speak("Sorry Going Back Isn't Allowed In This Screen!");

            if(!VOICE_ENABLED){

                pressToContinue(0);

            }

            continue;

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