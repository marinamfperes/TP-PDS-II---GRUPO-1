#ifndef FILTRO_COMBINADO_H
#define FILTRO_COMBINADO_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <memory>

class FiltroCombinado : public EstrategiaFiltro {
  private:
    std::vector<std::shared_ptr<EstrategiaFiltro>> filtros_;

  public:
    void adicionarFiltro(std::shared_ptr<EstrategiaFiltro> filtro);
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override;
};

#endif
