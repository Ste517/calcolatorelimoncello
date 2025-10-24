#include <iostream>
#include "funzionilimoncello.h"
using namespace std;
Tentativi tentativo1 = {95, 100, 130};

int main() {
    Tentativi tentativo2 = creaTentativoDaObiettivi(50, 30, 0.35);
    tentativo2.displayValori();
    return 0;
}
