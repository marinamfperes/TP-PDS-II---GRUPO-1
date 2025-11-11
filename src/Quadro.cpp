#include "Quadro.h"
#include <iostream>

Quadro::Quadro()
: aFazer_("A Fazer"), fazendo_("Fazendo"), feito_("Feito") {}

Quadro Quadro::construirDe(const std::vector<Tarefa>& tarefas) {
    Quadro q;
    for (const auto& t : tarefas) {
        const std::string& st = t.getStatus();
        if (st == "A Fazer")      q.aFazer_.adicionarTarefa(t);
        else if (st == "Fazendo") q.fazendo_.adicionarTarefa(t);
        else                      q.feito_.adicionarTarefa(t); //default = Feito
    }
    q.aFazer_.ordenarTarefas();
    q.fazendo_.ordenarTarefas();
    q.feito_.ordenarTarefas();
    return q;
}

void Quadro::exibirQuadro() const {
    std::cout << "\n====== QUADRO KANBAN ======\n";
    aFazer_.exibirTarefas();
    fazendo_.exibirTarefas();
    feito_.exibirTarefas();
}
