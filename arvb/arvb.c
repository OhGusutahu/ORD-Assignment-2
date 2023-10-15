#include <stdio.h>
#include <stdlib.h>
#include "arvb.h"

typedef struct _cabecalho CABECALHO;

typedef struct _pagina PAGINA;

int le_pagina(int rrn, PAGINA *pag)
{
    // ****** ****** implemente a funcao ****** ******

    int offset = sizeof(CABECALHO) + rrn * sizeof(PAGINA);
    if(fseek(arvb, offset, SEEK_SET) != 0) {
        return 0;
    }
    /* leia PAG do arquivo árvore-B */
    
}

int escreve_pagina(int rrn, PAGINA *pag)
{
    // ****** ****** implemente a funcao ****** ******

    int offset = sizeof(CABECALHO) + rrn * sizeof(PAGINA);
    if(fseek(arvb, offset, SEEK_SET) != 0) {
        return 0;
    }
    /* escreve PAG no arquivo árvore-B */

}

int novo_rrn()
{
    int tamanhopag = sizeof(PAGINA);
    int tamanhocab = sizeof(CABECALHO);
    
    fseek(arvb, 0, SEEK_END);
    int byteoffset = ftell(arvb);

    return (byteoffset - tamanhocab) / tamanhopag;
}

PAGINA inicializa_pagina()
{
    PAGINA pag;
    int i = 0;
    pag.num_chaves = 0;
    for(i = 0; i < ORDEM-1; i++) {
        pag.chaves[i] = NULO;
        pag.filhos[i] = NULO;
    }
    pag.filhos[i] = NULO;

    return pag;
}

void insere_na_pagina(int chv_pro, int rrn_pro, int chaves[], int filhos[], int *num_chaves)
{
    int i = num_chaves;
    while(i > 0 && chv_pro < chaves[i - 1]) {
        chaves[i] = chaves[i - 1];
        filhos[i + 1] = filhos[i];
        i--;
    }
    num_chaves++;
    chaves[i] = chv_pro;
    filhos[i + 1] = rrn_pro;
}

void divide(int chave_i, int rrn_i, PAGINA *pag, int *chave_pro, int *filho_d_pro, PAGINA *novapag)
{
    // ****** ****** implemente a funcao ****** ******

    PAGINA pagaux = *pag;
    insere_na_pagina(chave_i, rrn_i, pagaux.chaves, pagaux.filhos, &pagaux.num_chaves);
    int MEIO = ORDEM/2;
    *chave_pro = pagaux.chaves[MEIO];
    /* faça FILHO_D_PRO receber o RRN que o NOVAPAG terá no arquivo árvore-B */
    *filho_d_pro = novo_rrn(); // ????????

    /* Copie as chaves e ponteiros
        que vêm antes de CHAVE_PRO para PAG */
    
    *pag = inicializa_pagina();
    int i = 0;
    while(i < MEIO) {
        pag->chaves[i] = pagaux.chaves[i];
        pag->filhos[i] = pagaux.filhos[i];
        pag->num_chaves++;
        i++;
    }
    pag->filhos[i] = pagaux.filhos[i];

    /* Copie as chaves e ponteiros
        que vêm depois de CHAVE_PRO para NOVAPAG */
    
    *novapag = inicializa_pagina();
    i = MEIO + 1;
    while (i < ORDEM) {
        novapag->chaves[novapag->num_chaves] = pagaux.chaves[i];
        novapag->filhos[novapag->num_chaves] = pagaux.filhos[i];
        novapag->num_chaves++;
        i++;
    }
    novapag->filhos[novapag->num_chaves] = pagaux.filhos[i];

}

int insere(int rrn_atual, int chave, int *filho_d_pro, int *chave_pro)
{
    PAGINA pag = inicializa_pagina();
    int pos = 0, ACHOU = 0;

    if(rrn_atual == NULO) { // condição de parada
        chave_pro = chave;
        filho_d_pro = NULO;
        return PROMOCAO;
    }
    else {
        le_pagina(rrn_atual, &pag);

        ACHOU = busca_na_pagina(chave, pag, &pos);
    }
    if(ACHOU) {
        printf("\nChave duplicada!\n");
        return ERRO;
    }

    int rrn_pro, chv_pro;

    int RETORNO = insere(pag.filhos[pos], chave, &rrn_pro, &chv_pro);
    if(RETORNO == SEM_PROMOCAO || RETORNO == ERRO) {
        return RETORNO;
    }
    else {
        if(pag.num_chaves < ORDEM - 1) {
            insere_na_pagina(chv_pro, rrn_pro, pag.chaves, pag.filhos, &pag.num_chaves);
            escreve_pagina(rrn_atual, &pag);
            return SEM_PROMOCAO;
        }
        else {
            PAGINA novapag;

            divide(chv_pro, rrn_pro, &pag, chave_pro, filho_d_pro, &novapag);
            escreve_pagina(rrn_atual, &pag);
            escreve_pagina(filho_d_pro, &novapag);
            return PROMOCAO;
        }
    }
}

int busca_na_pagina(int chave, PAGINA pag, int *pos)
{
    int i = 0;
    while(i < pag.num_chaves && chave > pag.chaves[i]) i++;
    *pos = i;
    if(*pos < pag.num_chaves && chave == pag.chaves[*pos]) {
        return ENCONTRADO;
    } else return NAO_ENCONTRADO;
}

int busca(int rrn, int chave, int *rrn_encontrado, int *pos_encontrada)
{
    PAGINA pag;
    int pos;

    if(rrn == NULO) { // condição de parada
        return NAO_ENCONTRADO;
    }
    else {
        le_pagina(rrn, &pag);

        int ACHOU = busca_na_pagina(chave, pag, &pos);
        /* POS recebe a posição em que a CHAVE ocorre 
            ou deveria ocorrer se estivesse em PAG */

        if(ACHOU) {
            *rrn_encontrado = rrn; // RRN da página que contém a chave
            pos_encontrada = pos; // posição da chave na página
            return ENCONTRADO;
        }
        else { // siga o ponteiro para a próxima página da busca
            return(busca(pag.filhos[pos], chave, &rrn_encontrado, &pos_encontrada));
        }
    }
}

int imprime_pagina(int rrn)
{
    // ****** ****** implemente a funcao ****** ******
}

int imprime_arvore()
{
    // ****** ****** implemente a funcao ****** ******
}

int leia_chave(FILE * chaves)
{
    // ****** ****** implemente a funcao ****** ******
}
