# Étape 6 : Rendu des murs - Dessiner l'illusion 3D

## 📅 Date : 24 juin 2025

## 🎯 Objectif de cette étape
Comprendre et implémenter le système de rendu qui transforme les données du raycasting en pixels visibles à l'écran.

## 🧠 Concepts clés

### 1. Séparation Raycasting vs Rendu

**Raycasting** = Calcul des distances et positions
- Trouver où les rayons touchent les murs
- Calculer les distances
- Déterminer les côtés touchés (vertical/horizontal)

**Rendu** = Transformation en pixels visibles
- Convertir les distances en hauteurs de lignes
- Dessiner les pixels à l'écran
- Gérer les couleurs et textures

### 2. Le principe de perspective

```
Distance au mur → Hauteur de ligne → Pixels à dessiner

Mur proche (1m)  → Ligne haute (400px) → Beaucoup de pixels
Mur moyen (5m)   → Ligne moyenne (80px) → Peu de pixels  
Mur loin (10m)   → Ligne basse (40px)   → Très peu de pixels
```

## 🔨 Implémentation du rendu

### 1. Calcul de la hauteur de ligne

```c
int calculate_line_height(double distance)
{
    int line_height;
    
    if (distance <= 0)
        return (SCREEN_HEIGHT);
    line_height = (int)(SCREEN_HEIGHT / distance);
    if (line_height > SCREEN_HEIGHT)
        line_height = SCREEN_HEIGHT;
    return (line_height);
}
```

**Explication :**
- `SCREEN_HEIGHT / distance` = formule de perspective
- Plus la distance est grande, plus la ligne est petite
- Protection contre division par zéro
- Limitation à la hauteur de l'écran

### 2. Positionnement de la ligne

```c
draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
```

**Pourquoi centrer ?**
```
Sans centrage :           Avec centrage :
┌─────────┐              ┌─────────┐
│█████████│              │         │
│█████████│              │█████████│
│█████████│              │█████████│
│         │              │█████████│
│         │              │         │
└─────────┘              └─────────┘
```

### 3. Gestion des couleurs par direction - Explication détaillée

#### 🎨 Pourquoi des couleurs différentes ?

Imagine que tu es dans un labyrinthe et que tu veux savoir de quel côté vient le mur que tu vois :
- **Mur devant toi** → Rouge
- **Mur derrière toi** → Vert  
- **Mur à gauche** → Bleu
- **Mur à droite** → Jaune

Cela t'aide à comprendre ta position et l'orientation des murs !

#### 🧱 Les deux types de murs

Dans le raycasting, il y a **deux façons** de toucher un mur :

```
Vue de dessus (2D) :
┌─┬─┬─┬─┐
│ │ │ │ │
├─┼─┼─┼─┤
│ │P│ │1│  P = Joueur
├─┼─┼─┼─┤  1 = Mur
│ │ │ │ │
└─┴─┴─┴─┘

Rayon 1 : Touche le mur VERTICALEMENT (côté gauche du mur)
Rayon 2 : Touche le mur HORIZONTALEMENT (côté haut du mur)
```

#### 🔍 Variable `side` - Le détecteur de type de mur

```c
if (ray->side == 0)  // Mur VERTICAL
{
    // Le rayon a touché un côté vertical du mur
}
else  // Mur HORIZONTAL  
{
    // Le rayon a touché un côté horizontal du mur
}
```

**Explication :**
- `side == 0` = Le rayon a traversé une **ligne verticale** de la grille
- `side == 1` = Le rayon a traversé une **ligne horizontale** de la grille

#### 🔄 Comment `side` fonctionne dans la boucle DDA

**Important :** `side` ne change pas tout le temps ! Elle indique le **dernier type de ligne traversée** avant de toucher le mur.

