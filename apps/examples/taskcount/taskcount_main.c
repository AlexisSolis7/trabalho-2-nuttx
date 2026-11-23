#include <nuttx/config.h>
#include <stdio.h>
#include <nuttx/sched.h>
#include <unistd.h>

int tarefa_1(int argc, char **argv);
int tarefa_2(int argc, char **argv);

int quantidade;
int resultado;

int main(int argc, FAR char *argv[])
{
  printf("Iniciando o contador kkk...\n");

  task_create("T1", 100, 2048, tarefa_1, NULL);
  task_create("T2", 150, 2048, tarefa_2, NULL);

  resultado = escalonador_contar_faixa_prioridade(100, 100, &quantidade);
  printf("Retorno da consulta: %d\n", resultado);
  printf("Tarefas entre prioridade 100 e 150: %d\n", quantidade);

  resultado = escalonador_contar_faixa_prioridade(100, 150, NULL);

  printf("Retorno com ponteiro nulo: %d\n", resultado);
  return 0;
}

int tarefa_1(int argc, char **argv)
{
  while (1)
  {
    printf("Eu sou a TAREFA 1\n");
    sleep(1);
  }
}

int tarefa_2(int argc, char **argv)
{
  while (1)
  {
    printf("Eu sou a TAREFA 2\n");
    sleep(1);
  }
}
