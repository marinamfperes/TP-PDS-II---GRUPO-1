#ifndef GERENCIADORTAREFAS_H
#define GERENCIADORTAREFAS_H

#include "Tarefa.h"
#include <vector>
#include <string>

//declaração antecipada, só para o compilador saber que essas classes existem em algum lugar
class Quadro;
class Notificador;
class Relogio;

class GerenciadorTarefas {
public:
    GerenciadorTarefas(Notificador* notificador, Relogio* relogio);

    //associa o Quadro ao gerenciador
    void setQuadro(Quadro* q);

    //OPERAÇÕES COM TAREFAS
    void criarTarefa(Tarefa tarefa); // cria uma nova tarefa (valida campos e datas)
    void editarTarefa(int id, Tarefa tarefa); // edita campos da tarefa existente
    void excluirTarefa(int id); // exclui a tarefa
    void moverTarefa(int id, const std::string& novoStatus);//move a tarefa entre colunas via status

    //filtros e ordenação
    std::vector<Tarefa> listarTarefasPorStatus(const std::string&  status) const; //devolve somente as tarefas que estão em um determinado status do quadro
    //notificação
    void notificarTarefas(); //permite a sinalização de tareefas vencidas ou próximas de vencimento

    //contagem de tarefas pendentes
    int contarTarefasPendentes() const; //conta quantas tarefas estão em pendência

    //acessa todas as tarefas
    const std::vector<Tarefa>& getTodasTarefas() const;

private:
    std::vector<Tarefa> tarefas_;
    Quadro* quadro_;
    Notificador* notificador_;
    Relogio* relogio_;
};

#endif
