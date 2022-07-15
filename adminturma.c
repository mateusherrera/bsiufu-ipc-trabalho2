/**
* @file trabalho2_adminturma.c
* @brief O programa lê, cria, edita, exclui e imprimi uma lista de alunos, de uma determinada turma, e suas notas, faltas e situação
*         O usuário escolhe entre 7 opções, sendo elas: 1 - Ler turma de estudantes do arquivo; 2 - Imprimi turma de estudantes;
*         3 - Imprimi estatísticas da turma; 4 - Cadastrar novo estudante; 5 - Editar informações de um estudante; 6 - Reler estudantes
*         do arquivo; 7 - Salvar e Sair.
*
* O programa armazena um txt em uma estrutura, ou cria um txt. Através disso, conforme o demandado pelo usuário, serão chamadas funções
* que organizarão ou imprimirão na tela informações, que estarão na estrutura.
*
* @author Mateus Herrera Gobetti Borges
* @date 11/12/2018
* @bugs Nenhum conhecido.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_MAX_ALUNO 80 //quantidade máxima de alunos
#define OPCAO_MIN 1 //opção min para menus
#define OPCAO_MAX_1 3 //opção max para menu do case 1
#define OPCAO_MAX_5 3 //opção max para menu do case 5


typedef struct //estrutura para cada aluno
{
  char nome[51]; //nome do aluno
  char matricula[12]; //matrícula
  int nota1; //primeira nota
  int nota2; //segunda nota
  int nota3; //terceira nota
  int trab1; //primeiro trabalho
  int trab2; //segundo trabalho
  int faltas; //número de faltas
  int notafinal; //nota final
  char situacao; //aprovado, reprovado ou reprovado por falta
} ALUNOS; //tipo da estrutura criada


void limpar_estrutura(ALUNOS turma[])
{

/**
* @brief Limpa uma variável com a estrutura ALUNOS
*
* @param ALUNOS turma[] Variável que será limpada pela função
*/

  for(int i = 0; i < QTD_MAX_ALUNO; i++)  //limpar todas variáveis dentro da estrutura
  {

    strcpy(turma[i].nome, "");
    strcpy(turma[i].matricula, "");
    turma[i].nota1 = 0;
    turma[i].nota2 = 0;
    turma[i].nota3 = 0;
    turma[i].trab1 = 0;
    turma[i].trab2 = 0;
    turma[i].faltas = 0;
    turma[i].notafinal = 0;
    turma[i].situacao = 'R';

  } //limpar estrutura

} //limpar_estrutura

void ler_turma(ALUNOS turma[], char nome_arquivo[])
{

/**
* @brief Armazena dados de um arquivo txt em uma variável com a estrutura ALUNOS
*
* @param ALUNOS turma[] Variável de ALUNOS que armazenara os dados do txt
* @param char   nome_arquivo[] Variável que contem o nome do arquivo txt
*/

  FILE *arq_turma = NULL;
  
  limpar_estrutura(turma); //limpar estrutura
  arq_turma = fopen(nome_arquivo, "r"); //abrir arquivo

  if(arq_turma == NULL) //caso arquivo não exista
  {

    fprintf(stderr, "\nO arquivo não existe!!\n\n");
    return;

  } else
  {

    for(int i = 0; feof(arq_turma) == 0 && i < QTD_MAX_ALUNO; i++) //armazena dados do arquivo na variável do tipo da struct ALUNOS
    {

      fgets(turma[i].nome, sizeof(turma[i].nome), arq_turma); //lê nome do aluno
      turma[i].nome[strcspn(turma[i].nome, "\n")] = '\0'; //remove '\n' da string

      fgets(turma[i].matricula, sizeof(turma[i].matricula), arq_turma); //lê matrícula do aluno
      turma[i].matricula[strcspn(turma[i].matricula, "\n")] = '\0'; //remove '\n' da string

      fscanf(arq_turma, "%d", &turma[i].nota1); //lê nota 1 do aluno
      fscanf(arq_turma, "%d", &turma[i].nota2); //lê nota 2 do aluno
      fscanf(arq_turma, "%d", &turma[i].nota3); //lê nota 3 do aluno
      fscanf(arq_turma, "%d", &turma[i].trab1); //lê nota do trabalho 1 do aluno
      fscanf(arq_turma, "%d", &turma[i].trab2); //lê nota do trabalho 2 do aluno
      fscanf(arq_turma, "%d", &turma[i].faltas); //lê qtd. de faltas do aluno
      fscanf(arq_turma, "%d", &turma[i].notafinal); //lê nota final do aluno

      char c = fgetc(arq_turma); //consome '\n'
      turma[i].situacao = fgetc(arq_turma); //lê situação do aluno (aprovado, reprovado, reprovado por falta)
      c = fgetc(arq_turma); //consome '\n'

    } //ler arquivo na struct
    
    fclose(arq_turma); //fechar arquivo
    printf("\nO arquivo lido com sucesso!!\n\n");

  } //caso exista

} //ler_turma

