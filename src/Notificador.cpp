#include "Notificador.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

Notificador::Notificador(GerenciadorTarefas& mgr, const Usuario& usuario,  Relogio* relogio)
    : gerenciador_(mgr), usuario_(usuario), relogio_(relogio), segundosAntecedencia_(usuario.getHorasPreferenciaNotificacao() * 3600) {}
    //construído com base nas preferências do usuário

//retorna tarefas vencidas
std::vector<Tarefa> Notificador::getTarefasVencidas() const {
    const std::time_t agora = relogio_->agora(); //usa o relógio para obter o tempo atual
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

    return vencidas;
}

//filtra tarefas próximas do vencimento segundo a janela configurada
std::vector<Tarefa> Notificador::getTarefasProximasDoVencimento() const {
    const std::time_t agora = relogio_->agora();
    const int janelaHoras = static_cast<int>(segundosAntecedencia_ / 3600);

    std::vector<Tarefa> proximas;
    const auto& todas = gerenciador_.getTodasTarefas();
    proximas.reserve(todas.size());

    for (const auto& t : todas) {
        if (t.getStatus() == "Feito") continue;
        //próximas do vencimento = não vencidas e dentro da janela
        if (!t.estaVencida(agora) && t.estaProximaDoVencimento(agora, janelaHoras)) {
            proximas.push_back(t);
        }
    }

    return proximas;
}

//exibe os avisos de tarefas vencidas e próximas do vencimento
void Notificador::exibirAvisos() const {
    std::cout << "\n=== Avisos ===\n";
    auto vencidas = getTarefasVencidas();
    auto proximas = getTarefasProximasDoVencimento();

    //exibe tarefas vencidas
    std::cout << "\n[Vencidas]\n";
    if (vencidas.empty()) std::cout << "(nenhuma tarefa vencida)\n";
    else
        for (const auto& t : vencidas)
            std::cout << "ID: " << t.getId() << " | Titulo: " << t.getTitulo() << " | Vencimento: " << formataDataHora(t.getVencimento()) << "\n";

    //exibe tarefas próximas do vencimento
    std::cout << "\n[Proximas do Vencimento]\n";
    if (proximas.empty()) std::cout << "(nenhuma tarefa proxima do vencimento)\n";
    else
        for (const auto& t : proximas)
            std::cout << "ID: " << t.getId() << " | Titulo: " << t.getTitulo() << " | Vencimento: " << formataDataHora(t.getVencimento()) << "\n";
}