# Documentation des avancées - Cub3D

## 📅 Date : [Date actuelle]

### ✅ Ce qui est fait :
- Structure de base du projet
- Initialisation MLX
- Gestion des hooks (touches + fermeture)
- Structure combinée `t_game`

### 🎯 En cours :
- Compréhension du mouvement 3D
- Modification des structures pour le mouvement fluide

### 📋 Prochaines étapes :
1. **Étape 1** : Comprendre les bases du mouvement 3D
2. **Étape 2** : Modifier les structures de données
3. **Étape 3** : Implémenter le mouvement
4. **Étape 4** : Tester et documenter

### 🧠 Concepts à comprendre :
- Position du joueur (x, y)
- Direction du regard (vecteur)
- Mouvement vs Rotation
- Coordonnées en double pour fluidité

### 📁 Structure actuelle :
```
include/
├── cub3d.h (structure t_game, t_parsed_data)
└── mlx.h (structure t_mlx_data, définitions touches)

src/
├── parsing/simulation.c (données de test)
└── utils/string_utils.c (ft_strdup)

main.c (initialisation + hooks)
```

--- 