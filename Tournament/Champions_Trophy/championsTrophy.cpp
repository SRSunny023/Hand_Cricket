#include "championsTrophy.h"
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
#include <fstream>
using namespace std;









/****************************************************************************************************/
/* Structure Name: setupChampionsTrophy                                                             */
/****************************************************************************************************/

Tournament setupChampionsTrophy() {
    
    Tournament T("Champions Trophy", "Group");

    T.groupA = {Team("India"),Team("Pakistan"),Team("Bangladesh"),Team("NewZealand")};
    T.groupB = {Team("Australia"),Team("England"),Team("SouthAfrica"),Team("Afghanistan")};

    // Fixtures Group A
    T.fixtures.push_back({"India", "Pakistan"});
    T.fixtures.push_back({"India", "Bangladesh"});
    T.fixtures.push_back({"India", "NewZealand"});
    T.fixtures.push_back({"Pakistan", "Bangladesh"});
    T.fixtures.push_back({"Pakistan", "NewZealand"});
    T.fixtures.push_back({"Bangladesh", "NewZealand"});

    // Fixtures Group B
    T.fixtures.push_back({"Australia", "England"});
    T.fixtures.push_back({"Australia", "SouthAfrica"});
    T.fixtures.push_back({"Australia", "Afghanistan"});
    T.fixtures.push_back({"England", "SouthAfrica"});
    T.fixtures.push_back({"England", "Afghanistan"});
    T.fixtures.push_back({"SouthAfrica", "Afghanistan"});

    return T;
}


Tournament resetTournamentChampionsTrophy(const string &name) {
    
    return setupChampionsTrophy();

}





void championsTrophyMenu(string userTeam, int ball) {
    
    int choice;

    static Tournament championsTrophy;

    ifstream fin("Database/champions_trophy_save.txt");
    string tournamentName;
    if(fin >> tournamentName && !tournamentName.empty()){

        fin.close();

        championsTrophy = loadTournament("Champions Trophy");

        cout << "Loaded Previous Tournament!\n";

        pressToContinue();

    }
    else{

        championsTrophy = setupChampionsTrophy();

    }

    
    do {
        
        clearScreen();
        
        cout << "------------------" << championsTrophy.name << " Menu ------------------\n\n\n";

        cout << "Your Team: " << userTeam << " \nOver: " << ball/6 << " Over!\n\n";
        
        cout << "1. Play Next Match\n\n2. See Fixture\n\n3. See Points Table\n\n4. Reset\n\n5. Back\n\n";
        
        choice = getIntInput("Enter Your Choice: ");

        switch(choice) {
            
            case 1: clearScreen(); playNextFixture(championsTrophy, userTeam, ball); pressToContinue(); saveTournament(championsTrophy); break;
            
            case 2: clearScreen(); showFixtures(championsTrophy); pressToContinue(); break;
            
            case 3: clearScreen(); showPointsTable(championsTrophy); pressToContinue(); break;
            
            case 4: clearScreen(); championsTrophy = resetTournamentChampionsTrophy(championsTrophy.name); cout << "Tournament Reset!\n"; pressToContinue(); break;
            
            case 5: clearScreen(); cout << "Returning...\n"; pressToContinue(); break;
            
            default: clearScreen(); cout << "Invalid choice!\n"; pressToContinue(); break;
        
        }

    } while(choice != 5);

}