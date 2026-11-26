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

//função que tá no slide do professor
int HashPesquisa(TabelaHash *hTabela, char *palavraChave, int *achou){
    if(!hTabela || !palavraChave) return -1;
    if(!hTabela->listaDeAnagramas) return -1;

    int index = 0;
    int posicaoCalculada;
    int inicio = StringEmChaveTransformers(hTabela, palavraChave);
    //transforma a string em chave na busca

    while(index < hTabela->capacidadeTotal){
        
        posicaoCalculada = (inicio + index) % hTabela->capacidadeTotal;

        //se achou uma posição vazia
        if(hTabela->listaDeAnagramas[posicaoCalculada].chave == NULL)
            return posicao;//para quando não existe uma lista do tipo correspondente ao anagrama
        
        //se a as strings forem IGUAIS strcmp == 0
        if(strcmp(hTabela->listaDeAnagramas[posicaoCalculada].chave, palavraChave) == 0){
            *achou = 1;//para uma lista já existente
            return posicao;
        }
        //caso de colisão continua a verificação com a próxima posição
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

    posicaoNaHash = HashPesquisa(hTabela, palavraChave, &achouNaExistente);
    //recebe o indice onde achou e se achou

    if(posicaoNaHash == -1)
        return -1;

    entrada = &hTabela->listaDeAnagramas[posicaoNaHash];
    //passa o indice(endereço) da tabela hash onde a tabela de anagramas encontrada está

    //Situação 1 - se a chave existe e foi encontarda, já insere na lista corresp.
    if(achouNaExistente == 1){
        resultado = listaInserirUnica(&entradaH->palavrasLista, palavraChave);//funcao da Lista para inserir a palavra na lista de anagramas
        //'&entradaH->palavrasLista' é do tipo 'Lista' - então usa ela pra comunicação entre o TAD Lista
        
        if(resultado == 1)//1 se bem sucedido
            return resultado;
    }
    else {//Situação 2 - se a chave AINDA NÃO EXISTE e preciso inserir
    //se não tem alguma existente e tiver uma posição livre na tabela para inserir
        EntradaHASH *novaChave = malloc(sizeof(strlen(palavraChave)) + 1);//+1 para o '/0'

        if(!novaChave) return -1;

        //passa a nova palavra para a chave da nova lista que vai ser criada
        strcpy(novaChave, palavraChave);

        listaInicializar(&novaChave->palavrasLista);

        resultado = listaInserirUnica(&entradaH->palavrasLista, palavraChave);//funcao da Lista para inserir a palavra na lista de anagramas
        
        if(resultado == -1){//se deu ruim lebera tudo e finaliza
            listaLiberar(&novaChave->palavrasLista);
            free(novaChave);
            return -1;
        }

        entradaH->chave = novaChave;//passa a novaChave já atualizada pra chave da NOVA LISTA
        hTabela->quantidade++;
    }

    return -1;
}

void HashImprimeNaOrdem(TabelaHASH *hTabela){
    
}

void HashLiberar(TabelaHASH *hTabela){
    
}
