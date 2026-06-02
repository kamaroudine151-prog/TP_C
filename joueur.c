/* Depuis grille.c */
#define LIGNES   6
#define COLONNES 7
extern char grille[LIGNES][COLONNES];

int colonne_pleine(int col)
{
    return grille[0][col] != ' ';
}