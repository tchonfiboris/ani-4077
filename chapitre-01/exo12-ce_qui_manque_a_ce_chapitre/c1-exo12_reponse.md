

- `le calcul general :` Elles exécutent des calculs massivement parallèles (CUDA, OpenCL) pour la physique, la simulation, la cryptographie. Dans un moteur de jeu il permet de gerer les caluls de simulation des particules, physique(collision, fluides)


- `le lancer de rayon materiel :` Certaines cartes intègrent des unités dédiées (RT cores chez NVIDIA, Ray Accelerators chez AMD). Cela permet de calculer directement les intersections rayons‑scène pour produire des reflets, ombres réalistes et effets de lumière avancés. neamois ma carte ne dispose pas de cette caracterisique. Deplus dans un moteur de jeu il permet le calcul de reflexion, ombres et eclairage global en simulant un vrai trajet de la lumiere.


- `unite dediees a l'apprentissage automatique :` Les GPU récents embarquent des blocs spécialisés pour l’IA (reconnaissance d’image, upscaling DLSS, génération de textures). Ces unités ne se contentent pas de transformer ou colorer. elles exécutent des réseaux de neurones optimisés. mais ma carte ne dispose non plus de cette caracteristique. Dans un moteur de jeu il permet de faire de l'upscaling intelligent.
