#include <iostream>
#include "include.h"



int main() {
    long long c;
    int n;
    if (!(std::cin >> c >> n)){
         return 0;}
    if (c < 1){
         c = 1;}
    if (n < 0){
         n = 0;}

    std::vector<long long> arrivees;

    for (int i = 0; i < n; ++i) {
        long long a;
        if (!(std::cin >> a)) 
        break;
        arrivees.push_back(a);
    }

    afficher("WHILE", simuler(c, arrivees, true));
    afficher("IF", simuler(c, arrivees, false));
    
    return 0;
}
