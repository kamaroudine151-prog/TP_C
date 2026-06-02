#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

/* ==============================
   CONSTANTES ET VARIABLES
   ============================== */

#define LIGNES   6
#define COLONNES 7

char grille[LIGNES][COLONNES];

typedef struct {
    char nom[50];
    char symbole;
} Joueur;

Joueur joueurs[2];
int joueur_actuel;


/* ==============================
   UTILS
   ============================== */

void gotoxy(int x, int y)
{
    HANDLE h;
    COORD pos;
    fflush(stdout);
    pos.X = x;
    pos.Y = y;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, pos);
}

void clrscr()
{
    system("cls");
}

void Color(int t, int f)
{
    HANDLE H;
    H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

void draw_rectangle(int x, int y, int lon, int haut)
{
    int i;
    gotoxy(x, y);          printf("%c", 218);
    gotoxy(x+lon, y);      printf("%c", 191);
    gotoxy(x, y+haut);     printf("%c", 192);
    gotoxy(x+lon, y+haut); printf("%c", 217);
    for (i = 1; i < lon; i++)
    {
        gotoxy(x+i, y);      printf("%c", 196);
        gotoxy(x+i, y+haut); printf("%c", 196);
    }
    for (i = 1; i < haut; i++)
    {
        gotoxy(x, y+i);      printf("%c", 179);
        gotoxy(x+lon, y+i);  printf("%c", 179);
    }
}


/* ==============================
   GRILLE
   ============================== */

void init_grille()
{
    int i, j;
    for (i = 0; i < LIGNES; i++)
        for (j = 0; j < COLONNES; j++)
            grille[i][j] = ' ';
}

void afficher_pion(int ligne, int col, int startX, int startY, char symbole)
{
    int offsetX = startX + 2;
    gotoxy(offsetX + 1 + col * 4, startY + 2 + ligne * 2);
    if (symbole == 'X') Color(4, 0);
    else                Color(6, 0);
    printf("%c", symbole);
    Color(7, 0);
}

void grille4puissance(int startX, int startY)
{
    int i, j;
    int offsetX = startX + 2;

    for (j = 0; j < COLONNES; j++)
    {
        gotoxy(offsetX + 1 + j * 4, startY);
        printf("%d", j);
    }

    for (i = 0; i <= LIGNES; i++)
    {
        gotoxy(offsetX, startY + 1 + i * 2);

        if (i == 0)           printf("%c", 218);
        else if (i == LIGNES) printf("%c", 192);
        else                  printf("%c", 195);

        for (j = 0; j < COLONNES; j++)
        {
            printf("%c%c%c", 196, 196, 196);
            if (j < COLONNES - 1)
            {
                if (i == 0)           printf("%c", 194);
                else if (i == LIGNES) printf("%c", 193);
                else                  printf("%c", 197);
            }
            else
            {
                if (i == 0)           printf("%c", 191);
                else if (i == LIGNES) printf("%c", 217);
                else                  printf("%c", 180);
            }
        }

        if (i < LIGNES)
        {
            gotoxy(startX, startY + 2 + i * 2);
            printf("%d", i);
            gotoxy(offsetX, startY + 2 + i * 2);
            for (j = 0; j < COLONNES; j++)
            {
                printf("%c", 179);
                printf(" %c ", grille[i][j]);
            }
            printf("%c", 179);
        }
    }
}


/* ==============================
   JEU
   ============================== */

void afficher_infos_jeu(int startX, int startY)
{
    Color(11, 0);
    gotoxy(startX, startY);
    printf("JEU DE PUISSANCE 4");

    Color(7, 0);
    gotoxy(startX, startY + 2);
    printf("Symbole de %-10s : %c", joueurs[0].nom, joueurs[0].symbole);
    gotoxy(startX, startY + 3);
    printf("Symbole de %-10s : %c", joueurs[1].nom, joueurs[1].symbole);

    gotoxy(startX, startY + 5);
    printf("                              ");
    gotoxy(startX, startY + 5);
    Color(14, 0);
    printf("C'est %s qui joue !", joueurs[joueur_actuel].nom);
    Color(7, 0);
}

void init_jeu()
{
    char choix_symbole;
    int second;

    printf("Nom du joueur 1 : ");
    scanf(" %[^\n]", joueurs[0].nom);

    printf("Nom du joueur 2 : ");
    scanf(" %[^\n]", joueurs[1].nom);

    srand(time(NULL));
    joueur_actuel = rand() % 2;
    second        = 1 - joueur_actuel;

    printf("\nLe joueur qui commence est : %s !\n",
           joueurs[joueur_actuel].nom);

    do {
        printf("Quel est votre symbole (O ou X) ? : ");
        scanf(" %c", &choix_symbole);
        choix_symbole = toupper(choix_symbole);
    } while (choix_symbole != 'X' && choix_symbole != 'O');

    joueurs[joueur_actuel].symbole = choix_symbole;
    joueurs[second].symbole = (choix_symbole == 'X') ? 'O' : 'X';

    printf("\nAppuyez sur une touche pour commencer ...");
    getchar();
    getchar();
}


/* ==============================
   JOUEUR
   ============================== */

int colonne_pleine(int col)
{
    return grille[0][col] != ' ';
}


/* ==============================
   JOUER
   ============================== */

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


/* ==============================
   VERIFICATION
   ============================== */

int compter_direction(int ligne, int col, int dl, int dc, char symbole)
{
    int count = 0;
    int l     = ligne + dl;
    int c     = col   + dc;

    while (l >= 0 && l < LIGNES &&
           c >= 0 && c < COLONNES &&
           grille[l][c] == symbole)
    {
        count++;
        l += dl;
        c += dc;
    }
    return count;
}

int verif_gain(int ligne, int col)
{
    char symbole;
    int count;

    symbole = grille[ligne][col];

    /* Horizontal */
    count = 1
        + compter_direction(ligne, col,  0,  1, symbole)
        + compter_direction(ligne, col,  0, -1, symbole);
    if (count >= 4) return 1;

    /* Vertical */
    count = 1
        + compter_direction(ligne, col,  1,  0, symbole)
        + compter_direction(ligne, col, -1,  0, symbole);
    if (count >= 4) return 1;

    /* Diagonale ↘ ↖ */
    count = 1
        + compter_direction(ligne, col,  1,  1, symbole)
        + compter_direction(ligne, col, -1, -1, symbole);
    if (count >= 4) return 1;

    /* Diagonale ↙ ↗ */
    count = 1
        + compter_direction(ligne, col,  1, -1, symbole)
        + compter_direction(ligne, col, -1,  1, symbole);
    if (count >= 4) return 1;

    return 0;
}

int grille_pleine()
{
    int j;
    for (j = 0; j < COLONNES; j++)
        if (!colonne_pleine(j)) return 0;
    return 1;
}


/* ==============================
   MAIN
   ============================== */

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

        col   = demander_colonne(5, 16);
        ligne = jouer_colonne(joueur_actuel, col, 5, 2);

        if (verif_gain(ligne, col))
        {
            clrscr();
            grille4puissance(5, 2);
            afficher_infos_jeu(35, 3);
            gotoxy(5, 18);
            Color(10, 0);
            printf("** %s a gagne ! **",
                   joueurs[joueur_actuel].nom);
            Color(7, 0);
            jeu_termine = 1;
        }
        else if (grille_pleine())
        {
            clrscr();
            grille4puissance(5, 2);
            afficher_infos_jeu(35, 3);
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
    getchar();
    getchar();

    return 0;
}