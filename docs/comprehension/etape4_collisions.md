# Étape 4 : Collisions avec les murs

## 📅 Date : 16 juin 2025

## 🎯 Objectif de cette étape
Implémenter une détection de collision robuste pour empêcher le joueur de traverser les murs.

## 🧠 Concepts implémentés

### 1. Vérification des limites
- Empêcher le joueur de sortir de la map
- Vérifier les coordonnées avant tout mouvement
- Gérer les cas limites (bords de map)

### 2. Collision avec les murs
- Détecter la présence d'un mur ('1' dans la map)
- Bloquer le mouvement si collision
- Maintenir une distance minimale des murs

### 3. Sécurité
- Vérification des indices de la map
- Prévention des segfaults
- Gestion des erreurs

## 📐 Implémentation actuelle

### Fonction wall_collision
```c
int wall_collision(double new_x, double new_y, t_parsed_data *data)
{
    // Vérification des limites de la map
    if ((int)new_y < 0 || (int)new_y >= data->map_height || 
        (int)new_x < 0 || (int)new_x >= data->map_width)
        return (1);
    // Vérification de collision avec un mur
    if (data->map[(int)new_y][(int)new_x] == '1')
        return (1);
    return (0);
}
```

### Fonction try_move
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

## 🔍 Points à améliorer

### 1. Distance aux murs
- Ajouter une marge de sécurité
- Éviter de "coller" aux murs
- Améliorer la sensation de mouvement

### 2. Collisions précises
- Gérer les collisions en diagonale
- Éviter les "accrochages" aux coins
- Permettre de glisser le long des murs

### 3. Optimisation
- Réduire les calculs inutiles
- Améliorer la fluidité
- Maintenir la précision

## ✅ Validation de l'étape

**Cette étape est réussie si :**
- ✅ Le joueur ne peut pas traverser les murs
- ✅ Le joueur ne peut pas sortir de la map
- ✅ Les mouvements restent fluides
- ✅ Pas de segfault possible
- ✅ Comportement naturel aux coins des murs

## 🚀 Prochaine étape

### Étape 5 : Raycasting
- Implémenter le moteur de rendu
- Calculer la distance des murs
- Créer l'illusion de 3D

## 📁 Organisation du code

### Fichiers concernés
```
src/input/
└── movement.c    // wall_collision + try_move
```

### Points d'attention
- Garder le code modulaire
- Faciliter l'ajout de nouvelles fonctionnalités
- Maintenir la clarté du code 