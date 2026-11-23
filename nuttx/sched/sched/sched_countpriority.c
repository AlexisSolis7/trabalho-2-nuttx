#include <errno.h> // isso aque define constantes de erros como o EINVAL

#include "sched/sched.h"

struct taskcount_info
{
    int prioridade_min;
    int prioridade_max;
    int quantidade;
};

static void taskcount_callback(struct tcb_s *tcb,
                               void *arg)
{
    struct taskcount_info *info = arg; // O endereço guardado em arg aponta para uma estrutura taskcount_info; vou chamar esse endereço de info

    if (tcb->sched_priority >= info->prioridade_min && // estamos recebendo o endereço
        tcb->sched_priority <= info->prioridade_max)
    {
        info->quantidade++;
    }
}

int escalonador_contar_faixa_prioridade(int prioridade_min,
                                        int prioridade_max,
                                        int *quantidade)
{
    if (prioridade_min > prioridade_max)
    {
        return -EINVAL;
    }

    if (quantidade == NULL)
    {
        return -EINVAL;
    }

    struct taskcount_info info;

    info.prioridade_min = prioridade_min;
    info.prioridade_max = prioridade_max;
    info.quantidade = 0;
    // esse  &info envia o endereço do que esta encima
    nxsched_foreach(taskcount_callback, &info); // Ela percorre todas as tarefas registradas no sistema.

    *quantidade = info.quantidade;

    return 0;
}