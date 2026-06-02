/* Depuis grille.c */
#define LIGNES   6
#define COLONNES 7
extern char grille[LIGNES][COLONNES];

/* Depuis joueur.c */
extern int colonne_pleine(int col);

int compter_direction(int ligne, int col, int dl, int dc, char symbole)
{
    int count = 0;
    int l = ligne + dl;
    int c = col + dc;

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