```c
void dda_loop(t_game *game)
{
    game->raycasting.hit = 0;
    
    while (game->raycasting.hit == 0)  // ← Boucle jusqu'au premier mur
    {
        if (game->raycasting.side_dist_x < game->raycasting.side_dist_y)
        {
            // Le rayon traverse une ligne VERTICALE
            game->raycasting.side_dist_x += game->raycasting.delta_dist_x;
            game->raycasting.map_x += game->raycasting.step_x;
            game->raycasting.side = 0;  // ← Met à jour side
        }
        else
        {
            // Le rayon traverse une ligne HORIZONTALE
            game->raycasting.side_dist_y += game->raycasting.delta_dist_y;
            game->raycasting.map_y += game->raycasting.step_y;
            game->raycasting.side = 1;  // ← Met à jour side
        }
        
        // Vérification si on a touché un mur
        if (game->parsed_data.map[game->raycasting.map_y][game->raycasting.map_x] == '1')
        {
            game->raycasting.hit = 1;  // ← Arrête la boucle
        }
    }
    // À la sortie : side contient la dernière valeur mise à jour
}
```

#### 📝 Exemple concret étape par étape

Imaginons un rayon qui va en diagonale vers le nord-est :

```
Vue de dessus :
┌─┬─┬─┬─┐
│ │ │ │1│  1 = Mur
├─┼─┼─┼─┤
│ │P│→│ │  P = Joueur
├─┼─┼─┼─┤  → = Rayon en diagonale
│ │ │ │ │
└─┴─┴─┴─┘
```

**Progression du rayon :**

```
Étape 1 : Rayon traverse une ligne VERTICALE
- side = 0 (vertical)
- map_x = 1, map_y = 0
- Pas de mur → Continue

Étape 2 : Rayon traverse une ligne HORIZONTALE  
- side = 1 (horizontal)
- map_x = 1, map_y = 1
- Pas de mur → Continue

Étape 3 : Rayon traverse une ligne VERTICALE
- side = 0 (vertical)
- map_x = 2, map_y = 1
- MUR ! → Arrêt
```

**Résultat final :** `side = 0` (dernière ligne traversée = verticale)

#### 🎯 Pourquoi on ne garde que le dernier `side` ?

**Réponse simple :** On s'intéresse seulement au **côté du mur qu'on touche**, pas à tous les côtés qu'on traverse !

```
Exemple :
┌─┬─┬─┬─┐
│ │ │ │1│
├─┼─┼─┼─┤
│ │P│→│ │  Le rayon traverse :
├─┼─┼─┼─┤  1. Côté vertical (side=0)
│ │ │ │ │  2. Côté horizontal (side=1)  
└─┴─┴─┴─┘  3. Côté vertical (side=0) ← MUR !

Résultat final : side = 0 (mur vertical)
```

#### 💡 Pourquoi cette logique ?

1. **Couleur du mur** : On veut savoir de quel côté on voit le mur
2. **Textures** : Différentes textures selon l'orientation
3. **Réalisme** : Un mur a un côté visible et un côté caché

#### 🧪 Test pratique

```
Question : Si un rayon traverse 3 lignes verticales puis 1 ligne horizontale 
avant de toucher un mur, quelle sera la valeur finale de side ?

Réponse : side = 1 (horizontale, car c'est la dernière traversée)
```

#### 📋 Résumé en français simple

- **`side` change** pendant la progression du rayon
- **`side` final** = type de la dernière ligne traversée avant le mur
- **C'est cette valeur finale** qui détermine la couleur/texture
- **On ne s'intéresse pas** aux lignes traversées avant

#### ➡️ Variables `step_x` et `step_y` - La direction du rayon

Ces variables disent dans quelle direction va le rayon :

```c
// Dans ray_orientation()
if (ray_dir_x < 0)
    *step_x = -1;  // Rayon va vers la GAUCHE
else
    *step_x = 1;   // Rayon va vers la DROITE

if (ray_dir_y < 0)
    *step_y = -1;  // Rayon va vers le HAUT
else
    *step_y = 1;   // Rayon va vers le BAS
```

#### 🎯 Logique complète expliquée

```c
int get_wall_color(t_raycasting *ray)
{
    if (ray->side == 0)  // Mur VERTICAL
    {
        if (ray->step_x > 0)           // Rayon va vers la DROITE
            return (WALL_EAST_COLOR);   // → Mur EST (Bleu)
        else                           // Rayon va vers la GAUCHE  
            return (WALL_WEST_COLOR);   // → Mur OUEST (Jaune)
    }
    else  // Mur HORIZONTAL
    {
        if (ray->step_y > 0)           // Rayon va vers le BAS
            return (WALL_SOUTH_COLOR);  // → Mur SUD (Vert)
        else                           // Rayon va vers le HAUT
            return (WALL_NORTH_COLOR);  // → Mur NORD (Rouge)
    }
}
```