void criar_turma(ALUNOS turma[], char nome_arquivo[])
{

/**
* @brief Cria um arquivo txt e armazena uma variável ALUNOS, para se criar uma nova turma
*
* @param ALUNOS turma[] Variável ALUNOS que receberá informações sobre nova turma
* @param char nome_arquivo[] Variável que possui o nome do arquivo que deve ser criado, para armazenar dados da nova turma
*/

  FILE *arq_turma = NULL;
  char o; //S ou N para substituir arquivo ou não
  
  limpar_estrutura(turma);
  arq_turma = fopen(nome_arquivo, "r"); //abrir arquivo

  if(arq_turma != NULL) //caso arquivo já exista
  {

    printf("\nArquivo %s já existe. Deseja sobrescrevê-lo? (S/N)\n", nome_arquivo);

    do
    {

      printf("Escolha entre S (para sobrescrever o arquivo) ou N (para não sobrescrever): ");
      scanf("%c", &o); //ler opção do usuário
      getchar(); //limpar '\n'

    } while(o != 'S' && o != 's' && o != 'N' && o != 'n');
    
    if(o == 's' || o == 'S') //para sobrescrever arquivo
    {

      arq_turma = fopen(nome_arquivo, "w"); //sobrescrever arquivo
      turma[0].nome[0] = '*'; //marcar arquivo para cadastro de aluno
      fprintf(arq_turma, "*\n"); //marcar arquivo para cadastro de aluno

      fclose(arq_turma); //fechar arquivo
      printf("\nArquivo %s sobrescrito com sucesso!!\n\n", nome_arquivo);

    } else
    {

      fclose(arq_turma); //fechar arquivo
      printf("\nArquivo %s não foi sobrescrito!!\n\n", nome_arquivo);

    } //caso negativo

  } else
  {

    arq_turma = fopen(nome_arquivo, "w"); //criar arquivo
    turma[0].nome[0] = '*'; //marcar arquivo para cadastro de aluno
    fprintf(arq_turma, "*\n"); //marcar arquivo para cadastro de aluno

    fclose(arq_turma); //fechar arquivo
    printf("\nArquivo %s criado com sucesso!!\n\n", nome_arquivo);

  } //caso exista

} //criar_turma

void imprimir_turma(ALUNOS turma[])
{

/**
* @brief Imprimi dados da turma (desde que esteja carregada na variável ALUNOS) em uma tabela
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
*/

  if(turma[0].nome[0] == '\0') //caso não exista uma turma carregada
    printf("\nNão há turma carregada!!\n\n");

  else if(turma[0].nome[1] == '\0') //caso exista arquivo carregado, porém vazio
    printf("\nTurma Vazia!!\n\n");

  else //caso exista um arquivo carregado
  {

    printf("\n\n                                                 Estudantes\n");
    printf("  ========================================================================================================\n");
    printf("    Nome                                                Matrícula    N1  N2  N3  T1  T2  Fal  Final  Sit\n");
    printf("  ========================================================================================================\n");

    for(int i = 0; turma[i].nome[0] != '\0' && i < QTD_MAX_ALUNO; i++) //imprimir dados dos alunos da turma
    {

      printf("    %-50s", turma[i].nome);
      printf("  %11s", turma[i].matricula);
      printf("  %2d", turma[i].nota1);
      printf("  %2d", turma[i].nota2);
      printf("  %2d", turma[i].nota3);
      printf("  %2d", turma[i].trab1);
      printf("  %2d", turma[i].trab2);
      printf("  %3d", turma[i].faltas);
      printf("  %5d", turma[i].notafinal);
      printf("  %3c\n", turma[i].situacao);

    } //imprimir dados

    printf("  ========================================================================================================\n\n");

  } //caso exista um arquivo carregado

} //imprimir_turma

