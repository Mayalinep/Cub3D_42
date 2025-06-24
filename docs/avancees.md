# Documentation des avancées - Cub3D

## 📅 Date : 17 juin 2025

### ✅ Ce qui est fait :
- Structure de base du projet
- Initialisation MLX
- Gestion des hooks (touches + fermeture)
- Structure combinée `t_game`
- Compréhension du mouvement 3D
- Ajout des vecteurs de direction et plan de caméra
- Implémentation complète du mouvement 3D
- **NOUVEAU** : Système de touches avancé avec états (press/release)
- **NOUVEAU** : Mouvements fluides et diagonaux possibles
- **NOUVEAU** : Structure de base du raycasting

### 🎯 En cours :
- **ÉTAPE 4 TERMINÉE** : Collisions avec les murs
- **ÉTAPE 5 EN COURS** : Implémentation du raycasting

### 📋 Prochaines étapes :
1. ✅ **Étape 1** : Comprendre les bases du mouvement 3D
2. ✅ **Étape 2** : Modifier les structures de données
3. ✅ **Étape 3** : Implémenter le mouvement (W/S/A/D)
4. ✅ **Étape 4** : Ajouter les collisions avec les murs
5. **Étape 5** : Implémenter le raycasting (en cours)
6. **Étape 6** : Ajouter les textures
7. **Étape 7** : Créer le vrai parsing

### 🧠 Concepts compris :
- Position du joueur (x, y) en double pour fluidité
- Direction du regard (vecteur dir_x, dir_y)
- Plan de caméra (plane_x, plane_y) pour FOV
- Mouvement vs Rotation (W/S = mouvement, A/D = rotation)
- Vecteurs selon orientation (N: 0,-1, S: 0,1, E: 1,0, W: -1,0)
- Système de coordonnées (Y augmente vers le bas)
- Formules trigonométriques de rotation
- Variables à sauvegarder (old_dir_x, old_dir_y, old_plane_x)
- **NOUVEAU** : Système d'états des touches (t_keys)
- **NOUVEAU** : Hooks MLX pour keypress/keyrelease
- **NOUVEAU** : Concepts de base du raycasting
  - Lancement de rayons depuis la position du joueur
  - Calcul de direction du rayon pour chaque colonne
  - Algorithme DDA pour trouver les murs
  - Calcul de distance pour la perspective 3D

### 🎮 Concept du 2.5D :
- Le jeu n'est pas réellement en 3D, c'est une illusion !
- La carte est une grille 2D vue de dessus (comme Pacman)
- Le joueur se déplace uniquement sur le plan X/Y
- L'illusion de 3D est créée par le raycasting :
  - Les murs proches sont dessinés plus grands
  - Les murs lointains sont dessinés plus petits
  - Crée une sensation de profondeur
- C'est pourquoi une rotation 2D suffit :
  - Pas de regard vers le haut/bas
  - Uniquement des rotations gauche/droite
  - Similaire au jeu original Wolfenstein 3D

### 📁 Structure actuelle :
```
include/
├── cub3d.h (structure t_game, t_parsed_data avec vecteurs)
└── mlx.h (structure t_mlx_data, définitions touches)

src/
├── parsing/simulation.c (données de test)
├── input/
│   ├── keyboard_utils.c (gestion des états des touches)
│   ├── movement.c (mouvement et collisions)
│   └── rotation.c (rotation du joueur)
├── raycasting/
│   └── raycasting.c (structure de base du raycasting)
└── utils/string_utils.c (ft_strdup)

main.c (initialisation + hooks + mouvement 3D)
```

### 🔧 Modifications récentes :
- Ajout de `dir_x`, `dir_y` (vecteurs de direction)
- Ajout de `plane_x`, `plane_y` (plan de caméra pour raycasting)
- Position joueur en `double` pour mouvement fluide
- Fonction `handle_keypress` avec mouvement W/S
- Fonction `keypress_rotation` avec rotation A/D
- Gestion de la fermeture ESC
- **NOUVEAU** : Structure `t_keys` pour états des touches
- **NOUVEAU** : Fonctions `handle_keypress` et `handle_keyrelease`
- **NOUVEAU** : Fonction `update_player` pour mouvement continu
- **NOUVEAU** : Hooks MLX configurés (keypress, keyrelease, loop_hook)
- **NOUVEAU** : Structure de base du raycasting
  - `calculate_ray_direction` : calcule la direction du rayon
  - `find_wall_distance` : trouve la distance au mur (à implémenter)
  - `calculate_line_height` : calcule la hauteur de ligne (à implémenter)
  - `ray_casting` : boucle principale du raycasting

### 🎮 Fonctionnalités implémentées :
- **W/S** : mouvement linéaire selon direction (vitesse 0.1)
- **A/D** : rotation du champ de vision (angle ±0.1 radian)
- **ESC** : fermeture propre de la fenêtre
- **Formules trigonométriques** : rotation des vecteurs dir et plane
- **NOUVEAU** : Mouvements fluides avec états des touches
- **NOUVEAU** : Mouvements diagonaux possibles (W+D, etc.)
- **NOUVEAU** : Rotation continue possible
- **NOUVEAU** : Collisions avec les murs (wall_collision)

### 🎯 Prochain objectif :
**Étape 5 : Implémentation complète du raycasting**
- Implémenter l'algorithme DDA dans `find_wall_distance`
- Implémenter le calcul de hauteur dans `calculate_line_height`
- Tester avec des printf avant l'affichage graphique
- Intégrer le raycasting dans le loop_hook

### 📚 Documentation créée :
```
docs/
├── avancees.md (suivi général)
└── comprehension/
    ├── etape1_bases_mouvement.md (concepts théoriques)
    ├── etape2_structures_donnees.md (modifications techniques)
    ├── etape3_implementation_mouvement.md (implémentation complète)
    ├── etape4_collisions.md (gestion des collisions)
    └── etape5_raycasting_base.md (concepts du raycasting)
```

### 🚀 Progression :
- **Étape 1** : ✅ Terminée (concepts compris)
- **Étape 2** : ✅ Terminée (structures modifiées)
- **Étape 3** : ✅ Terminée (mouvement implémenté)
- **Étape 4** : ✅ Terminée (collisions implémentées)
- **Étape 5** : 🎯 En cours (raycasting en cours d'implémentation)
- **Étape 6** : 📋 À faire (textures)
- **Étape 7** : 📋 À faire (parsing)

--- 