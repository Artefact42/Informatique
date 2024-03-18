#include "huffman.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../file_prio/file_prio.h"
#define ever (;;)

arbre* huffman(tableau *marmotte)
{
    file_prio *pfile = file_prio_create(marmotte->taille);
    for(int i=0; i<marmotte->taille; i++)
    {
        arbre *arbre_tempo = malloc(sizeof(arbre));
        assert(arbre_tempo != NULL);
        arbre_tempo->gauche = NULL;
        arbre_tempo->droite = NULL;
        
        int elt = marmotte->data[i];
        arbre_tempo->valeur = elt;

        file_prio_insert(pfile,(couple){elt,arbre_tempo});
    }
    if (file_prio_est_vide(pfile))
    {
        return NULL;
    }

    for ever
    {
        arbre *arbre_tempo = malloc(sizeof(arbre));
        assert(arbre_tempo != NULL);

        int nb_g,nb_d;
        arbre *ab_g,*ab_d;

        couple
         gauche = file_prio_get(pfile),
         droite= file_prio_get(pfile);

        nb_g = gauche.cle;
        nb_d = droite.cle;

        ab_g = gauche.val;
        ab_d = droite.val;

        arbre_tempo->gauche = ab_g;
        arbre_tempo->droite = ab_d;
        arbre_tempo->valeur = 0;

        if(file_prio_est_vide(pfile))
        {
            return arbre_tempo;
        }

        file_prio_insert(pfile,(couple){nb_d+nb_g,arbre_tempo});
    }

}

void format_arbre(FILE* f, arbre* a) {

    if (a==NULL) return;
    fprintf(f, "(%d ", a->valeur);
    format_arbre(f,a->gauche);
    format_arbre(f,a->droite);
    fprintf(f, ")");
}

