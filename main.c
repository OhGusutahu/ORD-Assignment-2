/**
 * TRABALHO 2 de Organização e Recuperação de Dados
 * 
 * Docente: Paulo Roberto de Oliveira
 * Discente: Gustavo Giozeppe Bulgarelli (RA 129658)
 * 
 * construir e manter um índice
 * estruturado como uma Árvore-B.
**/

/* Obs.:
 * #pragma region name_region ~~ #pragma endregion
 * é usado pelo VSCode para separar o código em regiões
 * não afeta a compilação e/ou é ignorado por outros compliladores
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arvb\arvb.h"

#define NOME_ARQ_DADOS "dados.dat"
#define NOME_ARQ_BTREE "btree.dat"
#define BUFFER_TAM 512 // tamanho grande para facilitar
#define CAMPOS 6 // cada registro tem seis campos em dados.dat

// ponteiro do arquivo btree.dat (como variável global)
FILE *arvb;

typedef struct {
    char op_tipo; // b (busca), i (inserção)
    char op_info[BUFFER_TAM]; // as informações da operação
} operacao;

operacao op_leitura(FILE *op_arq);
// operações a serem executadas
void busca_reg(int IDENTIFICADOR, FILE *arq_dados/*, FILE *arvb */);
void insercao_reg(char *novo_reg, FILE *arq_dados/*, FILE *arvb */);

// funções principais
void cria_btree(FILE *arq_dados/*, FILE *arvb */);
void executa_operacoes(FILE *arq_dados/*, FILE *arvb */, FILE *op_arq);
void imprime_btree(/* FILE *arvb */);

// auxiliares
void gerenciador(int *raiz, FILE *arq_dados);

int main(int argc, char *argv[])
{
    FILE *arq_dados = fopen(NOME_ARQ_DADOS, "ab+");

    if(arq_dados == NULL) {
        // caso dados.dat não possa ser encontrado
        fprintf(stderr, "Não foi possivel encontrar o arquivo de dados. Tente novamente.");
        exit(EXIT_FAILURE);
    }

    if(argc == 2 && strcmp(argv[1], "-c") == 0) {
        printf("Modo de criacao do indice ativado ...\n");
        arvb = fopen(NOME_ARQ_BTREE, "wb+");
        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Houve algum erro na inicializacao do arquivo da Arvore-B, tente novamente.");
            exit(EXIT_FAILURE);
        }

        cria_btree(arq_dados);

        fclose(arvb);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        arvb = fopen(NOME_ARQ_BTREE, "rb+");
        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Não foi possivel encontrar o arquivo da Arvore-B. Tente novamente.");
            exit(EXIT_FAILURE);
        }
        
        FILE *op_arq = fopen(argv[2], "r");
        /* sem if(op_arq == NULL) considerando não necessário a verificação da integridade do arquivo */
        
        executa_operacoes(arq_dados/* , arvb */, op_arq);
        
        fclose(op_arq);
        fclose(arvb);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {
        printf("Modo de impressao da Arvore-B ativado ...\n");
        arvb = fopen(NOME_ARQ_BTREE, "rb");

        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Não foi possivel encontrar o arquivo da Arvore-B. Tente novamente.");
            exit(EXIT_FAILURE);
        }

        imprime_btree(/* arvb */);

        fclose(arvb);

    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s -c\n", argv[0]);
        fprintf(stderr, "$ %s -e nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    fclose(arq_dados);
    return 0;
}

#pragma region Operacoes

operacao op_leitura(FILE *op_arq)
{
    // lê no arquivo de operações a operação a ser realizada
    operacao op;

    op.op_tipo = (char)fgetc(op_arq);

    fseek(op_arq,1,SEEK_CUR);
    // setando o ponteiro L/E na posição da informação da operação

    fgets(op.op_info, BUFFER_TAM, op_arq);

    if(op.op_info[strlen(op.op_info) - 1] == '\n') op.op_info[strlen(op.op_info) - 1] = '\0';
    // remover '\n' da informação da operação para não afetar a leitura
    else op.op_info[strlen(op.op_info)] = '\0';

    return op;
}

void busca_reg(int IDENTIFICADOR, FILE *arq_dados/*, FILE *arvb */)
{
    // ****** ****** implemente a funcao ****** ******

    // busca de registro através da chave primária
    /* As buscas deverão ser realizadas no índice, i.e., no arquivo btree.dat.
        Uma vez localizada a chave no índice, o byte- offset do registro correspondente
        deverá ser recuperado e o registro deverá ser acessado de forma direta no arquivo dados.dat.*/

    printf("\nBusca pelo registro de chave \"%d\"", IDENTIFICADOR);

    CABECALHO cab;
    fread(&cab.rrn_raiz, sizeof(int), 1, arvb);

    int rrn_encontrado, pos_encontrada, result;
    result = busca(cab.rrn_raiz, IDENTIFICADOR, &rrn_encontrado, &pos_encontrada);
    if(result == ENCONTRADO) {
        PAGINA pag = inicializa_pagina();
        le_pagina(rrn_encontrado, &pag);

        char buffer[BUFFER_TAM], c;
        short tam;
        fseek(arq_dados, pag.offsets[pos_encontrada], SEEK_SET);
        fread(&tam, sizeof(short), 1, arq_dados);
        fread(buffer, sizeof(char), tam, arq_dados);
        
        printf("\n%s (%d bytes - offset %d)\n", buffer, strlen(buffer), pag.offsets[pos_encontrada]);

    } else if(result == NAO_ENCONTRADO) {
        printf("\nRegistro de chave \"%d\" nao encontrado...\n", IDENTIFICADOR);
    }
}

