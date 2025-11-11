#include "FiltroPrioridade.h"
#include "Tarefa.h"  //garante que a Tarefa e getPrioridade() são conhecidos
#include <vector>

//construtor
//apenas captura o valor da prioridade alvo. Mantemos 'int' porque seu
FiltroPrioridade::FiltroPrioridade(int prioridade)
    : prioridadeDesejada_(prioridade) {}

//recebe um vetor de tarefas e devolve um NOVO vetor somente com as
//tarefas que tem prioridade == prioridadeDesejada
//não altera o vetor original, ou seja, o mesmo vetor base pode ser
//reutilizado para outras combinações de filtros
//isso permite aplicar um filtro depois do outro sobre o resultado do
//anterior.
//exemplo: primeiro filtra por tag("Faculdade"), depois por prioridade
//(Alta)
std::vector<Tarefa> FiltroPrioridade::aplicar(const std::vector<Tarefa>& tarefas) const {
    std::vector<Tarefa> resultado;
    resultado.reserve(tarefas.size());//evita realocações

    for (const auto& t : tarefas) {
        if (t.getPrioridade() == prioridadeDesejada_) {
            //cópia por valor
            resultado.push_back(t);
        }
    }

    return resultado;
}
