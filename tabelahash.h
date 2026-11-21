#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

#define TAM_PESOS 5

//cada subLista é uma EntradaHash, com a chave e a lista e palavras
typedef struct {
    char *chave;
    Lista palavras;
} EntradaHASH;

typedef struct{
    EntradaHASH *listaDeAnagramas;
    int capacidadeTotal;
    int quantidade;
    int pesos[TAM_PESOS];
} TabelaHASH;

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial);
int HashInserir(TabelaHASH *hTabela, char *chave, char *palavraNova);
void HashImprimeNaOrdem(TabelaHASH *hTabela);
void HashLiberar(TabelaHASH *hTabela);

#endif
