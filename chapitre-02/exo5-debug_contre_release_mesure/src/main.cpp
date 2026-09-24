#include <iostream>

int AdditionEntier(){
    long a =0;
    for (long i = 1; i <= 100000000; i++){
        a = a + i;
    }
    return a;
}

int main() {

    std::cout << "Hello from exo5-debug_contre_release_mesure!" << std::endl;

    std::cout <<"la somme est :" << AdditionEntier()  << std::endl;

    return 0;
}
