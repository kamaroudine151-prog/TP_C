#include <stdio.h>
#include <conio.h>

/* Depuis utils.c */
extern void clrscr();

/* Depuis grille.c */
extern void init_grille();
extern void grille4puissance(int startX, int startY);

/* Depuis jeu.c */
extern void init_jeu();
extern void afficher_infos_jeu(int startX, int startY);
extern int joueur_actuel;

/* Depuis jouer.c */
extern int jouer_colonne(int num_joueur, int col, int startX, int startY);
extern int demander_colonne(int startX, int startY);

/* Depuis verification.c */
extern int verif_gain(int ligne, int col);
extern int grille_pleine();

int main()
{
    int col;
    int ligne;
    int jeu_termine = 0;

    clrscr();
    init_grille();
    grille4puissance(5, 2);
    init_jeu();

    while (!jeu_termine)
    {
        clrscr();
        grille4puissance(5, 2);
        afficher_infos_jeu(35, 3);

        col  = demander_colonne(5, 16);
        ligne = jouer_colonne(joueur_actuel, col, 5, 2);

        if (verif_gain(ligne, col))
        {
            clrscr();
            grille4puissance(5, 2);
            gotoxy(5, 18);
            Color(10, 0);
            printf("** %s a gagne ! **", joueurs[joueur_actuel].nom);
            Color(7, 0);
            jeu_termine = 1;
        }
        else if (grille_pleine())
        {
            clrscr();
            grille4puissance(5, 2);
            gotoxy(5, 18);
            Color(14, 0);
            printf("** Match nul ! La grille est pleine **");
            Color(7, 0);
            jeu_termine = 1;
        }
        else
        {
            joueur_actuel = 1 - joueur_actuel;
        }
    }

    gotoxy(5, 20);
    printf("Appuyez sur une touche pour quitter...");
    getch();
    return 0;
}