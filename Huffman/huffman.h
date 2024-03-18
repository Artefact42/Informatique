#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>

typedef struct _arbre {
    int valeur;
    struct _arbre* gauche;
    struct _arbre* droite;
} arbre;

typedef struct {
    int taille;
    int *data;
} tableau;


void format_arbre(FILE*, arbre*);
arbre* huffman(tableau*);

#endif //HUFFMAN_H
