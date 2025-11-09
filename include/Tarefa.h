#ifndef TAREFA_H
#define TAREFA_H

#include <string>
#include <vector>
#include <ctime> //para manipular data e hora

class Tarefa {
public:
    Tarefa(std::string titulo, std::string descricao, std::time_t agendada, std::time_t vencimento, int prioridade);

    //métodos de acesso
    int getId() const; //acessa o id único que diferencia as tarefas

    //usado só durante a leitura do repositório (carga de arquivo)
    void setIdParaCarga(int novoId);

    //chamado pelo repositório após carregar tudo para evitar colisão de ids
    static void ajustarProximoId(int proximoVal);

    const std::string&  getTitulo() const; //acessa o título
    const std::string&  getDescricao() const; //acessa a descrição
    std::time_t getAgendada() const; //acessa a data de realização agendada
    std::time_t getVencimento() const; //acessa a data de vencimento
    int getPrioridade() const; //acessa o nível de prioridade
    const std::string&  getStatus() const; //acessa o status no Kanban
    const std::vector<std::string>& getTags() const; //acessa as tags (categorias)

    //setters
    void setTitulo(const std::string& novo);
    void setDescricao(const std::string& novo);
    void setAgendada(std::time_t ts);
    void setVencimento(std::time_t ts);
    void setPrioridade(int p);

    //métodos de modificação
    void atualizarStatus(const std::string& novoStatus); //troca o status no Kanban
    bool estaVencida(std::time_t agora) const; //verifica se está vencida (overdue)
    bool estaProximaDoVencimento(std::time_t agora, int janelaHoras) const; //verifica se está próxima do vencimento
    void addTag(const std::string& tag); //adiciona tag
    void clearTags(); //apaga tags
    bool removeTag(const std::string& tag);
    bool validarCampos() const; //verifica se título está preenchido
    bool validarDatas(std::time_t agora) const; //verifica se data e horário são válidos
    bool validar(std::time_t agora, std::string* erro = nullptr) const; //unifica as duas validações

private:
    int id;
    static int proximoId_; //gerador incremental de ids
    std::string titulo_;
    std::string descricao_;
    std::time_t agendada_; //time_t pega o tempo atual do sistema
    std::time_t vencimento_;
    int prioridade_;
    std::string status_; //"A Fazer", "Fazendo" ou "Feito"
    std::vector<std::string> tags_; //lista de tags associadas à tarefa
};

#endif