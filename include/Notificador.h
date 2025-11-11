#ifndef NOTIFICADOR_H
#define NOTIFICADOR_H

#include "Tarefa.h"
#include "Usuario.h"
#include "GerenciadorTarefas.h"
#include "DataUtil.h"
#include <ctime>
#include <vector>
// sem isso ele abriria o gerenciador, e o arquivo do gerenciador pediria para abrir esse, criando um loop
class GerenciadorTarefas; // impede uma redundancia ao executar funcoes do gerenciador.h e do notificacao.h

class Notificador {
private:
    GerenciadorTarefas& gerenciador_; // guarda um atalho para o gerenciador original
    const Usuario& usuario_; // guarda um atalho para  usuario, para acessar a preferencia de notificacao
    long segundosAntecedencia_; // guarda em segundos o tempo de antecedencia (24h = 86400 seg)
    Relogio* relogio_; //guarda um atalho para relogio, para pegar o tempo atual

public:
    Notificador(GerenciadorTarefas& mgr, const Usuario& usuario,  Relogio* relogio); // constroi o notificador (usa o GerenciadorTarefas, colaborador)

    void setAntecedenciaNotificacao(long segundos); // define periodo considerado prox do vencimento

    // identifica quais venceram e sinaliza
    std::vector<Tarefa> getTarefasVencidas() const;

    // retorna a lista de quais nao venceram mas estao dentro da funcao de antecedencia(periodo prox de vencer) 
    std::vector<Tarefa> getTarefasProximasDoVencimento() const;

    // exibe os avisos na tela
    void exibirAvisos() const;

};
#endif
