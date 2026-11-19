#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelahash.h"

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial){
    hTabela->listaDeAnagramas = calloc(capacidadeIncicial, sizeof(EntradaHash*));
    //vetor de EntradaHASH's
    
}

int HashInserir(TabelaHASH *hTabela, char *chave, char *palavraNova);
void HashImprimeNaOrdem(TabelaHASH *hTabela);
void HashLiberar(TabelaHASH *hTabela);