#### 📝 Exemples concrets

**Exemple 1 : Joueur regarde vers l'EST**
```
Joueur → [P] → Mur
         ↑
    Rayon va vers la droite

- side = 0 (mur vertical)
- step_x = 1 (vers la droite)
- Résultat : WALL_EAST_COLOR (Bleu)
```

**Exemple 2 : Joueur regarde vers l'OUEST**
```
Mur ← [P] ← Joueur
         ↑
    Rayon va vers la gauche

- side = 0 (mur vertical)  
- step_x = -1 (vers la gauche)
- Résultat : WALL_WEST_COLOR (Jaune)
```

**Exemple 3 : Joueur regarde vers le SUD**
```
Joueur [P]
   ↓
   Mur

- side = 1 (mur horizontal)
- step_y = 1 (vers le bas)
- Résultat : WALL_SOUTH_COLOR (Vert)
```

#### 🎨 Visualisation complète

```
Vue de dessus avec couleurs :
┌─┬─┬─┬─┐
│R│ │ │R│  R = Rouge (Nord)
├─┼─┼─┼─┤
│ │P│ │ │  P = Joueur
├─┼─┼─┼─┤
│V│ │ │V│  V = Vert (Sud)
└─┴─┴─┴─┘

Vue de côté avec couleurs :
┌─┬─┬─┬─┐
│B│ │ │B│  B = Bleu (Est)
├─┼─┼─┼─┤
│ │P│ │ │  P = Joueur
├─┼─┼─┼─┤
│J│ │ │J│  J = Jaune (Ouest)
└─┴─┴─┴─┘
```

#### 💡 Pourquoi cette logique ?

1. **Orientation** : Tu sais de quel côté vient le mur
2. **Navigation** : Tu peux te repérer dans le labyrinthe
3. **Réalisme** : Différents côtés = couleurs différentes
4. **Debugging** : Facile de voir les erreurs

#### 📋 Résumé en français simple

```
Si le rayon touche un côté VERTICAL du mur :
  - Si le rayon va vers la droite → Mur EST (Bleu)
  - Si le rayon va vers la gauche → Mur OUEST (Jaune)

Si le rayon touche un côté HORIZONTAL du mur :
  - Si le rayon va vers le bas → Mur SUD (Vert)
  - Si le rayon va vers le haut → Mur NORD (Rouge)
```

## 🎨 Fonction put_pixel

### 1. Calcul d'adresse mémoire

```c
void put_pixel(int x, int y, int color, t_game *game)
{
    char *pixel;
    
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    pixel = game->mlx_data.addr + (y * game->mlx_data.line_length + 
            x * (game->mlx_data.bits_per_pixel / 8));
    *(int*)pixel = color;
}
```

### 2. Comprendre le saut de lignes

**Structure mémoire de l'image :**
```
Adresse mémoire :
┌─────────────────────────────────────┐
│ Ligne 0: [pixel0][pixel1][pixel2]...│  ← y=0
├─────────────────────────────────────┤
│ Ligne 1: [pixel0][pixel1][pixel2]...│  ← y=1  
├─────────────────────────────────────┤
│ Ligne 2: [pixel0][pixel1][pixel2]...│  ← y=2
└─────────────────────────────────────┘
```

**Calcul : `y * line_length`**
- `line_length` = octets par ligne
- `y * line_length` = "sauter" les lignes précédentes
- Accès direct à la ligne Y

**Exemple :**
```
line_length = 3200 octets (800px × 4 octets)

y=0 : 0 × 3200 = 0        → Début image
y=1 : 1 × 3200 = 3200     → Saut 3200 octets
y=100 : 100 × 3200 = 320000 → Saut 320000 octets
```

## 🖼️ Dessin de la ligne verticale

### 1. Fonction principale

```c
void draw_vertical_line_color(int x, int line_height, t_game *game)
{
    int draw_start;
    int draw_end;
    int color;
    int y;
    
    draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
        
    color = get_wall_color(&game->raycasting);
    y = draw_start;
    while (y <= draw_end)
    {
        put_pixel(x, y, color, game);
        y++;
    }
}
```

