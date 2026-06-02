#include <stdio.h>
#include <windows.h>
#include "utils.h"

/* ==============================
   CONSTANTES ET VARIABLES
   ============================== */

#define LIGNES   6
#define COLONNES 7

char grille[LIGNES][COLONNES];


/* ==============================
   FONCTIONS
   ============================== */

/* Initialise toutes les cases à vide */
void init_grille()
{
    int i, j;
    for (i = 0; i < LIGNES; i++)
        for (j = 0; j < COLONNES; j++)
            grille[i][j] = ' ';
}

/* Affiche la grille à la position (startX, startY) */
void grille4puissance(int startX, int startY)
{
    int i, j;
    int offsetX = startX + 2;

    /* Numéros de colonnes */
    for (j = 0; j < COLONNES; j++)
    {
        gotoxy(offsetX + 1 + j * 4, startY);
        printf("%d", j);
    }

    /* Dessiner la grille */
    for (i = 0; i <= LIGNES; i++)
    {
        gotoxy(offsetX, startY + 1 + i * 2);

        if (i == 0)           printf("%c", 218); /* ┌ */
        else if (i == LIGNES) printf("%c", 192); /* └ */
        else                  printf("%c", 195); /* ├ */

        for (j = 0; j < COLONNES; j++)
        {
            printf("%c%c%c", 196, 196, 196); /* ─── */

            if (j < COLONNES - 1)
            {
                if (i == 0)           printf("%c", 194); /* ┬ */
                else if (i == LIGNES) printf("%c", 193); /* ┴ */
                else                  printf("%c", 197); /* ┼ */
            }
            else
            {
                if (i == 0)           printf("%c", 191); /* ┐ */
                else if (i == LIGNES) printf("%c", 217); /* ┘ */
                else                  printf("%c", 180); /* ┤ */
            }
        }

        /* Ligne de contenu */
        if (i < LIGNES)
        {
            gotoxy(startX, startY + 2 + i * 2);
            printf("%d", i);

            gotoxy(offsetX, startY + 2 + i * 2);
            for (j = 0; j < COLONNES; j++)
            {
                printf("%c", 179); /* │ */
                printf(" %c ", grille[i][j]);
            }
            printf("%c", 179); /* │ */
        }
    }
}

/* Affiche un pion coloré dans la case (ligne, col) */
void afficher_pion(int ligne, int col, int startX, int startY, char symbole)
{
    int offsetX = startX + 2;
    gotoxy(offsetX + 1 + col * 4, startY + 2 + ligne * 2);

    if (symbole == 'X')
        Color(4, 0); /* Rouge */
    else
        Color(6, 0); /* Jaune */

    printf("%c", symbole);
    Color(7, 0);
}