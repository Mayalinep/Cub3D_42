# Étape 5 : Les bases du Raycasting

## 📅 Date : 17 juin 2025

## 🎯 Objectif de cette étape
Comprendre et implémenter le raycasting pour créer l'illusion 3D dans Cub3D.

## 🧠 Concepts clés

### 1. Principe du Raycasting

Le raycasting est une technique qui permet de donner l'illusion de la 3D à partir d'une simple carte en 2D. 
Imagine que tu es dans un labyrinthe vu du dessus : tu ne vois que des murs et des espaces vides. 
Le but du raycasting est de simuler ce que verrait un joueur à la première personne, comme dans un jeu de tir ou un jeu d'exploration.

**Comment ça marche ?**  
À chaque image, le programme va lancer des « rayons » (des lignes imaginaires) depuis la position du joueur, dans la direction où il regarde.  
Pour chaque colonne de l'écran, un rayon est lancé avec un angle légèrement différent, couvrant tout le champ de vision du joueur.  
Le programme calcule alors à quelle distance chaque rayon rencontre un mur.  
Plus le mur est proche, plus la colonne affichée à l'écran sera haute ; plus il est loin, plus elle sera basse.  
C'est ce qui donne l'effet de perspective : les murs proches paraissent grands, les murs lointains paraissent petits.

**Exemple visuel :**

Imagine que tu es dans un couloir, face à un mur. Si tu tends le bras devant toi, tu touches le mur à une certaine distance. Si tu regardes un peu à gauche ou à droite, tu verras d'autres murs, parfois plus loin, parfois plus près.

Dans le raycasting, le programme fait comme si tu lançais plein de « faisceaux laser » devant toi, un pour chaque colonne de ton écran. Pour chaque faisceau :
- Il calcule à quelle distance il va rencontrer un mur.
- Plus le mur est proche, plus la colonne affichée sur l'écran sera grande (car tu es juste devant).
- Plus le mur est loin, plus la colonne sera petite (car il est au fond du couloir).

**En résumé :**
- Le joueur est à un endroit précis dans la map.
- Pour chaque colonne de l'écran, on calcule la direction d'un rayon.
- On avance ce rayon dans la map jusqu'à ce qu'il touche un mur.
- On mesure la distance : c'est cette distance qui détermine la hauteur de la colonne à dessiner à l'écran.

**Exemple concret :**
- Si tu es à 1 mètre d'un mur, la colonne sera très haute.
- Si tu es à 10 mètres, la colonne sera toute petite.
- Si tu es dans un coin, tu verras des murs proches à gauche et à droite, et un mur plus loin en face.

### 2. Visualisation du concept
```
Vue de dessus (2D):          Vue à l'écran (3D):
                            
    Mur      Joueur         Plus proche = Plus haut
    1 ╔══════ O            ║██████║
    2 ║       ╲            ║████║
    3 ║        ╲           ║██║
    4 ║         ╲          ║║
```

3. Les rayons
Pour comprendre le raycasting, imagine que tes yeux sont comme une caméra qui regarde droit devant, mais qui peut aussi voir un peu à gauche et à droite (comme un champ de vision).
Le programme va simuler ce que tu vois en lançant un « rayon » pour chaque colonne de ton écran.
Chaque rayon part de la position du joueur et va dans une direction légèrement différente, couvrant tout l'angle de vue.
Exemple imagé :
Si ton écran fait 800 pixels de large, il y aura 800 rayons, chacun correspondant à une colonne de pixels.
Le rayon tout à gauche regarde vers la gauche, celui du milieu regarde droit devant, celui de droite regarde vers la droite.
À chaque rayon, le programme va chercher :
Où ce rayon va-t-il rencontrer un mur ?
À quelle distance ce mur se trouve-t-il du joueur ?
C'est cette distance qui va déterminer la hauteur de la colonne à dessiner à l'écran.

### 📐 Mathématiques du Raycasting
Pour que chaque rayon parte dans la bonne direction, il faut faire un peu de calcul.
On utilise la position du joueur, la direction dans laquelle il regarde, et un « plan de caméra » qui définit le champ de vision.
Calcul de la direction du rayon :
Pour chaque colonne de l'écran, on calcule une valeur camera_x qui va de -1 (extrême gauche de l'écran) à 1 (extrême droite).
Ensuite, on calcule la direction du rayon avec :

ray_dir_x = dir_x + plane_x * camera_x
ray_dir_y = dir_y + plane_y * camera_x

