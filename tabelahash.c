#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tabelahash.h"

int HashInicializar(TabelaHASH *hTabela, int capacidadeInicial){
    
    if(capacidadeInicial <= 0) return -1;

    hTabela->listaDeAnagramas = calloc(capacidadeInicial, sizeof(EntradaHash));
    //vetor de EntradaHASH's, com chaves
    /*só os ponteiros *chave vão começar NULL, usando calloc fica melhor
    para gerenciar e não precisar fazer 2 cofirmações de existência*/
    
    if(hTabela->listaDeAnagramas == NULL){
        hTabela->capacidadeTotal = 0; 
        hTabela->quantidade = 0;

        return -1;//deu ruim
    }
    
    hTabela->capacidadeTotal = capacidadeInicial; 
    hTabela->quantidade = 0;

    //ja defino pesos fixos pra evitar inconsistencias na busca pelas chaves
    //por exemplo: definir um indice para busca e ser devolvido um aleatorio (ERRO)

    //inicilaizando cada ponteiro da tabela com NULL
    for(int i = 0; i < hTabela->capacidadeTotal; i++){
        hTabela->listaDeAnagramas[i].chave = NULL;
        hTabela->listaDeAnagramas[i].palavrasLista = NULL;
    }

    //gera os pesos aleatórios 1 vez apenas na criação da tabela
    srand(time(NULL));

    for(int j = 0; j < TAM_PESOS; j++){
        hTabela->pesos[j] = 1 + (int) (100.0 * rand() % 100);
    }

    return 1;// deu bom
}

//as letras devem ser ORDENADAS antes de chamar esta função aqui
int StringEmChaveTransformers(TabelaHASH *hTabela, char *palavraChave){
    unsigned int soma = 0;//no código do professor Pedro (soma sempre positiva)
    int tamanhoString = strlen(palavraChave);

    for(int k = 0; k < tamanhoString; k++){
        soma += (unsigned char) palavraChave[k] * hTabela->pesos[k % TAM_PESOS];
        //TAM_PESOS = 5
    }
    //reutiliza os 5 pesos gerados la na inicialização
    //as palavras que são angramas entre si têm a MESMA CHAVE quando estão ORDENADAS

    return soma % hTabela->capacidadeTotal;
}

//função que tá no slide do professor
/*
modifiquei ela para retornar também o índice onde a CHAVE foi encontrada
por que facilitará na necessidade de inerir uma palavra nova
*/
int HashLocalizaPosicao(TabelaHASH *hTabela, char *palavraChave, int *achou){
    if(!hTabela || !palavraChave) return -1;
    if(!hTabela->listaDeAnagramas) return -1;

    *achou = 0;//caso não encontre uma chave EXISTENTE

    int index = 0;
    int posicaoCalculada;
    int inicio = StringEmChaveTransformers(hTabela, palavraChave);
    //transforma a string em chave na busca

    while(index < hTabela->capacidadeTotal){
        
        posicaoCalculada = ((unsigned int) inicio + index) % hTabela->capacidadeTotal;
        // o unsigned dobra a capacidade de valroes positivos do int, conforme o professor explicou

        //se achou uma posição vazia
        if(hTabela->listaDeAnagramas[posicaoCalculada].chave == NULL)
            return posicaoCalculada;
            //para inserir uma NOVA CHAVE quando não existir uma lista do tipo correspondente ao anagrama
        
        //se a as strings forem IGUAIS strcmp == 0
        if(strcmp(hTabela->listaDeAnagramas[posicaoCalculada].chave, palavraChave) == 0){
            *achou = 1;//para uma lista já existente
            return posicaoCalculada;
        }

        //caso de COLISÃO continua a verificação com a próxima posição
        index++;
    }

    //se a tabela tá cheia
    return -1;
}

/*
Entrada vazia: *chave == NULL
apenas 1 condição para representar posição livre na tabela.
*/
int HashInserir(TabelaHASH *hTabela, char *palavraChave, char *palavraNova){

    if(!hTabela || !palavraChave || !palavraNova) return -1;

    int achouNaExistente = 0;// 1 se achou
    int posicaoNaHash;
    int resultado;//int ou bool, tanto faz, confirma se inseiru ou nao

    EntradaHash *entradaH;//comunicador entre o TAD da Tabela Hash e o TAD lista

    posicaoNaHash = HashLocalizaPosicao(hTabela, palavraChave, &achouNaExistente);
    //recebe o indice onde achou e se achou (Hash Pesquisa Adaptada)

    if(posicaoNaHash == -1)
        return -1;

    entradaH = &hTabela->listaDeAnagramas[posicaoNaHash];
    //passa o indice(endereço) da tabela hash onde a tabela de anagramas encontrada está

    //SITUAÇÃO 1 - se a chave existe e foi encontarda, já insere na lista corresp.
    if(achouNaExistente == 1){
        resultado = listaInserirUnica(entradaH->palavrasLista, palavraNova);//funcao da Lista para inserir a palavra NORMAL na lista de anagramas
        //'entradaH->palavrasLista' é do tipo 'Lista' - então usa ela pra comunicação entre o TAD Lista
        
        if(resultado == 1)//1 se bem sucedido
            return resultado;
    }
    //SITUAÇÃO 2 - se a chave AINDA NÃO EXISTE e preciso inserir na TABELA
    else {
    //se não tem alguma existente e tiver uma posição livre na tabela para inserir
        char *novaChave = malloc(strlen(palavraChave) + 1);//+1 para o '/0'

        if(!novaChave) return -1;

        //passa a nova palavra para a chave da nova lista que vai ser criada
        strcpy(novaChave, palavraChave);
        
        //Aloca memória pro meu TAD Lista
        Lista *ListaNova = malloc(sizeof(Lista));

        if(!ListaNova){
            free(novaChave);
            return -1;
        }

        listaInicializar(novaChave->palavrasLista);

        //funcao da Lista para inserir a PALAVRA NOVA na lista de anagramas
        resultado = listaInserirUnica(entradaH->palavrasLista, palavraChave);
        
        //se deu ruim (resultado = -1) lebera tudo e finaliza
        if(resultado == -1){
            listaLiberar(novaChave->palavrasLista);
            free(novaChave);
            free(ListaNova);
            return -1;
        }

        entradaH->chave = novaChave;//passa a novaChave já atualizada pra chave da NOVA LISTA
        entradaH->palavrasLista = ListaNova;//tranfere a NOVA LISTA para a TABELA
        
        hTabela->quantidade++;//aumenta a quantidade atual da lista
        
        return 1;//deu CERTO
    }
}

void HashImprimeNaOrdem(TabelaHASH *hTabela){
    
}

void HashLiberar(TabelaHASH *hTabela){
    
    if(!hTabela) return;

    for(int i = 0; i < hTabela->capacidadeTotal; i++){
        if(hTabela->listaDeAnagramas[i]->chave != NULL){
            free(hTabela->listaDeAnagramas[i]->chave);
            ListaLiberar(hTabela->listaDeAnagramas[i]->palavrasLista);
        }
    }

    hTabela = NULL;
}
