#include <iostream>
#include <string>

// Code d'une version : majeur * 10 + mineur.
// Le majeur est le nombre avant le premier point,
// le mineur est le chiffre juste après. Le reste est ignoré.
int codeVersion(const std::string& v)
{
    std::size_t point = v.find('.');
    int majeur = std::stoi(v.substr(0, point));
    int mineur = v[point + 1] - '0';
    return majeur * 10 + mineur;
}

int main()
{
    int n;
    if (!(std::cin >> n)) {
        
         return 0;}

    int acceptables = 0; 
    int suspects = 0; 
    int refuses = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        std::string chemin;
        std::string demande; 
        std::string rapporte;
        std::cin >> nom;
        std::cin >> chemin;
        std::cin >> demande; 
        std::cin >> rapporte;

        int d = codeVersion(demande);
        int r = codeVersion(rapporte);

        std::string verdict;
        if (r < d)
        {
            verdict = "TROP VIEUX";
            ++refuses;
        }
        else if (chemin == "WGL" && r > d)
        {
            verdict = "CONTEXTE PROVISOIRE";
            ++suspects;
        }
        else if (r == d)
        {
            verdict = "EXACT";
            ++acceptables;
        }
        else
        {
            verdict = "ACCEPTE";
            ++acceptables;
        }

        std::cout << nom << " " << d << " " << r << " " << verdict << std::endl;
    }

    std::cout << "ACCEPTABLES " << acceptables << std::endl;
    std::cout << "SUSPECTS " << suspects << std::endl;
    std::cout << "REFUSES " << refuses << std::endl;

    return 0;
}
