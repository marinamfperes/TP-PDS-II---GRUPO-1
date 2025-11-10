#include "FiltroCombinado.h"
#include "EstrategiaFiltro.h"
#include "Tarefa.h"

#include <vector>
#include <memory>

//adiciona um filtro à cadeia (ignora ponteiros nulos)
void FiltroCombinado::adicionarFiltro(std::shared_ptr<EstrategiaFiltro>
filtro) {
    if (filtro) {
        filtros_.push_back(std::move(filtro));
    }
}

//aplica os filtros sequencialmente sobre a coleção de tarefas
//cada filtro recebe a saída do filtro anterior
std::vector<Tarefa> FiltroCombinado::aplicar(const std::vector<Tarefa>&
tarefas) const {
    std::vector<Tarefa> resultado = tarefas;
    for (const auto& f : filtros_) {
        if (!f) continue;
        resultado = f->aplicar(resultado); //aplica em cascata
    }
    return resultado;
}
