#ifndef GERENCIADORTAREFAS_H
#define GERENCIADORTAREFAS_H

#include "Tarefa.h"
#include "Relogio.h"
#include "EstrategiaFiltro.h"
#include "FiltroCombinado.h"
#include <vector>
#include <memory>
#include <string>

class GerenciadorTarefas {
public:
    GerenciadorTarefas(Relogio* relogio);


    //OPERAÇÕES COM TAREFAS
    void criarTarefa(Tarefa tarefa); // cria uma nova tarefa (valida campos e datas)
    void editarTarefa(int id, Tarefa tarefaAtualizada); // edita campos da tarefa existente
    void excluirTarefa(int id); // exclui a tarefa
    void moverTarefa(int id, const std::string& novoStatus);//move a tarefa entre colunas via status


    bool obterTarefaPorId(int id, Tarefa& out) const;

    //contagem de tarefas pendentes
    int contarTarefasPendentes() const; //conta quantas tarefas estão em pendência

    //acessa todas as tarefas
    const std::vector<Tarefa>& getTodasTarefas() const;

    //função para aplicar filtros
    void aplicarFiltros(const std::vector<std::shared_ptr<EstrategiaFiltro>>& filtros);

    private:
    std::vector<Tarefa> tarefas_;
    Relogio* relogio_;
};

#endif
