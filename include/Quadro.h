#ifndef QUADRO_H
#define QUADRO_H

#include "Coluna.h"
#include <vector>

class Quadro {
public:
    Quadro();

    // Constrói um quadro a partir do vetor de tarefas atual
    static Quadro construirDe(const std::vector<Tarefa>& tarefas);

    void exibirQuadro() const;

private:
    Coluna aFazer_;
    Coluna fazendo_;
    Coluna feito_;
};

#endif