void imprimir_estat(ALUNOS turma[])
{

/**
* @brief Imprimi a estatística da turma (desde que esteja carregada na variável ALUNOS) em uma tabela
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
*/

  if(turma[0].nome[0] == '\0') //caso não exista turma carregada
    printf("\nNão há turma carregada!!\n\n");

  else if(turma[0].nome[1] == '\0') //caso exista arquivo carregado, porém vazio
    printf("\nTurma Vazia!!\n\n");

  else //caso exista um arquivo carregado
  {
    
    int qtdA = 0;
    int qtdR = 0;
    int qtdF = 0;
    int qtdalunos = 0;
    int maiorn1 = turma[0].nota1;
    int maiorn2 = turma[0].nota2;
    int maiorn3 = turma[0].nota3;
    int maiort1 = turma[0].trab1;
    int maiort2 = turma[0].trab2;
    int menorn1 = turma[0].nota1;
    int menorn2 = turma[0].nota2;
    int menorn3 = turma[0].nota3;
    int menort1 = turma[0].trab1;
    int menort2 = turma[0].trab2;
    int maiorfn = turma[0].notafinal;
    int menorfn = turma[0].notafinal;

    double perA = 0.0;
    double perR = 0.0;
    double perF = 0.0;
    double median1 = 0;
    double median2 = 0;
    double median3 = 0;
    double mediat1 = 0;
    double mediat2 = 0;
    double mediafn = 0;
    
    for(int i = 0; turma[i].nome[0] != '\0' && i < QTD_MAX_ALUNO; i++, qtdalunos++) //guardar maiores e menores nota
    {

      if(turma[i].situacao == 'A') qtdA++;
      if(turma[i].situacao == 'R') qtdR++;
      if(turma[i].situacao == 'F') qtdF++;
      
      if(maiorn1 < turma[i].nota1) maiorn1 = turma[i].nota1;
      if(maiorn2 < turma[i].nota2) maiorn2 = turma[i].nota2;
      if(maiorn3 < turma[i].nota3) maiorn3 = turma[i].nota3;
      if(maiort1 < turma[i].trab1) maiort1 = turma[i].trab1;
      if(maiort2 < turma[i].trab2) maiort2 = turma[i].trab2;
      if(maiorfn < turma[i].notafinal) maiorfn = turma[i].notafinal;
      if(menorn1 > turma[i].nota1) menorn1 = turma[i].nota1;
      if(menorn2 > turma[i].nota2) menorn2 = turma[i].nota2;
      if(menorn3 > turma[i].nota3) menorn3 = turma[i].nota3;
      if(menort1 > turma[i].trab1) menort1 = turma[i].trab1;
      if(menort2 > turma[i].trab2) menort2 = turma[i].trab2;
      if(menorfn > turma[i].notafinal) menorfn = turma[i].notafinal;
      
      median1 += turma[i].nota1;
      median2 += turma[i].nota2;
      median3 += turma[i].nota3;
      mediat1 += turma[i].trab1;
      mediat2 += turma[i].trab2;
      mediafn += turma[i].notafinal;

    } //maiores e menor notas
    
    perA = (qtdA * 100) / (double)qtdalunos;
    perR = (qtdR * 100) / (double)qtdalunos;
    perF = (qtdF * 100) / (double)qtdalunos;
    
    median1 /= qtdalunos;
    median2 /= qtdalunos;
    median3 /= qtdalunos;
    mediat1 /= qtdalunos;
    mediat2 /= qtdalunos;
    mediafn /= qtdalunos;
      
    printf("                                 Estatísticas\n");
    printf("  ==========================================================================\n");
    printf("                                N1      N2      N3      T1      T2    Final\n");
    printf("  ==========================================================================\n");

    printf("    Maiores notas da turma    %4d    %4d    %4d    %4d    %4d    %5d\n", maiorn1, maiorn2, maiorn3, maiort1, maiort2, maiorfn);
    printf("    Menores notas da turma    %4d    %4d    %4d    %4d    %4d    %5d\n",menorn1, menorn2, menorn3, menort1, menort2, menorfn);
    printf("    Notas médias da turma     %4.1lf    %4.1lf    %4.1lf    %4.1lf    %4.1lf    %5.1lf\n",median1, median2, median3, mediat1, mediat2, mediafn);

    printf("  ==========================================================================\n\n");
    printf("  Número de estudantes aprovados:             %2d (%5.1lf %%)\n",qtdA, perA);
    printf("  Número de estudantes reprovados:            %2d (%5.1lf %%)\n",qtdR, perR);
    printf("  Número de estudantes reprovados por falta:  %2d (%5.1lf %%)\n\n",qtdF, perF);

  } //caso exista um arquivo carregado

} //imprimir_estat

