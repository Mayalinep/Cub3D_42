# Refactorisation du fichier draw.c

## 📋 Analyse initiale

Le fichier `src/rendering/draw.c` présente plusieurs problèmes par rapport aux normes 42 :

**🔴 Problèmes identifiés :**
1. **Trop de fonctions** : 9 fonctions (limite : 5)
2. **Fonction trop longue** : `draw_vertical_line_texture` fait 35 lignes (limite : 25)
3. **Trop de paramètres** : `draw_horizontal_line` a 5 paramètres (limite : 4)

**📊 Détail des fonctions :**
- `put_pixel` : 8 lignes ✅
- `get_wall_color` : 21 lignes ✅
- `draw_vertical_line_color` : 18 lignes ✅
- `get_texture_index` : 14 lignes ✅
- `draw_vertical_line_texture` : 35 lignes ❌ (trop longue)
- `draw_vertical_line` : 6 lignes ✅
- `draw_horizontal_line` : 15 lignes ✅ mais 5 paramètres ❌
- `create_rgb_color` : 3 lignes ✅
- `draw_floor_and_ceiling` : 16 lignes ✅

## 🛠️ Tentative de refactorisation

J'ai essayé de résoudre le problème de la fonction trop longue en créant deux fonctions helper :

### Fonctions ajoutées :
1. `calculate_texture_x()` - 12 lignes
2. `render_texture_pixels()` - 17 lignes

### Fonction modifiée :
- `draw_vertical_line_texture` réduite de 35 à 10 lignes

### ⚠️ Problème créé :
Cette approche a aggravé le problème principal :
- **Avant** : 9 fonctions (4 de trop)
- **Après** : 11 fonctions (6 de trop)

## 🔄 Restauration à l'état original

**Date : 10 juillet 2025**

Suite à la demande de l'utilisateur, j'ai retiré toutes les modifications pour revenir à l'état original :

✅ **Actions effectuées :**
1. Supprimé `calculate_texture_x()`
2. Supprimé `render_texture_pixels()`
3. Restauré `draw_vertical_line_texture()` à 35 lignes (état original)

✅ **Résultat :**
- Fichier revenu à **9 fonctions** (état original)
- Compilation réussie ✅

## 📝 Conclusion

Le fichier `draw.c` est **complexe à refactoriser** car :

1. **Problème principal** : Trop de fonctions (9 vs 5 autorisées)
2. **Dilemme** : Réduire la longueur des fonctions créé encore plus de fonctions
3. **Solution nécessaire** : Repenser l'architecture plutôt que diviser les fonctions

**État actuel :** Fichier restauré à son état original - compilation OK

**Recommandations futures :**
- Considérer une refactorisation architecturale plus profonde
- Peut-être regrouper certaines fonctions liées au rendu
- Évaluer si certaines fonctions peuvent être simplifiées sans les diviser 