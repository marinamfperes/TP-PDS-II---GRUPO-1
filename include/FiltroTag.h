#ifndef FILTRO_TAG_H
#define FILTRO_TAG_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <string>

class FiltroTag : public EstrategiaFiltro {
  private:
    std::string tagDesejada_;

  public:
    FiltroTag(const std::string& tag);
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override;
};

#endif