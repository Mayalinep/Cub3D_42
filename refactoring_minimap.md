# Refactoring de la Minimap - Étapes et Apprentissages

## État Actuel du Code

### Analyse des fonctions dans `minimap_bonus.c`

1. **draw_minimap_square** - ❌ PROBLÈME : 7 paramètres (limite : 4)
2. **draw_minimap_walls** - ✅ OK : 1 paramètre, ~20 lignes
3. **draw_minimap_player** - ✅ OK : 1 paramètre, ~17 lignes  
4. **draw_minimap_direction** - ✅ OK : 1 paramètre, ~18 lignes
5. **draw_minimap** - ✅ OK : 1 paramètre, 4 lignes

**Total : 5 fonctions (limite respectée)**

## Problèmes Identifiés

### 1. Trop de paramètres dans `draw_minimap_square`
- **Actuel** : `(int map_x, int map_y, int scale, int offset_x, int offset_y, int color, t_game *game)` → 7 paramètres
- **Maximum autorisé** : 4 paramètres

## Solutions Proposées

### Approche 1 : Créer une structure pour les paramètres de position
```c
typedef struct s_minimap_params
{
    int scale;
    int offset_x;
    int offset_y;
} t_minimap_params;
```

### Approche 2 : Calculer les offsets à l'intérieur de la fonction
- Passer seulement : `map_x`, `map_y`, `color`, `game`
- Calculer `scale`, `offset_x`, `offset_y` dans la fonction

## Plan d'Action

1. **Étape 1** : Analyser comment les paramètres sont utilisés
2. **Étape 2** : Choisir la meilleure approche de refactoring
3. **Étape 3** : Implémenter les changements progressivement
4. **Étape 4** : Tester que tout fonctionne encore

## Concepts Importants à Retenir

### Pourquoi limiter les paramètres ?
- **Lisibilité** : Moins de paramètres = code plus facile à comprendre
- **Maintenance** : Moins de risques d'erreurs lors des modifications
- **Performance** : Moins de passage de paramètres sur la pile

### Techniques de refactoring
1. **Regroupement** : Mettre les paramètres liés dans une structure
2. **Calcul local** : Calculer les valeurs dans la fonction plutôt que les passer
3. **Constantes** : Utiliser des constantes pour les valeurs fixes

---
*Mise à jour en cours...* 