#include "t20wc.h"
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
/* Structure Name: setupT20WorldCup                                                                 */
/****************************************************************************************************/

Tournament setupT20WorldCup() {
    
    Tournament T("T20 World Cup", "Group");

    T.groupA = { {"India"}, {"Pakistan"}, {"Ireland"}, {"USA"}, {"Canada"} };
    T.groupB = { {"Australia"}, {"England"}, {"Scotland"}, {"Oman"}, {"Namibia"} };
    T.groupC = { {"NewZealand"}, {"SouthAfrica"}, {"SriLanka"}, {"Bangladesh"}, {"Netherlands"} };
    T.groupD = { {"Afghanistan"}, {"WestIndies"}, {"Zimbabwe"}, {"Nepal"}, {"UAE"} };

    T.fixtures.clear();
    auto makeFixtures=[&](vector<Team> &g){
        for(size_t i=0;i<g.size();i++)
            for(size_t j=i+1;j<g.size();j++)
                T.fixtures.push_back({g[i].name,g[j].name});
    };
    makeFixtures(T.groupA);
    makeFixtures(T.groupB);
    makeFixtures(T.groupC);
    makeFixtures(T.groupD);

    return T;
}


Tournament resetTournamentT20WorldCup(const string &name) {
    
    return setupT20WorldCup();

}





void t20WorldCupMenu(string userTeam, int ball) {
    
    int choice;

    static Tournament t20WorldCup;

    ifstream fin("Database/t20_world_cup_save.txt");
    string tournamentName;
    if(fin >> tournamentName && !tournamentName.empty()){

        fin.close();

        t20WorldCup = loadTournament("T20 World Cup");

        cout << "Loaded Previous Tournament!\n";

        pressToContinue();

    }
    else{

        t20WorldCup = setupT20WorldCup();

    }

    
    do {
        
        clearScreen();
        
        cout << "------------------" << t20WorldCup.name << " Menu ------------------\n\n\n";

        cout << "Your Team: " << userTeam << " \nOver: " << ball/6 << " Over!\n\n";
        
        cout << "1. Play Next Match\n\n2. See Fixture\n\n3. See Points Table\n\n4. Reset\n\n5. Back\n\n";
        
        choice = getIntInput("Enter Your Choice: ");

        switch(choice) {
            
            case 1: clearScreen(); playNextFixture(t20WorldCup, userTeam, ball); pressToContinue(); saveTournament(t20WorldCup); break;
            
            case 2: clearScreen(); showFixtures(t20WorldCup); pressToContinue(); break;
            
            case 3: clearScreen(); showPointsTable(t20WorldCup); pressToContinue(); break;
            
            case 4: clearScreen(); t20WorldCup = resetTournamentT20WorldCup(t20WorldCup.name); cout << "Tournament Reset!\n"; pressToContinue(); break;
            
            case 5: clearScreen(); cout << "Returning...\n"; pressToContinue(); break;
            
            default: clearScreen(); cout << "Invalid choice!\n"; pressToContinue(); break;
        
        }

    } while(choice != 5);

}