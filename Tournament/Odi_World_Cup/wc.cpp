#include "wc.h"
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
/* Structure Name: setupWorldCup                                                                    */
/****************************************************************************************************/

Tournament setupWorldCup() {
    
    Tournament T("World Cup", "QualifierA");

    T.qualifierA = {Team("NewZealand"),Team("Australia"),Team("SriLanka"),Team("Bangladesh"),Team("England"),Team("Afghanistan"),Team("Scotland")};
    T.qualifierB = {Team("India"),Team("SouthAfrica"),Team("Pakistan"),Team("WestIndies"),Team("Ireland"),Team("Zimbabwe"),Team("Netherlands")};

    
    for (size_t i = 0; i < T.qualifierA.size(); i++)
        for (size_t j = i + 1; j < T.qualifierA.size(); j++)
            T.fixtures.push_back({T.qualifierA[i].name, T.qualifierA[j].name});

    
    return T;
}


Tournament resetTournamentWorldCup(const string &name) {
    
    return setupWorldCup();

}





void worldCupMenu(string userTeam, int ball) {
    
    int choice;

    static Tournament worldCup;

    ifstream fin("Database/world_cup_save.txt");
    string tournamentName;
    if(fin >> tournamentName && !tournamentName.empty()){

        fin.close();

        worldCup = loadTournament("World Cup");

        cout << "Loaded Previous Tournament!\n";

        pressToContinue();

    }
    else{

        worldCup = setupWorldCup();

    }

    
    do {
        
        clearScreen();
        
        cout << "------------------" << worldCup.name << " Menu ------------------\n\n\n";

        cout << "Your Team: " << userTeam << " \nOver: " << ball/6 << " Over!\n\n";
        
        cout << "1. Play Next Match\n\n2. See Fixture\n\n3. See Points Table\n\n4. Reset\n\n5. Back\n\n";
        
        choice = getIntInput("Enter Your Choice: ");

        switch(choice) {
            
            case 1: clearScreen(); playNextFixture(worldCup, userTeam, ball); pressToContinue(); saveTournament(worldCup); break;
            
            case 2: clearScreen(); showFixtures(worldCup); pressToContinue(); break;
            
            case 3: clearScreen(); showPointsTable(worldCup); pressToContinue(); break;
            
            case 4: clearScreen(); worldCup = resetTournamentWorldCup(worldCup.name); cout << "Tournament Reset!\n"; pressToContinue(); break;
            
            case 5: clearScreen(); cout << "Returning...\n"; pressToContinue(); break;
            
            default: clearScreen(); cout << "Invalid choice!\n"; pressToContinue(); break;
        
        }

    } while(choice != 5);

}