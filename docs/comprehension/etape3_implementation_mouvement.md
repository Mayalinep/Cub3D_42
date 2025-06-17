# Étape 3 : Implémentation du mouvement avancé

## 📅 Date : 17 juin 2025

## 🎯 Objectif de cette étape
Implémenter un système de mouvement fluide et réactif avec :
- Gestion d'état des touches (press/release)
- Mouvements simultanés (diagonaux possibles)
- Hooks MLX pour une meilleure réactivité

## 🔧 Organisation des fichiers

### Structure du code

## 🧠 Concepts implémentés

### 1. Mouvement linéaire (W/S)
- **W** : avancer dans la direction du regard (`dir_x`, `dir_y`)
- **S** : reculer (opposé de la direction)
- **Formule** : `position += direction * vitesse`

### 2. Strafe latéral (A/D)
- **A** : déplacement latéral gauche avec `plane_x`, `plane_y`
- **D** : déplacement latéral droit avec `plane_x`, `plane_y`
- **Formule** : `position += plan_camera * vitesse`

### 3. Rotation (Flèches)
- **Flèche gauche** : rotation négative (-0.1 radian)
- **Flèche droite** : rotation positive (0.1 radian)
- **Formules trigonométriques** pour rotation des vecteurs

### 4. Vitesse de mouvement
- **Mouvement** : `0.1` (petite valeur pour fluidité)
- **Rotation** : `0.1` radian (~6 degrés)

## 🎓 Comprendre le strafe et la rotation

### Pourquoi utiliser le plan de caméra pour le strafe ?
- Le plan de caméra est **perpendiculaire** à la direction du regard
- Parfait pour le déplacement latéral (gauche/droite)
- Exemple : 
  - Si on regarde vers le nord (0, -1)
  - Le plan de caméra est (0.66, 0)
  - Strafe = déplacement sur l'axe X

### Explication de la formule de rotation
```
nouveau_x = x * cos(θ) - y * sin(θ)
nouveau_y = x * sin(θ) + y * cos(θ)
```

## 📐 Organisation du code

### 1. Fichiers séparés
```
src/input/
├── keyboard_utils.c  // Gestion des états des touches
├── movement.c        // Logique de mouvement et collisions
└── rotation.c        // Gestion de la rotation
```

### 2. Fonction try_move (générique)
```c
int try_move(t_game *game, double dir_x, double dir_y)
{
    double new_x = player_x + dir_x * speed;
    double new_y = player_y + dir_y * speed;
    
    if (!wall_collision(new_x, new_y, &game->parsed_data))
    {
        game->parsed_data.player_x = new_x;
        game->parsed_data.player_y = new_y;
        return (1);
    }
    return (0);
}
```

### 3. Handler de touches
```c
if (keycode == KEY_W)
    try_move(game, game->parsed_data.dir_x, game->parsed_data.dir_y);
if (keycode == KEY_S)
    try_move(game, -game->parsed_data.dir_x, -game->parsed_data.dir_y);
if (keycode == KEY_A)
    try_move(game, -game->parsed_data.plane_x, -game->parsed_data.plane_y);
if (keycode == KEY_D)
    try_move(game, game->parsed_data.plane_x, game->parsed_data.plane_y);
if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
    keypress_rotation(keycode, game);
```

## ✅ Points importants

### Variables à sauvegarder pour la rotation
- **`old_dir_x`**, **`old_dir_y`** : nécessaires pour les calculs de rotation
- **`old_plane_x`** : nécessaire pour le plan de caméra
- Évite d'utiliser les nouvelles valeurs par erreur

### Angles de rotation
- **Flèche gauche** : `-0.1` radian (rotation négative)
- **Flèche droite** : `0.1` radian (rotation positive)

## ❓ Problèmes résolus

### 1. Clarification du strafe
- Utilisation du plan de caméra pour le déplacement latéral
- Distinction claire entre mouvement et rotation

### 2. Organisation du code
- Séparation en fichiers logiques
- Fonction générique pour tous les mouvements

### 3. Gestion des touches
- W/S pour avancer/reculer
- A/D pour strafe gauche/droite
- Flèches pour la rotation

