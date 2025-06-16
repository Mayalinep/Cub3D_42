# Documentation des avancées - Cub3D

## 📅 Date : 16 juin 2025

### ✅ Ce qui est fait :
- Structure de base du projet
- Initialisation MLX
- Gestion des hooks (touches + fermeture)
- Structure combinée `t_game`
- **NOUVEAU** : Compréhension du mouvement 3D
- **NOUVEAU** : Ajout des vecteurs de direction et plan de caméra

### 🎯 En cours :
- **ÉTAPE 2 TERMINÉE** : Modification des structures de données
- **PRÊT POUR ÉTAPE 3** : Implémentation du mouvement

### 📋 Prochaines étapes :
1. ✅ **Étape 1** : Comprendre les bases du mouvement 3D
2. ✅ **Étape 2** : Modifier les structures de données
3. **Étape 3** : Implémenter le mouvement (W/S/A/D)
4. **Étape 4** : Tester et documenter

### 🧠 Concepts compris :
- ✅ Position du joueur (x, y) en double pour fluidité
- ✅ Direction du regard (vecteur dir_x, dir_y)
- ✅ Plan de caméra (plane_x, plane_y) pour FOV
- ✅ Mouvement vs Rotation (W/S = mouvement, A/D = rotation)
- ✅ Vecteurs selon orientation (N: 0,-1, S: 0,1, E: 1,0, W: -1,0)
- ✅ Système de coordonnées (Y augmente vers le bas)

### 📁 Structure actuelle :
```
include/
├── cub3d.h (structure t_game, t_parsed_data avec vecteurs)
└── mlx.h (structure t_mlx_data, définitions touches)

src/
├── parsing/simulation.c (données de test)
└── utils/string_utils.c (ft_strdup)

main.c (initialisation + hooks)
```

### 🔧 Modifications récentes :
- Ajout de `dir_x`, `dir_y` (vecteurs de direction)
- Ajout de `plane_x`, `plane_y` (plan de caméra pour raycasting)
- Position joueur en `double` pour mouvement fluide

### 🎮 Prochain objectif :
Implémenter `handle_keypress` avec :
- W/S : mouvement linéaire selon direction
- A/D : rotation du champ de vision
- Collision avec les murs

--- 