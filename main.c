#include <stdio.h>
#include <conio.h>

/* ==============================
   DEPUIS utils.c
   ============================== */
extern void gotoxy(int x, int y);
extern void clrscr();
extern void Color(int t, int f);
extern void draw_rectangle(int x, int y, int lon, int haut);

/* ==============================
   DEPUIS grille.c
   ============================== */
#define LIGNES   6
#define COLONNES 7
extern char grille[LIGNES][COLONNES];
extern void init_grille();
extern void grille4puissance(int startX, int startY);
extern void afficher_pion(int ligne, int col,
                          int startX, int startY, char symbole);

/* ==============================
   DEPUIS jeu.c
   ============================== */
typedef struct {
    char nom[50];
    char symbole;
} Joueur;

extern Joueur joueurs[2];
extern int joueur_actuel;
extern void init_jeu();
extern void afficher_infos_jeu(int startX, int startY);

/* ==============================
   DEPUIS joueur.c
   ============================== */
extern int colonne_pleine(int col);

/* ==============================
   DEPUIS jouer.c
   ============================== */
extern int jouer_colonne(int num_joueur, int col,
                         int startX, int startY);
extern int demander_colonne(int startX, int startY);

/* ==============================
   DEPUIS verification.c
   ============================== */
extern int verif_gain(int ligne, int col);
extern int grille_pleine();


/* ==============================
   MAIN
   ============================== */
int main()
{
    int col;
    int ligne;
    int jeu_termine = 0;

    /* Initialisation */
    clrscr();
    init_grille();
    grille4puissance(5, 2);
    init_jeu();

    /* Boucle principale */
    while (!jeu_termine)
    {
        clrscr();
        grille4puissance(5, 2);
        afficher_infos_jeu(35, 3);

        /* Tour du joueur actuel */
        col  = demander_colonne(5, 16);
        ligne = jouer_colonne(joueur_actuel, col, 5, 2);

        /* Vérifier victoire */
        if (verif_gain(ligne, col))
        {
            clrscr();
            grille4puissance(5, 2);
            afficher_infos_jeu(35, 3);
            gotoxy(5, 18);
            Color(10, 0); /* Vert */
            printf("** %s a gagne ! **",
                   joueurs[joueur_actuel].nom);
            Color(7, 0);
            jeu_termine = 1;
        }
        /* Vérifier match nul */
        else if (grille_pleine())
        {
            clrscr();
            grille4puissance(5, 2);
            afficher_infos_jeu(35, 3);
            gotoxy(5, 18);
            Color(14, 0); /* Jaune */
            printf("** Match nul ! La grille est pleine **");
            Color(7, 0);
            jeu_termine = 1;
        }
        /* Changer de joueur */
        else
        {
            joueur_actuel = 1 - joueur_actuel;
        }
    }

    /* Fin du jeu */
    gotoxy(5, 20);
    printf("Appuyez sur une touche pour quitter...");
    getchar();

    return 0;
}