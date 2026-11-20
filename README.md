# Trabalho 2 — Serviço de kernel no Apache NuttX

Trabalho da disciplina **Sistemas Operacionais Embarcados — DEC7562**

**Eu:** Alexis S.

**Professor:** Anderson Luiz Fernandes Perez

## Estado do projeto

Repositório inicial de organização do trabalho. **CONTINUARA...** 

## Objetivo

Implementar no kernel do NuttX uma função que receba prioridade mínima, máxima e um ponteiro para a contagem. Se a faixa for válida e o ponteiro não for nulo, o NuttX percorre suas tarefas, compara as prioridades e devolve a quantidade. Se a faixa for inválida ou o ponteiro for nulo, retorna erro. A implementação ficará no subsistema de agendamento e o arquivo será incluído na compilação. Aplicação de teste: um exemplo em apps barra examples no mesmo. A aplicação chama a nova interface, imprime o resultado no NuttShell, cria tarefas de teste, consulta antes e depois e testa entradas inválidas. Testes no ESP32 pelo terminal

