#include <iostream>
#include "funzionilimoncello.h"
using namespace std;
Tentativi tentativo1 = {95, 100, 130};

int main() {
    cout << tentativo1.gradazione << endl;
    Tentativi tentativo2(tentativo1, 100.0);
    tentativo2.displayValori();
    Tentativi tentativo3(100.0,35.0,0.40);
    tentativo3.displayValori();
    return 0;
}
