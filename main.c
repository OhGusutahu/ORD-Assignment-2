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

typedef struct {
    char op_tipo; // b (busca), i (inserção)
    char op_info[512]; // as informações da operação
} operacao;

operacao op_leitura(FILE *op_arq);
// operações a serem executadas
int busca_reg(char *IDENTIFICADOR, FILE *arq_dados, FILE *arvb);
void insercao_reg(char *novo_reg, FILE *arq_dados, FILE *arvb);

// funções principais
int cria_btree(FILE *arq_dados, FILE *arvb);
int executa_operacoes(FILE *arq_dados, FILE *arvb, FILE *op_arq);
void imprime_btree(FILE *arvb);

// auxiliares

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
        FILE *arvb = fopen(NOME_ARQ_BTREE, "wb");
        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Não foi possivel encontrar o arquivo da Arvore-B. Tente novamente.");
            exit(EXIT_FAILURE);
        }

        // cria_btree(arq_dados, arvb);

        fclose(arvb);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        FILE *arvb = fopen(NOME_ARQ_BTREE, "rb+");
        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Não foi possivel encontrar o arquivo da Arvore-B. Tente novamente.");
            exit(EXIT_FAILURE);
        }
        
        FILE *op_arq = fopen(argv[2], "r");
        /* sem if(op_arq == NULL) considerando não necessário a verificação da integridade do arquivo */
        
        // executa_operacoes(arq_dados, arvb, op_arq);
        
        fclose(op_arq);
        fclose(arvb);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {
        printf("Modo de impressao da Arvore-B ativado ...\n");
        FILE *arvb = fopen(NOME_ARQ_BTREE, "rb");

        if(arq_dados == NULL) {
            // caso btree.dat não possa ser encontrado
            fprintf(stderr, "Não foi possivel encontrar o arquivo da Arvore-B. Tente novamente.");
            exit(EXIT_FAILURE);
        }

        //imprime_btree(arvb);

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

    op.op_tipo = fgetc(op_arq);

    fseek(op_arq,1,SEEK_CUR);
    // setando o ponteiro L/E na posição da informação da operação

    fgets(op.op_info, 512, op_arq);

    if(op.op_info[strlen(op.op_info) - 1] == '\n') op.op_info[strlen(op.op_info) - 1] = '\0';
    // remover '\n' da informação da operação para não afetar a leitura
    else op.op_info[strlen(op.op_info)] = '\0';

    return op;
}

int busca_reg(char *IDENTIFICADOR, FILE *arq_dados, FILE *arvb)
{

}
void insercao_reg(char *novo_reg, FILE *arq_dados, FILE *arvb)
{

}

#pragma endregion

#pragma region Principais

int cria_btree(FILE *arq_dados, FILE *arvb)
{
    // implemente a função
}

int executa_operacoes(FILE *arq_dados, FILE *arvb, FILE *op_arq)
{
    // executa as operações no arquivo de operações
    operacao op;
    op = op_leitura(op_arq);
    while(op.op_tipo != EOF) {
        if(op.op_tipo == 'b') {
            busca_reg(op.op_info, arq_dados, arvb);

        } else if(op.op_tipo == 'i') {
            insercao_reg(op.op_info, arq_dados, arvb);
            
        }
        /*
        sem else "default" considerando não necessário
        a verificação da integridade do arquivo
        */
        op = op_leitura(op_arq);
        
    }
}

void imprime_btree(FILE *arvb)
{
    // implemente a função
}

#pragma endregion