dir_x et dir_y : la direction dans laquelle le joueur regarde (par exemple, tout droit).
plane_x et plane_y : définissent l'angle de vue (le champ de vision).
camera_x : permet de balayer tout l'écran de gauche à droite.
Exemple concret :
Si camera_x vaut -1, le rayon part complètement à gauche.
Si camera_x vaut 0, le rayon part droit devant.
Si camera_x vaut 1, le rayon part complètement à droite.

Pourquoi faire ça ?
Cela permet de simuler le fait que tu vois plus large que juste devant toi, comme si tu avais un vrai champ de vision.

### 2. DDA (Digital Differential Analysis)

L'algorithme DDA sert à trouver précisément où un rayon lancé depuis le joueur va toucher un mur dans la carte.  
Plutôt que d'avancer le rayon pixel par pixel (ce qui serait très lent), on avance de case en case, en suivant la grille de la map.

**Comment ça marche ?**

1. **Départ**  
   On part de la position du joueur, à l'intérieur d'une case de la grille.

2. **Direction**  
   On connaît la direction du rayon (calculée précédemment).

3. **Avancement**  
   À chaque étape, on regarde :  
   - Est-ce que le rayon va d'abord croiser une ligne verticale (changer de colonne) ou une ligne horizontale (changer de ligne) ?  
   - On avance jusqu'à la prochaine ligne de la grille dans la direction du rayon.

4. **Vérification**  
   À chaque nouvelle case traversée, on regarde si c'est un mur (`1`).  
   - Si oui, on s'arrête : le rayon a touché un mur.
   - Sinon, on continue d'avancer.

**Exemple imagé :**

Imagine une grille comme un damier.  
Le joueur est dans une case, il lance un rayon vers la droite :  
- Le rayon avance, traverse la première case, puis la suivante, etc.  
- Dès qu'il entre dans une case contenant un mur, on s'arrête.

**Pourquoi c'est efficace ?**  
Parce qu'on ne teste que les cases de la grille, pas chaque pixel du rayon.  
C'est beaucoup plus rapide, surtout pour de grandes maps.


```
Exemple de DDA :
┌─┬─┬─┬─┐
│ │ │ │ │
├─┼─┼─┼─┤
│O→│→│→│1│  O = Joueur
├─┼─┼─┼─┤  → = Rayon
│ │ │ │ │  1 = Mur
└─┴─┴─┴─┘
```
**Résumé étape par étape :**
- On part de la position du joueur.
- On avance le rayon de case en case, en suivant la direction.
- On s'arrête dès qu'on touche un mur.

## 🔨 Étapes d'implémentation

### 1. Préparation

Avant de commencer le raycasting, il faut s'assurer que tout est bien configuré et que toutes les données nécessaires sont disponibles.

**Créer les structures nécessaires :**
- Il faut avoir une structure pour stocker les données du jeu (position du joueur, direction, etc.).
- Une structure pour gérer la fenêtre et l'affichage (connexion MLX, fenêtre, image).
- Des variables pour stocker les informations de la map (largeur, hauteur, contenu).

**Initialiser les variables de raycasting :**
- La position du joueur dans la map (coordonnées X et Y).
- La direction dans laquelle le joueur regarde (vecteur dir_x, dir_y).
- Le plan de caméra qui définit le champ de vision (vecteur plane_x, plane_y).
- Ces valeurs sont généralement définies au début du jeu ou chargées depuis le fichier de configuration.

**Configurer la fenêtre de rendu :**
- Créer la connexion avec la bibliothèque MLX.
- Ouvrir une fenêtre de la taille souhaitée (par exemple 800x600 pixels).
- Créer une image en mémoire pour dessiner avant d'afficher à l'écran.
- Configurer les paramètres de l'image (bits par pixel, longueur de ligne, etc.).

**Vérifications importantes :**
- S'assurer que la map est valide (fermée, sans erreurs).
- Vérifier que toutes les textures sont chargées correctement.
- Contrôler que la position initiale du joueur est dans un espace vide (pas dans un mur).

**Exemple concret :**
Si le joueur commence à la position (2.5, 3.2) et regarde vers le nord, on aura :
- `player_x = 2.5`, `player_y = 3.2`
- `dir_x = 0`, `dir_y = -1` (vers le nord)
- `plane_x = 0.66`, `plane_y = 0` (pour un FOV de 66°)

**Structures nécessaires dans le projet :**
D'après l'analyse du code, nous avons déjà :
- ✅ `t_game` : structure principale du jeu
- ✅ `t_parsed_data` : contient position joueur, direction, plan caméra, map
- ✅ `t_mlx_data` : gère la fenêtre et l'affichage MLX
- ✅ `t_keys` : gère les touches du clavier

