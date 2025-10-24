#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    explicit Usuario(const std::string& nome);

    std::string getNome() const;
    int getHorasPreferenciaNotificacao() const;

    void definirHorasPreferenciaNotificacao(int horas);

private:
    std::string nome;
    int horasPreferenciaNotificacao;  
};

#endif 
