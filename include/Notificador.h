#ifndef NOTIFICADOR_H
#define NOTIFICADOR_H

#include "Tarefa.h"
#include <ctime>
#include <vector>
// sem isso ele abriria o gerenciador, e o arquivo do gerenciador pediria para abrir esse, criando um loop
class GerenciadorTarefas; // impede uma redundancia ao executar funcoes do gerenciador.h e do notificacao.h

class Notificador {
private:
    GerenciadorTarefas& gerenciador_; // guarda um atalho para o gerenciador original

    long segundosAntecedencia_; // guarda em segundos o tempo de antecedencia (24h = 86400 seg)

    // Verificar tarefas vencidas ou próximas do vencimento
    void verificarTarefas(std::vector<Tarefa>& tarefas, std::time_t agora);

public:
    Notificador(GerenciadorTarefas& mgr); // constroi o notificador (usa o GerenciadorTarefas, colaborador)


    void setAntecedenciaNotificacao(long segundos); // define periodo considerado prox do vencimento

    // identifica quais venceram e sinaliza
    std::vector<Tarefa> getTarefasVencidas();

    // retorna a lista de quais nao venceram mass estao dentro da funcao de antecedencia(periodo prox de vencer) 
    std::vector<Tarefa> getTarefasProximasDoVencimento();
};
#endif
