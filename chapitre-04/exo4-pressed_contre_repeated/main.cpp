#include <iostream>
#include <algorithm>

// Nombre d'images k, avec 0 <= k <= n-1, dont l'instant k*t tombe dans [a, b)
static long long imagesDans(long long a, long long b, long long t, long long n) {
    long long lo = (a + t - 1) / t;       // première image à l'instant >= a
    long long hi = (b + t - 1) / t - 1;   // dernière image à l'instant < b
    if (hi > n - 1) {
        hi = n - 1;}
    if (lo < 0) {
        lo = 0;}
        
    return std::max(0LL, hi - lo + 1);
}

int main() {

    long long t; 
    long long d; 
    long long p; 
    long long n; 

    if (!(std::cin >> t >> d >> p >> n)){
         return 0;}

    int m;

    if (!(std::cin >> m)){ 
        m = 0;}

    long long totalPressed = 0; 
    long long totalRepeated = 0; 
    long long totalCaracteres = 0;

    for (int i = 1; i <= m; ++i) {

        long long debut; 
        long long fin;
        if (!(std::cin >> debut >> fin)) 
        break;

        long long pressed = imagesDans(debut, fin, t, n);
        long long repeated = imagesDans(debut + d, fin, t, n);

        // Répétitions aux instants debut + d + j*p, tant qu'ils sont < fin
        long long reps = 0;
        if (debut + d < fin){
             reps = (fin - 1 - (debut + d)) / p + 1;}

        long long caracteres = 1 + reps;

        std::cout << "APPUI " << i << " PRESSED " << pressed
                  << " REPEATED " << repeated
                  << " CARACTERES " << caracteres << " RETARD ";

        if (repeated == 0) {
            std::cout << "JAMAIS";
        } else {
            long long premierePressed = (debut + t - 1) / t;
            long long premiereRepeated = (debut + d + t - 1) / t;
            std::cout << premiereRepeated - premierePressed;
        }
        std::cout << std::endl;

        totalPressed += pressed;
        totalRepeated += repeated;
        totalCaracteres += caracteres;
    }

    std::cout << "PRESSED " << totalPressed << std::endl;
    std::cout << "REPEATED " << totalRepeated << std::endl;
    std::cout << "CARACTERES " << totalCaracteres << std::endl;

    return 0;
}
