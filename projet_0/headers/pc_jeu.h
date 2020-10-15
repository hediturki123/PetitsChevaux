#ifndef __PC_JEU_H__
#define __PC_JEU_H__

/** Définition des constantes de l'environnement de jeu. */
#define NOMBRE_JOUEURS 4 // Nombre de joueurs dans une partie ; par défaut 4, minimum 2, maximum 4.
#define NOMBRE_CHEVEAUX 4 // Nombre de cheveaux par joueurs ; par défaut 4, minimum 1.
#define TAILLE_PLATEAU 56 // Taille du plateau de jeu en nombre de cases ; par défaut 56, minimum 4 (doit être un multiple de 4).

// Une case de plateau de jeu.
// L'entier -1 (CASE_VIDE) correspond à une case vide, tandis qu'un entier n (n allant de 0 à 3) correspondent à un cheval du joueur n (CASE_Jn).
typedef enum Case {
    CASE_VIDE = -1,
    CHEVAL_J0 = 0,
    CHEVAL_J1 = 1,
    CHEVAL_J2 = 2,
    CHEVAL_J3 = 3
} Case;

// Un plateau de jeu contenant TAILLE_PLATEAU cases qui forment un parcours circulaire.
// Les cases des écuries de chaque joueur sont également contenues ici.
typedef struct Plateau {
    Case cases[TAILLE_PLATEAU];
    Case ecuries[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
} Plateau;


// Fonction permettant de vider un plateau de jeu.
// Les cases régulières aussi bien que les écuries sont réinitialisées à CASE_VIDE (-1).
void viderPlateau(Plateau*);

// Fonction permettant d'indiquer si une case est vide.
// Retourne 1 si la case est vide, 0 sinon.
int caseEstVide(Case);

// Fonction retournant un entier aléatoire compris entre min et max.
int entierAleatoire(int, int);

// Fonction permettant de lancer un dé à six faces.
// Le résultat est un entier compris entre 1 et 6.
int lancerDeDe(void);

#endif // !__PC_JEU_H__