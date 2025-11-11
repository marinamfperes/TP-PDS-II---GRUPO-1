#include "Coluna.h"
#include <algorithm>
#include <iostream>

Coluna::Coluna(std::string status) : status_(std::move(status)) {}

void Coluna::adicionarTarefa(const Tarefa& tarefa) {
    Tarefa cpy = tarefa;
    cpy.atualizarStatus(status_);
    tarefas_.push_back(std::move(cpy));
}

void Coluna::ordenarTarefas() {
    std::stable_sort(tarefas_.begin(), tarefas_.end(),
        [](const Tarefa& a, const Tarefa& b){
            if (a.getPrioridade() != b.getPrioridade())
                return a.getPrioridade() > b.getPrioridade();
            const auto va = a.getVencimento();
            const auto vb = b.getVencimento();
            if (va == 0 && vb == 0) return false;
            if (va == 0) return false;
            if (vb == 0) return true;
            return va < vb;
        }
    );
}

void Coluna::exibirTarefas() const {
    std::cout << "=== " << status_ << " (" << tarefas_.size() << ") ===\n";
    for (const auto& t : tarefas_) {
        std::cout << "ID:" << t.getId()
                  << " | Titulo:" << t.getTitulo()
                  << " | Pri:" << t.getPrioridade()
                  << " | Venc:" << formataDataHora(t.getVencimento())
                   << " | Tags: ";
                  for (const auto& tag : t.getTags()) {
                      std::cout << tag << " "; //exibe as tags de cada tarefa
                  }
                  std::cout << "\n";
    }
    std::cout << std::endl;
}

const std::string& Coluna::getStatus() const { return status_; }
const std::vector<Tarefa>& Coluna::getTarefas() const { return tarefas_; }
