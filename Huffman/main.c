#include "huffman.h"

int main()
{
    int  josephine[8] = {2,2,2,4,4,5,5,6};
    tableau rennee = (tableau){
        8,
        josephine
    };

    arbre *nicolas = huffman(&rennee);
    format_arbre(stdout, nicolas);
    return 0;
}
