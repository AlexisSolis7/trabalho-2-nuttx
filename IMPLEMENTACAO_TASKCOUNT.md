# Trabalho 2 — Contagem de tarefas por prioridade

## O que eu fiz

Eu criei uma função nova dentro do NuttX para contar quantas tarefas estão
dentro de uma faixa de prioridades.

A função criada foi:

```c
int escalonador_contar_faixa_prioridade(int prioridade_min,
                                         int prioridade_max,
                                         int *quantidade);
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

O WSL não mostrou a porta serial como `/dev/ttyUSB` ou `/dev/ttyACM`. No
Windows, a placa apareceu como `COM9`.

Usei o `esptool` instalado no PowerShell e gravei o firmware com:

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

## O que aprendi

Eu não precisei entender todos os arquivos do NuttX. Primeiro fiz um exemplo
simples em `apps/examples`, seguindo o estilo das aulas. Depois localizei a
função `nxsched_foreach`, que já percorre as tarefas internas, e usei essa
estrutura para implementar a nova consulta no kernel.

A aplicação é apenas o teste. A funcionalidade principal está dentro do
NuttX, no arquivo `sched_countpriority.c`.
