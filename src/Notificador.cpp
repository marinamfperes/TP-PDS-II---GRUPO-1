#include "Notificador.h"
#include "GerenciadorTarefas.h" //include real aqui
#include <algorithm>
#include <ctime>


//comparador
static bool comparaPrioridadeDepoisPrazo(const Tarefa& a, const Tarefa& b) {
    if (a.getPrioridade() != b.getPrioridade())
        return a.getPrioridade() > b.getPrioridade();


    const auto va = a.getVencimento();
    const auto vb = b.getVencimento();


    if (va == 0 && vb == 0) return false;
    if (va == 0) return false; //'a' sem prazo vem depois
    if (vb == 0) return true;  //'b' sem prazo vem depois
    return va < vb; //mais cedo vem primeiro
}


Notificador::Notificador(GerenciadorTarefas& mgr)
    : gerenciador_(mgr),
      segundosAntecedencia_(24 * 60 * 60) //padrão: 24h
{}


//define jnela de antecedência em segundos
void Notificador::setAntecedenciaNotificacao(long segundos) {
    if (segundos <= 0) {
        segundosAntecedencia_ = 24 * 60 * 60; //antecedência volta para o padrão de 24h
    } else {
        segundosAntecedencia_ = segundos;
    }
}


//retorna tarefas vencidas
std::vector<Tarefa> Notificador::getTarefasVencidas() {
    const std::time_t agora = std::time(nullptr);
    std::vector<Tarefa> vencidas;


    //requer que GerenciadorTarefas exiba getTodasTarefas()
    const auto& todas = gerenciador_.getTodasTarefas();
    vencidas.reserve(todas.size());


    for (const auto& t : todas) {
        if (t.getStatus() == "Feito") continue;  //não notificar concluídas
        if (t.estaVencida(agora)) {
            vencidas.push_back(t);
        }
    }


    std::stable_sort(vencidas.begin(), vencidas.end(), comparaPrioridadeDepoisPrazo);
    return vencidas;
}


//filtra tarefas próximas do vencimento segundo a janela configurada
std::vector<Tarefa> Notificador::getTarefasProximasDoVencimento() {
    const std::time_t agora = std::time(nullptr);
    const int janelaHoras = static_cast<int>(segundosAntecedencia_ / 3600);


    std::vector<Tarefa> proximas;
    const auto& todas = gerenciador_.getTodasTarefas();
    proximas.reserve(todas.size());




    for (const auto& t : todas) {
        if (t.getStatus() == "Feito") continue;
        // Próximas do vencimento = não vencidas e dentro da janela
        if (!t.estaVencida(agora) && t.estaProximaDoVencimento(agora, janelaHoras)) {
            proximas.push_back(t);
        }
    }


    std::stable_sort(proximas.begin(), proximas.end(), comparaPrioridadeDepoisPrazo);
    return proximas;
}


void Notificador::verificarTarefas(std::vector<Tarefa>& tarefas, std::time_t /*agora*/) {
    std::stable_sort(tarefas.begin(), tarefas.end(), comparaPrioridadeDepoisPrazo);
}