void cadastrar_estudante(ALUNOS turma[])
{

/**
* @brief Cadastra novo estudante na estrutura da variável ALUNOS
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
*/

  if(turma[0].nome[0] == '\0') //caso não exista turma carregada 
    printf("\nNão há turma carregada!!\n\n");

  else //caso exista um arquivo carregado
  {

    int novo = 0; //proxima vaga livre
    
    while(turma[novo].nome[0] != '\0' && novo < QTD_MAX_ALUNO && turma[novo].nome[0] != '*') //descobrir proxima vaga livre
      novo++;
    
    if(novo == (QTD_MAX_ALUNO - 1)) //limite de alunos alcançado
      printf("\nImpossível adicionar outro aluno, pois o número máximo de alunos foi alcançado!!\n\n");

    else //adicione aluno
    {

      printf("\n\t  ========================================\n");
      printf("\t          Cadastrar Novo Estudante\n");
      printf("\t  ========================================\n");
      printf("\nDigite o nome: ");
      if(fgets(turma[novo].nome, sizeof(turma[novo].nome), stdin) == NULL) //caso de erro ao ler o nome do aluno
      {

        fprintf(stderr, "\nErro ao ler nome do aluno!!\n\n");
        exit(1);

      } //erro ao ler nome
      turma[novo].nome[strcspn(turma[novo].nome, "\n")] = '\0'; //remover '\n' do final da string

      printf("Digite a matrícula: ");
      if(fgets(turma[novo].matricula, sizeof(turma[novo].matricula), stdin) == NULL) //caso de erro ao ler a matrícula do aluno
      {

        fprintf(stderr, "\nErro ao ler nome do aluno!!\n\n");
        exit(1);

      } //erro ao ler nome
      turma[novo].matricula[strcspn(turma[novo].matricula, "\n")] = '\0'; //remover '\n' do final da string

      printf("Digite as três notas das provas: ");
      scanf("%d %d %d", &turma[novo].nota1, &turma[novo].nota2, &turma[novo].nota3);
      getchar();

      printf("Digite as duas notas dos trabalhos: ");
      scanf("%d %d", &turma[novo].trab1, &turma[novo].trab2);
      getchar();

      printf("Digite o número de faltas: ");
      scanf("%d", &turma[novo].faltas);
      getchar();

      turma[novo].notafinal = turma[novo].nota1 + turma[novo].nota2 + turma[novo].nota3 + turma[novo].trab1 + turma[novo].trab2;

      printf("\nNota final calculada: %d\n", turma[novo].notafinal);
      if(turma[novo].notafinal >= 60 && turma[novo].faltas <= 18) //aluno aprovado
      {

        turma[novo].situacao = 'A';
        printf("Situação final: Aprovado\n");

      } else if(turma[novo].faltas > 18) //reprovou por falta
      {

        turma[novo].situacao = 'F';
        printf("Situação final: Reprovado por falta\n");

      } else //reprovou pela nota final
      {

        turma[novo].situacao = 'R';
        printf("Situação final: Reprovado\n");

      }// if else

    } //adiciona aluno

  } //caso exista um arquivo carregado

} //cadastrar_estudante

