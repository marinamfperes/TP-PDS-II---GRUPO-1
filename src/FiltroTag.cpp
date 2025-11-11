#include "FiltroTag.h"
#include "Tarefa.h"
#include <algorithm> //std::find

FiltroTag::FiltroTag(const std::string& tag)
    : tagDesejada_(tag) {}

//retorna apenas às tarefas que CONTÉM a tag exata na sua lista de tags
//se a tag desejada estiver vazia, retorna a coleção original (sem filtrar)
std::vector<Tarefa> FiltroTag::aplicar(const std::vector<Tarefa>&
tarefas) const {

    if (tagDesejada_.empty()) {
        return tarefas; //sem critério = sem filtro
    }

    std::vector<Tarefa> filtradas;
    filtradas.reserve(tarefas.size());

    for (const auto& t : tarefas) {
        const auto& tags = t.getTags();
        if (std::find(tags.begin(), tags.end(), tagDesejada_) !=
tags.end()) {

            filtradas.push_back(t);
        }
    }
    return filtradas;
}