Toutes les structures nécessaires sont déjà définies dans `cub3d.h` !

### 2. Boucle principale

La boucle principale est le cœur du raycasting. Elle va être exécutée pour chaque image affichée à l'écran, et c'est elle qui va créer l'illusion de la 3D.
Principe général :
Pour chaque colonne de l'écran (de gauche à droite), on va lancer un rayon et calculer ce qu'il voit. Plus le mur est proche, plus la colonne sera haute.
Déroulement étape par étape :
Calculer la position sur le plan caméra :
On calcule camera_x qui va de -1 (extrême gauche) à 1 (extrême droite).
Cette valeur détermine l'angle du rayon pour cette colonne spécifique.
Calculer la direction du rayon :
```c
On utilise la formule : ray_dir_x = dir_x + plane_x * camera_x
Et : ray_dir_y = dir_y + plane_y * camera_x
Cela donne la direction exacte du rayon pour cette colonne.
```

Trouver la distance au mur (DDA) :
On utilise l'algorithme DDA pour avancer le rayon dans la map.
On s'arrête dès qu'on touche un mur.
On calcule la distance perpendiculaire pour éviter l'effet "fisheye".
Calculer la hauteur de la ligne :
Plus le mur est loin, plus la ligne sera petite.
Plus le mur est proche, plus la ligne sera grande.
On calcule aussi où commence et où finit la ligne sur l'écran.
Dessiner la colonne :
On dessine une ligne verticale de la hauteur calculée.
Cette ligne représente ce que le joueur voit à cet endroit.


### 3. Algorithme DDA détaillé (pseudocode enrichi)

```plaintext
1. Prendre la position du joueur sur la grille :
    - Récupérer la position du joueur en X et Y (en double)
    - Convertir ces positions en indices de case (en int)
    - Stocker ces indices comme position de départ du rayon (map_x, map_y)

2. Calculer la distance pour traverser une case en X (delta_dist_x) :
    - Prendre la direction du rayon en X
    - Si la direction n'est pas nulle :
        - Calculer la valeur absolue de (1 divisé par la direction du rayon en X)
        - Stocker ce résultat comme distance à parcourir pour traverser une case en X
    - Sinon :
        - Mettre une valeur très grande (le rayon ne traverse jamais en X)

3. Calculer la distance pour traverser une case en Y (delta_dist_y) :
    - Prendre la direction du rayon en Y
    - Si la direction n'est pas nulle :
        - Calculer la valeur absolue de (1 divisé par la direction du rayon en Y)
        - Stocker ce résultat comme distance à parcourir pour traverser une case en Y
    - Sinon :
        - Mettre une valeur très grande (le rayon ne traverse jamais en Y)

4. Déterminer le sens du rayon en X (step_x) :
    - Si la direction du rayon en X est négative :
        - Le pas en X est -1 (on va vers la gauche)
    - Sinon :
        - Le pas en X est +1 (on va vers la droite)

   Déterminer le sens du rayon en Y (step_y) :
    - Si la direction du rayon en Y est négative :
        - Le pas en Y est -1 (on va vers le haut)
    - Sinon :
        - Le pas en Y est +1 (on va vers le bas)

5. Calculer la distance du joueur à la première ligne verticale (side_dist_x) :
    - Si le pas en X est positif :
        - Calculer la distance entre la position du joueur et le bord droit de la case actuelle
        - Multiplier cette distance par delta_dist_x
    - Si le pas en X est négatif :
        - Calculer la distance entre la position du joueur et le bord gauche de la case actuelle
        - Multiplier cette distance par delta_dist_x

6. Calculer la distance du joueur à la première ligne horizontale (side_dist_y) :
    - Si le pas en Y est positif :
        - Calculer la distance entre la position du joueur et le bord bas de la case actuelle
        - Multiplier cette distance par delta_dist_y
    - Si le pas en Y est négatif :
        - Calculer la distance entre la position du joueur et le bord haut de la case actuelle
        - Multiplier cette distance par delta_dist_y

7. Répéter tant qu'aucun mur n'est touché :
    a. Si la distance à la prochaine ligne verticale (side_dist_x) est plus petite que la distance à la prochaine ligne horizontale (side_dist_y) :
        - Avancer d'une case en X dans le sens du rayon (ajouter step_x à map_x)
        - Ajouter la distance d'une case en X à la distance totale en X (ajouter delta_dist_x à side_dist_x)
        - Se souvenir qu'on a traversé une ligne verticale
    b. Sinon :
        - Avancer d'une case en Y dans le sens du rayon (ajouter step_y à map_y)
        - Ajouter la distance d'une case en Y à la distance totale en Y (ajouter delta_dist_y à side_dist_y)
        - Se souvenir qu'on a traversé une ligne horizontale
    c. Vérifier si la nouvelle case (map_x, map_y) est un mur :
        - Si oui, arrêter la boucle

8. Calculer la distance exacte entre le joueur et le mur touché :
    - Si le dernier déplacement était en X (ligne verticale traversée) :
        - Utiliser la formule suivante :
            distance = (map_x - player_x + (1 - step_x) / 2) / ray_dir_x
    - Sinon (ligne horizontale traversée) :
        - Utiliser la formule suivante :
            distance = (map_y - player_y + (1 - step_y) / 2) / ray_dir_y
```

