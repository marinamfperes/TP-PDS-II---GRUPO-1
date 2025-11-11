#ifndef COLUNA_H
#define COLUNA_H

#include "Tarefa.h"
#include "Notificador.h"
#include <vector>
#include <string>

class Coluna {
public:
    explicit Coluna(std::string status);

    void adicionarTarefa(const Tarefa& tarefa);
    void ordenarTarefas();

    void exibirTarefas() const;

    const std::string& getStatus() const;
    const std::vector<Tarefa>& getTarefas() const;

private:
    std::string status_;
    std::vector<Tarefa> tarefas_;
};

#endif