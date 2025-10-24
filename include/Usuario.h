#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    explicit Usuario(const std::string& nome);

    // Getters
    std::string getNome() const;
    int getHorasPreferenciaNotificacao() const;

    // Define a antecedência das notificações (em horas)
    void definirHorasPreferenciaNotificacao(int horas);

private:
    std::string nome;
    int horasPreferenciaNotificacao; // Exemplo: 24, 48 etc.
};

#endif // USUARIO_H
