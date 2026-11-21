#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tabelahash.h"

int HashInicializar(TabelaHASH *hTabela, int capacidadeIncicial){
    
    if(capacidadeInicial <= 0) return -1;
    
    hTabela->listaDeAnagramas = calloc(capacidadeIncicial, sizeof(EntradaHash*));
    //vetor de EntradaHASH's, com chaves
    /*só os ponteiros *chave vão começar NULL, usando calloc fica melhor
    para gerenciar e não precisar fazer 2 cofirmações de existência*/
    
    if(hTabela->entradas == NULL){
        hTabela->capacidadeTotal = 0; 
        hTabela->quantidade = 0;

        return -1;//deu ruim
    }
    
    hTabela->capacidadeTotal = capacidadeInicial; 
    hTabela->quantidade = 0;

    //ja defino pesos fixos pra evitar inconsistencias na busca pelas chaves
    //por exemplo: definir um indice para busca e ser devolvido um aleatorio (ERRO)

    srand(time(NULL));

    for(int j = 0; j < TAM_PESOS; j++){
        hTabela->pesos[j] = 1 + rand() % 100;
    }

    return 1;// deu bom
}

//as letras devem ser ORDENADAS (Counting) antes de chamar esta função aqui
int StringEmChaveTransformers(TabelaHASH *hTabela, char *palavraChave){
    unsigned int soma = 0;//no código do professor Pedro
    int tamanhoString = strlen(palavraChave);

    for(int k = 0; k < tamanhoString; k++){
        soma += (unsigned int) palavraChave[k] * hTabela->pesos[k % TAM_PESOS];
        //TAM_PESOS = 5
    }
    //reutiliza os 5 pesos gerados la na inicialização pra evitar inconsitencias
    //as palavras 'roma' e 'amor' vão para o mesmo lugar, pq tem o mesmo valor 'char -> int'

    return soma % hTabela->capacidadeTotal;
}

int HashPesquisa(TabelaHash *hTabela, char *palavraChave, int *achou){
    if(!hTabela || !palavraChave) return -1;
    if(!hTabela->listaDeAnagramas) return -1;


}
/*
Entrada vazia: *chave == NULL
apenas 1 condição para representar posição livre na tabela.
*/
int HashInserir(TabelaHASH *hTabela, char *palavraChave, char *palavraNova){
    if(!hTabela || !palavraChave || !palavraNova) return -1;

    int achouChave = 0;//1 se achou
    int posicaoNaHash;
    int resultado;//int ou bool, tanto faz, confirma se inseiru ou nao

    //busca diretamente na tabela o indice da lista
    EntradaHash *entradaH;

    posicaoNaHash = HashPesquisa(hTabela, palavraChave, &achouChave);
    //recebe o indice onde achou e se achou

    if(posicaoNaHash == -1)
        return -1;

    entrada = &hTabela->listaDeAnagramas[posicaoNaHash];
    //passa o indice(endereço) da tabela hash onde a tabela de anagramas encontrada está

    //Situação 1 - se a chave existe e foi encontarda, já insere na lista corresp.
    if(achouChave == 1){
        reultado = //funcao da Lista para inserir a palavra na lista de anagramas;
        
        if(resultado == 1)//1 se bem sucedido
            return resultado;
    }
}

void HashImprimeNaOrdem(TabelaHASH *hTabela){
    
}

void HashLiberar(TabelaHASH *hTabela){
    
}
