#include <stdio.h>
#include <stdlib.h>
#include "arvb.h"

typedef struct _cabecalho CABECALHO;

typedef struct _pagina PAGINA;

int le_pagina(int rrn, PAGINA *pag)
{
    // implemente a funcao
}

int escreve_pagina(int rrn, PAGINA *pag)
{
    // implemente a funcao
}

int novo_rrn()
{
    // implemente a funcao
}

void inicializa_pagina(PAGINA *pag)
{
    // implemente a funcao
}

void insere_na_pagina(int chv_pro, int rrn_pro, int chaves[], int filhos[], int *num_chaves)
{
    // implemente a funcao
}

void divide(int chave_i, int rrn_i, PAGINA *pag, int *chave_pro, int *filho_d_pro, PAGINA *novapag)
{
    // implemente a funcao
}

int insere(int rrn_atual, int chave, int *filho_d_pro, int *chave_pro)
{
    // implemente a funcao
}

int busca_na_pagina(int chave, PAGINA pag, int *pos)
{
    // implemente a funcao
}

int busca(int rrn, int chave, int *rrn_encontrado, int *pos_encontrada)
{
    // implemente a funcao
}

int imprime_pagina(int rrn)
{
    // implemente a funcao
}

int imprime_arvore()
{
    // implemente a funcao
}

int leia_chave(FILE * chaves)
{
    // implemente a funcao
}