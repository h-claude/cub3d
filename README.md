# Cub3D - Moteur de Raycasting 🎮

Un moteur de raycasting 3D inspiré de Wolfenstein 3D, développé en C avec la bibliothèque graphique MLX42.

![Language](https://img.shields.io/badge/language-C-blue)
![Graphics](https://img.shields.io/badge/graphics-MLX42-green)
![Project](https://img.shields.io/badge/project-42-orange)

## 📋 Table des matières
- [Description](#-description)
- [Fonctionnalités](#-fonctionnalités)
- [Installation](#-installation)
- [Utilisation](#-utilisation)
- [Format des cartes](#-format-des-cartes)
- [Contrôles](#-contrôles)
- [Architecture technique](#-architecture-technique)
- [Exemples](#-exemples)
- [Dépannage](#-dépannage)

## 🎯 Description

Cub3D est une implémentation d'un moteur de rendu 3D utilisant la technique du **raycasting**. Ce projet recrée l'expérience des premiers jeux de tir à la première personne comme Wolfenstein 3D, en projetant des rayons depuis la position du joueur pour calculer la distance aux murs et rendre une vue 3D en pseudo-perspective.

Le moteur supporte :
- Rendu 3D en temps réel avec raycasting
- Textures murales différenciées par direction (Nord, Sud, Est, Ouest)
- Couleurs personnalisables pour le sol et le plafond
- Système de mouvement fluide avec détection de collisions
- Rotation avec la souris (fonctionnalité bonus)
- Éclairage basé sur la distance

## ✨ Fonctionnalités

### Fonctionnalités principales
- **Moteur de raycasting** : Calcul en temps réel des distances aux murs
- **Rendu texturé** : Application de textures PNG sur les murs
- **Détection de collisions** : Empêche le joueur de traverser les murs
- **Couleurs RGB** : Sol et plafond colorés selon les spécifications
- **Validation de cartes** : Vérification automatique de la validité des cartes

### Fonctionnalités bonus
- **Rotation à la souris** : Contrôle de la caméra avec la souris (espace pour activer/désactiver)
- **Compteur FPS** : Affichage des performances en temps réel
- **Éclairage dynamique** : Assombrissement basé sur la distance
- **Interface intuitive** : Contrôles WASD + flèches

## 🛠️ Installation

### Prérequis
- GCC ou Clang
- Make
- Git
- CMake (pour MLX42)
- GLFW (macOS : `brew install glfw`)

### Étapes d'installation

```bash
# Cloner le repository
git clone https://github.com/h-claude/cub3d.git
cd cub3d

# Initialiser les sous-modules
git submodule update --init --recursive

# Compiler le projet
make
```

Le binaire `cub3D` sera créé dans le répertoire racine.

## 🚀 Utilisation

```bash
./cub3D [fichier_carte.cub]
```

### Exemple
```bash
./cub3D maps/good/subject_map.cub
```

## 🗺️ Format des cartes

Les cartes utilisent le format `.cub` avec la structure suivante :

### Spécification des textures
```
NO ./maps/textures/north_texture.png    # Texture mur Nord
SO ./maps/textures/south_texture.png    # Texture mur Sud  
WE ./maps/textures/west_texture.png     # Texture mur Ouest
EA ./maps/textures/east_texture.png     # Texture mur Est
```

### Couleurs
```
F 220,100,0    # Couleur du sol (RGB)
C 225,30,0     # Couleur du plafond (RGB)
```

### Grille de la carte
```
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

### Légende
- `1` : Mur
- `0` : Espace libre
- `N/S/E/W` : Position et orientation initiale du joueur
- Espaces : Zones inaccessibles (vide)

### Règles de validation
- La carte doit être fermée (entourée de murs)
- Un seul joueur doit être présent
- Toutes les textures et couleurs doivent être définies
- Les valeurs RGB doivent être entre 0 et 255
- Les fichiers de texture doivent être au format PNG

## 🎮 Contrôles

### Mouvement
- `W` : Avancer
- `S` : Reculer
- `A` : Se déplacer à gauche
- `D` : Se déplacer à droite

### Rotation
- `←` : Tourner à gauche
- `→` : Tourner à droite
- `Souris` : Rotation libre (après avoir appuyé sur Espace)

### Système
- `Espace` : Activer/Désactiver la rotation souris
- `Échap` : Quitter le jeu

## 🔧 Architecture technique

### Structure du projet
```
cub3d/
├── include/
│   └── cub.h              # Définitions et structures principales
├── srcs/
│   ├── main.c             # Point d'entrée et initialisation
│   ├── parsing/           # Analyse et validation des cartes
│   │   ├── get_data.c     # Extraction des données .cub
│   │   ├── map.c          # Traitement de la grille
│   │   ├── verif.c        # Validations
│   │   └── flood_fill.c   # Vérification de fermeture
│   ├── raycasting/        # Moteur de rendu 3D
│   │   ├── init_raycasting.c  # Initialisation MLX42
│   │   ├── draw_wall.c    # Calculs de raycasting
│   │   ├── input.c        # Gestion des entrées
│   │   └── utils.c        # Utilitaires de rendu
│   ├── utils/             # Fonctions utilitaires
│   └── bonus_mouse_rotate.c # Rotation souris (bonus)
├── maps/
│   ├── good/              # Cartes valides d'exemple
│   ├── bad/               # Cartes invalides pour tests
│   └── textures/          # Textures PNG
└── makefile               # Configuration de compilation
```

### Structures de données principales

```c
typedef struct cub {
    float    x_p, y_p;        // Position du joueur
    float    dir_p;           // Direction du joueur
    char     **map;           // Grille de la carte
    t_textcol *textcol;       // Textures et couleurs
    t_dr     *dr;             // Données de raycasting
    mlx_t    *mlx;            // Interface MLX42
    mlx_image_t *image;       // Buffer d'image
} t_cub;
```

### Algorithme de raycasting

1. **Initialisation** : Position et direction du joueur
2. **Lancement de rayons** : Pour chaque colonne d'écran (1920 colonnes)
3. **Calcul DDA** : Algorithme Digital Differential Analyzer
4. **Détection de collision** : Distance au premier mur rencontré
5. **Calcul de hauteur** : Projection de la distance en hauteur de mur
6. **Application de texture** : Mapping des pixels de texture
7. **Rendu** : Affichage de la colonne avec couleurs sol/plafond

### Paramètres configurables
```c
#define WIDTH 1920           // Résolution horizontale
#define HEIGHT 1080          // Résolution verticale  
#define FOV 60               // Champ de vision en degrés
#define MOVE_SPEED 0.05      // Vitesse de déplacement
#define MOUSE_SENSITIVITY 0.00075  // Sensibilité souris
```

## 📖 Exemples

### Carte simple
```bash
./cub3D maps/good/square_map.cub
```

### Carte complexe avec textures
```bash
./cub3D maps/good/dungeon.cub
```

### Test de validation
```bash
# Ces commandes doivent échouer avec des messages d'erreur appropriés
./cub3D maps/bad/player_none.cub
./cub3D maps/bad/wall_hole_north.cub
```

## 🐛 Dépannage

### Erreurs courantes

**"Error: Invalid number of arguments"**
```bash
# Solution : Fournir exactement un fichier .cub
./cub3D maps/good/subject_map.cub
```

**"Error: File is not good"**
- Vérifier que le fichier .cub existe
- S'assurer que toutes les textures et couleurs sont définies
- Contrôler la validité de la grille (fermée, un joueur unique)

**"Error: Malloc failed"**
- Fichier carte trop volumineux
- Mémoire système insuffisante

**Problèmes de compilation**
```bash
# Réinitialiser les sous-modules
git submodule update --init --recursive --force

# Nettoyer et recompiler
make fclean && make
```

**Performance faible**
- Réduire la résolution dans `cub.h` (WIDTH/HEIGHT)
- Vérifier que les textures ne sont pas trop volumineuses
- Fermer les autres applications consommatrices

### Support

Pour signaler des bugs ou demander de l'aide :
1. Vérifier que la carte respecte le format .cub
2. Tester avec les cartes d'exemple fournies
3. Consulter les messages d'erreur détaillés
4. Vérifier la compilation des dépendances (MLX42, libft)

---

**Développé par** : [h-claude](https://github.com/h-claude) & [aurban](https://github.com/aurban)  
**École** : 42  
**Langage** : C  
**Graphiques** : MLX42
