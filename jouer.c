#include <stdio.h>
#include <windows.h>

/* Depuis utils.c */
extern void gotoxy(int x, int y);
extern void Color(int t, int f);

/* Depuis grille.c */
#define LIGNES   6
#define COLONNES 7
extern char grille[LIGNES][COLONNES];
extern void afficher_pion(int ligne, int col,
                          int startX, int startY, char symbole);

/* Depuis jeu.c */
typedef struct { char nom[50]; char symbole; } Joueur;
extern Joueur joueurs[2];
extern int joueur_actuel;

/* Depuis joueur.c */
extern int colonne_pleine(int col);

int jouer_colonne(int num_joueur, int col, int startX, int startY)
{
    int ligne;
    int i;
    char symbole;

    if (colonne_pleine(col)) return -1;

    symbole = joueurs[num_joueur].symbole;

    ligne = LIGNES - 1;
    while (ligne >= 0 && grille[ligne][col] != ' ')
        ligne--;

    for (i = 0; i <= ligne; i++)
    {
        if (i > 0)
        {
            gotoxy(startX + 3 + col * 4, startY + 2 + (i-1) * 2);
            printf(" ");
        }
        afficher_pion(i, col, startX, startY, symbole);
        Sleep(120);
    }

    grille[ligne][col] = symbole;
    return ligne;
}

int demander_colonne(int startX, int startY)
{
    int col;

    do
    {
        gotoxy(startX, startY + 1);
        printf("                                        ");
        gotoxy(startX, startY);
        printf("                                        ");
        gotoxy(startX, startY);
        Color(14, 0);
        printf("%s, vous jouez quelle colonne ? : ",
               joueurs[joueur_actuel].nom);
        Color(7, 0);
        scanf("%d", &col);

        if (col < 0 || col >= COLONNES)
        {
            gotoxy(startX, startY + 1);
            Color(4, 0);
            printf("Colonne invalide ! Entrez (0 a %d)", COLONNES - 1);
            Color(7, 0);
        }
        else if (colonne_pleine(col))
        {
            gotoxy(startX, startY + 1);
            Color(4, 0);
            printf("Colonne pleine ! Choisissez une autre.");
            Color(7, 0);
        }
    } while (col < 0 || col >= COLONNES || colonne_pleine(col));

    return col;
}