#include "Usuario.h"

// Construtor: inicializa o nome e define uma preferência padrão (24 horas)
Usuario::Usuario(const std::string& nome)
    : nome_(nome), horasPreferenciaNotificacao_(24) {}

std::string Usuario::getNome() const {
    return nome_;
}

int Usuario::getHorasPreferenciaNotificacao() const {
    return horasPreferenciaNotificacao_;
}

void Usuario::definirHorasPreferenciaNotificacao(int horas) {
    if (horas <= 0) {
        horasPreferenciaNotificacao_ = 24; // padrão
    } else {
        horasPreferenciaNotificacao_ = horas;
    }
}