### 2. Analyse détaillée de `draw_vertical_line_color`

#### 📋 Signature et paramètres

```c
void draw_vertical_line_color(int x, int line_height, t_game *game)
```

**Paramètres :**
- `x` : Position horizontale sur l'écran (colonne)
- `line_height` : Hauteur de la ligne à dessiner
- `game` : Structure contenant toutes les données du jeu

#### 🔢 Variables locales

```c
int draw_start;    // Position Y où commence la ligne
int draw_end;      // Position Y où finit la ligne  
int color;         // Couleur du mur à dessiner
int y;             // Variable de boucle pour parcourir les pixels
```

#### 🎯 Calcul du centrage de la ligne

```c
draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
```

**Explication de la formule :**

```
Écran 600 pixels de haut :
┌─────────────────────────┐
│                         │  ← y = 0
│                         │
│     ████████████████    │  ← draw_start
│     ████████████████    │  ← Ligne du mur
│     ████████████████    │
│     ████████████████    │  ← draw_end
│                         │
│                         │  ← y = 599
└─────────────────────────┘
```

**Exemple concret :**
```
Si line_height = 400 et SCREEN_HEIGHT = 600 :

draw_start = -400/2 + 600/2 = -200 + 300 = 100
draw_end = 400/2 + 600/2 = 200 + 300 = 500

La ligne va de y=100 à y=500 (centrée sur l'écran)
```

#### 🛡️ Protection contre les débordements

```c
if (draw_start < 0)
    draw_start = 0;
if (draw_end >= SCREEN_HEIGHT)
    draw_end = SCREEN_HEIGHT - 1;
```

**Pourquoi ces protections ?**

```
Cas 1 : Ligne trop haute (mur très proche)
┌─────────────────────────┐
│████████████████████████│  ← draw_start < 0 → Corrigé à 0
│████████████████████████│
│████████████████████████│
│████████████████████████│
│████████████████████████│
│████████████████████████│  ← draw_end > 599 → Corrigé à 599
└─────────────────────────┘

Cas 2 : Ligne normale
┌─────────────────────────┐
│                         │
│     ████████████████    │  ← draw_start = 100 (OK)
│     ████████████████    │
│     ████████████████    │
│     ████████████████    │  ← draw_end = 500 (OK)
│                         │
└─────────────────────────┘
```

#### 🎨 Détermination de la couleur

```c
color = get_wall_color(&game->raycasting);
```

Cette fonction retourne une couleur selon :
- `side` (vertical/horizontal)
- `step_x` et `step_y` (direction du rayon)

**Couleurs possibles :**
- `WALL_NORTH_COLOR` (Rouge) : Mur nord
- `WALL_SOUTH_COLOR` (Vert) : Mur sud  
- `WALL_EAST_COLOR` (Bleu) : Mur est
- `WALL_WEST_COLOR` (Jaune) : Mur ouest

#### 🔄 Boucle de dessin

```c
y = draw_start;
while (y <= draw_end)
{
    put_pixel(x, y, color, game);
    y++;
}
```

**Ce que fait cette boucle :**

```
Pour chaque pixel de la ligne :
┌─────────────────────────┐
│                         │
│     █ ← put_pixel(x, 100, color)  │
│     █ ← put_pixel(x, 101, color)  │
│     █ ← put_pixel(x, 102, color)  │
│     █ ← put_pixel(x, 103, color)  │
│     █ ← put_pixel(x, 104, color)  │
│                         │
└─────────────────────────┘
```

#### 📝 Exemple complet étape par étape

**Scénario :** Mur proche, ligne haute de 400 pixels

```
1. Calcul des positions :
   draw_start = -400/2 + 600/2 = 100
   draw_end = 400/2 + 600/2 = 500

2. Vérifications :
   draw_start = 100 (≥ 0) → OK
   draw_end = 500 (< 600) → OK

3. Couleur :
   color = get_wall_color() → Rouge (mur nord)

4. Dessin :
   y = 100
   put_pixel(x, 100, rouge)
   put_pixel(x, 101, rouge)
   put_pixel(x, 102, rouge)
   ...
   put_pixel(x, 500, rouge)
```

#### 🎯 Visualisation du résultat

