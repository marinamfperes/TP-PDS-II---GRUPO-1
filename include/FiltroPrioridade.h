#ifndef FILTRO_PRIORIDADE_H
#define FILTRO_PRIORIDADE_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <string>

class FiltroPrioridade : public EstrategiaFiltro {
private:
    int prioridadeDesejada; //prioridade a ser filtrada

public:
    FiltroPrioridade(int prioridade) : prioridadeDesejada(prioridade) {}

    //implementa o método aplicar da interface
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override {
        std::vector<Tarefa> resultado;

        for (const auto& t : tarefas) {
            if (t.getPrioridade() == prioridadeDesejada) {
                resultado.push_back(t);
            }
        }

        return resultado; //retorna só as tarefas que possuem esse filtro
    }
};

#endif
