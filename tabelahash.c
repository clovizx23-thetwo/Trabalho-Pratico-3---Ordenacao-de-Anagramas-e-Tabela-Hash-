#include <stdio.h>
#include <string.h>
#include "tabelahash.h"

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial){
    
    hTabela->listaDeAnagramas = calloc(capacidadeIncicial, sizeof(EntradaHash*));
    //vetor de EntradaHASH's, com chaves
    
    if(hTabela->entradas == NULL){
        hTabela->capacidadeTotal = 0; 
        hTabela->quantidade = 0;
        return -1;
    }
    
    hTabela->capacidadeTotal = capacidadeInicial; 
    hTabela->quantidade = 0;

    return 1;// deu bom
}
/*
Entrada vazia: *chave == NULL
apenas 1 condição para representar posição livre na tabela
*/
int HashInserir(TabelaHASH *hTabela, char *chave, char *palavraNova){
        
}

void HashImprimeNaOrdem(TabelaHASH *hTabela){
    
}

void HashLiberar(TabelaHASH *hTabela){
    
}
