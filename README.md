# Trabalho 2 — Serviço de kernel no Apache NuttX

Trabalho da disciplina **Sistemas Operacionais Embarcados — DEC7562**

**Eu:** Alexis S.

**Professor:** Anderson Luiz Fernandes Perez

## Estado do projeto

Repositório inicial de organização do trabalho. **CONTINUARA...** 

## Objetivo

Implementar no kernel do NuttX uma função que receba prioridade mínima, máxima e um ponteiro para a contagem. Se a faixa for válida e o ponteiro não for nulo, o NuttX percorre suas tarefas, compara as prioridades e devolve a quantidade. Se a faixa for inválida ou o ponteiro for nulo, retorna erro. A implementação ficará no subsistema de agendamento e o arquivo será incluído na compilação. Aplicação de teste: um exemplo em apps barra examples no mesmo. A aplicação chama a nova interface, imprime o resultado no NuttShell, cria tarefas de teste, consulta antes e depois e testa entradas inválidas. Testes no ESP32 pelo terminal

# Investigação do código interno do NuttX

Nesta etapa, investiguei como o NuttX representa e consulta suas tarefas. Não precisei estudar todo o sistema operacional, apenas os arquivos relacionados ao gerenciamento de tarefas.

## Estrutura de uma tarefa

O primeiro arquivo analisado foi:

```text
/home/aluno/nuttxspace/nuttx/include/nuttx/sched.h
```

Nesse arquivo encontrei a estrutura `struct tcb_s`, que representa a ficha de cada tarefa. Alguns campos importantes são:

```c
pid_t pid;
uint8_t sched_priority;
tstate_t task_state;
```

O campo `pid` identifica a tarefa, `sched_priority` guarda sua prioridade e `task_state` informa o estado atual, como executando ou esperando.

## Encontrar uma tarefa pelo PID

Arquivo analisado:

```text
/home/aluno/nuttxspace/nuttx/sched/sched/sched_gettcb.c
```

A função `nxsched_get_tcb(pid)` recebe o PID de uma tarefa e procura o TCB correspondente. Se encontrar a tarefa, retorna sua estrutura. Caso contrário, retorna `NULL`.

## Consultar a prioridade

Arquivo analisado:

```text
/home/aluno/nuttxspace/nuttx/sched/sched/sched_getparam.c
```

A função `nxsched_get_param(pid, &param)` consulta a prioridade de uma tarefa específica. Ela encontra a tarefa pelo PID, lê o campo:

```c
tcb->sched_priority
```

e grava o resultado em:

```c
param.sched_priority
```

O retorno da função indica se a consulta funcionou ou se ocorreu algum erro. A prioridade é armazenada em `param.sched_priority`.

## Percorrer todas as tarefas

Arquivo analisado:

```text
/home/aluno/nuttxspace/nuttx/sched/sched/sched_foreach.c
```

A função `nxsched_foreach()` percorre todas as tarefas existentes. Para cada tarefa encontrada, ela chama uma função auxiliar chamada `handler`, entregando o TCB daquela tarefa.

Esse mecanismo será importante para o meu trabalho, pois para contar tarefas por faixa de prioridade será necessário:

1. Percorrer cada tarefa;
2. Ler o campo `sched_priority`;
3. Verificar se a prioridade está dentro da faixa;
4. Aumentar um contador quando a condição for atendida.

## Consultar o estado da tarefa

Arquivo analisado:

```text
/home/aluno/nuttxspace/nuttx/sched/sched/sched_get_stateinfo.c
```

Esse arquivo possui funções que analisam o campo `task_state` e obtêm informações sobre o estado atual da tarefa.

## Proteção das estruturas

Durante a consulta das tarefas, o NuttX utiliza mecanismos como:

```c
enter_critical_section();
sched_lock();
```

Esses mecanismos protegem as estruturas internas enquanto estão sendo analisadas, evitando que as tarefas sejam modificadas no meio da operação.

## Resumo das funções estudadas

```text
nxsched_get_tcb()       → encontra uma tarefa pelo PID
nxsched_get_param()     → consulta a prioridade de uma tarefa
nxsched_foreach()       → percorre todas as tarefas
nxsched_get_stateinfo() → consulta o estado de uma tarefa
```

Com essa investigação, entendi como o NuttX armazena as informações das tarefas, como consulta uma tarefa específica e como percorre todas elas. Esse conhecimento será usado como base para criar uma nova função que conte tarefas dentro de uma determinada faixa de prioridade.


## Procurando se já existe no nuttx o que eu estou tentando fazer: 
A pesquisa no código do NuttX não encontrou uma interface pública equivalente a contar tarefas por faixa de prioridade. Foram encontradas apenas funções auxiliares de percurso e consulta individual. Por isso, a nova função proposta representa uma operação ainda não oferecida diretamente pelo sistema.
