/**
 * TRABALHO 2 de Organização e Recuperação de Dados
 * 
 * Docente: Paulo Roberto de Oliveira
 * Discente: Gustavo Giozeppe Bulgarelli (RA 129658)
 * 
 * construir e manter um índice
 * estruturado como uma Árvore-B.
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arvb\arvb.h"

#define NOME_ARQ_DADOS ".dat" // inserir nome


// funções principais
int cria_btree(FILE *arq_dados);
int executa_operacoes(FILE *arq_dados, FILE *op_arq);
void imprime_btree(FILE *arq_dados);

int main(int argc, char *argv[])
{
    FILE *arq_dados = fopen(NOME_ARQ_DADOS, "rb+");

    // não necessário?
    /*
    if(arq_dados == NULL) {
        // caso dados.dat não possa ser encontrado
        fprintf(stderr, "Não foi possivel encontrar o arquivo de dados. Tente novamente.");
        exit(EXIT_FAILURE);
    }
    */
    // não necessário?

    if(argc == 2 && strcmp(argv[1], "-c") == 0) {
        printf("Modo de criacao do indice ativado ...\n");
        // cria_btree(arq_dados);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        FILE *op_arq = fopen(argv[2], "r");
        // sem if(op_arq == NULL) considerando não necessário a verificação da integridade do arquivo
        // executa_operacoes(arq_dados, op_arq);
        fclose(op_arq);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {
        printf("Modo de impressao da LED ativado ...\n");
        //imprime_btree(arq_dados);

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