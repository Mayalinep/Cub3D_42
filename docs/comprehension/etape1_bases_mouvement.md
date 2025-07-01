# Étape 1 : Les bases du mouvement 3D dans Cub3D

## 📅 Date : 16 juin 2025

## 🎯 Objectif de cette étape
Comprendre les concepts fondamentaux du mouvement 3D avant de coder.

## 🧠 Concepts clés

### 1. Position du joueur
- **Coordonnées** : `(x, y)` où se trouve le joueur
- **Type** : `double` pour un mouvement fluide (pas en cases entières)
- **Exemple** : `(2.5, 3.2)` = position entre les cases

### 2. Direction du regard
- **Vecteur** : `(dir_x, dir_y)` indiquant où le joueur regarde
- **Longueur** : toujours 1.0 (vecteur unitaire)
- **Exemple** : `(0, -1)` = regarde vers le nord

### 3. Plan de caméra
- **Vecteur** : `(plane_x, plane_y)` pour le champ de vision
- **Perpendiculaire** à la direction du regard
- **FOV** : détermine l'angle de vision (90° par défaut)

## 🎮 Types de mouvements

### Mouvement linéaire (W/S)
- **W** : avancer dans la direction du regard
- **S** : reculer (opposé de la direction)
- **Calcul** : `nouvelle_position = position + (direction * vitesse)`

### Rotation (A/D)
- **A** : tourner à gauche (rotation négative)
- **D** : tourner à droite (rotation positive)
- **Effet** : modifie les vecteurs `dir` et `plane`

## 📐 Système de coordonnées

### Orientation des axes
```
Y=0  111111
Y=1  100001
Y=2  101001
Y=3  100N01  ← N à (3, 3)
Y=4  111111
```

### Vecteurs selon l'orientation
- **N (Nord)** : `dir_x = 0.0`, `dir_y = -1.0`
- **S (Sud)** : `dir_x = 0.0`, `dir_y = 1.0`
- **E (Est)** : `dir_x = 1.0`, `dir_y = 0.0`
- **W (Ouest)** : `dir_x = -1.0`, `dir_y = 0.0`

## 🔍 Pourquoi des double ?

### Mouvement en int (saccadé)
```
Position : (3, 3)
Avancer  : (3, 3) → (3, 2) → (3, 1) → (3, 0)
```

### Mouvement en double (fluide)
```
Position : (3.0, 3.0)
Avancer  : (3.0, 3.0) → (3.0, 2.9) → (3.0, 2.8) → (3.0, 2.7)
```

## 🎯 Exemple concret

### Situation initiale
- **Map** : N à la position (3, 3)
- **Position joueur** : `x = 3.0`, `y = 3.0`
- **Direction** : `dir_x = 0.0`, `dir_y = -1.0` (regarde nord)

### Actions possibles
- **W** : `y = 3.0 + (-1.0 * 0.1) = 2.9` (monte)
- **S** : `y = 3.0 - (-1.0 * 0.1) = 3.1` (descend)
- **A** : rotation de -0.1 radian (tourne à gauche)
- **D** : rotation de +0.1 radian (tourne à droite)

## ❓ Questions de compréhension

1. **Pourquoi Y augmente vers le bas ?**
   - Convention en programmation graphique
   - Plus facile pour les calculs d'affichage

2. **Pourquoi le plan de caméra ?**
   - Nécessaire pour le raycasting
   - Détermine le champ de vision
   - Permet de voir à gauche et à droite

3. **Comment calculer la rotation ?**
   - Formules trigonométriques
   - `cos()` et `sin()` pour les nouveaux vecteurs

## ✅ Validation de l'étape

**Cette étape est réussie si vous comprenez :**
- ✅ La différence entre position et direction
- ✅ Pourquoi utiliser des double
- ✅ Les vecteurs pour chaque orientation
- ✅ La différence mouvement vs rotation

--- 