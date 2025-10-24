#ifndef QUADRO_H
#define QUADRO_H

#include "Coluna.h"
#include <vector>
#include <string>


class Quadro {
  public:
    Quadro();
      void adicionarColuna(const Coluna& coluna); //adicao de colunas
      void exibirQuadro() const; //exibicao das colunas
      void moverTarefaParaColuna(int id,  std::string& novoStatus);

  private:
     std::vector<Coluna> colunas;
};

#endif
  
