#include "Coluna.h"
#include <iostream> 
#include <string> 

Coluna::Coluna(const std::string& status) : status(status) {}
void Coluna::adicionarTarefa(const Tarefa& tarefa) {
    tarefas.push_back(tarefa);
} //add tarefa no final do vetor

void Coluna::removerTarefa(int id) {
    int idx = -1;
    for (size_t i = 0; i < tarefas.size(); ++i) {
        if (tarefas[i].getId() == id) {
            idx = static_cast<int>(i); // remove a primeira ocorrência de tarefa com o id fornecido
            break;
        }
    } if (idx != -1) {
        for (size_t j = idx; j + 1 < tarefas.size(); ++j) {
            tarefas[j] = std::move(tarefas[j + 1]);
        }
        tarefas.pop_back();
    }
}

void Coluna::ordenarTarefas() {
  const size_t n = tarefas.size();
  for (size_t i = 0; i < n; ++i) {
      size_t best = i;
      for (size_t j = i + 1; j < n; ++j) {
          const Tarefa& a = tarefas[j];
          const Tarefa& b = tarefas[best];
          if (a.getPrioridade() != b.getPrioridade()) {
                if (a.getPrioridade() > b.getPrioridade()) best = j; //maior prioridade primeiro
            } else {
                if (a.getVencimento() < b.getVencimento()) best = j; //se mesma prioridade, vencimento menor (mais próximo) primeiro
            }
        }
        if (best != i) {
            Tarefa tmp = std::move(tarefas[best]);
            tarefas[best] = std::move(tarefas[i]);
            tarefas[i] = std::move(tmp);
        }
    }
}

int Coluna::contarTarefas() const {
    return static_cast<int>(tarefas.size());
}

void Coluna::exibirTarefas() const {
    std::cout << "=== Coluna: " << status << " (" << tarefas.size() << " tarefas) ===\n";
    for (const auto& t : tarefas) { //exibição dos campos principais
        std::cout << "ID: " << t.getId()
                  << " | Título: " << t.getTitulo()
                  << " | Status: " << t.getStatus()
                  << " | Prioridade: " << t.getPrioridade()
                  << " | Venc.: " << static_cast<long long>(t.getVencimento())
                  << "\n";
    }
    std::cout << std::endl;
}

std::string Coluna::getStatus() const {
    return status;
}

bool Coluna::extrairTarefaPorId(int id, Tarefa& outTarefa) {
    int idx = -1;
    for (size_t i = 0; i < tarefas.size(); ++i) {
        if (tarefas[i].getId() == id) {
            idx = static_cast<int>(i);
            break;
        }
    }
    if (idx == -1) {
        return false;
    }
    outTarefa = tarefas[idx];  //copia a tarefa encontrada para outTarefa
    for (size_t j = idx; j + 1 < tarefas.size(); ++j) {
        tarefas[j] = std::move(tarefas[j + 1]);
    }
    tarefas.pop_back();
    return true;
}
