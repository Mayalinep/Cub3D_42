# 🖱️ Gestion de la Souris avec MLX - Guide Complet

## 📋 Problématique Initiale

**Question** : `mlx_mouse_hide` provoque-t-elle des fuites mémoire avec Valgrind ?

**Hypothèse** : Recoder `mlx_mouse_hide` pour éviter les leaks potentiels.

## 🔍 Analyse du Problème

### Code MLX Original

```c
int	mlx_mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);  // ⚠️ Potentiel problème
}
```

**Problème identifié** : La fonction libère le curseur immédiatement après l'avoir appliqué, mais le serveur X peut maintenir des références internes.

## ✅ Solutions Implémentées

### Solution 1 : Cleanup Approprié

**Fichier** : `src/bonus/mouse_control_bonus.c`

```c
// Fonction pour nettoyer les événements souris
void	cleanup_mouse_events(t_game *game)
{
	if (game->mlx_data.mlx && game->mlx_data.win)
		mlx_mouse_show(game->mlx_data.mlx, game->mlx_data.win);
}

// Initialisation
void	init_mouse_events(t_game *game)
{
	mlx_mouse_hide(game->mlx_data.mlx, game->mlx_data.win);
	mlx_mouse_move(game->mlx_data.mlx, game->mlx_data.win, SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
	mlx_hook(game->mlx_data.win, 6, 1L << 6, mouse_rotation, game);
}

// Dans main()
int	main(int ac, char **av)
{
	// ... initialisation ...
	init_mouse_events(&game);
	mlx_loop(game.mlx_data.mlx);
	cleanup_mouse_events(&game);  // ✅ Restauration du curseur
	quity(&game, 0, "finito");
	return (0);
}
```

**Fichier** : `src/parsing/utils_four.c`

```c
void	free_mlx(t_game *game)
{
	if (game->mlx_data.mlx && game->mlx_data.win)
		mlx_mouse_show(game->mlx_data.mlx, game->mlx_data.win);  // ✅ Sécurité
	if (game->mlx_data.img && game->mlx_data.mlx)
		mlx_destroy_image(game->mlx_data.mlx, game->mlx_data.img);
	if (game->mlx_data.win)
		mlx_destroy_window(game->mlx_data.mlx, game->mlx_data.win);
	if (game->mlx_data.mlx)
	{
		mlx_destroy_display(game->mlx_data.mlx);
		free(game->mlx_data.mlx);
	}
}
```

### Solution 2 : Alternative Sans mlx_mouse_hide

**Fichier** : `src/bonus/mouse_control_alternative.c`

```c
// Alternative sans mlx_mouse_hide - utilise seulement le recentrage
int	mouse_rotation_alt(int x, int y, void *param)
{
	t_game	*game;
	int		center_x;
	int		delta_x;
	double	angle;

	(void)y;
	game = (t_game *)param;
	center_x = SCREEN_WIDTH / 2;
	delta_x = x - center_x;
	
	// Seuil pour éviter les micro-mouvements
	if (abs(delta_x) < 5)
		return (0);
	
	if (delta_x != 0)
	{
		angle = delta_x * SENSITIVITY;
		rotate_player(angle, game);
		// Recentrer la souris au centre
		mlx_mouse_move(game->mlx_data.mlx, game->mlx_data.win, center_x,
			SCREEN_HEIGHT / 2);
	}
	return (0);
}

// Version alternative sans mlx_mouse_hide
void	init_mouse_events_alt(t_game *game)
{
	mlx_mouse_move(game->mlx_data.mlx, game->mlx_data.win, SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
	mlx_hook(game->mlx_data.win, 6, 1L << 6, mouse_rotation_alt, game);
}
```

## 🧪 Tests et Validation

### Test Valgrind

```bash
valgrind --leak-check=full --track-origins=yes ./cub3D_bonus ./maps/good/cheese_maze.cub
```

**Résultats** :
```
HEAP SUMMARY:
    in use at exit: 114,608 bytes in 573 blocks
  total heap usage: 2,088 allocs, 1,515 frees, 238,376 bytes allocated

LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks          ✅ AUCUN LEAK CONFIRMÉ
   indirectly lost: 0 bytes in 0 blocks          ✅ AUCUN LEAK INDIRECT  
     possibly lost: 2,304 bytes in 1 blocks      ⚠️ SYSTÈME DLOPEN
   still reachable: 112,304 bytes in 572 blocks  ✅ MÉMOIRE NORMALE

ERROR SUMMARY: 1 errors from 1 contexts
```

### Interprétation des Résultats

**✅ Pas de problème avec mlx_mouse_hide** :
- 0 bytes definitely lost → Aucun leak dans notre code
- L'erreur vient de `dlopen` (chargement des bibliothèques X11)
- C'est normal pour une application MLX

**⚠️ Sources d'erreur communes** :
```
_dlfo_mappings_segment_allocate (dl-find_object.c:217)  
dl_open_worker_begin (dl-open.c:735)                    // Système
dlopen@@GLIBC_2.34 (dlopen.c:81)                       // Pas notre code
```

## 📖 Principes Appris

### 1. Gestion des Ressources MLX

**Principe** : Toujours restaurer l'état initial avant la destruction
```c
// ✅ BIEN
mlx_mouse_hide();   // Cacher
// ... utilisation ...
mlx_mouse_show();   // Restaurer
mlx_destroy_window(); // Détruire

// ❌ MAL  
mlx_mouse_hide();   // Cacher
mlx_destroy_window(); // Détruire sans restaurer
```

### 2. Interprétation de Valgrind

**Types de "leaks"** :
- **definitely lost** → Vrai problème à corriger
- **possibly lost** → Souvent faux positifs du système
- **still reachable** → Mémoire gardée volontairement (normal)

### 3. Debug vs Production

**Debug actuel** :
```c
Debug: Tentative de chargement de la texture: 'textures/simonkraft/wet_sponge.xpm'
Debug: Texture 'textures/simonkraft/wet_sponge.xpm' chargée avec succès
```

**Pour la production** : Enlever ou conditionner les prints de debug.

## 🎯 Recommandations Finales

### Option Recommandée : Solution 1

**Pourquoi** :
- ✅ Utilise MLX normalement
- ✅ Gestion propre des ressources  
- ✅ Aucun leak confirmé
- ✅ Compatible avec toutes les distributions

### Utilisation :

```c
// Dans ton main bonus
init_mouse_events(&game);
mlx_loop(game.mlx_data.mlx);
cleanup_mouse_events(&game);  // Important !
```

### Si problèmes persistants : Solution 2

Utilise `mouse_control_alternative.c` qui évite complètement `mlx_mouse_hide`.

## 🧠 Leçons d'Autonomie

1. **Analyser avant d'agir** : Tests révèlent que le problème n'existait pas
2. **Interpréter les outils** : Valgrind n'est pas toujours parfait
3. **Solutions graduelles** : Correction simple avant refonte complète
4. **Documentation** : Capitaliser sur l'apprentissage

---

**Créé le** : 10 Juillet 2025  
**Auteur** : Assistant Mentor  
**Contexte** : Cub3D - Gestion souris MLX 