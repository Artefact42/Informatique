#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


typedef struct {
    int** data;
    int ligne;
    int col;
} matrice;

typedef struct {
    int* data;
    int taille;
} tableau;

typedef enum {
    HAUT,
    GAUCHE,
} direction;

tableau resoudre(matrice terrain)
{
    int* precedente = malloc(sizeof(int)*terrain.col);
    assert(precedente!=NULL);
    int* calcul = malloc(sizeof(int)*terrain.col);
    assert(calcul!=NULL);
    direction** les_directions = malloc(sizeof(direction*)*terrain.ligne);
    assert(les_directions!=NULL);
    for (int i=0;i<terrain.ligne;i++)
    {
        les_directions[i] = malloc(sizeof(direction)*terrain.col);
        assert(les_directions[i]!=NULL);
    }
    for (int i=0;i<terrain.col;i++)
    {
        les_directions[0][i] = GAUCHE;
        if (i!=0)
        {
            calcul[i] = calcul[i-1] + terrain.data[0][i];
        }
    }
    for (int i=1 ; i<terrain.ligne ; i++)
    {
        memcpy(calcul,precedente,terrain.col);
        calcul[0] = precedente[0] + terrain.data[0][i];
        for (int j=1 ; j<terrain.col ; j++)
        {
            int max;
            if (precedente[j]>calcul[j-1])
            {
                les_directions[i][j] = HAUT;
                max = precedente[j];
            }
            else
            {
                les_directions[i][j]=GAUCHE;
                max = calcul[j-1];
            }
            calcul[j] = terrain.data[i][j]+max;
        }
    }
    free(calcul);
    free(precedente);
    tableau resultat = {malloc(sizeof(int)*(terrain.col+terrain.ligne-2)), (terrain.col+terrain.ligne-2)};
    assert(resultat.data!=NULL);
    int x = terrain.col;
    int y = terrain.ligne;
    for (int i=resultat.taille-1 ; i<=0 ; i--)
    {
        resultat.data[i]=les_directions[x][y];
        if(resultat.data[i]==HAUT)
        {
            y--;
        }
        else
        {
            x--;
        }
    }
    for (int i=0;i<terrain.ligne;i++)
    {
        free(les_directions[i]);
    }
    free(les_directions);
    return resultat;
}

int main(){
    return 42;
}
