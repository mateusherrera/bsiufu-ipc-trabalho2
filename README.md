# Trabalho 2 - IPC

Segundo trabalho realizado na disciplina de Introdução à Programação de Computadores (IPC).

## Descrição do trabalho

Este trabalho consiste em escrever um programa em C11, usando o GCC no Ubuntu, que mantenha registros e realize uma análise estatı́stica de uma turma de estudantes.
Para cada estudante, precisaremos de um nome com até 50 caracteres, um matrı́cula com 11 caracteres, três notas de provas, duas notas de trabalhos, um inteiro para o número de faltas, uma nota final, um caractere para a situação final: ’A’ - aprovado, ’R’ - reprovado, ’F’ - reprovado por faltas.
Os dados dos estudantes serão armazenados em um arranjo de estruturas de estudantes. Esse arranjo deve ser capaz de manter até 80 estudantes.

## Para compilar com gcc no terminal do Linux

Com o terminal, vá a pasta em que está o código fonte, e rode o seguinte comando:

```
gcc -c adminturma.c
```

E depois:

```
gcc -o adminturma adminturma.o
```

## Opcional: Organizar '.o' e executável

Na pasta da compilação.
Crie os diretórios 'obj/', para o '.o', e bin/, para o executável:

```
mkdir obj/
mkdir bin/
```

Depois mova o arquivo objeto e o executável para suas pastas:

```
mv adminturma.o obj/
mv adminturma bin/
```

## Para rodar o executável no terminal

Digite o comando na pasta onde está o executável:

```
./adminturma
```
