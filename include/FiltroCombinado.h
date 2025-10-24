#ifndef FILTRO_COMBINADO_H
#define FILTRO_COMBINADO_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <memory>

class FiltroCombinado : public EstrategiaFiltro {
  private:
    std::vector<std::shared_ptr<EstrategiaFiltro>> filtros;

  public:
    void adicionarFiltro(std::shared_ptr<EstrategiaFiltro> filtro) {
        filtros.push_back(filtro);
    } //adição de filtro
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override {
        std::vector<Tarefa> resultado = tarefas;
        for (const auto& filtro : filtros) {
            resultado = filtro->aplicar(resultado); // aplica filtro 
        }
        return resultado;
    }
};

#endif