void insercao_reg(char *novo_reg, FILE *arq_dados/*, FILE *arvb */)
{
    // ****** ****** implemente a funcao ****** ******

    PAGINA pag = inicializa_pagina();

    short novo_tam = strlen(novo_reg);
    printf("\nInsercao do registro de chave \"%s\" (%i bytes)", novo_reg, novo_tam);

    // checando se o registro já existe
    int chave = atoi(novo_reg);
    fseek(arq_dados, 0, SEEK_END);
    int offset = ftell(arq_dados);

    fseek(arvb, 0, SEEK_SET);
    CABECALHO cab;
    fread(&cab.rrn_raiz, sizeof(int), 1, arvb);

    int rrn_econtrado = NULO, pos_encontrada = NULO;
    if(busca(cab.rrn_raiz, chave, &rrn_econtrado, &pos_encontrada) == ENCONTRADO) {
        printf("Erro, chave duplicada...");
        return;
    } else {
        fwrite(novo_reg, novo_tam, 1, arq_dados);

        int filho_d_pro = NULO, chave_pro = NULO, offset_pro = NULO;
        insere(cab.rrn_raiz, chave, offset, &filho_d_pro, &chave_pro, &offset_pro);

        printf("%s (%d bytes - offset %d)", novo_reg, novo_tam, offset);

    }
}

#pragma endregion

#pragma region Principais

// auxiliares
void gerenciador(int *raiz, FILE *arq_dados)
{
    fseek(arq_dados, sizeof(int), SEEK_SET); // passar cabeçalho
    short tam;
    int i, offset;
    char c, chave_prim[64] = {'\0'};
    offset = ftell(arq_dados);

    // ler a primeira chave
    fread(&tam, sizeof(short), 1, arq_dados);
    i = 0;
    c = fgetc(arq_dados);
    while(c != '|') {
        chave_prim[i] = c;
        i++;
        c = fgetc(arq_dados);
    }
    i++;
    int chave = atoi(chave_prim);

    int filho_d_pro = NULO, chave_pro = NULO, offset_pro = NULO;
    while(!feof(arq_dados)) {
        if(insere(*raiz, chave, offset, &filho_d_pro, &chave_pro, &offset_pro) == PROMOCAO) {
            PAGINA novapag = inicializa_pagina();
            novapag.chaves[0] = chave_pro;   // nova chave raiz
            novapag.offsets[0] = offset_pro; // offset da chave
            novapag.filhos[0] = *raiz;        // filho esquerdo
            novapag.filhos[1] = filho_d_pro; // filho direito
            novapag.num_chaves++;

            int rrn = novo_rrn();
            escreve_pagina(rrn, &novapag);
            *raiz = rrn;
        }
        // ler a próxima chave
        fseek(arq_dados, tam - i, SEEK_CUR);
        offset = ftell(arq_dados);
        fread(&tam, sizeof(short), 1, arq_dados);
        i = 0;
        c = fgetc(arq_dados);
        while(c != '|') {
            chave_prim[i] = c;
            i++;
            c = fgetc(arq_dados);
        }
        i++;
        chave = atoi(chave_prim);
    }
    fseek(arvb, 0, SEEK_SET);
    fwrite(&(*raiz), sizeof(int), 1, arvb);

}

void cria_btree(FILE *arq_dados/*, FILE *arvb */)
{
    // ****** ****** implemente a funcao ****** ******

    CABECALHO cab;
    cab.rrn_raiz = 0;
    fseek(arvb, 0, SEEK_SET);
    fwrite(&cab.rrn_raiz, sizeof(int), 1, arvb);
    PAGINA novapag = inicializa_pagina();
    int rrn = novo_rrn();
    escreve_pagina(rrn, &novapag);

    gerenciador(&cab.rrn_raiz, arq_dados);


}

void executa_operacoes(FILE *arq_dados/*, FILE *arvb */, FILE *op_arq)
{
    // executa as operações no arquivo de operações
    operacao op;
    op = op_leitura(op_arq);
    while(op.op_tipo != EOF) {
        if(op.op_tipo == 'b') {
            int info = atoi(op.op_info); // transformando char em int (chave)
            busca_reg(info, arq_dados /*, arvb */);

        } else if(op.op_tipo == 'i') {
            insercao_reg(op.op_info, arq_dados);

        }
        /*
        sem else "default" considerando não necessário
        a verificação da integridade do arquivo
        */
        op = op_leitura(op_arq);
        
    }
}

void imprime_btree(/* FILE *arvb */)
{
    imprime_arvore();
}

#pragma endregion

