#include <iostream>
#include "register.hpp"

int main(void) {
    Register r;
    r.readToRegister("readtester2.txt");
    r.Print();
    r.Add(new Aircraft("G_BOAC", "British Airways", "Concorde SST", 80.8, 2000));
    r.Add(new Car("YUU-123", "Teemu Teekkari", "Volkswagen Polo", 800, true));
    r.Add(new Aircraft("RU-123", "Russian Federation", "MiG-21", 80.8, 1600));
    r.Add(new Car("EES-321", "Nikola", "Tesla", 600, false));
    r.Add(new Boat("FI123", "Pekka Purjehtija", "Mariella", 0.0, 1.8));
    r.outputAll("test2.txt");
    r.Print();
}
