#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct _arbre {
    int valeur;
    _arbre* gauche;
    _arbre* droite;
} arbre;

typedef struct {
    int taille;
    int *data;
} tableau;


void format_arbre(FILE*, arbre*);
arbre* huffman(tableau*);

#endif //HUFFMAN_H
