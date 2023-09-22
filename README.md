# ORD-Assignment-2


### 2nd Data Organization and Recovery assignment


*(in Portuguese)*

O 2o trabalho prático da disciplina Organização e Recuperação de Dados consiste na construção de um programa a ser desenvolvido em conformidade com as especificações abaixo.


O objetivo deste trabalho é criar um programa que, a partir de um arquivo de registros, construa e mantenha um índice estruturado como uma árvore-B. Além disso, o programa também deverá ser capaz de imprimir informações sobre a árvore construída.

O arquivo de registros conterá informações sobre jogos e estará armazenado no arquivo dados.dat no mesmo formato utilizado no 1o trabalho prático. Para cada registro lido, a chave (o identificador do jogo) deverá ser inserida em uma árvore-B de determinada ORDEM, juntamente com o byte-offset do registro correspondente. Para facilitar a experimentação com árvores de diferentes ordens, faça ORDEM ser uma constante e use-a ao longo do código sempre que precisar referenciar a ordem da árvore.

A estrutura interna das páginas da árvore será similar à vista em aula, porém deverá conter, adicionalmente, um vetor para o armazenamento dos byte-offsets dos registros. A árvore-B deverá ser criada e mantida em arquivo, logo, a árvore nunca estará completamente carregada na memória.

O programa deverá oferecer as seguintes funcionalidades:

- Criação do índice (árvore-B) a partir do arquivo de registros;
- Execução de um arquivo de operações (apenas busca e inserção);
- Impressão das informações do índice (árvore-B).

Assim como no 1o trabalho, as operações deverão ser realizadas sem interação direta com o usuário, utilizando para isso a linha de comando com passagem de parâmetros.


O trabalho também deverá ser apresentado pelos alunos da equipe em data e horário agendado pelo(a) professor(a).