/**
* @brief Edita informações de um aluno
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
* @param int pos Indica a posição na estrutura, em que estão as informações do aluno que terá suas informações modificadas
*/

void editar_inf(ALUNOS turma[], int pos)
{
  int opcao = 0;
  
  while(opcao != 9) //menu para editar dados do aluno
  {
    switch(opcao) //menu dos dados do aluno
    {
      case 0:
        printf("\n\t=========================================\n");
        printf("\t     Editar Informações do Estudante\n");
        printf("\t=========================================\n");
        printf("Opções:\n");
        printf("\n1 - Alterar nome\n");
        printf("2 - Alterar matrícula\n");
        printf("3 - Alterar nota da prova 1\n");
        printf("4 - Alterar nota da prova 2\n");
        printf("5 - Alterar nota da prova 3\n");
        printf("6 - Alterar nota da trabalho 1\n");
        printf("7 - Alterar nota da trabalho 2\n");
        printf("8 - Alterar número de faltas\n");
        printf("9 - Voltar ao menu anterior\n");
        printf("\nDigite uma opção: ");
        scanf("%d", &opcao); //ler opção
        getchar(); //limpar '\n'
        break;
      case 1: //alterar nome
        printf("\nDigite o nome: ");
        if(fgets(turma[pos].nome, sizeof(turma[pos].nome), stdin) == NULL) //erro ao ler nome
        {
          fprintf(stderr, "\nErro ao ler string!!\n\n");
          exit(1);
        } //erro ao ler nome
        else //lido com sucesso
        {
          turma[pos].nome[strcspn(turma[pos].nome, "\n")] = '\0'; //remover '\n' da string
        } //lido com sucesso
        opcao = 0;
        break;
      case 2: //alterar matrícula
        printf("\nDigite a matrícula: ");
        if(fgets(turma[pos].matricula, sizeof(turma[pos].matricula), stdin) == NULL) //erro ao ler matrícula
        {
          fprintf(stderr, "\nErro ao ler string!!\n\n");
          exit(1);
        } //erro ao ler matrícula
        else //lido com sucesso
        {
          turma[pos].matricula[strcspn(turma[pos].matricula, "\n")] = '\0'; //remover '\n' da string
        } //lido com sucesso
        opcao = 0;
        break;
      case 3: //alterar nota prova 1
        printf("\nDigite a nota da prova 1: ");
        scanf("%d", &turma[pos].nota1); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      case 4: //alterar nota prova 2
        printf("\nDigite a nota da prova 2: ");
        scanf("%d", &turma[pos].nota2); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      case 5: //alterar nota prova 3
        printf("\nDigite a nota da prova 3: ");
        scanf("%d", &turma[pos].nota3); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      case 6: //alterar nota trabalho 1
        printf("\nDigite a nota do trabalho 1: ");
        scanf("%d", &turma[pos].trab1); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      case 7: //alterar nota trabalho 2
        printf("\nDigite a nota do trabalho 2: ");
        scanf("%d", &turma[pos].trab2); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      case 8: //alterar número de faltas
        printf("\nDigite o número de faltas: ");
        scanf("%d", &turma[pos].faltas); //ler nota
        getchar(); //limpar '\n'
        opcao = 0;
        break;
      default: 
        printf("\nOPÇÃO INVÁLIDA!!\nDigite uma opção válida: ");
        scanf("%d", &opcao); //ler opção
        getchar(); //limpar '\n'
        break;
    } //switch case
  } //menu para editar dados do aluno
  
  turma[pos].notafinal = turma[pos].nota1 + turma[pos].nota2 + turma[pos].nota3 + turma[pos].trab1 + turma[pos].trab2;
  if(turma[pos].notafinal >= 60 && turma[pos].faltas <= 18) //aluno aprovado
  {
    turma[pos].situacao = 'A';
  } //aluno aprovado
  else if(turma[pos].faltas > 18) //aluno reprovado por falta
  {
    turma[pos].situacao = 'F';
  } //aluno reprovado por falta
  else //aluno reprovado
  {
    turma[pos].situacao = 'R';
  } //aluno reprovado
  return;
} //editar_inf

