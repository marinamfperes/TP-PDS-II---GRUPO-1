#ifndef QUADRO_H
#define QUADRO_H

#include "Coluna.h"
#include <vector>
#include <string>

using namespace std;

class Quadro{
  public:
    Quadro();
      void adicionarColuna(const Coluna& coluna); //adicao de colunas
      void exibirQuadro() const; //exibicao das colunas
      void moverTarefaParaColuna(int idTarefa, string novoStatus);

  private:
    vector<Coluna> colunas;
}

#endif
  
