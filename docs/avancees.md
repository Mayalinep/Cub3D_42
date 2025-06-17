# Documentation des avancées - Cub3D

## 📅 Date : 16 juin 2025

### ✅ Ce qui est fait :
- Structure de base du projet
- Initialisation MLX
- Gestion des hooks (touches + fermeture)
- Structure combinée `t_game`
- **NOUVEAU** : Compréhension du mouvement 3D
- **NOUVEAU** : Ajout des vecteurs de direction et plan de caméra
- **NOUVEAU** : Implémentation complète du mouvement 3D

### 🎯 En cours :
- **ÉTAPE 3 TERMINÉE** : Implémentation du mouvement 3D
- **PRÊT POUR ÉTAPE 4** : Collisions avec les murs

### 📋 Prochaines étapes :
1. ✅ **Étape 1** : Comprendre les bases du mouvement 3D
2. ✅ **Étape 2** : Modifier les structures de données
3. ✅ **Étape 3** : Implémenter le mouvement (W/S/A/D)
4. **Étape 4** : Ajouter les collisions avec les murs
5. **Étape 5** : Créer le rendu graphique

### 🧠 Concepts compris :
- ✅ Position du joueur (x, y) en double pour fluidité
- ✅ Direction du regard (vecteur dir_x, dir_y)
- ✅ Plan de caméra (plane_x, plane_y) pour FOV
- ✅ Mouvement vs Rotation (W/S = mouvement, A/D = rotation)
- ✅ Vecteurs selon orientation (N: 0,-1, S: 0,1, E: 1,0, W: -1,0)
- ✅ Système de coordonnées (Y augmente vers le bas)
- ✅ **NOUVEAU** : Formules trigonométriques de rotation
  - Formule : nouveau_x = x * cos(θ) - y * sin(θ)
  - Formule : nouveau_y = x * sin(θ) + y * cos(θ)
  - Exemple : Rotation de (0,-1) de 90° donne (1,0)
  - Pourquoi 2D ? Car le jeu est en fait "2.5D" (pseudo-3D)
  - Le joueur ne peut que tourner gauche/droite (pas haut/bas)
- ✅ **NOUVEAU** : Variables à sauvegarder (old_dir_x, old_dir_y, old_plane_x)
  - Nécessaire pour garder les valeurs originales
  - Utilisées dans les deux formules de rotation
  - Évite d'utiliser les nouvelles valeurs par erreur

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
└── utils/string_utils.c (ft_strdup)

main.c (initialisation + hooks + mouvement 3D)
```

### 🔧 Modifications récentes :
- Ajout de `dir_x`, `dir_y` (vecteurs de direction)
- Ajout de `plane_x`, `plane_y` (plan de caméra pour raycasting)
- Position joueur en `double` pour mouvement fluide
- **NOUVEAU** : Fonction `handle_keypress` avec mouvement W/S
- **NOUVEAU** : Fonction `keypress_rotation` avec rotation A/D
- **NOUVEAU** : Gestion de la fermeture ESC

### 🎮 Fonctionnalités implémentées :
- **W/S** : mouvement linéaire selon direction (vitesse 0.1)
- **A/D** : rotation du champ de vision (angle ±0.1 radian)
- **ESC** : fermeture propre de la fenêtre
- **Formules trigonométriques** : rotation des vecteurs dir et plane

### 🎯 Prochain objectif :
**Étape 4 : Collisions avec les murs**
- Vérifier si la nouvelle position est dans un mur
- Empêcher le mouvement en cas de collision
- Garder le mouvement fluide
- Formule : `map[(int)new_y][(int)new_x] != '1'`

### 📚 Documentation créée :
```
docs/
├── avancees.md (suivi général)
└── comprehension/
    ├── etape1_bases_mouvement.md (concepts théoriques)
    ├── etape2_structures_donnees.md (modifications techniques)
    └── etape3_implementation_mouvement.md (implémentation complète)
```

### 🚀 Progression :
- **Étape 1** : ✅ 100% (concepts compris)
- **Étape 2** : ✅ 100% (structures modifiées)
- **Étape 3** : ✅ 100% (mouvement implémenté)
- **Étape 4** : 🎯 0% (collisions à implémenter)
- **Étape 5** : 📋 0% (rendu à créer)

--- 