/**
* @brief Acha a posição que está o aluno na estrutura, segundo seu nome ou matrícula, caso ele esteja na turma carregada
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
* @param int opcao Indica se a busca deve ser feita por nome ou matrícula. Se opcao == 1, pesquise por matrícula, se opcao == 2,
*                  pesquise por nome
*/

void achar_aluno(ALUNOS turma[], int opcao)
{
  char procurar[51];
  
  if(opcao == 1) //procurar por matrícula
  {
    printf("\nDigite o número de matrícula: ");
  } //por matrícula
  else if(opcao == 2) //procurar por nome
  {
    printf("\nDigite o nome: ");
  } //por nome
  if(fgets(procurar, sizeof(procurar), stdin) == NULL) //erro ao ler string
  {
    fprintf(stderr, "\nErro ao ler a string!!\n\n");
    exit(1);
  } //erro ao ler string
  else //string lida
  {
    procurar[strcspn(procurar, "\n")] = '\0'; //remover '\n' da string
  } //string lida
  
  int i = 0;
  int n = 81;
  int m = 81;
  for(;turma[i].nome[0] != '\0' && i < QTD_MAX_ALUNO; i++) //achar posição do aluno no arranja da estrutura
  {
    if(opcao == 1) //matrícula
    {
      if(strcmp(procurar, turma[i].matricula) == 0) m = i;
    } //matrícula
    else //nome
    {
      if(strcmp(procurar, turma[i].nome) == 0) n = i;
    } //nome
  } //achar posição do aluno no arranja da estrutura

  if(n == 81 && m == 81) //valor inválido
  {
    printf("\nNão exite esse aluno na turma carregada!!\n\n");
  } //valor inválido
  else //valor valido
  {
    if(opcao == 1) editar_inf(turma, m);
    if(opcao == 2) editar_inf(turma, n);
  } //valor valido
  return;
} //achar_aluno

/**
* @brief Grava informações de um turma, presente na estrutura ALUNOS de variável, em um arquivo txt
*
* @param ALUNOS turma[] Variável que guarda dados da turma carregada
* @param char nome_arquivo[] Variável que guarda o nome do arquivo txt, em que será escrito as informações da classe
*/

