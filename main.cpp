#include "utility.h"
#include "authentication.h"




#include <iostream>
using namespace std;





int main(){

    srand(time(NULL));

    loadConfig();
    
    authenticationMenu();

    return 0;

}