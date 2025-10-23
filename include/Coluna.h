#ifndef COLUNA_H
#define COLUNA_H

#include "Tarefa.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Coluna {
  public: 
    Coluna(string status
    void adicionarTarefa(const Tarefa& tarefa);
    void removerTarefa(int id);
    void ordenarTarefas();
    int contarTarefas() const;
    void exibirTarefas() const;

  private:
    string status;
    vector<Tarefa> tarefas;
}

#endif