**Explication des formules :**
- map_x, map_y : indices de la case où le mur a été touché
- player_x, player_y : position réelle du joueur (en double)
- step_x, step_y : sens du rayon (+1 ou -1)
- ray_dir_x, ray_dir_y : direction du rayon
- (1 - step_x) / 2 ou (1 - step_y) / 2 permet de corriger l'offset selon le sens du rayon
- Cette formule donne la distance exacte entre la position du joueur et le mur touché, en tenant compte du sens dans lequel on a traversé la grille.

## 📏 Comprendre les Distances en Detail

### 1. La Grille et le Joueur
```
+---+---+---+---+  Légende:
| 1 | 1 | 1 | 1 |  1 = Mur
+---+---+---+---+  0 = Espace vide
| 0 | P | 0 | 1 |  P = Joueur (position 1.3, 1.5)
+---+---+---+---+  + = Intersection de grille
| 1 | 0 | 0 | 1 |  | et - = Lignes de grille
+---+---+---+---+
| 1 | 1 | 1 | 1 |
+---+---+---+---+
```

### 2. Les Distances Importantes
- **deltaDistX** : Distance entre deux lignes verticales de la grille suivant le rayon
- **deltaDistY** : Distance entre deux lignes horizontales de la grille suivant le rayon
- **sideDistX** : Distance initiale jusqu'à la première ligne verticale
- **sideDistY** : Distance initiale jusqu'à la première ligne horizontale

### 3. Exemple Concret
```
  +-----+-----+
  |     |     |
  |  P→ |     |  Si P est à (1.3, 1.5):
  |     |     |  - sideDistX = 0.7 (distance jusqu'à x=2)
  +-----+-----+  - sideDistY = 0.5 (distance jusqu'à y=2)
```

### 4. Comment Calculer
1. **Distance Initiale en X**:
   - Si rayon va vers la droite: (prochain x entier - position_x)
   - Si rayon va vers la gauche: (position_x - x actuel entier)

2. **Distance Initiale en Y**:
   - Si rayon va vers le bas: (prochain y entier - position_y)
   - Si rayon va vers le haut: (position_y - y actuel entier)

### 5. Progression du DDA
```
Étape par étape:
+---+---+---+
| 1 | 2 | 3 |  Les chiffres montrent
+---+---+---+  l'ordre dans lequel le
|P→ |   |   |  rayon vérifie les cases
+---+---+---+
```

## 🎮 Variables importantes

### 1. Pour le rayon
```c
double ray_dir_x;    // Direction X du rayon
double ray_dir_y;    // Direction Y du rayon
double camera_x;     // Position X sur le plan caméra
```

### 2. Pour le DDA
```c
int map_x;          // Position X dans la map
int map_y;          // Position Y dans la map
double side_dist_x; // Distance au prochain x
double side_dist_y; // Distance au prochain y
```

### 3. Pour l'affichage
```c
int line_height;    // Hauteur de la ligne à dessiner
int draw_start;     // Début de la ligne
int draw_end;       // Fin de la ligne
```

## 🎯 Résultat attendu

### À chaque frame
1. Effacer l'écran
2. Pour chaque colonne :
   - Calculer la distance au mur
   - Dessiner une ligne verticale
   - Hauteur inversement proportionnelle à la distance

### Effet visuel
```
Plus proche = Plus haut
Plus loin = Plus bas

║████████║  ← Mur proche
║████║      ← Mur moyen
║██║        ← Mur loin
```

## ✅ Validation de l'étape

Cette étape est réussie si :
- ✅ Les rayons sont correctement calculés
- ✅ Les distances sont précises
- ✅ L'affichage donne une impression de 3D
- ✅ Le rendu est fluide
- ✅ Pas d'effet de "fisheye"

## 🚀 Prochaine étape
- Ajout des textures
- Optimisation du rendu
- Gestion des couleurs sol/plafond

--- e