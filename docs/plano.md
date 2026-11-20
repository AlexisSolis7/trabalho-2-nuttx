# Plano de desenvolvimento

## Decisões pendentes

| Decisão | Estado |
| --- | --- |
| Funcionalidade nova | A definir |
| Subsistema do NuttX | A definir |
| Versões/commits de nuttx e nuttx-apps | A definir |
| Forma de versionar o código do NuttX e as alterações | A definir |
| Interface pública e contrato de erros | A definir |
| Estruturas e funções internas necessárias | A investigar |
| Mecanismo de sincronização | A avaliar conforme a funcionalidade |

## Etapas

1. Investigar uma funcionalidade pequena e verificar o que o NuttX já oferece.
2. Descrever a proposta, sua utilidade e a diferença em relação às interfaces existentes.
3. Registrar as versões-base e reproduzir a compilação original para ESP32-DevKitC em modo FLAT.
4. Rastrear no código uma interface existente do subsistema escolhido.
5. Definir parâmetros, retornos, erros e regras de acesso concorrente.
6. Implementar o serviço no kernel e integrar a compilação e os registros necessários.
7. Implementar a aplicação de teste e executar os casos na placa.
8. Atualizar o README e preparar a demonstração prática.

## Planejamento dos testes

Os casos serão detalhados após a definição da interface. Nenhum resultado foi obtido ainda.

| Categoria | O que verificar | Estado |
| --- | --- | --- |
| Uso normal | Retorno e dados de saída correspondem ao contrato | Pendente |
| Entrada inválida | Erros previstos são retornados sem comportamento indevido | Pendente |
| Limites | Valores extremos e tamanhos mínimos/máximos, se aplicáveis | Pendente |
| Concorrência | Acesso simultâneo ou mudanças nas estruturas consultadas, se aplicável | Pendente |
| Repetição | Chamadas repetidas mantêm o comportamento esperado | Pendente |
| Plataforma | Compilação FLAT e execução no ESP32-DevKitC | Pendente |

Para cada teste executado, registrar: versão do firmware, configuração, entrada, resultado esperado, resultado observado e evidência obtida.

## Entrega

- Disponibilizar o código das modificações no NuttX e a aplicação de teste.
- Identificar claramente todos os arquivos modificados ou adicionados.
- Documentar estruturas e funções internas utilizadas.
- Fornecer instruções reproduzíveis de compilação e execução.
- Registrar os resultados reais dos testes.
- Conferir os prazos no Moodle e agendar a apresentação com o professor.
