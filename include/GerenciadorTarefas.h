#ifndef GERENCIADORTAREFAS_H
#define GERENCIADORTAREFAS_H

#include "Tarefa.h"
#include "Quadro.h"
#include "Notificador.h"
#include "Relogio.h"
#include <vector>

class GerenciadorTarefas {
public:
    GerenciadorTarefas(Notificador* notificador, Relogio* relogio);

    //operações com tarefas
    void criarTarefa(Tarefa tarefa); //cria uma nova tarefa
    void editarTarefa(int id, Tarefa tarefa); //permite editar campos da tarefa
    void excluirTarefa(int id); //exclui a tarefa
    void moverTarefa(int id, std::string novoStatus); //move a tarefa no quadro Kanban via status

    //filtros e ordenação
    std::vector<Tarefa> listarTarefasPorStatus(std::string status); //devolve somente as tarefas que estão em um determinado status do quadro
    void ordenarTarefasPorPrioridade(); //ordena as tarefas por prioridade
    void ordenarTarefasPorData(); //ordena as tarefas por prazo

    //notificação
    void notificarTarefas(); //permite a sinalização de tareefas vencidas ou próximas de vencimento

    //contagem de tarefas pendentes
    int contarTarefasPendentes() const; //conta quantas tarefas estão em pendência

private:
    std::vector<Tarefa> tarefas;
    Quadro* quadro;
    Notificador* notificador;
    Relogio* relogio;
};

#endif
