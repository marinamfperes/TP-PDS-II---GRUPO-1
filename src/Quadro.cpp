#include "Quadro.h"
#include "Coluna.h"
#include <iostream>
#include <algorithm>
#include <string>

namespace { //encontra índice da coluna pelo status
    int idxPorStatus(const std::vector<Coluna>& colunas, const std::string& status) {
        for (size_t i = 0; i < colunas.size(); ++i) {
            if (colunas[i].getStatus() == status) return static_cast<int>(i);
        }
        return -1;
    }
}

Quadro::Quadro() = default;

void Quadro::adicionarColuna(const Coluna& coluna) { //add coluna
    //evita duplicar colunas com o mesmo status
    if (idxPorStatus(colunas_, coluna.getStatus()) == -1) {
        colunas_.push_back(coluna);
    }
}

void Quadro::exibirQuadro() const { //exibição do quadro reutilizando o exibirTarefas de cada uma
    std::cout << "KANBAN\n";
    for (const auto& c : colunas_) {
        c.exibirTarefas();
    }
    std::cout << std::flush;
}

void Quadro::moverTarefaParaColuna(int id, const std::string& novoStatus) { //Tarefa não tem construtor default -> criar um temporário “vazio”
    Tarefa tarefaExtraida("", "", 0, 0, 0);
    bool encontrada = false;
    for (size_t i = 0; i < colunas_.size(); ++i) {
      if (colunas_[i].extrairTarefaPorId(id, tarefaExtraida)) { //procura coluna de origem
            encontrada = true;
            break;
        }
    }
      if (!encontrada) {
        std::cout << "Aviso: tarefa com ID " << id << " não encontrada.\n";
        return;
    }
   
    tarefaExtraida.atualizarStatus(novoStatus); //atualiza status da tarefa extraída

    int destino = idxPorStatus(colunas_, novoStatus);
    if (destino == -1) {
        //cia a coluna caso a dada não exista
        colunas_.emplace_back(novoStatus); //cria a coluna diretamente no vetor
        destino = static_cast<int>(colunas_.size()) - 1;
        std::cout << "Coluna '" << novoStatus << "' criada.\n";
    }

    colunas_[destino].adicionarTarefa(tarefaExtraida);
    std::cout << "Tarefa " << id << " movida para coluna '" << novoStatus << "'.\n";
}

bool Quadro::removerTarefaPorId(int id) { //remove a tarefa (por id) de qualquer coluna em que estiver
    bool removeu = false;
    for (auto& c : colunas_) {
        int antes = c.contarTarefas();
        c.removerTarefa(id);
        if (c.contarTarefas() < antes) removeu = true;
    }
    return removeu;
}
