
### ce qu'il faudrait ecrire si je ne recevais pas `NKWindows`, `NKEvent`, `NKMath`, `NKGlad`, `jenga` ###

**NKWindows :**  Si vous ne la receviez pas, il faudrait écrire un gestionnaire de fenêtre natif (Win32, X11, Cocoa). Estimer a plusieurs centaines de lignes, car il faut gérer création, événements, destruction.
**NKEvent :**  Sans eux, il faudrait interroger directement le système d’exploitation pour chaque périphérique.Estimer a quelques centaines de lignes pour un support basique, plus si multiplateforme.
**NKMath :** Si elles n’étaient pas fournies, il faudrait coder une bibliothèque de calcul matriciel et vectoriel. Estimer a quelques dizaines à centaines de lignes selon le niveau (2D, 3D, transformations).
**NKGlad :** Sans eux, il faudrait déclarer manuellement toutes les fonctions et constantes de l’API.
Estimer a plusieurs milliers de lignes, car OpenGL est vaste.