```
Écran final avec plusieurs colonnes :
┌─────────────────────────────────┐
│         ████████████████        │  ← Mur proche (ligne haute)
│       ████████████████████      │
│     ████████████████████████    │
│   ████████████████████████████  │
│ ████████████████████████████████│
│   ████████████████████████████  │
│     ████████████████████████    │
│       ████████████████████      │
│         ████████████████        │  ← Mur loin (ligne basse)
└─────────────────────────────────┘
```

#### 💡 Pourquoi cette approche ?

1. **Centrage** : La ligne est toujours centrée sur l'écran
2. **Protection** : Évite les erreurs de débordement
3. **Efficacité** : Dessine seulement les pixels nécessaires
4. **Modularité** : Séparée de la logique de calcul

#### 📋 Résumé en français simple

```
1. Calcule où commence et finit la ligne (centrée)
2. Vérifie que ça ne dépasse pas l'écran
3. Détermine la couleur selon l'orientation du mur
4. Dessine pixel par pixel de haut en bas
5. Résultat : Une ligne verticale colorée représentant le mur
```

### 3. Les deux types de "saut de lignes"

**Saut logique (raycasting) :**
```c
// On ne dessine que certains pixels
y = draw_start;
while (y <= draw_end)  // On "saute" plafond/sol
{
    put_pixel(x, y, color, game);
    y++;
}
```

**Saut physique (mémoire) :**
```c
// Dans put_pixel, saut en mémoire
pixel = addr + (y * line_length + x * bytes_per_pixel);
//     ↑        ↑
//     │        └── Saut de lignes en mémoire
//     └── Adresse de base
```

## 🎮 Boucle de rendu

### 1. Pour chaque colonne

```c
int ray_casting(t_game *game)
{
    int x = 0;
    
    while (x < SCREEN_WIDTH)
    {
        // 1. Calculer direction du rayon
        calculate_ray_direction(x, game, &ray_dir_x, &ray_dir_y);
        
        // 2. Trouver distance au mur
        distance = find_wall_distance(ray_dir_x, ray_dir_y, game);
        
        // 3. Calculer hauteur de ligne
        line_height = calculate_line_height(distance);
        
        // 4. Dessiner la colonne
        draw_vertical_line(x, line_height, game);
        
        x++;
    }
    return (0);
}
```

### 2. Résultat visuel

```
Écran final :
┌─────────────────────────────────┐
│         ████████████████        │  ← Mur proche (ligne haute)
│       ████████████████████      │
│     ████████████████████████    │
│   ████████████████████████████  │
│ ████████████████████████████████│
│   ████████████████████████████  │
│     ████████████████████████    │
│       ████████████████████      │
│         ████████████████        │  ← Mur loin (ligne basse)
└─────────────────────────────────┘
```

## 🔧 Architecture modulaire

### 1. Séparation des responsabilités

```
raycasting.c  → Calculs (distances, directions)
draw.c        → Rendu (pixels, couleurs)
```

### 2. Fonctions spécialisées

```c
// Raycasting (calculs)
calculate_ray_direction()
find_wall_distance()
calculate_line_height()

// Rendu (affichage)
put_pixel()
get_wall_color()
draw_vertical_line_color()
```

### 3. Préparation pour les textures

```c
void draw_vertical_line(int x, int line_height, t_game *game)
{
    // Pour l'instant : couleurs
    draw_vertical_line_color(x, line_height, game);
    
    // Plus tard : textures
    // draw_vertical_line_texture(x, line_height, game);
}
```

## ✅ Validation de l'étape

Cette étape est réussie si :
- ✅ Les murs s'affichent avec la bonne perspective
- ✅ Les couleurs changent selon l'orientation
- ✅ Le rendu est fluide (60 FPS)
- ✅ Pas d'artefacts visuels
- ✅ Architecture modulaire respectée

## 🚀 Prochaine étape
- Implémentation des textures
- Gestion du sol et plafond
- Optimisations du rendu

## 💡 Points clés à retenir

1. **Raycasting ≠ Rendu** : Deux étapes distinctes
2. **Perspective** : Distance → Hauteur de ligne
3. **Centrage** : Lignes centrées sur l'écran
4. **Saut de lignes** : Logique (pixels) + Physique (mémoire)
5. **Modularité** : Séparation calculs/affichage
6. **Couleurs directionnelles** : Identifier les murs 