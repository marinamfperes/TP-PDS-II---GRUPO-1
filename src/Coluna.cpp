#include "Coluna.h"
#include <iostream>
#include <string>
#include <algorithm>

Coluna::Coluna(const std::string& status) : status_(status) {} //construtor

void Coluna::adicionarTarefa(const Tarefa& tarefa) { //add tarefa na coluna e sincroniza status da tarefa com o da coluna
    Tarefa copia = tarefa;
    copia.atualizarStatus(status_);
    tarefas_.push_back(std::move(copia));
    ordenarTarefas(); //reordena por PrioridadeDepoisPrazo
} //add tarefa no final do vetor

void Coluna::removerTarefa(int id) { //remove a tarefa por id
    auto it = std::remove_if(tarefas_.begin(), tarefas_.end(),
                             [id](const Tarefa& t){ return t.getId() == id; });
    tarefas_.erase(it, tarefas_.end());
}

void Coluna::ordenarTarefas() { //ordena por prioridade (maior primeiro) e depois por vencimento caso haja empate (quem vence antes vem antes e sem prazo = 0)
    std::stable_sort(tarefas_.begin(), tarefas_.end(),
        [](const Tarefa& a, const Tarefa& b){
            if (a.getPrioridade() != b.getPrioridade()) //prioridade da maior para menor
                return a.getPrioridade() > b.getPrioridade();

            const auto va = a.getVencimento(); //prazo do mais próximo para o mais longe; "sem prazo" vem por último
            const auto vb = b.getVencimento();

            if (va == 0 && vb == 0) return false;
            if (va == 0) return false; // 'a' sem prazo vai depois
            if (vb == 0) return true; // 'b' sem prazo vai depois
            return va < vb; // mais cedo primeiro
        }
    );
}

int Coluna::contarTarefas() const {
    return static_cast<int>(tarefas_.size());
}

void Coluna::exibirTarefas() const {
    std::cout << "=== Coluna: " << status_ << " (" << tarefas_.size() << " tarefas) ===\n";
    for (const auto& t : tarefas_) { //exibição dos campos principais
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
    return status_;
}

bool Coluna::extrairTarefaPorId(int id, Tarefa& outTarefa) { //extrai tarefa por id para mover ela entre colunas
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return false;


    outTarefa = *it; //copia para outro tarefa
    tarefas_.erase(it); //remove da coluna
    return true; //retorna verdadeiro se achou
}