void escrever_txt(ALUNOS turma[], char nome_arquivo[])
{
  FILE *arq_turma = NULL;
  char o; //S ou N para substituir arquivo ou não
  
  arq_turma = fopen(nome_arquivo, "r"); //abrir arquivo
  if(arq_turma != NULL) //caso arquivo já exista
  {
    printf("\nArquivo %s já existe. Deseja sobrescrevê-lo? (S/N)\n", nome_arquivo);
    do{
      printf("Escolha entre S (para sobrescrever o arquivo) ou N (para não sobrescrever): ");
      scanf("%c", &o); //ler opção do usuário
      getchar(); //limpar '\n'
    }while(o != 'S' && o != 's' && o != 'N' && o != 'n');
    
    if(o == 's' || o == 'S') //para sobrescrever arquivo
    {
      arq_turma = fopen(nome_arquivo, "w"); //sobrescrever arquivo
      for(int i = 0; turma[i].nome[0] != '\0' && i < QTD_MAX_ALUNO; i++) //escrever struct no arquivo aberto
      {
        fprintf(arq_turma, "%s\n", turma[i].nome);
        fprintf(arq_turma, "%s\n", turma[i].matricula);
        fprintf(arq_turma, "%d\n", turma[i].nota1);
        fprintf(arq_turma, "%d\n", turma[i].nota2);
        fprintf(arq_turma, "%d\n", turma[i].nota3);
        fprintf(arq_turma, "%d\n", turma[i].trab1);
        fprintf(arq_turma, "%d\n", turma[i].trab2);
        fprintf(arq_turma, "%d\n", turma[i].faltas);
        fprintf(arq_turma, "%d\n", turma[i].notafinal);
        fprintf(arq_turma, "%c\n", turma[i].situacao);
      } //escrever struct no arquivo aberto
    } //caso positivo
    fclose(arq_turma); //fechar arquivo
  } //caso não exista
  else //caso arquivo ainda não exista
  {
    printf("\nArquivo %s não existe. Deseja criá-lo? (S/N)\n", nome_arquivo);
    do{
      printf("Escolha entre S (para criar o arquivo) ou N (para não criar): ");
      scanf("%c", &o); //ler opção do usuário
    }while(o != 'S' && o != 's' && o != 'N' && o != 'n');
    getchar(); //limpar '\n'
    
    if(o == 's' || o == 'S') //para criar arquivo
    {
      arq_turma = fopen(nome_arquivo, "w"); //criar arquivo
      for(int i = 0; turma[i].nome[0] != '\0' && i < QTD_MAX_ALUNO; i++) //escrever struct no arquivo aberto
      {
        fprintf(arq_turma, "%s\n", turma[i].nome);
        fprintf(arq_turma, "%s\n", turma[i].matricula);
        fprintf(arq_turma, "%d\n", turma[i].nota1);
        fprintf(arq_turma, "%d\n", turma[i].nota2);
        fprintf(arq_turma, "%d\n", turma[i].nota3);
        fprintf(arq_turma, "%d\n", turma[i].trab1);
        fprintf(arq_turma, "%d\n", turma[i].trab2);
        fprintf(arq_turma, "%d\n", turma[i].faltas);
        fprintf(arq_turma, "%d\n", turma[i].notafinal);
        fprintf(arq_turma, "%c\n", turma[i].situacao);
      } //escrever struct no arquivo aberto
    } //criar arquivo
    fclose(arq_turma); //fechar arquivo
  } //caso exista
  return;
} //escrever_txt

/**
* @brief Organiza e ordena o menu de opções, conforme a escolha do usuário. Nessa função serão chamadas as  demais funções
*        para cada escolha do usuário (com exceção de duas: "editar_inf" e "limpar_estrutura", pois são utilizadas por outras,
*        quando necessário).
*/

