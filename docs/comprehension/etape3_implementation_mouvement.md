# Étape 3 : Implémentation du mouvement 3D

## 📅 Date : 16 juin 2025

## 🎯 Objectif de cette étape
Implémenter le mouvement 3D fluide avec rotation dans `handle_keypress`.

## 🧠 Concepts implémentés

### 1. Mouvement linéaire (W/S)
- **W** : avancer dans la direction du regard
- **S** : reculer (opposé de la direction)
- **Formule** : `nouvelle_position = position + (direction * vitesse)`

### 2. Rotation (A/D)
- **A** : tourner à gauche (rotation négative)
- **D** : tourner à droite (rotation positive)
- **Formules trigonométriques** pour rotation des vecteurs

### 3. Vitesse de mouvement
- **Mouvement** : `0.1` (petite valeur pour fluidité)
- **Rotation** : `0.1` radian (~6 degrés)

## 📐 Formules mathématiques

### Mouvement linéaire
```c
// Avancer (W)
new_x = player_x + (dir_x * speed);
new_y = player_y + (dir_y * speed);

// Reculer (S)
new_x = player_x - (dir_x * speed);
new_y = player_y - (dir_y * speed);
```

### Rotation des vecteurs
```c
// Sauvegarder les anciennes valeurs
old_dir_x = dir_x;
old_dir_y = dir_y;
old_plane_x = plane_x;

// Nouvelle direction
dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);

// Nouveau plan de caméra
plane_x = old_plane_x * cos(angle) - plane_y * sin(angle);
plane_y = old_plane_x * sin(angle) + plane_y * cos(angle);
```

## 🎮 Implémentation dans le code

### Fonction `handle_keypress`
```c
int handle_keypress(int keycode, t_game *game)
{
    double speed = 0.1;
    
    if (keycode == KEY_W)
    {
        game->parsed_data.player_x += game->parsed_data.dir_x * speed;
        game->parsed_data.player_y += game->parsed_data.dir_y * speed;
    }
    if (keycode == KEY_S)
    {
        game->parsed_data.player_x -= game->parsed_data.dir_x * speed;
        game->parsed_data.player_y -= game->parsed_data.dir_y * speed;
    }
    if (keycode == KEY_A || keycode == KEY_D)
        keypress_rotation(keycode, game);
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
        exit(0);
    }
    return (0);
}
```

### Fonction `keypress_rotation`
```c
int keypress_rotation(int keycode, t_game *game)
{
    double old_dir_x = game->parsed_data.dir_x;
    double old_dir_y = game->parsed_data.dir_y;
    double old_plane_x = game->parsed_data.plane_x;
    double angle;
    
    if (keycode == KEY_A)
    {
        angle = -0.1;  // Rotation gauche (négatif)
        game->parsed_data.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
        game->parsed_data.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
        game->parsed_data.plane_x = old_plane_x * cos(angle) - game->parsed_data.plane_y * sin(angle);
        game->parsed_data.plane_y = old_plane_x * sin(angle) + game->parsed_data.plane_y * cos(angle);
    }
    if (keycode == KEY_D)
    {
        angle = 0.1;   // Rotation droite (positif)
        game->parsed_data.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
        game->parsed_data.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
        game->parsed_data.plane_x = old_plane_x * cos(angle) - game->parsed_data.plane_y * sin(angle);
        game->parsed_data.plane_y = old_plane_x * sin(angle) + game->parsed_data.plane_y * cos(angle);
    }
    return (0);
}
```

## 🔍 Points importants

### Variables à sauvegarder
- **`old_dir_x`** : nécessaire pour calculer `dir_y`
- **`old_dir_y`** : nécessaire pour calculer `dir_x`
- **`old_plane_x`** : nécessaire pour calculer `plane_y`
- **`plane_y`** : pas besoin de sauvegarder (utilisé directement)

### Angles de rotation
- **A (gauche)** : `-0.1` radian (rotation négative)
- **D (droite)** : `0.1` radian (rotation positive)
- **0.1 radian** ≈ 5.7 degrés

### Fonctions trigonométriques
- **`cos(angle)`** : cosinus de l'angle
- **`sin(angle)`** : sinus de l'angle
- **Nécessaire** : `#include <math.h>` et compiler avec `-lm`

## ❓ Problèmes résolus

### 1. Formules de rotation
- **Problème** : confusion sur les variables à sauvegarder
- **Solution** : utiliser `old_dir_x`, `old_dir_y`, `old_plane_x`

### 2. Variables manquantes
- **Problème** : `old_plane_y` n'existe pas
- **Solution** : utiliser directement `game->parsed_data.plane_y`

### 3. Angles de rotation
- **Problème** : quelle valeur choisir pour l'angle
- **Solution** : 0.1 radian (bon compromis vitesse/précision)

## ✅ Validation de l'étape

**Cette étape est réussie si :**
- ✅ Le mouvement W/S fonctionne (avancer/reculer)
- ✅ La rotation A/D fonctionne (tourner gauche/droite)
- ✅ Les formules trigonométriques sont correctes
- ✅ Le code compile sans erreur
- ✅ ESC ferme proprement la fenêtre

## 🚀 Prochaines étapes

### Étape 4 : Collisions avec les murs
- Vérifier si la nouvelle position est dans un mur
- Empêcher le mouvement en cas de collision
- Garder le mouvement fluide

### Étape 5 : Rendu graphique
- Créer une fonction de rendu
- Afficher quelque chose à l'écran
- Tester le mouvement visuellement

## 📁 Fichiers modifiés

### `main.c`
- Ajout de `handle_keypress` avec mouvement W/S
- Ajout de `keypress_rotation` avec rotation A/D
- Gestion de la fermeture ESC

### `include/cub3d.h`
- Structures déjà modifiées dans l'étape 2
- Prêt pour les collisions

--- 