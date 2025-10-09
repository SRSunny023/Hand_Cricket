#include "settings.h"
#include "utility.h"


#include <iostream>
#include <string>
using namespace std;



void voiceSettings(){

    do{

        clearScreen();

        if(VOICE_ENABLED){

            cout << "Voice Is Currently Enabled!" << endl;

            speak("Voice Is Currently Enabled!");

            int choiceSetting = getIntInput("If You Want To Disable The Voice Please Click 1 If You Want To Go Back Click - : ");

            if(choiceSetting == 1){

                loadingScreen("Setting Application In Progress... ");

                cout << "Voice Successfully Disabled! You Wont Hear Me Again Until You Turn Me On Again" << endl;

                speak("Voice Successfully Disabled! You Wont Hear Me Again Until You Turn Me On Again");

                VOICE_ENABLED = false;

                saveConfig(VOICE_ENABLED);

                cout << "Voice Is Currently DISABLED!" << endl;

            }

            else if(choiceSetting == -1){

                break;

            }

            else{

                cout << "Wrong Input! Choose Only 1" << endl;

                speak("Wrong Input! Choose Only 1");

                continue;

            }

        }

        else{

            cout << "Voice Is Currently DISABLED!" << endl;

            int choiceSetting = getIntInput("If You Want To Enable The Voice Please Click 1 If You Want To Go Back Click - : ");

            if(choiceSetting == 1){

                loadingScreen("Setting Application In Progress... ");

                cout << "Voice Successfully Enabled! You Will Here Me Again Until You Tune Me Off Again" << endl;

                speak("Voice Successfully Enabled! You Will Here Me Again Until You Tune Me Off Again");

                VOICE_ENABLED = true;

                saveConfig(VOICE_ENABLED);

                cout << "Voice Is Currently ENABLED!" << endl;

            }

            else if(choiceSetting == -1){

                break;

            }

            else{

                cout << "Wrong Input! Choose Only 1" << endl;

                speak("Wrong Input! Choose Only 1");

                continue;

            }

        }

    }   while(true);

}