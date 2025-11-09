#ifndef FILTRO_PRIORIDADE_H
#define FILTRO_PRIORIDADE_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <string>

class FiltroPrioridade : public EstrategiaFiltro {
private:
    int prioridadeDesejada_; //prioridade a ser filtrada

public:
    FiltroPrioridade(int prioridade);

    //implementa o método aplicar da interface
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override;

};

#endif
