#include <iostream>
#include <string>

int main() {

    int n;

    if (!(std::cin >> n)) n = 0;

    int graves = 0; 
    int traites = 0;

    for (int i = 0; i < n; ++i) {

        std::string plateforme, evenement;
        int traite;

        if (!(std::cin >> plateforme >> evenement >> traite)) 
        break;

        std::string consequence;

        if (traite == 1) {
            // le drapeau passe avant la table
            consequence = "OK";
            
        } else if (plateforme == "BUREAU" || plateforme == "MOBILE") {
            bool mobile = (plateforme == "MOBILE");
            if (evenement == "REDIMENSIONNEMENT") {
                consequence = "IMAGE FLOUE";
            } else if (evenement == "PERTE_DE_FOCUS") {
                consequence = mobile ? "BATTERIE VIDEE" : "IMPOLI";
            } else if (evenement == "PERTE_DE_SURFACE") {
                consequence = mobile ? "ECRAN NOIR" : "N ARRIVE PAS";
            } else {
                consequence = "INCONNU";
            }
        } else {
            consequence = "INCONNU";
        }

        if (consequence == "OK"){
             ++traites;}
        if (consequence == "BATTERIE VIDEE" || consequence == "ECRAN NOIR"){
             ++graves;}

        std::cout << plateforme << " " << evenement << " " << consequence << std::endl;
    }

    std::cout << "GRAVES " << graves << std::endl;
    std::cout << "TRAITES " << traites << std::endl;

    return 0;
}
