# Étape 5 : Les bases du Raycasting

## 📅 Date : 17 juin 2025

## 🎯 Objectif de cette étape
Comprendre et implémenter le raycasting pour créer l'illusion 3D dans Cub3D.

## 🧠 Concepts clés

### 1. Principe du Raycasting
- **Définition** : Technique qui simule une vue 3D à partir d'une carte 2D
- **Méthode** : Lance des rayons depuis la position du joueur
- **But** : Calculer la distance jusqu'aux murs pour chaque colonne de l'écran

### 2. Visualisation du concept
```
Vue de dessus (2D):          Vue à l'écran (3D):
                            
    Mur      Joueur         Plus proche = Plus haut
    1 ╔══════ O            ║██████║
    2 ║       ╲            ║████║
    3 ║        ╲           ║██║
    4 ║         ╲          ║║
```

### 3. Les rayons
- Un rayon par colonne de l'écran
- Direction calculée en fonction de :
  * La direction du joueur
  * Le plan de caméra
  * La position sur l'écran

## 📐 Mathématiques du Raycasting

### 1. Calcul de la direction du rayon
```
ray_dir_x = dir_x + plane_x * camera_x
ray_dir_y = dir_y + plane_y * camera_x

où camera_x va de -1 (gauche) à 1 (droite)
```

### 2. DDA (Digital Differential Analysis)
- Algorithme pour trouver où le rayon touche un mur
- Avance case par case dans la direction du rayon
- Plus efficace qu'une vérification pixel par pixel

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

## 🔨 Étapes d'implémentation

### 1. Préparation
- Créer les structures nécessaires
- Initialiser les variables de raycasting
- Configurer la fenêtre de rendu

### 2. Boucle principale
```c
pour chaque colonne x de l'écran {
    1. Calculer position sur plan caméra
    2. Calculer direction du rayon
    3. Trouver distance au mur (DDA)
    4. Calculer hauteur de la ligne
    5. Dessiner la colonne
}
```

### 3. Algorithme DDA détaillé
1. Calculer la longueur du rayon pour un déplacement unitaire
2. Calculer la distance jusqu'au prochain x et y
3. Avancer jusqu'à toucher un mur
4. Calculer la distance exacte

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

--- 