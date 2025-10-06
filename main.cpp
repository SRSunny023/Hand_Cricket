#include "Menu/menu.h"
#include "Match/battingEngine.h"




#include <iostream>
using namespace std;





int main(){

    srand(time(NULL));

    loadSounds();
    
    account_menu();

    return 0;

}