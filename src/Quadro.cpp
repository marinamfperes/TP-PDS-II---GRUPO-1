#include "Quadro.h"
#include "Coluna.h"
#include <iostream>
#include <string>

Quadro::Quadro() {
    
}

void Quadro::adicionarColuna(const Coluna& coluna) { //add coluna 
    colunas.push_back(coluna);
}

void Quadro::exibirQuadro() const { //exibição do quadro reutilizando o exibirTarefas de cada uma
    std::cout << "Quadro\n";
    for (size_t i = 0; i < colunas.size(); ++i) {
        colunas[i].exibirTarefas();
    }
}

void Quadro::moverTarefaParaColuna(int id, std::string& novoStatus) {
    Tarefa tarefaExtraida;
    bool encontrada = false;
    for (size_t i = 0; i < colunas.size(); ++i) {
        if (colunas[i].extrairTarefaPorId(id, tarefaExtraida)) { //procura coluna de origem
            encontrada = true;
            break;
        }
    }

        if (!encontrada) {
        std::cout << "Aviso: tarefa com ID " << id << " não encontrada.\n";
        return;
    }
    tarefaExtraida.atualizarStatus(novoStatus) //atualizar status da tarefa extraída
    for (size_t i = 0; i < colunas.size(); ++i) {
        if (colunas[i].getStatus() == novoStatus) {
            colunas[i].adicionarTarefa(tarefaExtraida);
            std::cout << "Tarefa " << id << " movida para coluna '" << novoStatus << "'.\n";
            return;
        }
    }
    Coluna nova(novoStatus); //cria coluna, se a dada na etapa anterior não existir
    nova.adicionarTarefa(tarefaExtraida);
    colunas.push_back(nova);
    std::cout << "Coluna '" << novoStatus << "' criada e tarefa " << id << " adicionada.\n";
}
