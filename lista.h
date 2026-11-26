#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

void listaInicializar(Lista *lista);
int listaInserirUnica(Lista *lista, char *palavra);
/*vai ter que percorrer a lista e ver se tem uma palavra igual
a que você quer inserir, só vai entrar se não tiver na lista ainda.
Tem que manter a ordem de leitura das palavras.
*/
void listaImprimir(Lista *lista);
void listaLiberar(Lista *lista);

#endif