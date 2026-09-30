#include <windows.h>
#include <iostream>
#include <iomanip>
#include <cstdint>

static LRESULT CALLBACK ProcFenetre(HWND h, UINT msg, WPARAM w, LPARAM l) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(h);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(h, msg, w, l);
}

static void afficherPoignee(const char* nom, void* valeur) {
    std::cout << "poignee : " << nom << ", valeur : "
              << std::hex << std::setw(16) << std::setfill('0')
              << (unsigned long long)(uintptr_t)valeur
              << std::dec << std::setfill(' ') << std::endl;
}

int main() {
    
    SetProcessDPIAware();  // sinon Windows ment sur les tailles en pixels

    HINSTANCE instance = GetModuleHandleA(nullptr);

    WNDCLASSA classe = {};
    classe.lpfnWndProc = ProcFenetre;
    classe.hInstance = instance;
    classe.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    classe.lpszClassName = "ExoFenetre";
    RegisterClassA(&classe);

    // 1280x720 doit être la zone cliente : on agrandit le rectangle
    // pour la bordure et la barre de titre
    RECT r = {0, 0, 1280, 720};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);

    HWND fenetre = CreateWindowA("ExoFenetre", "Une fenetre et rien dedans",
                                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 r.right - r.left, r.bottom - r.top,
                                 nullptr, nullptr, instance, nullptr);

    // Relevé du descripteur : on lit la vraie taille de la zone cliente
    RECT client = {};
    int largeur = 0; 
    int hauteur = 0; 
    int dpi = 0;

    if (fenetre) {
        GetClientRect(fenetre, &client);
        largeur = client.right - client.left;
        hauteur = client.bottom - client.top;
        dpi = (int)GetDpiForWindow(fenetre) * 1000 / 96;  // 1000 = 96 dpi
    }

    // Test de validité AVANT la boucle
    bool valide = (fenetre != nullptr) && largeur > 0 && hauteur > 0;

    std::cout << "surface : " << largeur << "x" << hauteur
              << ", dpi : " << dpi
              << ", valide : " << (valide ? "oui" : "non") << std::endl;
    afficherPoignee("hwnd", fenetre);
    afficherPoignee("hinstance", instance);
    std::cout.flush();

     if (!valide) return 1; 

    // Boucle : la pompe d'événements tourne à chaque tour
    long long images = 0;
    bool continuer = true;
    while (continuer) {
        MSG msg;
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) continuer = false;
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        ++images;
        Sleep(1);
    }

    std::cout << "images : " << images << std::endl;
    UnregisterClassA("ExoFenetre", instance);

    return 0;
}
