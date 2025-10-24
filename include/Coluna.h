#ifndef COLUNA_H
#define COLUNA_H

#include "Tarefa.h"
#include <vector>
#include <string>
#include <iostream>

class Coluna {
  public: 
    Coluna(const std::string& status);
    void adicionarTarefa(const Tarefa& tarefa);
    void removerTarefa(int id);
    void ordenarTarefas();
    int contarTarefas() const;
    void exibirTarefas() const;

  private:
    std::string status;
    std::vector<Tarefa> tarefas;
};

#endif