void menu(void)
{
  ALUNOS turma[QTD_MAX_ALUNO]; //arranjo de estrutura ALUNOS pertencentes à turma
  int opcao = 0; //inicia menu principal (case 0)
  char nome_arquivo[21] = {'\0'};
    
  while(opcao != 8) //enquanto não se digita 7 para fechar o programa
  {
    switch(opcao) //organização dos menus
    {
      case 0: //menu principal
        printf("\t========================\n");
        printf("\t     Menu Principal\n");
        printf("\t========================\n");
        printf("Opções:\n");
        printf("\n1 - Ler turma de estudantes do arquivo\n");
        printf("2 - Imprimir turma de estudantes\n");
        printf("3 - Imprimir estatísticas da turma\n");
        printf("4 - Cadastrar novo estudante\n");
        printf("5 - Editar informações de um estudante\n");
        printf("6 - Reler turma de estudantes do arquivo\n");
        printf("7 - Salvar e Sair\n");
        printf("\nDigite uma opção: ");
        scanf("%d", &opcao); //ler opção
        getchar(); //limpar '\n'
        break;
      case 1: //menu para opção: Ler turma de estudantes do arquivo
        printf("\t===================\n");
        printf("\t     Ler Turma\n");
        printf("\t===================\n");
        printf("Opções:\n");
        printf("\n1 - Ler turma existente\n");
        printf("2 - Criar nova turma\n");
        printf("3 - Voltar ao menu principal\n");
        opcao = 0;
        do
        {
          printf("\nDigite uma opção: ");
          scanf("%d", &opcao); //ler opção
          getchar(); //limpar '\n'
        }while(opcao > OPCAO_MAX_1 || opcao < OPCAO_MIN);
        
        if(opcao == 1) //opção: Ler turma existente
        {
          printf("\nDigite o nome do arquivo da turma: ");
          if(fgets(nome_arquivo, sizeof(nome_arquivo), stdin) == NULL) //caso ocorra algum erro na leitura da string
          {
            fprintf(stderr, "\nErro ao ler nome do arquivo!!\n");
            exit(1);
          } //erro na leitura da string
          else //caso a string seja lida corretamente
          {
            nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; //remover '\n' do final da string
          } //caso a string seja lida corretamente
          
          ler_turma(turma, nome_arquivo); //ler arquivo de uma turma
          opcao = 1; //abrir case: 1 novamente
        } //opção 1
        else if(opcao == 2) //opção: Criar nova turma
        {
          printf("\nDigite o nome do arquivo para nova turma: ");
          if(fgets(nome_arquivo, sizeof(nome_arquivo), stdin) == NULL) //caso ocorra algum erro na leitura da string
          {
            fprintf(stderr, "Erro ao ler nome do arquivo!!\n");
            exit(1);
          } //erro na leitura da string
          else //caso a string seja lida corretamente
          {
            nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; //remover '\n' do final da string
          } //caso a string seja lida corretamente
          
          criar_turma(turma, nome_arquivo); //criar arquivo de uma turma
          opcao = 1; //abrir case: 1 novamente
        } //opção 2
        else //opção: Voltar ao menu principal
        {
          opcao = 0; //voltar ao menu principal
        } //opção 3
        break;
      case 2: //Imprimir turma de estudantes
        imprimir_turma(turma); //imprimi dados do aluno, conforme arquivo carregado anteriormente
        opcao = 0;
        break;
      case 3: //Imprimir estatísticas da turma
        imprimir_estat(turma);
        opcao = 0;
        break;
      case 4: //Cadastrar novo estudante
        cadastrar_estudante(turma);
        opcao = 0;
        break;
      case 5: //Editar informação de estudante
        printf("\t=========================================\n");
        printf("\t     Editar Informações do Estudante\n");
        printf("\t=========================================\n");
        printf("Opções:\n");
        printf("\n1 - Selecionar por número de matrícula\n");
        printf("2 - Selecionar por nome\n");
        printf("3 - Voltar ao menu principal\n");
        opcao = 0;
        do
        {
          printf("\nDigite uma opção: ");
          scanf("%d", &opcao);
          getchar();
        }while(opcao > OPCAO_MAX_5 || opcao < OPCAO_MIN);
        
        if(opcao == 1 || opcao == 2) //editar informações
        {
          achar_aluno(turma, opcao);
          opcao = 5;
        } //editar informações
        else //voltar ao menu principal
        {
          opcao = 0;
        } //voltar ao menu principal
        break;
      case 6: //Reler turma de estudantes
        if(nome_arquivo[0] == '\0') //arquivo não lido
        {
          printf("\nNão existe arquivo carregado!!\n");
        } //arquivo não lido
        else
        { //reler arquivo
          ler_turma(turma, nome_arquivo);
        } //reler arquivo
        opcao = 1;
        break;
      case 7: //Salvar e Sair
        if(nome_arquivo[0] == '\0') //arquivo não lido
        {
          printf("\nNão existe arquivo carregado!!\n");
        } //arquivo não lido
        else
        { //reler arquivo
          escrever_txt(turma, nome_arquivo);
        } //reler arquivo
        opcao = 8;
        break;
      default: //Caso o usuário digite uma opção inexistente
        printf("\nOPÇÃO INVÁLIDA!!\nDigite uma opção válida: ");
        scanf("%d", &opcao);
        break;
    } //switch case
  } //while
  return;
} //menu

int main(void)
{
  menu();
  
  printf("\nAté próxima.\n\n");
  
  return 0;
} //main