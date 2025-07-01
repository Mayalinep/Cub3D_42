# Étape 2 : Modification des structures de données

## 📅 Date : 16 juin 2025

## 🎯 Objectif de cette étape
Modifier les structures de données pour supporter le mouvement 3D fluide.

## 🔧 Modifications apportées

### Structure `t_parsed_data` - Avant
```c
typedef struct s_parsed_data
{
    // Position et orientation du joueur
    int player_x;           // ❌ Mouvement saccadé
    int player_y;           // ❌ Mouvement saccadé
    char player_orientation; // N, S, E, W
    // ... autres champs
} t_parsed_data;
```

### Structure `t_parsed_data` - Après
```c
typedef struct s_parsed_data
{
    // Position et orientation du joueur
    double player_x;        // ✅ Mouvement fluide
    double player_y;        // ✅ Mouvement fluide
    char player_orientation; // N, S, E, W
    
    // NOUVEAU : Vecteurs de direction et plan de caméra
    double dir_x;           // ✅ Direction du regard (vecteur X)
    double dir_y;           // ✅ Direction du regard (vecteur Y)
    double plane_x;         // ✅ Plan de caméra (vecteur X)
    double plane_y;         // ✅ Plan de caméra (vecteur Y)
    
    // ... autres champs
} t_parsed_data;
```

## 📐 Explication des nouveaux champs

### Vecteurs de direction (`dir_x`, `dir_y`)
- **Rôle** : indiquent où le joueur regarde
- **Type** : `double` pour précision
- **Valeurs** : toujours entre -1.0 et 1.0
- **Exemple** : `(0.0, -1.0)` = regarde vers le nord

### Plan de caméra (`plane_x`, `plane_y`)
- **Rôle** : déterminent le champ de vision
- **Type** : `double` pour précision
- **Relation** : perpendiculaire aux vecteurs de direction
- **FOV** : angle de vision (90° par défaut , mais on va prendre 60° pour plus de realisme.)

## 🧮 Calcul du plan de caméra (0.66)

### Fonction trigonométrique `tan`
- **`tan(angle)`** = rapport entre côté opposé et côté adjacent
- **Formule** : `tan(angle) = côté_opposé / côté_adjacent`

### Schéma du triangle rectangle
```
    Côté opposé
        ↕️
    ┌─────────┐
    │    \    │
    │     \   │ ← Hypothénuse
    │      \  │
    │       \ │
    └─────────┘
    Côté adjacent
```

### Calcul pour FOV de 60°
- **FOV** = 60° (champ de vision total)
- **FOV/2** = 30° (moitié du champ de vision)
- **`tan(30°)`** = 0.577... ≈ 0.66
- **Résultat** : `plane_x = 0.66` pour un FOV réaliste

### Valeurs importantes
- **`tan(30°)`** = 0.577... ≈ 0.66 (FOV 60°)
- **`tan(45°)`** = 1.0 (FOV 90°)
- **`tan(60°)`** = 1.732... (FOV 120°)

## 🎮 Initialisation selon l'orientation

### Pour N (Nord)
```c
data->dir_x = 0.0;
data->dir_y = -1.0;
data->plane_x = 0.66;  // tan(30°) ≈ 0.66
data->plane_y = 0.0;
```

### Pour S (Sud)
```c
data->dir_x = 0.0;
data->dir_y = 1.0;
data->plane_x = -0.66;  // opposé du nord
data->plane_y = 0.0;
```

### Pour E (Est)
```c
data->dir_x = 1.0;
data->dir_y = 0.0;
data->plane_x = 0.0;
data->plane_y = 0.66;  // tan(30°) ≈ 0.66
```

### Pour W (Ouest)
```c
data->dir_x = -1.0;
data->dir_y = 0.0;
data->plane_x = 0.0;
data->plane_y = -0.66;  // opposé de l'est
```

## 🔍 Pourquoi ces modifications ?

### 1. Mouvement fluide
- **Avant** : `int` = mouvement case par case
- **Après** : `double` = mouvement continu

### 2. Support du raycasting
- **Vecteurs de direction** : nécessaires pour lancer les rayons
- **Plan de caméra** : détermine l'étendue du champ de vision

### 3. Rotation du joueur
- **Modification des vecteurs** : permet de tourner le regard
- **Calculs trigonométriques** : rotation des vecteurs `dir` et `plane`

## 📁 Impact sur le code

### Fonctions à modifier
1. **`init_test_player`** : initialiser les nouveaux vecteurs
2. **`handle_keypress`** : utiliser les vecteurs pour le mouvement
3. **Futures fonctions de rotation** : modifier les vecteurs

### Structure de données
- **Taille augmentée** : 4 nouveaux champs `double`
- **Compatibilité** : reste compatible avec le parsing existant
- **Extensibilité** : prêt pour le raycasting

## ✅ Validation de l'étape

**Cette étape est réussie si :**
- ✅ Les structures sont modifiées avec les nouveaux champs
- ✅ Les types sont corrects (`double` pour position et vecteurs)
- ✅ La structure reste organisée et lisible
- ✅ Le code compile sans erreur

## 🚀 Prêt pour l'étape suivante

**Prochain objectif :**
- Implémenter `handle_keypress` avec le vrai mouvement 3D
- Utiliser les nouveaux vecteurs pour les calculs
- Ajouter la rotation du joueur

--- 