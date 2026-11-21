#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "lista.h"
#include <stdlib.h>

//cada subLista é uma EntradaHash, com a chave e a lista e palavras
typedef struct {
    char *chave;
    Lista palavras;
} EntradaHASH;

typedef struct{
    EntradaHASH *listaDeAnagramas;
    int capacidadeTotal;
    int quantidade;
} TabelaHASH;

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial);
int HashInserir(TabelaHASH *hTabela, char *chave, char *palavraNova);
void HashImprimeNaOrdem(TabelaHASH *hTabela);
void HashLiberar(TabelaHASH *hTabela);

#endif
