# Guide : Forcer le Contenu d'une Branche sur Main 🔥

## ⚠️ ATTENTION - Opérations Destructives !

Ces opérations peuvent **écraser définitivement** le contenu de ta branche `main`. Assure-toi toujours d'avoir une sauvegarde !

## 🎯 Tes Options

### Option 1 : Merge Classique (Recommandé) 
**Sécurité : ✅ Élevée**
```bash
# Aller sur main
git checkout main

# Fusionner ta branche
git merge reajust-20250710

# Pousser les changements
git push origin main
```

**Avantages :**
- Conserve l'historique complet
- Réversible facilement
- Sécurisé

**Inconvénients :**
- Peut créer des conflits à résoudre
- Historique plus complexe

### Option 2 : Reset Hard (Destructif)
**Sécurité : ⚠️ Moyenne**
```bash
# Aller sur main
git checkout main

# Écraser main avec le contenu de ta branche
git reset --hard reajust-20250710

# Force push (attention !)
git push --force-with-lease origin main
```

**Avantages :**
- Historique linéaire et propre
- Pas de conflits

**Inconvénients :**
- Perte de l'historique de main
- Irréversible sans sauvegarde

### Option 3 : Force Push Direct (Très Destructif)
**Sécurité : ❌ Faible**
```bash
# Aller sur main
git checkout main

# Écraser complètement main
git reset --hard reajust-20250710

# Force push brutal
git push --force origin main
```

**Avantages :**
- Rapide et direct

**Inconvénients :**
- Très dangereux
- Peut affecter d'autres développeurs
- Perte totale de l'historique

### Option 4 : Rebase et Push (Intermédiaire)
**Sécurité : ✅ Élevée**
```bash
# Rester sur ta branche
git checkout reajust-20250710

# Rebase sur main
git rebase main

# Aller sur main et merger
git checkout main
git merge reajust-20250710

# Push normal
git push origin main
```

## 🛡️ Méthode Sécurisée Recommandée

### Étape 1 : Sauvegarde
```bash
# Créer une branche de sauvegarde de main
git checkout main
git checkout -b backup-main-$(date +%Y%m%d)
git push origin backup-main-$(date +%Y%m%d)
```

### Étape 2 : Exécution
```bash
# Retourner sur main
git checkout main

# Option sécurisée : merge
git merge reajust-20250710

# Ou option clean : reset (après sauvegarde)
git reset --hard reajust-20250710
```

### Étape 3 : Push sécurisé
```bash
# Push avec vérification
git push --force-with-lease origin main
```

## 📋 Checklist Avant d'Agir

- [ ] J'ai créé une sauvegarde de main
- [ ] J'ai vérifié le contenu de ma branche
- [ ] J'ai prévenu mes collaborateurs (si applicable)
- [ ] J'ai choisi la méthode appropriée
- [ ] J'ai testé localement

## 🚨 Codes d'Urgence

### Annuler un merge (si pas encore pushé)
```bash
git reset --hard HEAD~1
```

### Récupérer main depuis la sauvegarde
```bash
git checkout main
git reset --hard backup-main-YYYYMMDD
git push --force-with-lease origin main
```

### Voir l'historique avant de décider
```bash
git log --oneline --graph main reajust-20250710
```

## 💡 Conseils de Mentor

1. **Toujours sauvegarder** avant une opération destructive
2. **Utiliser --force-with-lease** au lieu de --force
3. **Tester en local** avant de pousser
4. **Communiquer** avec ton équipe
5. **Préférer merge** pour la sécurité

## 🎯 Quelle Option Choisir ?

**Si tu travailles seule :** Option 2 (Reset Hard) après sauvegarde
**Si tu travailles en équipe :** Option 1 (Merge Classique)
**Si tu veux un historique propre :** Option 4 (Rebase)
**Si tu es pressée et sûre :** Option 3 (mais déconseillé)

---

*Rappel : En cas de doute, choisis toujours la méthode la plus sécurisée ! 🛡️* 