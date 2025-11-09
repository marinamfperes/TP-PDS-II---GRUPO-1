#ifndef ESTRATEGIA_FILTRO_H
#define ESTRATEGIA_FILTRO_H

#include "Tarefa.h"
#include <vector>

class EstrategiaFiltro {
public:
    virtual ~EstrategiaFiltro();

    virtual std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const = 0;
};

#endif 