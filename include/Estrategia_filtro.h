#ifndef ESTRATEGIA_FILTRO_H
#define ESTRATEGIA_FILTRO_H

#include "Tarefa.h"
#include <vector>

class EstrategiaFiltro {
public:
    virtual ~EstrategiaFiltro() = default;

    // Aplica o filtro sobre uma lista de tarefas e retorna as que atendem ao critério
    virtual std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const = 0;
};

#endif // ESTRATEGIA_FILTRO_H
