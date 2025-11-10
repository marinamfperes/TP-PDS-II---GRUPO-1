#include "Relogio.h"
#include <ctime>

// Construtor padrão
Relogio::Relogio() = default;

// Retorna a hora atual do sistema
std::time_t Relogio::agora() const {
    return std::time(nullptr); // Retorna o timestamp atual em segundos desde 1970
}
