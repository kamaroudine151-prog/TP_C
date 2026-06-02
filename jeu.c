#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

/* Depuis utils.c */
extern void gotoxy(int x, int y);
extern void Color(int t, int f);

typedef struct {
    char nom[50];
    char symbole;
} Joueur;

Joueur joueurs[2];
int joueur_actuel;

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
    second = 1 - joueur_actuel;

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
    getch();
}

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