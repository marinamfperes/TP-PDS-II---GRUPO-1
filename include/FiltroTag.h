#ifndef FILTRO_TAG_H
#define FILTRO_TAG_H

#include "EstrategiaFiltro.h"
#include <vector>
#include <string>

class FiltroTag : public EstrategiaFiltro {
  private:
    std::string tagDesejada;

  public:
    FiltroTag(const std::string& tag) : tagDesejada(tag) {}
    std::vector<Tarefa> aplicar(const std::vector<Tarefa>& tarefas) const override {
        std::vector<Tarefa> resultado;
         for (const auto& t : tarefas) {
            for (const auto& tag : t.getTags()) { //supondo que Tarefa tenha getTags()
                if (tag == tagDesejada) {
                    resultado.push_back(t);
                    break; //evita de adicionar a mesma tarefa mais de uma vez
                }
            }
        }

        return resultado;
    }
};

#endif
