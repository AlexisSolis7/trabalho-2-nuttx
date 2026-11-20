# Trabalho 2 — Serviço de kernel no Apache NuttX

Trabalho individual da disciplina **Sistemas Operacionais Embarcados — DEC7562**, do curso de Engenharia de Computação da Universidade Federal de Santa Catarina (UFSC).

**Autor:** Alexis S.

**Professor:** Anderson Luiz Fernandes Perez

## Estado do projeto

Repositório inicial de organização do trabalho. **A funcionalidade ainda será definida.** Não há implementação, firmware ou testes executados neste repositório.

## Objetivo

Desenvolver uma nova interface de serviço do kernel do Apache NuttX, acessível por aplicações e implementada por meio de modificações no próprio sistema operacional. A aplicação de teste servirá para validar essa interface.

## Plataforma exigida

- Sistema operacional: Apache NuttX.
- Placa: ESP32-DevKitC.
- Modelo de compilação: **FLAT**.
- Versão/commit do NuttX e de nuttx-apps: a definir e registrar antes da implementação.

## Funcionalidade proposta

**A definir.** A escolha deverá identificar o subsistema envolvido, as estruturas e funções internas utilizadas e a contribuição nova em relação às interfaces existentes.

O enunciado permite investigar, por exemplo, tarefas e processos, escalonamento, memória, sincronização e comunicação, temporizadores ou monitoramento de recursos. Não é necessário implementar todas essas áreas.

## Requisitos de implementação

- [ ] Definir a funcionalidade e investigar as interfaces já existentes.
- [ ] Identificar o subsistema e os mecanismos internos envolvidos.
- [ ] Definir a interface pública, os parâmetros e o comportamento em caso de erro.
- [ ] Implementar o serviço dentro do subsistema apropriado do NuttX.
- [ ] Integrar os arquivos ao sistema de compilação.
- [ ] Tratar o registro na infraestrutura de chamadas de sistema conforme necessário à interface e à configuração.
- [ ] Tratar validação, concorrência e sincronização.
- [ ] Criar a aplicação de teste.
- [ ] Compilar e executar no ESP32-DevKitC em modo FLAT.
- [ ] Registrar testes normais e situações de erro aplicáveis.

## Organização inicial

```text
README.md       Descrição e acompanhamento do trabalho
docs/plano.md   Decisões pendentes, etapas e planejamento dos testes
```

A forma de versionar as modificações no NuttX será definida antes da implementação. O código modificado e a aplicação de teste deverão ficar disponíveis, com identificação clara da versão-base e das alterações.

## Arquivos do NuttX modificados ou adicionados

Nenhum até o momento. Esta seção será atualizada com o caminho de cada arquivo e a finalidade da alteração.

## Estruturas e funções internas utilizadas

A definir após a investigação do subsistema escolhido.

## Compilação e execução

Instruções pendentes. Ainda não existe uma aplicação deste trabalho para compilar ou executar.

Ao implementar, registrar nesta seção:

1. Versões/commits do NuttX e de nuttx-apps e ferramentas utilizadas.
2. Preparação do ambiente e configuração da placa, incluindo o modo FLAT.
3. Comandos de compilação e gravação.
4. Acesso ao NuttShell (NSH) e comando para executar a aplicação de teste.
5. Saída esperada e procedimento para reproduzir os resultados.

## Testes e resultados

Nenhum teste foi executado neste projeto. O planejamento inicial está em [docs/plano.md](docs/plano.md).

Os resultados deverão distinguir o comportamento esperado do observado, incluindo as entradas utilizadas e as evidências da execução na placa.

## Apresentação

O autor deverá demonstrar a execução na placa e explicar a interface, os arquivos alterados, as estruturas internas, as decisões de implementação e os testes realizados.

## Referências

- [Apache NuttX — documentação](https://nuttx.apache.org/docs/latest/)
- [Código-fonte do NuttX](https://github.com/apache/nuttx)
- [Aplicações do NuttX](https://github.com/apache/nuttx-apps)
- Enunciado do Segundo Trabalho Prático disponibilizado pelo professor.
