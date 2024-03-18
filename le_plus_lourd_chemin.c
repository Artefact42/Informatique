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


void visualiser (matrice terrain,direction** directions,int ligne){
    printf("\n\n\n ");
    for(int i=0;i<ligne;i++){
        for(int j=0;j<terrain.col;j++){
            if (directions[i][j]==HAUT) {
                putchar('|');
            } else {putchar(' ');}
            printf("  ");
        }
        putchar('\n');
        for (int j=0;j<terrain.col;j++ ) {
            if (directions[i][j]==GAUCHE) 
                putchar('-');
            else putchar(' ');
            printf("%2i",terrain.data[i][j]);
        }
        printf("\n  ");
    }
    for(int i=ligne;i<terrain.ligne;i++){
        putchar('\n');
        for (int j=0;j<terrain.col;j++ ) {
            if (directions[i][j]==GAUCHE) 
                putchar('-');
            else putchar(' ');
            printf("%2i",terrain.data[i][j]);
        }
        putchar('\n');
    }
    getchar();
}
void visualiser_solution(matrice terrain,tableau solution){
    int x=0;
    int y=0;
    for(int i=0;i<solution.taille;i++){
        printf("%2i",terrain.data[y][x]);
        if (solution.data[i]==GAUCHE) {
            putchar('-');
            x++;
        } else {
            for(int j=x+1;j<terrain.col;j++)
                printf(" %2i",terrain.data[y][j]);
            y++;
            putchar('\n');
            for(int j=0;j<x;j++)
                printf("   ");
            printf(" |\n");
            for(int j=0;j<x;j++)
                printf("%2i ",terrain.data[y][j]);
        }
    }
    printf("%2i\n",terrain.data[y][x]);
}



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
    calcul[0] = 0;
    for (int i=0;i<terrain.col;i++)
    {
        les_directions[0][i] = GAUCHE;
        if (i!=0)
        {
            calcul[i] = calcul[i-1] + terrain.data[0][i];
        }
    }
    visualiser(terrain,les_directions ,1 );

    
    for (int i=1 ; i<terrain.ligne ; i++)
    {
        memcpy(precedente,calcul,sizeof(int)*terrain.col);
        calcul[0] = precedente[0] + terrain.data[i][0];
        les_directions[i][0]=HAUT;
        
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
        visualiser(terrain, les_directions, i+1);
    }

    
    free(calcul);
    free(precedente);
    tableau resultat = {malloc(sizeof(int)*(terrain.col+terrain.ligne-2)), (terrain.col+terrain.ligne-2)};
    assert(resultat.data!=NULL);
    int x = terrain.col-1;
    int y = terrain.ligne-1;
    
    for (int i=resultat.taille-1 ; i>=0 ; i--)
    {
        resultat.data[i]=les_directions[y][x];
        if(resultat.data[i]==HAUT)
            y--;
        else
            x--;
    }
    for (int i=0;i<terrain.ligne;i++)
    {
        free(les_directions[i]);
    }
    free(les_directions);
    return resultat;
}

int main(){

    // On commence par initialiser le générateur de nombre pseudo-aléatoires.
    srand( 459304 );

    // matrice test = {malloc(sizeof(int*)*10),10,10};
    // test.data[0] = (int[]){0,1,2,3,4,5,6,7,8,9};
    // test.data[1] = (int[]){9,9,9,9,6,6,1,1,1,1};
    // test.data[2] = (int[]){1,2,3,4,5,6,7,8,9,0};
    // test.data[3] = (int[]){9,8,7,6,5,4,3,2,1,0};
    // test.data[4] = (int[]){9,9,20,1,1,1,1,1,1,1};
    // test.data[5] = (int[]){1,2,3,3,2,1,1,2,3,1};
    // test.data[6] = (int[]){0,0,0,0,0,0,0,0,0,0};
    // test.data[7] = (int[]){0,1,2,3,4,5,6,7,7,7};
    // test.data[8] = (int[]){0,1,2,3,4,5,6,7,8,9};
    // test.data[9] = (int[]){0,1,2,3,4,5,6,7,8,9};

    int nbligne = 10;
    int nbcolonne = 20;

    matrice test = {malloc(sizeof(int*)*nbcolonne),nbligne,nbcolonne};
    for (int i = 0; i < nbligne; i++) {
        test.data[i] = malloc(sizeof(int)*nbcolonne);
        assert(test.data[i] != NULL);
        for (int j = 0 ; j < nbcolonne; j++) {

            test.data[i][j] = rand() % 100 ; // On ne veut que des nombres entre 0 et 99

        }
    }


    tableau resultat = resoudre(test);
    printf("\n\n");
    visualiser_solution(test,resultat); 

    for (int i =0;i<nbligne;i++){
        free(test.data[i]);
    }   
    free (test.data);
    free (resultat.data);
    return 0;
}
