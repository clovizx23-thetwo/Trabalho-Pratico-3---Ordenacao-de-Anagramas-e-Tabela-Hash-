#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "lista.h"

#define TAM_PESOS 5

//cada subLista é uma EntradaHash, com a chave e a lista e palavras
typedef struct {
    char *chave;// chave de identificação (ordenada)
    Lista *palavrasLista;// lista das palavras
} EntradaHASH;

typedef struct{
    //não é vetor de ponteiros, é vetor de ENTRADAS
    EntradaHASH *listaDeAnagramas;// meu vetor de EntradaHASH (listas e chaves) que aponta para as Listas
    int capacidadeTotal;
    int quantidade;
    int pesos[TAM_PESOS];
} TabelaHASH;

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial);
int HashInserir(TabelaHASH *hTabela, char *chave, char *palavraNova);
void HashImprimeNaOrdem(TabelaHASH *hTabela);
void HashLiberar(TabelaHASH *hTabela);

#endif
