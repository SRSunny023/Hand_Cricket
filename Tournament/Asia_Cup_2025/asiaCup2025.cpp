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
    
    Tournament T("Asia Cup", "QualifierA");

    T.qualifierA = {Team("Nepal"),Team("HongKong"),Team("Qatar"),Team("SaudiArabia"),Team("Malaysia")};
    T.qualifierB = {Team("Oman"),Team("UAE"),Team("Kuwait"),Team("Bahrain"),Team("Cambodia")};


    // Fixtures Qualifier A
    T.fixtures.push_back({"Malaysia", "Nepal"});
    T.fixtures.push_back({"HongKong", "Qatar"});
    T.fixtures.push_back({"Nepal", "Qatar"});
    T.fixtures.push_back({"Malaysia", "SaudiArabia"});
    T.fixtures.push_back({"SaudiArabia", "HongKong"});
    T.fixtures.push_back({"HongKong", "Nepal"});
    T.fixtures.push_back({"Malaysia", "Qatar"});
    T.fixtures.push_back({"Qatar", "SaudiArabia"});
    T.fixtures.push_back({"Malaysia", "HongKong"});
    T.fixtures.push_back({"SaudiArabia", "Nepal"});

    /*
    // Fixtures Qualifier B
    T.fixtures.push_back({"Oman", "Bahrain"});
    T.fixtures.push_back({"Kuwait", "UAE"});
    T.fixtures.push_back({"Cambodia", "Kuwait"});
    T.fixtures.push_back({"UAE", "Bahrain"});
    T.fixtures.push_back({"Oman", "Cambodia"});
    T.fixtures.push_back({"UAE", "Oman"});
    T.fixtures.push_back({"Kuwait", "Bahrain"});
    T.fixtures.push_back({"Cambodia", "Bahrain"});
    T.fixtures.push_back({"Cambodia", "UAE"});
    T.fixtures.push_back({"Oman", "Kuwait"});
    */

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