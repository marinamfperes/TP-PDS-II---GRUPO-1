#ifndef TAREFA_H
#define TAREFA_H

#include <string>
#include <vector>
#include <ctime>  //para manipular data e hora

class Tarefa {
public:
    Tarefa(std::string titulo, std::string descricao, std::string categoria,
           std::time_t agendada, std::time_t vencimento, int prioridade);

    //métodos de acesso
    int getId() const; //acessa o id único que diferencia as tarefas
    std::string getTitulo() const; //acessa o título
    std::string getDescricao() const; //acessa a descrição
    std::string getCategoria() const; //acessa a categoria
    std::time_t getAgendada() const; //acessa a data de realização agendada
    std::time_t getVencimento() const; //acessa a data de vencimento
    int getPrioridade() const; //acessa o nível de prioridade
    std::string getStatus() const; //acessa o status no Kanban

    //métodos de modificação
    void atualizarStatus(std::string novoStatus); //troca o status no Kanban
    bool estaVencida(std::time_t agora) const; //verifica se está vencida (overdue)
    bool estaProximaDoVencimento(std::time_t agora, int janelaHoras) const; //verifica se está próxima do vencimento
    void addTag(std::string tag); //adiciona tag (categoria)
    bool validarCampos() const; //verifica se título está preenchido
    bool validarDatas(std::time_t agora) const; //verifica se data e horário são válidos

private:
    int id;
    std::string titulo;
    std::string descricao;
    std::string categoria;
    std::time_t agendada; //time_t pega o tempo atual do sistema
    std::time_t vencimento;
    int prioridade;
    std::string status;  //"A Fazer", "Fazendo" ou "Feito"
    std::vector<std::string> tags;  //lista de tags associadas à tarefa
};

#endif
