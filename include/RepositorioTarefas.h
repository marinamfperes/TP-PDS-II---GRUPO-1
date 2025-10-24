#ifndef REPOSITORIO_TAREFAS_H
#define REPOSITORIO_TAREFAS_H

#include "Tarefa.h"
#include <vector>
#include <string>

class RepositorioTarefas {
private:
    // repositorio sabera em qual arquivo deve salvar
    std::string Arquivo;

public:

    // Salvar tarefas em arquivo
    void salvarTarefa(const std::vector<Tarefa>& tarefas);

    // Carrega a lista Rde tarefas do banco de dados ou arquivo
    std::vector<Tarefa> carregarTarefas();

}

#endif
