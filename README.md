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

## Parte de como eu pensei o contrato da função

Nesta parte, defini o contrato da nova função antes de começar a implementação. A função será usada para contar quantas tarefas do NuttX estão dentro de uma determinada faixa de prioridades.
O nome escolhido foi:
```c
int escalonador_contar_faixa_prioridade(int prioridade_min,
                                        int prioridade_max,
                                        FAR int *quantidade);
```
Os parâmetros têm as seguintes funções:
- `prioridade_min`: menor prioridade da faixa consultada;
- `prioridade_max`: maior prioridade da faixa consultada;
- `quantidade`: endereço onde o resultado da contagem será armazenado.
A faixa de prioridades será inclusiva. Isso significa que, ao consultar as prioridades de 50 até 100, as tarefas com prioridade exatamente 50 ou 100 também serão contadas.
O retorno da função será definido assim:
- `0` quando a consulta for realizada com sucesso;
- `-EINVAL` quando algum argumento for inválido.
A função deverá retornar `-EINVAL` quando a prioridade mínima for maior que a máxima:
```c
prioridade_min > prioridade_max
```
Essa situação representa uma faixa inválida. Por exemplo, não faz sentido informar 100 como prioridade mínima e 50 como prioridade máxima quando estamos considerando a faixa em ordem crescente.
Também deverá retornar `-EINVAL` quando o ponteiro `quantidade` for nulo:
```c
quantidade == NULL
```
Nesse caso, não existiria um local válido para armazenar o resultado.
Aqui estou apenas define como a função será chamada, quais dados receberá e como informará se a operação foi realizada corretamente ou se houve algum erro.




## O que eu fiz no codigo

Eu criei uma função nova dentro do NuttX para contar quantas tarefas estão
dentro de uma faixa de prioridades.
A função criada foi como eu disse encima:
```c
int escalonador_contar_faixa_prioridade(int prioridade_min, int prioridade_max, int *quantidade);
```
Ela retorna `0` quando a consulta funciona. Ela retorna `-EINVAL` quando:
- a prioridade mínima é maior que a máxima;
- o ponteiro `quantidade` é nulo.
A faixa é inclusiva. Por exemplo, a consulta de `100` até `150` inclui as
prioridades 100 e 150.
## Onde ficam os arquivos
Eu usei o ambiente do NuttX em:
```text
/home/aluno/nuttxspace/
```
Dentro dele existem duas pastas principais:
```text
/home/aluno/nuttxspace/nuttx
/home/aluno/nuttxspace/apps
```
O `nuttx` contém o sistema operacional. A pasta `apps` contém os programas
que aparecem no NuttShell.
No VS Code, a pasta aberta aparece como `nuttxspace`. Por isso os caminhos
relativos usados no editor foram estes:
```text
nuttx/sched/sched/sched_countpriority.c
nuttx/include/nuttx/sched.h
nuttx/sched/sched/Make.defs
apps/examples/taskcount/taskcount_main.c
```
## Arquivos modificados
### 1. Implementação no kernel
Arquivo:
```text
nuttx/sched/sched/sched_countpriority.c
```
Neste arquivo eu criei a estrutura que guarda a prioridade mínima, a máxima
e o contador. Também criei o callback que recebe cada tarefa e verifica o
campo `tcb->sched_priority`.
A função `nxsched_foreach` percorre as tarefas internas do NuttX e chama o
callback uma vez para cada tarefa. O callback aumenta o contador somente
quando a prioridade está dentro da faixa.
### 2. Declaração da função
Arquivo:
```text
nuttx/include/nuttx/sched.h
```
Adicionei o protótipo da função para que outros arquivos, como a aplicação de
teste, possam chamá-la.
### 3. Inclusão na compilação
Arquivo:
```text
nuttx/sched/sched/Make.defs
```
Adicionei `sched_countpriority.c` à lista de arquivos C do escalonador. Sem
isso, o arquivo existiria, mas não seria compilado junto com o kernel.
### 4. Aplicação de teste
Arquivo:
```text
apps/examples/taskcount/taskcount_main.c
```
A aplicação cria duas tarefas, `T1` e `T2`, chama a função do kernel e mostra
os resultados no terminal serial.
## Como compilei
No terminal WSL, entrei na pasta do NuttX:
```bash
cd /home/aluno/nuttxspace/nuttx
```
Depois configurei o ESP32-DevKitC:
```bash
./tools/configure.sh esp32-devkitc:nsh
```
No menu de configuração, habilitei o aplicativo em:
```text
Application Configuration
  → Examples
    → taskcount
```
A compilação foi feita com:
```bash
make -j$(nproc)
```
O arquivo gerado foi:
```text
/home/aluno/nuttxspace/nuttx/nuttx.bin
```
## Como gravei no ESP32
no PowerShell e gravei o firmware com:
```powershell
python -m esptool --chip esp32 --port COM9 --baud 921600 write-flash --flash-mode dio --flash-freq 40m --flash-size 4MB 0x1000 "\\wsl.localhost\Ubuntu-NuttX\home\aluno\nuttxspace\nuttx\nuttx.bin"
```
Depois abri o terminal serial com:
```powershell
python -m serial.tools.miniterm COM9 115200
```
## Resultado dos testes
No NuttShell, executei:
```text
taskcount
```
O resultado da faixa válida foi:
```text
Retorno da consulta: 0
Tarefas entre prioridade 100 e 150: 3
```
O número de tarefas pode variar conforme as tarefas internas que estão
ativas no momento.
Também testei uma faixa inválida, usando prioridade mínima 150 e máxima 100:
```text
Retorno da consulta invalida: -22
```
Por fim, testei o ponteiro nulo:
```text
Retorno com ponteiro nulo: -22
```
O valor `-22` corresponde a `-EINVAL`.

