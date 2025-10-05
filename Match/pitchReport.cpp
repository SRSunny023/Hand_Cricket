#include "pitchReport.h"
#include "utility.h"


#include <iostream>
#include <string>
using namespace std;



void pitchReport(string pitch, int temparature, int rainProbability){

    clearScreen();
    
    cout << "------------------------------------------------------------\n";
    cout << "                      Pitch Report                          \n";
    cout << "------------------------------------------------------------\n\n";
    
    cout << "Pitch : " << pitch << " \n";

    cout << "Temparature (Celcius) : " << temparature << " \n";

    cout << "Rain Probability : " << rainProbability << " \n";

    cout << "------------------------------------------------------------\n\n";

}