## ✅ Validation de l'étape

**Cette étape est réussie si :**
- ✅ Le mouvement W/S fonctionne (avancer/reculer)
- ✅ Le strafe A/D fonctionne (déplacement latéral)
- ✅ La rotation avec les flèches fonctionne
- ✅ Le code est bien organisé en fichiers séparés
- ✅ Les formules trigonométriques sont correctes

## 🚀 Prochaine étape

### Étape 4 : Collisions avec les murs
- Améliorer la détection de collision
- Gérer les cas limites (bords de map)
- Optimiser la fluidité du mouvement

## 📁 Fichiers modifiés

### `main.c`
- Ajout de `handle_keypress` avec mouvement W/S
- Ajout de `keypress_rotation` avec rotation A/D
- Gestion de la fermeture ESC

### `include/cub3d.h`
- Structures déjà modifiées dans l'étape 2
- Prêt pour les collisions

## 💡 Système d'états des touches

### 1. Structure t_keys
```c
typedef struct s_keys
{
    int w_press;    // État touche W
    int a_press;    // État touche A
    int s_press;    // État touche S
    int d_press;    // État touche D
    int l_press;    // État flèche gauche
    int r_press;    // État flèche droite
} t_keys;
```

### 2. Initialisation (keyboard_utils.c)
```c
int init_keys(t_keys *keys)
{
    keys->w_press = 0;
    keys->a_press = 0;
    // ... autres touches à 0
    return (0);
}
```

### 3. Gestion des événements
```c
// Quand une touche est pressée
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w_press = 1;
    // ... autres touches
}

// Quand une touche est relâchée
int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w_press = 0;
    // ... autres touches
}
```

## 🎮 Système de mouvement (movement.c)

### 1. Update Player
```c
int update_player(t_game *game)
{
    // Vérifie chaque touche et applique le mouvement
    if(game->keys.w_press)
        try_move(game, game->parsed_data.dir_x, game->parsed_data.dir_y);
    if(game->keys.s_press)
        try_move(game, -game->parsed_data.dir_x, -game->parsed_data.dir_y);
    // ... autres mouvements
}
```

### 2. Try Move
```c
int try_move(t_game *game, double dir_x, double dir_y)
{
    double new_x = game->parsed_data.player_x + dir_x * speed;
    double new_y = game->parsed_data.player_y + dir_y * speed;
    
    if (!wall_collision(new_x, new_y, &game->parsed_data))
    {
        game->parsed_data.player_x = new_x;
        game->parsed_data.player_y = new_y;
        return (1);
    }
    return (0);
}
```

## 🔄 Configuration des hooks MLX

### Dans le main.c
```c
// Hook pour touches pressées
mlx_hook(game.mlx_data.win, 2, 1L << 0, handle_keypress, &game);

// Hook pour touches relâchées
mlx_hook(game.mlx_data.win, 3, 1L << 1, handle_keyrelease, &game);

// Hook pour fermeture fenêtre
mlx_hook(game.mlx_data.win, 17, 1L << 17, handle_close, &game);

// Hook pour update continu
mlx_loop_hook(game.mlx_data.mlx, update_player, &game);
```

## 🎯 Avantages du nouveau système

### 1. Mouvements fluides
- Possibilité de mouvements diagonaux (W+D par exemple)
- Pas de saccades lors du maintien des touches
- Rotation continue possible

### 2. Meilleure réactivité
- État des touches toujours à jour
- Pas de délai de répétition du clavier
- Mise à jour continue via mlx_loop_hook

### 3. Code plus modulaire
- Séparation claire des responsabilités
- Facilité de maintenance
- Extension facile (nouveaux mouvements)

## ✅ Validation de l'étape

Cette étape est réussie si :
- ✅ Les mouvements sont fluides
- ✅ Plusieurs touches peuvent être pressées simultanément
- ✅ La rotation est continue
- ✅ Pas de saccades ou de délais
- ✅ Le code est bien organisé et modulaire

## 🚀 Prochaine étape
- Optimisation des collisions
- Préparation pour le raycasting

--- 