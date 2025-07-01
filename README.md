# Cub3D

Un moteur de jeu 3D basé sur le raycasting, inspiré de Wolfenstein 3D, développé pour l'école 42.

## 🎮 Description

Cub3D est un moteur de rendu 3D qui utilise la technique du raycasting pour créer une représentation graphique d'un labyrinthe en vue subjective.

## 🚀 Fonctionnalités

### Fonctionnalités Obligatoires
- **Rendu 3D** : Affichage en perspective avec raycasting
- **Textures** : Différentes textures selon l'orientation des murs
- **Couleurs personnalisables** : Sol et plafond avec couleurs RGB
- **Contrôles** : 
  - `WASD` : Déplacement du joueur
  - `Flèches gauche/droite` : Rotation de la caméra
  - `ESC` : Quitter le programme
- **Parsing de maps** : Format `.cub` avec validation complète

### Fonctionnalités Bonus
- **🎮 Contrôle Souris** : Rotation de la caméra avec la souris
- **🗺️ Minimap Interactive** : Vue d'ensemble de la map en temps réel

### Compilation

```bash
# Version normale
make

# Version bonus (avec minimap et contrôle souris)
make bonus

# Nettoyage
make clean
make fclean
```

## 🎯 Utilisation

### Format des Maps (.cub)

```cub
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 100,150,200
C 50,100,150

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Lancement

```bash
# Version normale
./cub3D maps/test.cub

# Version bonus
./cub3D_bonus maps/test.cub
```

## 🎮 Contrôles

### Version Normale
- **WASD** : Déplacement
- **Flèches** : Rotation
- **ESC** : Quitter

### Version Bonus
- **Souris** : Rotation de la caméra
- **WASD** : Déplacement
- **Flèches** : Rotation
- **ESC** : Quitter
- **Minimap** : Affichée automatiquement

## 🧪 Tests

```bash
# Test de la map simple
./cub3D maps/test_simple.cub

# Test de la map plus grande
./cub3D maps/test_plus_grande.cub
```
