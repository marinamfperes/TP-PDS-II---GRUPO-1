#ifndef RELOGIO_H
#define RELOGIO_H

#include <ctime>

class Relogio {
public:
    Relogio();

    // Retornar a hora atual do sistema
    virtual std::time_t agora() const; // a variavel virtual permitirá criar dados de mentira para testar codigos
};

#endif       
  
