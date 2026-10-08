#include <iostream>
#include <map>
#include <string>

int main()
{
    int n;
    if (!(std::cin >> n))
    {
        n = 0;
    }

    bool dc = false; 
    bool format = false;
    bool wglCharge = false; 
    bool glCharge = false;
    std::map<std::string, bool> contextes; 
    std::string courant = "";             
    int erreurs = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::string cmd;
        std::string nom;
        std::cin >> cmd;
        if (cmd != "GETDC" && cmd != "FORMAT" && cmd != "CHARGER_WGL" && cmd != "CHARGER_GL")
            std::cin >> nom;

        std::string res = "OK";

        if (cmd == "GETDC")
        {
            dc = true;
        }
        else if (cmd == "FORMAT")
        {
            if (!dc)
            { 
                res = "ERREUR PAS DE DC";
            }
            else if (format) 
            {
                res = "ERREUR FORMAT DEJA POSE";
            }
            else 
            {
                format = true;
            }
        }
        else if (cmd == "CREER")
        {
            if (!format) 
            {
                res = "ERREUR PAS DE FORMAT";
            }
            else if (contextes.count(nom)) 
            {
                res = "ERREUR NOM PRIS";
            }
            else 
            {
                contextes[nom] = false;
            }
        }
        else if (cmd == "CREER_ATTRIBS")
        {
            if (!format) 
            {
                res = "ERREUR PAS DE FORMAT";
            }
            else if (!wglCharge) 
            {
                res = "ERREUR EXTENSION NON CHARGEE";
            }
            else if (contextes.count(nom)) 
            {
                res = "ERREUR NOM PRIS";
            }
            else 
            {
                contextes[nom] = true;
            }
        }
        else if (cmd == "COURANT")
        {
            if (nom == "AUCUN") 
            {
                courant = "";
            }
            else if (!contextes.count(nom)) 
            {
                res = "ERREUR CONTEXTE INCONNU";
            }
            else 
            {
                courant = nom;
            }
        }
        else if (cmd == "CHARGER_WGL" || cmd == "CHARGER_GL")
        {
            if (courant.empty())
            { 
                res = "ERREUR PAS DE CONTEXTE COURANT";
            }
            else if (cmd == "CHARGER_WGL") 
            {
                wglCharge = true;
            }
            else 
            {
                glCharge = true;
            }
        }
        else if (cmd == "DETRUIRE")
        {
            if (!contextes.count(nom)) 
            {
                res = "ERREUR CONTEXTE INCONNU";
            }
            else if (courant == nom) 
            {
                res = "ERREUR CONTEXTE COURANT";
            }
            else 
            {
                contextes.erase(nom);
            }
        }
        else if (cmd == "GL")
        {
            if (courant.empty() || !glCharge) 
            {
                res = "PLANTAGE ADRESSE ZERO";
            }
        }

        if (res != "OK")
        { 
            ++erreurs;
        }
        std::cout << i << " " << res << std::endl;
    }

    std::string profil = "AUCUN";
    if (!courant.empty())
        profil = contextes[courant] ? "CORE" : "COMPATIBILITE";

    std::cout << "ERREURS " << erreurs << std::endl;
    std::cout << "COURANT " << (courant.empty() ? "AUCUN" : courant) << std::endl;
    std::cout << "PROFIL " << profil << std::endl;
    std::cout << "VIVANTS " << contextes.size() << std::endl;

    return 0;
}
