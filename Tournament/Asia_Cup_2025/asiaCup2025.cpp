#include "asiaCup2025.h"
#include "../Engine/tournamentEngine.h"
#include "../../Authentication/loginSystem.h"
#include "../../Utility/utility.h"






#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;




/****************************************************************************************************/
/* Structure Name: setupAsiaCup                                                                     */
/****************************************************************************************************/

Tournament setupAsiaCup() {
    
    Tournament T("Asia Cup");

    T.groupA = {Team("India"),Team("Pakistan"),Team("UAE"),Team("Oman")};
    T.groupB = {Team("Bangladesh"),Team("SriLanka"),Team("Afghanistan"),Team("Hongkong")};

    // Fixtures Group A
    T.fixtures.push_back({"India", "Pakistan"});
    T.fixtures.push_back({"India", "UAE"});
    T.fixtures.push_back({"India", "Oman"});
    T.fixtures.push_back({"Pakistan", "UAE"});
    T.fixtures.push_back({"Pakistan", "Oman"});
    T.fixtures.push_back({"UAE", "Oman"});

    // Fixtures Group B
    T.fixtures.push_back({"Bangladesh", "SriLanka"});
    T.fixtures.push_back({"Bangladesh", "Afghanistan"});
    T.fixtures.push_back({"Bangladesh", "Hongkong"});
    T.fixtures.push_back({"SriLanka", "Afghanistan"});
    T.fixtures.push_back({"SriLanka", "Hongkong"});
    T.fixtures.push_back({"Afghanistan", "Hongkong"});

    return T;
}

Tournament resetTournament(const string &name) {
    
    return setupAsiaCup();

}











void asiaCupMenu(string userTeam) {
    
    int choice;

    static Tournament asia = setupAsiaCup();
    
    do {
        
        clearScreen();
        
        cout << "------------------" << asia.name << " Menu ------------------\n\n\n";

        cout << "Your Team: " << userTeam << " \n\n";
        
        cout << "1. Play Next Match\n\n2. See Fixture\n\n3. See Points Table\n\n4. Reset\n\n5. Back\n\n";
        
        choice = getIntInput("Enter Your Choice: ");

        switch(choice) {
            
            case 1: clearScreen(); playNextFixture(asia, userTeam); pressToContinue(); break;
            
            case 2: clearScreen(); showFixtures(asia); pressToContinue(); break;
            
            case 3: clearScreen(); showPointsTable(asia); pressToContinue(); break;
            
            case 4: clearScreen(); asia = resetTournament(asia.name); cout << "Tournament Reset!\n"; pressToContinue(); break;
            
            case 5: clearScreen(); cout << "Returning...\n"; pressToContinue(); break;
            
            default: clearScreen(); cout << "Invalid choice!\n"; pressToContinue(); break;
        
        }

    } while(choice != 5);

}